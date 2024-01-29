#ifndef IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORMACHINE_H
#define IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORMACHINE_H

#include "common_typename.h"

#include "yaml-cpp/yaml.h"

#include <fstream>
#include <unordered_set>
#include <stdlib.h>
//#include <unistd.h>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ProtoFileGenerator;
class RpcServiceCodeGenerator;

class ServiceGeneratorMachine : public StateMachine
{
 public:
    ServiceGeneratorMachine(bool generate_rpc_file = true);

    ServiceGeneratorMachine(const std::string& profile_path, bool generate_rpc_file = true);

    ServiceGeneratorMachine(const YAML::Node& config, bool generate_rpc_file = true);

    ~ServiceGeneratorMachine();

    void Init(const YAML::Node& config);

    void Init();

    void ParseRpcServiceFile();

    void ParseRpcServiceFile(const std::string& service_file);

    std::string GetContent() const;

    bool IsAttributeKeyWord(const std::string& unchecked_str) const;

    bool IsProtobufDataTypeKeyWord(const std::string& unchecked_str) const;

    bool IsCustomKeyWord(const std::string& unchecked_str) const;

    bool IsImportAlready(const std::string& import_file_path) const;

    bool IsImportCustomKeyWord(const std::string& unchecked_str) const;

    bool IsDirectImportCustomKeyWord(const std::string& unchecked_str) const;

    bool IsIndirectImportCustomKeyWord(const std::string& unchecked_str) const;

    bool IsCXXKeyWord(const std::string& unchecked_str) const;

    bool IsKeyWord(const std::string& unchecked_str) const;

    ServiceGeneratorMachine* AddCustomMessageKeyWord(const std::string& new_keyword);

    ServiceGeneratorMachine* AddCustomEnumKeyWord(const std::string& new_keyword);

    ServiceGeneratorMachine* AddCustomKeyWord(const std::string& new_keyword, bool not_from_import = true);

    ServiceGeneratorMachine* AddDirectImportCustomKeyWord(const std::string& import_file_path, const std::unordered_set<std::string>& keywords);

    ServiceGeneratorMachine* AddIndirectImportCustomKeyWord(const std::string& import_file_path, const std::unordered_set<std::string>& keywords);

    ServiceGeneratorMachine* AddImportPackage(const std::string pkg_name);

    ServiceGeneratorMachine* AddCustomField(const std::string& new_field);

    ServiceGeneratorMachine* AddUndefinedKeyWord(const std::string& new_keyword_pre, const std::string& new_keyword);

    ServiceGeneratorMachine* AddImport(const std::string& import_file_name);

    ServiceGeneratorMachine* AddMessageField(const std::string& msg_name, const std::string& attribute, const std::string& data_type, const std::string& field_name, const std::string& field_value);

    ServiceGeneratorMachine* AddEnumField(const std::string& enum_name, const std::string& field_name, const std::string& field_value);

    ServiceGeneratorMachine* AddService(const std::string& service_name);

    ServiceGeneratorMachine* AddMethod(const std::string& service_name, const std::string& method_name, const std::string& request_msg, const std::string& response_msg);

    void SetSyntax(const std::string& syntax_str);

    void SetPackageName(const std::string& pkg_name);

    std::string GetPackageName() const;

    const std::unordered_map<std::string, bool>& GetCustomKeyWords() const;

    const std::unordered_map<std::string, std::unordered_set<std::string>>& GetDirectImportCustomKeyWords() const;

    const std::unordered_map<std::string, std::unordered_set<std::string>>& GetIndirectImportCustomKeyWords() const;

    const std::unordered_set<std::string>& GetPackageSet() const;

    std::string GetServiceFile() const;

    std::string GetCompleteCustomKeyWordsName(const std::string& str) const;

    std::string GetServiceFilePath() const;

    ServiceGeneratorMachine* SetProtoFileOutputPath(const std::string& proto_file_output_path);

    std::string GetProtoFileOutputPath() const;

    ServiceGeneratorMachine* SetCXXFileOutputPath(const std::string& cxx_file_output_path);

    std::string GetCXXFileOutputPath() const;

 private:
   Logger* logger_;

 private:
    const std::unordered_set<char> symbols_{ {'{'}, {'}'},  {';'}, {'"'}, {'='}, {','}, {'<'}, {'>'} };

    const std::unordered_set<char> separators_{ {' '}, {'\t'}, {'\r'}, {'\n'} };

    const std::unordered_set<std::string> parse_task_classify_keywords_{{KEYWORD_SYNTAX}, {KEYWORD_PACKAGE}, {KEYWORD_MESSAGE}, {KEYWORD_ENUM}, {KEYWORD_IMPORT}, {KEYWORD_RPCSERVICE}};

    const std::unordered_set<std::string> protobuf_data_attribute_keywords_{{KEYWORD_OPTIONAL}, {KEYWORD_REQUIRED}, {KEYWORD_REPEATED}};

    const std::unordered_set<std::string> protobuf_data_type_keywords_{ {KEYWORD_INT32},     {KEYWORD_SINT32},    {KEYWORD_UINT32},    {KEYWORD_INT64},
                                                                        {KEYWORD_SINT64},    {KEYWORD_UINT64},    {KEYWORD_FIXED32},   {KEYWORD_FIXED64},
                                                                        {KEYWORD_SFIXED32},  {KEYWORD_SFIXED64},  {KEYWORD_BYTES},     {KEYWORD_STRING} };

    const std::unordered_set<std::string> cxx_keywords_{ {KEYWORD_CHAR},   {KEYWORD_INT},       {KEYWORD_LONG},   {KEYWORD_FLOAT}, 
                                                         {KEYWORD_DOUBLE}, {KEYWORD_BOOL},      {KEYWORD_CLASS},  {KEYWORD_IF}, 
                                                         {KEYWORD_ELSE},   {KEYWORD_FOR},       {KEYWORD_WHILE},  {KEYWORD_RETURN}, 
                                                         {KEYWORD_USING},  {KEYWORD_TYPENAME},  {KEYWORD_STRUCT}, {KEYWORD_TEMPLATE} };

 private:
    std::string service_file_;
    std::string proto_file_;
    std::string proto_file_path_;
    std::string cxx_output_path_;
    std::string service_file_path_;
    std::string content_;
    std::string pkg_name_;
    std::unordered_map<std::string, bool> custom_keywords_;
    std::unordered_set<std::string> custom_field_;
    std::unordered_map<std::string, std::unordered_set<std::string>> undefined_keywords_;
    std::unordered_map<std::string, std::unordered_set<std::string>> direct_import_custom_keywords_;
    std::unordered_map<std::string, std::unordered_set<std::string>> indirect_import_custom_keywords_;
    std::unordered_set<std::string> package_set_;

 private:
    ProtoFileGenerator* proto_file_stub_;
    RpcServiceCodeGenerator* service_file_stub_;
    bool generate_rpc_file_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif