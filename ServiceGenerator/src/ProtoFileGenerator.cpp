#include "ServiceGenerator/ProtoFileGenerator.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

ProtoFileGenerator::ProtoFileGenerator(const std::string& file_name) : CodeGenerator(file_name)
{
}

ProtoFileGenerator::~ProtoFileGenerator()
{
    for (auto enum_it = enum_map_.begin(); enum_it != enum_map_.end(); enum_it++) {
        delete enum_it->second;
    }
    for (auto msg_it = msg_map_.begin(); msg_it != msg_map_.end(); msg_it++) {
        delete msg_it->second;
    }
}

void ProtoFileGenerator::SetSyntax(const std::string& syntax_str)
{
    syntax_str_ = syntax_str;
}

void ProtoFileGenerator::SetPackageName(const std::string& pkg_name)
{
    pkg_str_ = pkg_name;
}

ProtoFileGenerator::Message* ProtoFileGenerator::FindMessage(const std::string& msg_name)
{
    if (msg_name.size() == 0) {
        throw std::exception();
    }
    if (msg_name.substr(msg_name.size() - 1, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
        throw std::exception();
    }
    size_t idx = msg_name.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    if (idx == std::string::npos) {
        if (msg_map_.find(msg_name) != msg_map_.end()) {
            return msg_map_.find(msg_name)->second;
        } else {
            return nullptr;
        }
    }
    if (idx == 0) {
        throw std::exception();
    }
    if (msg_map_.find(msg_name.substr(0, idx)) == msg_map_.end()) {
        throw std::exception();
    }
    Message* temp_msg = msg_map_.find(msg_name.substr(0, idx))->second;
    std::string temp_msg_name = msg_name.substr(idx + 1, msg_name.size() - idx - 1);
    idx = temp_msg_name.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    while (idx != std::string::npos) {
        if (idx == 0) {
            throw std::exception();
        }
        temp_msg = temp_msg->FindSubMessage(temp_msg_name.substr(0, idx));
        if (temp_msg == nullptr) {
            throw std::exception();
        }
        temp_msg_name = temp_msg_name.substr(idx + 1, temp_msg_name.size() - idx - 1);
        idx = temp_msg_name.find(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    }

    return temp_msg->FindSubMessage(temp_msg_name);
}

void ProtoFileGenerator::AddImport(const std::string& import_file_name)
{
    import_file_.insert(import_file_name.find('/') != std::string::npos ? import_file_name.substr(import_file_name.find_last_of('/') + 1, import_file_name.size() - import_file_name.find_last_of('/') - 1) : import_file_name);
}

void ProtoFileGenerator::AddMessage(const std::string& msg_name)
{
    if (msg_name.size() == 0) {
        throw std::exception();
    }
    if (msg_name.substr(msg_name.size() - 1, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
        throw std::exception();
    }
    size_t idx = msg_name.find_last_of(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    if (idx == 0) {
        throw std::exception();
    }
    if (idx == std::string::npos) {
        msg_map_.insert(std::make_pair(msg_name, new Message(msg_name)));
        return;
    }
    Message* parent_msg = FindMessage(msg_name.substr(0, idx));
    if (parent_msg == nullptr) {
        throw std::exception();
    }
    parent_msg->AddSubMessage(msg_name.substr(idx + 1, msg_name.size() - idx - 1), new Message(msg_name.substr(idx + 1, msg_name.size() - idx - 1)));
}

void ProtoFileGenerator::AddEnum(const std::string& enum_name)
{
    if (enum_name.size() == 0) {
        throw std::exception();
    }
    if (enum_name.substr(enum_name.size() - 1, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
        throw std::exception();
    }
    size_t idx = enum_name.find_last_of(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    if (idx == 0) {
        throw std::exception();
    }
    if (idx == std::string::npos) {
        enum_map_.insert(std::make_pair(enum_name, new Enum(enum_name)));
        return;
    }
    Message* parent_msg = FindMessage(enum_name.substr(0, idx));
    if (parent_msg == nullptr) {
        throw std::exception();
    }
    parent_msg->AddSubEnum(enum_name.substr(idx + 1, enum_name.size() - idx - 1), new Enum(enum_name.substr(idx + 1, enum_name.size() - idx - 1)));
}

void ProtoFileGenerator::AddMessageField(const std::string& msg_name, const std::string& attribute_type, const std::string& data_type, const std::string& field_name, const std::string& field_value)
{
    Message* parent_msg = FindMessage(msg_name);
    if (parent_msg == nullptr || field_value[0] == '-' || field_value[0] == '0') {
        throw std::exception();
    }
    parent_msg->AddField(attribute_type, data_type, field_name, field_value);
}

void ProtoFileGenerator::AddEnumField(const std::string& enum_name, const std::string& field_name, const std::string& field_value)
{
    if (enum_name.size() == 0) {
        throw std::exception();
    }
    if (enum_name.substr(enum_name.size() - 1, 1) == PROTOBUF_NAMESPACE_DIVIDE_SYMBOL) {
        throw std::exception();
    }
    size_t idx = enum_name.find_last_of(PROTOBUF_NAMESPACE_DIVIDE_SYMBOL);
    if (idx == 0) {
        throw std::exception();
    }
    if (idx == std::string::npos) {
        auto enum_it = enum_map_.find(enum_name);
        if (enum_it == enum_map_.end()) {
            throw std::exception();
        }
        enum_it->second->AddField(field_name, field_value);
        return;
    }
    Message* parent_msg = FindMessage(enum_name.substr(0, idx));
    if (parent_msg == nullptr) {
        throw std::exception();
    }
    Enum* enum_ptr = parent_msg->FindSubEnum(enum_name.substr(idx + 1, enum_name.size() - idx - 1));
    if (enum_ptr == nullptr) {
        throw std::exception();
    }
    enum_ptr->AddField(field_name, field_value);
}

bool ProtoFileGenerator::Generate()
{
    if (syntax_str_ != "proto3" && syntax_str_ != "proto2") {
        throw std::exception();
    }
    InputData("syntax = \"" + syntax_str_ + "\";\n\n");
    for (auto import_it = import_file_.begin(); import_it != import_file_.end(); import_it++) {
        InputData("import \"" + *import_it + "\";\n");
    }
    if (import_file_.size()) {
        InputData("\n");
    }
    if (pkg_str_.size()) {
        InputData("package " + pkg_str_ + ";\n\n");
    }
    for (auto enum_it = enum_map_.begin(); enum_it != enum_map_.end(); enum_it++) {
        GenerateEnum(enum_it->second);
    }
    for (auto msg_it = msg_map_.begin(); msg_it != msg_map_.end(); msg_it++) {
        GenerateMessage(msg_it->second);
    }

    return true;
}

void ProtoFileGenerator::GenerateMessage(Message* msg_ptr, std::string indentation)
{
    auto fields_type_map = msg_ptr->GetFieldsTypeMap();
    auto fields_num_map = msg_ptr->GetFieldsNumMap();
    auto sub_msg_map_ = msg_ptr->GetSubMessageMap();
    auto sub_enum_map = msg_ptr->GetSubEnumMap();
    auto fields_vec = msg_ptr->GetFields();
    InputData(indentation + "message " + msg_ptr->GetMessageName() + " {\n");
    for (auto sub_enum_it = sub_enum_map.begin(); sub_enum_it != sub_enum_map.end(); sub_enum_it++) {
        GenerateEnum(sub_enum_it->second, indentation + "\t");
    }
    for (auto sub_msg_it = sub_msg_map_.begin(); sub_msg_it != sub_msg_map_.end(); sub_msg_it++) {
        GenerateMessage(sub_msg_it->second, indentation + "\t");
    }
    for (auto field_it = fields_vec.begin(); field_it != fields_vec.end(); field_it++) {
        std::string field_str = "";
        std::string field_value = fields_num_map.find(*field_it)->second;
        if (fields_type_map.find(field_value)->second.first.size()) {
            field_str += fields_type_map.find(field_value)->second.first + " ";
        }
        field_str += fields_type_map.find(field_value)->second.second + " " + *field_it + " = " + field_value + ";";
        InputData(indentation + "\t" + field_str + "\n");
    }
    InputData(indentation + "}\n");
}

void ProtoFileGenerator::GenerateEnum(Enum* enum_ptr, std::string indentation)
{
    auto fields_map = enum_ptr->GetFieldsMap();
    auto fields = enum_ptr->GetFields();
    InputData(indentation + "enum " + enum_ptr->GetEnumName() + " {\n");
    for (auto field_it = fields.begin(); field_it != fields.end(); field_it++) {
        InputData(indentation + "\t" + *field_it + " = " + fields_map.find(*field_it)->second + ";\n");
    }
    InputData(indentation + "}\n");
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
