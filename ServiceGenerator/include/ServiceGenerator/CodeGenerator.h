#ifndef IMAGINE_RPC_SERVICEGENERATOR_CODEGENERATOR_H
#define IMAGINE_RPC_SERVICEGENERATOR_CODEGENERATOR_H

#include <string>
#include <fstream>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class CodeGenerator
{
 public:
    CodeGenerator();

    CodeGenerator(const std::string& file_name);

    ~CodeGenerator();

    void InputData(const std::string& data);

    std::string GetName() const;

    virtual bool Generate() = 0;

    virtual void Flush();

    bool DeleteFile();

 private:
    std::ofstream* output_file_;
    std::string file_name_;
};


} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif