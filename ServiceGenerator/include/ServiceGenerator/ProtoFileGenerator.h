#ifndef IMAGINE_RPC_SERVICEGENERATOR_PROTOFILEGENERATOR_H
#define IMAGINE_RPC_SERVICEGENERATOR_PROTOFILEGENERATOR_H

#include "CodeGenerator.h"
#include "common_typename.h"

#include <unordered_set>
#include <unordered_map>
#include <queue>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ProtoFileGenerator : public CodeGenerator
{
 public:
    class Enum
    {
     public:
        Enum(const std::string& enum_name) : enum_name_(enum_name) {}

        Enum* AddField(const std::string& field_name, const std::string& field_value)
        {
            if (fields_.size() == 0 && field_value != "0") {
                // enum的第一个值必须为0
                throw std::exception();
            }
            if (fields_.find(field_name) != fields_.end() || values_.find(field_value) != values_.end()) {
               throw std::exception();
            }

            fields_.insert(std::make_pair(field_name, field_value));
            values_.insert(field_value);
            fields_vec_.push_back(field_name);

            return this;
        }

        std::string GetEnumName() const
        {
            return enum_name_;
        }

        const std::vector<std::string>& GetFields() const
        {
            return fields_vec_;
        }

        const std::unordered_map<std::string, std::string>& GetFieldsMap() const
        {
            return fields_;
        }

     private:
        std::string enum_name_;
        std::unordered_map<std::string, std::string> fields_;
        std::unordered_set<std::string> values_;
        std::vector<std::string> fields_vec_;
    };
    class Message
    {
     public:
        Message(const std::string& msg_name) : msg_name_(msg_name) {}

        Message* FindSubMessage(const std::string& msg_name) 
        {
            if (sub_msg_map_.find(msg_name) == sub_msg_map_.end()) {
                return nullptr;
            }

            return sub_msg_map_.find(msg_name)->second; 
        }

        Enum* FindSubEnum(const std::string& enum_name)
        {
            if (sub_enum_map_.find(enum_name) == sub_enum_map_.end()) {
               return nullptr;
            }

            return sub_enum_map_.find(enum_name)->second;
        }

        Message* AddSubMessage(const std::string& msg_name, Message* msg) { sub_msg_map_.insert(std::make_pair(msg_name, msg)); }

        Message* AddSubEnum(const std::string& enum_name, Enum* enum_ptr) { sub_enum_map_.insert(std::make_pair(enum_name, enum_ptr)); }

        Message* AddField(const std::string& attribute_type, const std::string& data_type, const std::string& field_name, const std::string& field_value)
        {
            if (fields_type_.find(field_name) != fields_type_.end() || fields_num_.find(field_value) != fields_num_.end()) {
               throw std::exception();
            }
            fields_type_.insert(std::make_pair(field_value, std::make_pair(attribute_type, data_type)));
            fields_num_.insert(std::make_pair(field_name, field_value));
            fields_vec_.push_back(field_name);

            return this;
        }

        std::string GetMessageName() const
        {
            return msg_name_;
        }

        const std::unordered_map<std::string, std::pair<std::string, std::string>>& GetFieldsTypeMap() const
        {
            return fields_type_;
        }

        const std::unordered_map<std::string, std::string>& GetFieldsNumMap() const
        {
            return fields_num_;
        }

        const std::unordered_map<std::string, Message*>& GetSubMessageMap() const
        {
            return sub_msg_map_;
        }

        const std::unordered_map<std::string, Enum*>& GetSubEnumMap() const
        {
            return sub_enum_map_;
        }

        const std::vector<std::string>& GetFields() const
        {
            return fields_vec_;
        }

     private:
        std::string msg_name_;
        std::unordered_map<std::string, std::pair<std::string, std::string>> fields_type_;   // value到type的映射
        std::unordered_map<std::string, std::string> fields_num_;                            // name到value的映射
        std::unordered_map<std::string, Message*> sub_msg_map_;
        std::unordered_map<std::string, Enum*> sub_enum_map_;
        std::vector<std::string> fields_vec_;
    };

 public:
    ProtoFileGenerator(const std::string& file_name);

    ~ProtoFileGenerator();

    void SetSyntax(const std::string& syntax_str);

    void SetPackageName(const std::string& pkg_name);

    Message* FindMessage(const std::string& msg_name);

    void AddImport(const std::string& import_file_name);

    void AddMessage(const std::string& msg_name);

    void AddEnum(const std::string& enum_name);

    void AddMessageField(const std::string& msg_name, const std::string& attribute, const std::string& data_type, const std::string& field_name, const std::string& field_value);

    void AddEnumField(const std::string& msg_name, const std::string& field_name, const std::string& field_value);

    void GenerateMessage(Message* msg_ptr, std::string indentation = "");

    void GenerateEnum(Enum* enum_ptr, std::string indentation = "");

 public:
    bool Generate() override;

 private:
    std::string syntax_str_;
    std::string pkg_str_;
    std::unordered_set<std::string> import_file_;
    std::unordered_map<std::string, Message*> msg_map_;
    std::unordered_map<std::string, Enum*> enum_map_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif