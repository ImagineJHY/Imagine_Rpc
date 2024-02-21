#include "ServiceGenerator/RpcServiceCodeGenerator.h"

#include "ServiceGenerator/ServiceGeneratorUtil.h"
#include "ServiceGenerator/ServiceGeneratorMachine.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

RpcServiceCodeGenerator::RpcServiceCodeGenerator(const std::string& file_name, const ServiceGeneratorMachine* sm) : CodeGenerator(), sm_(sm), header_generator_(new RpcServiceCodeGenerator::Generator(file_name + ".h")), source_generator_(new RpcServiceCodeGenerator::Generator(file_name + ".cpp"))
{
}

RpcServiceCodeGenerator::~RpcServiceCodeGenerator()
{
    delete header_generator_;
    delete source_generator_;
}

std::string RpcServiceCodeGenerator::ConvertFormatFromProtoToCXX(const std::string& proto_msg_name) const
{
    std::string cxx_msg_name;
    for (size_t i = 0; i < proto_msg_name.size(); i++) {
        if (proto_msg_name.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
            cxx_msg_name += "::";
        } else {
            cxx_msg_name += proto_msg_name[i];
        }
    }

    return cxx_msg_name;
}

void RpcServiceCodeGenerator::SetPackageName(const std::string& pkg_name)
{
    pkg_name_ = pkg_name;
}

void RpcServiceCodeGenerator::AddImport(const std::string& import_file_name)
{
    import_file_.insert(import_file_name);
}

void RpcServiceCodeGenerator::AddService(const std::string& service_name)
{
    if (service_.find(service_name) != service_.end()) {
        throw std::exception();
    }
    std::unordered_map<std::string, std::pair<std::string, std::string>> method_map;
    service_.insert(std::make_pair(service_name, method_map));
}

void RpcServiceCodeGenerator::AddMethod(const std::string& service_name, const std::string& method_name, const std::string& request_msg, const std::string& response_msg)
{
    if (service_.find(service_name) == service_.end()) {
        throw std::exception();
    }
    auto& method_map = service_.find(service_name)->second;
    if (method_map.find(method_name) != method_map.end()) {
        throw std::exception();
    }
    method_map.insert(std::make_pair(method_name, std::make_pair(request_msg, response_msg)));
    if (msg_type_.find(request_msg) == msg_type_.end()) {
        msg_type_.insert(request_msg);
    }
    if (msg_type_.find(response_msg) == msg_type_.end()) {
        msg_type_.insert(response_msg);
    }
}

bool RpcServiceCodeGenerator::Generate()
{
    if (service_.size() == 0) {
        header_generator_->DeleteFile();
        source_generator_->DeleteFile();

        return false;
    }
    GenerateHeader();
    GenerateSource();
}

RpcServiceCodeGenerator::NamespaceTreeNode* RpcServiceCodeGenerator::GenerateNamespaceTree()
{
    NamespaceTreeNode* root_node = new NamespaceTreeNode("");
    for (auto msg_it = msg_type_.begin(); msg_it != msg_type_.end(); msg_it++) {
        std::string msg_name = sm_->GetCompleteCustomKeyWordsName(*msg_it);
        NamespaceTreeNode* temp_root_node = root_node;
        size_t idx = 1;
        for (size_t i = 1; i < msg_name.size(); i++) {
            if (msg_name.substr(i ,1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
                temp_root_node = temp_root_node->GetChild(msg_name.substr(idx, i - idx));
                idx = i + 1;
            }
        }
        temp_root_node->AddMessage(msg_name.substr(idx, msg_name.size() - idx));
    }

    return root_node;
}

void RpcServiceCodeGenerator::GenerateForwardDeclaration()
{
    NamespaceTreeNode* root_node = GenerateNamespaceTree();
    root_node->GenerateForwardDeclaration(header_generator_);
    delete root_node;
}

void RpcServiceCodeGenerator::GenerateHeader()
{
    std::string file_name = ServiceGeneratorUtil::GetFileNameFromFilePath(header_generator_->GetName());
    std::string capital_file_name = "";
    std::stack<std::string> namespace_stack;

    for (size_t i = 0; i < file_name.size(); i++) {
        if ('a' <= file_name[i] && file_name[i] <= 'z') {
            capital_file_name.push_back(file_name[i] + 'A' - 'a');
        } else if (file_name[i] == '.'){
            capital_file_name.push_back('_');
        } else {
            capital_file_name.push_back(file_name[i]);
        }
    }
    header_generator_->InputData("#ifndef " + capital_file_name + "\n");
    header_generator_->InputData("#define " + capital_file_name + "\n\n");
    header_generator_->InputData("#include \"Imagine_Rpc/Imagine_Rpc.h\"\n\n");

    GenerateForwardDeclaration();

    if (pkg_name_.size() != 0 && (pkg_name_.substr(0, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL || pkg_name_.substr(pkg_name_.size() - 1, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL)) {
        throw std::exception();
    }
    size_t idx = 0;
    for (size_t i = 0; i < pkg_name_.size(); i++) {
        if (pkg_name_.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
            if (idx == i) {
                throw std::exception();
            }
            namespace_stack.push(pkg_name_.substr(idx, i - idx));
            header_generator_->InputData("namespace " + pkg_name_.substr(idx, i - idx) + "\n");
            header_generator_->InputData("{\n\n");
            idx = i + 1;
        }
    }
    if (pkg_name_.size() != 0) {
        namespace_stack.push(pkg_name_.substr(idx, pkg_name_.size() - idx));
        header_generator_->InputData("namespace " + pkg_name_.substr(idx, pkg_name_.size() - idx) + "\n");
        header_generator_->InputData("{\n\n");
    }

    for (auto service_it = service_.begin(); service_it != service_.end(); service_it++) {
        header_generator_->InputData("class " + service_it->first + " : public ::Imagine_Rpc::Service\n");
        header_generator_->InputData("{\n");
        header_generator_->InputData(" public:\n");
        header_generator_->InputData("\t" + service_it->first + "();\n\n");
        header_generator_->InputData("\t~" + service_it->first + "();\n\n");
        header_generator_->InputData("\tvoid Init();\n");
        for (auto method_it = service_it->second.begin(); method_it != service_it->second.end(); method_it++) {
            std::string request_msg_type = ConvertFormatFromProtoToCXX(sm_->GetCompleteCustomKeyWordsName(method_it->second.first));
            std::string response_msg_type = ConvertFormatFromProtoToCXX(sm_->GetCompleteCustomKeyWordsName(method_it->second.second));
            header_generator_->InputData("\n\t::Imagine_Rpc::Status " + method_it->first + "(::Imagine_Rpc::Context* context, " + request_msg_type + "* request_msg, " + response_msg_type + "* response_msg);\n");
        }
        header_generator_->InputData("};\n\n");
    }

    while (namespace_stack.size()) {
        std::string temp_namespace = namespace_stack.top();
        namespace_stack.pop();
        header_generator_->InputData("} // namespace " + temp_namespace + "\n\n");
    }

    header_generator_->InputData("#endif");
}

void RpcServiceCodeGenerator::GenerateSource()
{
    std::string file_name = ServiceGeneratorUtil::GetFileNameFromFilePath(header_generator_->GetName());
    std::stack<std::string> namespace_stack;

    CODE_GENERATE(source_generator_, INCLUDE_GENERATOR(file_name));
    CODE_GENERATE(source_generator_, NEW_LINE);
    CODE_GENERATE(source_generator_, INCLUDE_GENERATOR(ServiceGeneratorUtil::RemoveFileNameSuffix(file_name, "rpc.h") + ".pb.h"));

    for (auto import_it = import_file_.begin(); import_it != import_file_.end(); import_it++) {
        CODE_GENERATE(source_generator_, INCLUDE_GENERATOR(ServiceGeneratorUtil::GetFileNameFromFilePath(*import_it) + ".pb.h"));
    }
    CODE_GENERATE(source_generator_, NEW_LINE);

    size_t idx = 0;
    for (size_t i = 0; i < pkg_name_.size(); i++) {
        if (pkg_name_.substr(i, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
            if (idx == i) {
                throw std::exception();
            }
            namespace_stack.push(pkg_name_.substr(idx, i - idx));
            CODE_GENERATE(source_generator_, NAMESPACE_TITLE_GENERATOR(pkg_name_.substr(idx, i - idx)));
            CODE_GENERATE(source_generator_, NAMESPACE_LEFT_BRACKET_GENERATOR(""));
            idx = i + 1;
        }
    }
    if (pkg_name_.size() != 0) {
        namespace_stack.push(pkg_name_.substr(idx, pkg_name_.size() - idx));
        CODE_GENERATE(source_generator_, NAMESPACE_TITLE_GENERATOR(pkg_name_.substr(idx, pkg_name_.size() - idx)));
        CODE_GENERATE(source_generator_, NAMESPACE_LEFT_BRACKET_GENERATOR(""));
    }

    for (auto service_it = service_.begin(); service_it != service_.end(); service_it++) {
        CODE_GENERATE(source_generator_, CONSTRUCTOR_FUNCTION_DEFINITION_STRING_GENERATOR(service_it->first, pkg_name_ + "_" + service_it->first));
        CODE_GENERATE(source_generator_, DESTRUCTOR_FUNCTION_DEFINITION_STRING_GENERATOR(service_it->first));
        INIT_FUNCTION_STRING_GENERATOR(source_generator_, service_it, sm_);
        for (auto method_it = service_it->second.begin(); method_it != service_it->second.end(); method_it++) {
            std::string request_msg_type = ConvertFormatFromProtoToCXX(sm_->GetCompleteCustomKeyWordsName(method_it->second.first));
            std::string response_msg_type = ConvertFormatFromProtoToCXX(sm_->GetCompleteCustomKeyWordsName(method_it->second.second));
            source_generator_->InputData("::Imagine_Rpc::Status " + service_it->first + "::" + method_it->first + "(::Imagine_Rpc::Context* context, " + request_msg_type + "* request_msg, " + response_msg_type + "* response_msg)\n");
            source_generator_->InputData("{\n");
            source_generator_->InputData("\t// Write Your Code Here :\n");
            source_generator_->InputData("}\n\n");
        }
    }

    while (namespace_stack.size()) {
        std::string temp_namespace = namespace_stack.top();
        namespace_stack.pop();
        CODE_GENERATE(source_generator_, NAMESPACE_RIGHT_BRACKET_GENERATOR(temp_namespace));
    }
}

void RpcServiceCodeGenerator::Flush()
{
    header_generator_->Flush();
    source_generator_->Flush();
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
