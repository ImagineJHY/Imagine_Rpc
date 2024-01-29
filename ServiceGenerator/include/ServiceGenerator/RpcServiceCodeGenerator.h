#ifndef IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICECODEGENERATOR_H
#define IMAGINE_RPC_SERVICEGENERATOR_RPCSERVICECODEGENERATOR_H

#include "CodeGenerator.h"

#include <unordered_map>
#include <unordered_set>
#include <stack>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ServiceGeneratorMachine;

class RpcServiceCodeGenerator : public CodeGenerator
{
 private:
    class Generator : public CodeGenerator
    {
     public:
        Generator(const std::string& file_name) : CodeGenerator(file_name) {}

        bool Generate() override { return true; };
    };

    class NamespaceTreeNode
    {
      public:
         NamespaceTreeNode(const std::string& name) : name_(name) {}

         ~NamespaceTreeNode()
         {
            for (auto it = child_map.begin(); it != child_map.end(); it++) {
               delete it->second;
            }
         }

         void GenerateForwardDeclaration(Generator* stub)
         {
            if (name_.size() != 0) {
               stub->InputData("namespace " + name_ + "\n");
               stub->InputData("{\n\n");  
            }
            for (auto it = msg_set.begin(); it != msg_set.end(); it++) {
               stub->InputData("class " + *it + ";\n");
            }
            stub->InputData("\n");
            for (auto it = child_map.begin(); it != child_map.end(); it++) {
               it->second->GenerateForwardDeclaration(stub);
            }
            if (name_.size() != 0) {
               stub->InputData("} // namespace " + name_ + "\n\n");
            }
         }

         NamespaceTreeNode* GetChild(const std::string& child_name)
         {
            if (child_map.find(child_name) != child_map.end()) {
               return child_map.find(child_name)->second;
            } else {
               return AddChild(child_name);
            }
         }

         void AddMessage(const std::string& msg_name)
         {
            msg_set.insert(msg_name);
         }

         std::string GetName() const { return name_; }

         const std::unordered_set<std::string>& GetMessage() const { return msg_set; }
      
      private:
         NamespaceTreeNode* AddChild(const std::string& child_name)
         {
            NamespaceTreeNode* new_child = new NamespaceTreeNode(child_name);
            child_map.insert(std::make_pair(child_name, new_child));

            return new_child;
         }

      private:
         std::string name_;
         std::unordered_set<std::string> msg_set;
         std::unordered_map<std::string, NamespaceTreeNode*> child_map;
    };

 public:
    RpcServiceCodeGenerator(const std::string& file_name, const ServiceGeneratorMachine* sm);
    
    ~RpcServiceCodeGenerator();

    std::string ConvertFormatFromProtoToCXX(const std::string& proto_msg_name) const;

    void SetPackageName(const std::string& pkg_name);

    void AddImport(const std::string& import_file_name);

    void AddService(const std::string& service_name);

    void AddMethod(const std::string& service_name, const std::string& method_name, const std::string& request_msg, const std::string& response_msg);

    NamespaceTreeNode* GenerateNamespaceTree();

    void GenerateForwardDeclaration();

    void GenerateHeader();

    void GenerateSource();

    void Flush();

 public:
    bool Generate() override;

 private:
    const ServiceGeneratorMachine* sm_;
    Generator* header_generator_;
    Generator* source_generator_;
    std::string pkg_name_;
    std::unordered_set<std::string> import_file_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<std::string, std::string>>> service_;
    std::unordered_set<std::string> msg_type_;
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif