#include "ServiceGenerator/CodeGenerator.h"

#include "ServiceGenerator/log_macro.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

CodeGenerator::CodeGenerator() : output_file_(nullptr)
{
}

CodeGenerator::CodeGenerator(const std::string& file_name) : file_name_(file_name)
{
    output_file_ = new std::ofstream(file_name_);
    if (!output_file_->is_open()) {
        throw std::exception();
    }
}

CodeGenerator::~CodeGenerator()
{
    if (output_file_ != nullptr) {
        output_file_->close();
        IMAGINE_RPC_SERVICEGENERATOR_LOG_INFO("close output file!\n");
        delete output_file_;
    }
}

std::string CodeGenerator::GetName() const
{
    return file_name_;
}

void CodeGenerator::InputData(const std::string& data)
{
    *output_file_ << data;
    // output_file_->write(data.c_str(), data.size());
}

void CodeGenerator::Flush()
{
    output_file_->flush();
}

bool CodeGenerator::DeleteFile()
{
    if (output_file_ != nullptr) {
        output_file_->close();
    } else {
        throw std::exception();

        return false;
    }

    if (remove(file_name_.c_str()) == 0) {
        delete output_file_;
        file_name_ = "";
        output_file_ = nullptr;
        return true;
    } else {
        throw std::exception();
    }

    return false;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
