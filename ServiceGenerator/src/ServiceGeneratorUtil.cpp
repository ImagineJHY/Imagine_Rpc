#include "ServiceGenerator/ServiceGeneratorUtil.h"

namespace Imagine_Rpc
{
namespace ServiceGenerator
{

bool ServiceGeneratorUtil::IsValidName(const std::string& custom_name)
{
    if (custom_name.size() == 0) {
        return false;
    }
    if ('0' <= custom_name[0] && custom_name[0] <= '9') {
        return false;
    }
    for (size_t i = 0; i < custom_name.size(); i++) {
        if (('0' <= custom_name[i] && custom_name[i] <= '9') ||
            ('a' <= custom_name[i] && custom_name[i] <= 'z') ||
            ('A' <= custom_name[i] && custom_name[i] <= 'Z') ||
            (custom_name[i] == '_')) {
                continue;
            }
        
        return false;
    }

    return true;
}

std::string ServiceGeneratorUtil::GetFileNameFromFilePath(const std::string& file_path)
{
    size_t idx = file_path.find_last_of('/');
    return idx != std::string::npos ? file_path.substr(idx + 1, file_path.size() - idx - 1) : file_path;
}

std::string ServiceGeneratorUtil::RemoveFileNameSuffix(const std::string& file_name, const std::string& suffix)
{
    std::string suffix_with_point = "." + suffix;
    size_t last_suffix_idx = file_name.find_last_of(suffix_with_point);
    if (last_suffix_idx == std::string::npos) {
        return file_name;
    }
    last_suffix_idx = last_suffix_idx - suffix_with_point.size() + 1;

    return file_name.substr(0, last_suffix_idx);
}

std::string ServiceGeneratorUtil::AddSuffixToFileName(const std::string& file_name, const std::string& suffix)
{
    if (suffix.size() == 0) {
        return file_name;
    }

    return file_name + "." + suffix;
}

std::string ServiceGeneratorUtil::ConnectPath(const std::string& path_pre, const std::string& path_post)
{
    return path_pre + "/" + path_post;
}

std::string ServiceGeneratorUtil::ConnectPackageNameAndMessageName(const std::string& pkg_name, const std::string& msg_name)
{
    return PROTOBUF_NAMESPACE_DIVIDE_SYMBOL + (pkg_name.size() != 0 ? pkg_name + PROTOBUF_NAMESPACE_DIVIDE_SYMBOL : "") + msg_name;
}

} // namespace ServiceGenerator

} // namespace Imagine_Rpc
