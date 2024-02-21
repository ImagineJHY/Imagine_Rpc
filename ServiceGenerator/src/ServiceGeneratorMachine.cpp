#include "ServiceGenerator/ServiceGeneratorMachine.h"

#include "ServiceGenerator/log_macro.h"
#include "ServiceGenerator/ProtoFileGenerator.h"
#include "ServiceGenerator/ServiceGeneratorUtil.h"
#include "ServiceGenerator/RpcServiceCodeGenerator.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ServiceGeneratorMachine::ServiceGeneratorMachine(bool generate_rpc_file) : pkg_name_(""), generate_rpc_file_(generate_rpc_file)
{
}

ServiceGeneratorMachine::ServiceGeneratorMachine(const std::string& profile_path, bool generate_rpc_file) : generate_rpc_file_(generate_rpc_file)
{
    YAML::Node config = YAML::LoadFile(profile_path);
    Init(config);
}

ServiceGeneratorMachine::ServiceGeneratorMachine(const YAML::Node& config, bool generate_rpc_file) : generate_rpc_file_(generate_rpc_file)
{
    Init(config);
}

ServiceGeneratorMachine::~ServiceGeneratorMachine()
{
    delete proto_file_stub_;
    if (generate_rpc_file_) {
        delete service_file_stub_;
    }
}

void ServiceGeneratorMachine::Init(const YAML::Node& config)
{
    service_file_ = config["service_file"].as<std::string>();
    proto_file_path_ = config["proto_file_path"].as<std::string>();
    cxx_output_path_ = config["cxx_output_path"].as<std::string>();
    if (config["singleton_log_mode"].as<bool>()) {
        logger_ = SingletonLogger::GetInstance();
    } else {
        logger_ = new NonSingletonLogger();
        Logger::SetInstance(logger_);
    }
    logger_->Init(config);
    Init();
}

void ServiceGeneratorMachine::Init()
{
    pkg_name_ = "";
    if (service_file_.find_last_of('/') != std::string::npos) {
        service_file_path_ = service_file_.substr(0, service_file_.find_last_of('/'));
        service_file_ = service_file_.substr(service_file_.find_last_of('/') + 1, service_file_.size() - service_file_.find_last_of('/') - 1);
    } else {
        service_file_path_ = ".";
    }
    std::string file_name = ServiceGeneratorUtil::RemoveFileNameSuffix(service_file_, RPC_SERVICE_FILE_SUFFIX);
    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("service file is %s\n", service_file_.c_str());
    proto_file_ = ServiceGeneratorUtil::AddSuffixToFileName(file_name, PROTO_FILE_SUFFIX);
    printf("file name is %s\n", file_name.c_str());
    std::string command = COMMAND_MKDIR(proto_file_path_);
    std::system(command.c_str());
    proto_file_stub_ = new ProtoFileGenerator(ServiceGeneratorUtil::ConnectPath(proto_file_path_, proto_file_));
    if (generate_rpc_file_) {
        command = COMMAND_MKDIR(cxx_output_path_);
        std::system(command.c_str());
        service_file_stub_ = new RpcServiceCodeGenerator((ServiceGeneratorUtil::ConnectPath(cxx_output_path_, ServiceGeneratorUtil::AddSuffixToFileName(file_name, RPC_SERVICE_FILE_SUFFIX))), this);
    }
}

void ServiceGeneratorMachine::ParseRpcServiceFile()
{
    std::ifstream input_file(ServiceGeneratorUtil::ConnectPath(service_file_path_, service_file_));
    if (!input_file.is_open()) {
        IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Error occur while open file %s!\n", service_file_.c_str());
        throw std::exception();
    }
    std::string line_content;
    while (getline(input_file, line_content)) {
        IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Get Line : %s\n", line_content.c_str());
        size_t idx = 0;
        for (size_t i = idx; i < line_content.size(); i++) {
            if (separators_.find(line_content[i]) == separators_.end()) {
                idx = i;
                if (symbols_.find(line_content[idx]) != symbols_.end()) {
                    content_ = line_content.substr(idx, 1);
                    IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Parse Symbol Event : %s\n", content_.c_str());
                    EventExecute(PARSE_SYMBOL_EVENT_NAME);
                    continue;
                }
                for (size_t j = idx; j < line_content.size(); j++) {
                    // 注释暂时手动处理
                    if (line_content[j] == '/') {
                        if (j + 1 == line_content.size()) {
                            // 不是注释, 丢给后面处理
                        } else if (line_content[j + 1] == '/') {
                            i = line_content.size() - 1;
                            break;
                        } else if (line_content[j + 1] == '*') {
                            bool in_annotation = true;
                            size_t k = j + 2;
                            while (in_annotation) {
                                for (; k < line_content.size(); k++) {
                                    if (line_content[k] == '*' && k + 1 < line_content.size() && line_content[k + 1] == '/') {
                                        in_annotation = false;
                                        idx = i = line_content.size();
                                        for (size_t x = k + 2; x < line_content.size(); x++) {
                                            if (separators_.find(line_content[x]) == separators_.end()) {
                                                idx = i = x;
                                                break;
                                            }
                                        }
                                        j = idx;
                                        break;
                                    }
                                }
                                if (!in_annotation) {
                                    break;
                                }
                                if (!getline(input_file, line_content)) {
                                    throw std::exception();
                                }
                                k = 0;
                            }
                            if (idx == line_content.size()) {
                                break;
                            }
                        } else {
                            // 不是注释, 丢给后面处理
                        }
                    }

                    if (!(('a' <= line_content[j] && line_content[j] <= 'z') || ('A' <= line_content[j] && line_content[j] <= 'Z') || ('0' <= line_content[j] && line_content[j] <= '9') ||
                        (separators_.find(line_content[j]) != separators_.end()) || (symbols_.find(line_content[j]) != symbols_.end()) || (line_content.substr(j ,1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) || (line_content[j] == '_') || (line_content[j] == '-') || (line_content[j] == '/'))) {
                            throw std::exception();
                        }
                    if ((separators_.find(line_content[j]) != separators_.end()) || (symbols_.find(line_content[j]) != symbols_.end()) || (j + 2 < line_content.size() && line_content[j + 1] == '/' && (line_content[j + 2] == '/' || line_content[j + 2] == '*'))) {
                        content_ = line_content.substr(idx, j - idx);
                        if (parse_task_classify_keywords_.find(content_) != parse_task_classify_keywords_.end()) {
                            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Classify Task Event : %s\n", content_.c_str());
                            EventExecute(CLASSIFY_TASK_EVENT_NAME);
                        } else {
                            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Parse Field Event : %s\n", content_.c_str());
                            EventExecute(PARSE_FIELD_EVENT_NAME);
                        }
                        i = j - 1;
                        break;
                    } else if (j + 1 == line_content.size()) {
                        content_ = line_content.substr(idx, line_content.size() - idx);
                        if (parse_task_classify_keywords_.find(content_) != parse_task_classify_keywords_.end()) {
                            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Classify Task Event : %s\n", content_.c_str());
                            EventExecute(CLASSIFY_TASK_EVENT_NAME);
                        } else {
                            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Parse Field Event : %s\n", content_.c_str());
                            EventExecute(PARSE_FIELD_EVENT_NAME);
                        }
                        i = j;
                    }
                }
            }
        }
    }
    std::unordered_map<std::string, bool> custom_keywords_bak;
    for (auto it = custom_keywords_.begin(); it != custom_keywords_.end(); it++) {
        std::string complete_keyword = (it->first.substr(0, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) ? it->first : ((pkg_name_.size() ? PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name_ : "") + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + it->first);
        if (custom_keywords_bak.find(complete_keyword) == custom_keywords_bak.end()) {
            custom_keywords_bak.insert(std::make_pair(complete_keyword, it->second));
            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("%s\n", complete_keyword.c_str());
        } else {
            throw std::exception();
        }
    }
    custom_keywords_ = custom_keywords_bak;
    for (auto it = undefined_keywords_.begin(); it != undefined_keywords_.end(); it++) {
        for (auto undefined_keyword_it = it->second.begin(); undefined_keyword_it != it->second.end(); undefined_keyword_it++) {
            std::string undefined_keyword = *undefined_keyword_it;
            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("%s:%s\n", it->first.c_str(), undefined_keyword.c_str());
            std::string temp_content = (pkg_name_.size() ? PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name_ : "") + (it->first.size() ? PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + it->first : "");
            if (it->second.size() == 0) {
                throw std::exception();
            }
            if (IsIndirectImportCustomKeyWord(undefined_keyword)) {
                // 必然是完整名称(以.开头), 并且在subsubFile中有同名message, 不允许
                throw std::exception();
            }
            if (undefined_keyword.substr(0, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
                // 必然是完整名称
                if (IsCustomKeyWord(undefined_keyword)) {
                    // 已经排除subsubFile, 故名称必合法
                    continue;
                } else {
                    // 没有该类型的完整名称, 必然不合法
                    throw std::exception();
                }
            }
            if ((undefined_keyword.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) != std::string::npos && IsCustomKeyWord(temp_content + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword.substr(0, undefined_keyword.find('.')))) ||
                (undefined_keyword.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) == std::string::npos && IsCustomKeyWord(temp_content + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword))) {
                // field开头的名字是父message的submessage, 则只能对submessage进行匹配, 不再考虑正交的message(包括当父message的名字和submessage的名字相同)
                if (!IsCustomKeyWord(temp_content + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword)) {
                    throw std::exception();
                } else {
                    continue;
                }
            }
            if (IsCustomKeyWord(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword) && !IsIndirectImportCustomKeyWord("." + undefined_keyword)) {
                // 以packageName开头的名称, 加上.恢复全称
                continue;
            }
            if (IsCustomKeyWord(temp_content + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword)) {
                continue;
            }
            bool flag = false;
            for (size_t i = temp_content.size() - 1; i >= 1; i--) {
                if (temp_content.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
                    if (IsCustomKeyWord(temp_content.substr(0, i) + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + undefined_keyword)) {
                        flag = true;
                        break;
                    }
                }
            }
            if (!flag) {
                throw std::exception();
            }
        }
    }
    for (auto pkg_it = package_set_.begin(); pkg_it != package_set_.end(); pkg_it++) {
        if (IsCustomKeyWord(*pkg_it)) {
            throw std::exception();
        }
    }
    proto_file_stub_->Generate();
    proto_file_stub_->Flush();
    if (generate_rpc_file_) {
        if (service_file_stub_->Generate()) {
            service_file_stub_->Flush();
        }
        std::string command = PROTOBUF_CODE_GENERATE_COMMAND(cxx_output_path_, proto_file_path_, proto_file_);
        printf("%s\n", command.c_str());
        if (std::system(command.c_str()) >= 0) {
            IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("Generate C++ Head/Source File of Proto Successfully!\n");
        } else {
            throw std::exception();
        }
    }
}

void ServiceGeneratorMachine::ParseRpcServiceFile(const std::string& service_file)
{
    service_file_ = service_file;
    Init();
    ParseRpcServiceFile();
}

std::string ServiceGeneratorMachine::GetContent() const
{
    return content_;
}

bool ServiceGeneratorMachine::IsAttributeKeyWord(const std::string& unchecked_str) const
{
    if (protobuf_data_attribute_keywords_.find(unchecked_str) != protobuf_data_attribute_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsProtobufDataTypeKeyWord(const std::string& unchecked_str) const
{
    if (protobuf_data_type_keywords_.find(unchecked_str) != protobuf_data_type_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsCustomKeyWord(const std::string& unchecked_str) const
{
    if (custom_keywords_.find(unchecked_str) != custom_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsImportAlready(const std::string& import_file_path) const
{
    if (direct_import_custom_keywords_.find(import_file_path) != direct_import_custom_keywords_.end() ||
        indirect_import_custom_keywords_.find(import_file_path) != indirect_import_custom_keywords_.end()) {
            return true;
        }
    
    return false;
}

bool ServiceGeneratorMachine::IsImportCustomKeyWord(const std::string& unchecked_str) const
{
    return IsDirectImportCustomKeyWord(unchecked_str) || IsIndirectImportCustomKeyWord(unchecked_str);
}


bool ServiceGeneratorMachine::IsDirectImportCustomKeyWord(const std::string& unchecked_str) const
{
    if (direct_import_custom_keywords_.find(unchecked_str) != direct_import_custom_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsIndirectImportCustomKeyWord(const std::string& unchecked_str) const
{
    if (indirect_import_custom_keywords_.find(unchecked_str) != indirect_import_custom_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsCXXKeyWord(const std::string& unchecked_str) const
{
    if (cxx_keywords_.find(unchecked_str) != cxx_keywords_.end()) {
        return true;
    }

    return false;
}

bool ServiceGeneratorMachine::IsKeyWord(const std::string& unchecked_str) const
{
    if ((parse_task_classify_keywords_.find(unchecked_str) != parse_task_classify_keywords_.end()) ||
        (protobuf_data_attribute_keywords_.find(unchecked_str) != protobuf_data_attribute_keywords_.end()) ||
        (protobuf_data_type_keywords_.find(unchecked_str) != protobuf_data_type_keywords_.end()) ||
        (cxx_keywords_.find(unchecked_str) != cxx_keywords_.end()) ||
        (custom_keywords_.find(unchecked_str) != custom_keywords_.end()) ||
        (custom_field_.find(unchecked_str) != custom_field_.end())) {
            return true;
        }
    
    return false;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddCustomMessageKeyWord(const std::string& new_keyword)
{
    proto_file_stub_->AddMessage(new_keyword);

    return AddCustomKeyWord(new_keyword);
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddCustomEnumKeyWord(const std::string& new_keyword)
{
    proto_file_stub_->AddEnum(new_keyword);

    return AddCustomKeyWord(new_keyword);
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddCustomKeyWord(const std::string& new_keyword, bool not_from_import)
{
    custom_keywords_.insert(std::make_pair(new_keyword, not_from_import));

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddDirectImportCustomKeyWord(const std::string& import_file_path, const std::unordered_set<std::string>& keywords)
{
    direct_import_custom_keywords_.insert(std::make_pair(import_file_path, keywords));

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddIndirectImportCustomKeyWord(const std::string& import_file_path, const std::unordered_set<std::string>& keywords)
{
    indirect_import_custom_keywords_.insert(std::make_pair(import_file_path, keywords));

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddImportPackage(const std::string pkg_name)
{
    if (package_set_.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name) == package_set_.end()) {
        package_set_.insert(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name);
    }

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddCustomField(const std::string& new_field)
{
    custom_field_.insert(new_field);

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddUndefinedKeyWord(const std::string& new_keyword_pre, const std::string& new_keyword)
{
    if (undefined_keywords_.find(new_keyword_pre) == undefined_keywords_.end()) {
        undefined_keywords_.insert(std::make_pair(new_keyword_pre, std::unordered_set<std::string>{new_keyword}));

        return this;
    }
    if (undefined_keywords_.find(new_keyword_pre)->second.find(new_keyword) == undefined_keywords_.find(new_keyword_pre)->second.end()) {
        undefined_keywords_.find(new_keyword_pre)->second.insert(new_keyword);
    }

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddImport(const std::string& import_file_name)
{
    std::string import_file = ServiceGeneratorUtil::RemoveFileNameSuffix(import_file_name, RPC_SERVICE_FILE_SUFFIX);
    std::string proto_file_name = import_file + "." + PROTO_FILE_SUFFIX;
    printf("import file is %s\n", import_file.c_str());
    proto_file_stub_->AddImport(proto_file_name);
    if (generate_rpc_file_) {
        service_file_stub_->AddImport(import_file);
    }

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddMessageField(const std::string& msg_name, const std::string& attribute_type, const std::string& data_type, const std::string& field_name, const std::string& field_value)
{
    proto_file_stub_->AddMessageField(msg_name, attribute_type, data_type, field_name, field_value);

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddEnumField(const std::string& enum_name, const std::string& field_name, const std::string& field_value)
{
    proto_file_stub_->AddEnumField(enum_name, field_name, field_value);

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddService(const std::string& service_name)
{
    if (generate_rpc_file_) {
        service_file_stub_->AddService(service_name);
    }

    return this;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::AddMethod(const std::string& service_name, const std::string& method_name, const std::string& request_msg, const std::string& response_msg)
{
    if (generate_rpc_file_) {
        service_file_stub_->AddMethod(service_name, method_name, request_msg, response_msg);
    }
}

void ServiceGeneratorMachine::SetSyntax(const std::string& syntax_str)
{
    proto_file_stub_->SetSyntax(syntax_str);
}

void ServiceGeneratorMachine::SetPackageName(const std::string& pkg_name)
{
    if (pkg_name_.size() != 0) {
        throw std::exception(); // package唯一
    }
    pkg_name_ = pkg_name;
    if (package_set_.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name) == package_set_.end()) {
        package_set_.insert(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + pkg_name);
    }
    proto_file_stub_->SetPackageName(pkg_name_);
    if (generate_rpc_file_) {
        service_file_stub_->SetPackageName(pkg_name_);
    }
}

std::string ServiceGeneratorMachine::GetPackageName() const
{
    return pkg_name_;
}

const std::unordered_map<std::string, bool>& ServiceGeneratorMachine::GetCustomKeyWords() const
{
    return custom_keywords_;
}

const std::unordered_map<std::string, std::unordered_set<std::string>>& ServiceGeneratorMachine::GetDirectImportCustomKeyWords() const
{
    return direct_import_custom_keywords_;
}

const std::unordered_map<std::string, std::unordered_set<std::string>>& ServiceGeneratorMachine::GetIndirectImportCustomKeyWords() const
{
    return indirect_import_custom_keywords_;
}

const std::unordered_set<std::string>& ServiceGeneratorMachine::GetPackageSet() const
{
    return package_set_;
}

std::string ServiceGeneratorMachine::GetServiceFile() const
{
    return service_file_;
}

// 用于RpcService查找message全称, RpcService中message要么是message全称(同一文件下), 要么是namespace + message全称, 要么是.namespace + message全称
std::string ServiceGeneratorMachine::GetCompleteCustomKeyWordsName(const std::string& str) const
{
    if (str.size() == 0) {
        throw std::exception();
    }
    if (custom_keywords_.find(ServiceGeneratorUtil::ConnectPackageNameAndMessageName(pkg_name_, str)) != custom_keywords_.end()) {
        // message全称的情况(先与本文件匹配)
        std::string temp_msg_name = str;
        for (size_t i = 0; i < temp_msg_name.size(); i++) {
            if (temp_msg_name.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
                temp_msg_name[i] = '_';
            }
        }

        return ServiceGeneratorUtil::ConnectPackageNameAndMessageName(pkg_name_, temp_msg_name);
    }
    std::string temp_str = str;
    if (temp_str.substr(0, 1) != PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
        temp_str = PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + temp_str;
    }
    if (!IsCustomKeyWord(temp_str) || IsIndirectImportCustomKeyWord(temp_str)) {
        throw std::exception();
    }
    for (size_t i = temp_str.size() - 1; i > 0; i--) {
        if (temp_str.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
            if (package_set_.find(temp_str.substr(0, i)) != package_set_.end()) {
                return temp_str;
            }
            temp_str[i] = '_';
        }
    }
    // 没有namespace
    return temp_str;
}

std::string ServiceGeneratorMachine::GetServiceFilePath() const
{
    return service_file_path_;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::SetProtoFileOutputPath(const std::string& proto_file_output_path)
{
    proto_file_path_ = proto_file_output_path;

    return this;
}

std::string ServiceGeneratorMachine::GetProtoFileOutputPath() const
{
    return proto_file_path_;
}

ServiceGeneratorMachine* ServiceGeneratorMachine::SetCXXFileOutputPath(const std::string& cxx_file_output_path)
{
    cxx_output_path_ = cxx_file_output_path;

    return this;
}

std::string ServiceGeneratorMachine::GetCXXFileOutputPath() const
{
    return cxx_output_path_;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc