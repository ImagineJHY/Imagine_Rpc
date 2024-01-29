#ifndef IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORUTIL_H
#define IMAGINE_RPC_SERVICEGENERATOR_SERVICEGENERATORUTIL_H

#include "common_typename.h"

#include <string>

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

class ServiceGeneratorUtil
{
 private:
    ServiceGeneratorUtil() = default;

    ~ServiceGeneratorUtil() = default;

    ServiceGeneratorUtil& operator=(const ServiceGeneratorUtil& obj) = default;

 public:
   static bool IsValidName(const std::string& custom_name);

   // ServiceGenerator内部定义所有的path都不以/结尾, 故内部也不做检查
   static std::string GetFileNameFromFilePath(const std::string& file_path);

   // suffix不指定时, 移除文件名最末尾的.及之后的内容, 若文件名没有.,返回原字符串
   // suffix指定时, 若文件名以.suffix结尾, 则返回移除该部分的字符串, 否则返回原字符串
   // 当指定suffix时, suffix不需要包含.(否则不会得到预期结果)
   static std::string RemoveFileNameSuffix(const std::string& file_name, const std::string& suffix = "");

   // suffix不需要包含.(否则不会得到预期结果)
   static std::string AddSuffixToFileName(const std::string& file_name, const std::string& suffix);

   // 将两个路径进行拼接, 一般用于相对路径的拼接
   // 这里的路径要求不以/结尾
   static std::string ConnectPath(const std::string& path_pre, const std::string& path_post);

   // package name 和 message name 都不需要以.开头或结尾
   // 返回 . + pkg_name + . + msg_name
   static std::string ConnectPackageNameAndMessageName(const std::string& pkg_name, const std::string& msg_name);
};

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif