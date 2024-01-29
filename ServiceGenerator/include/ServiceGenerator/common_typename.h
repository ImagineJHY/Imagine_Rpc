#ifndef IMAGINE_RPC_SERVICEGENERATOR_COMMON_TYPENAME_H
#define IMAGINE_RPC_SERVICEGENERATOR_COMMON_TYPENAME_H

#include "Imagine_StateMachine/StateMachine.h"
#include "Imagine_StateMachine/StateMachineState.h"

#include "Imagine_Log/Imagine_Log.h"

namespace Imagine_Rpc
{

namespace ServiceGenerator
{

#define PROTO_FILE_SUFFIX       "proto"
#define RPC_SERVICE_FILE_SUFFIX "rpc"

#define PROTOBUF_NAMESPACE_DIVIDE_SYMBOL "."

#define KEYWORD_SYNTAX      "syntax"
#define KEYWORD_PACKAGE     "package"
#define KEYWORD_MESSAGE     "message"
#define KEYWORD_RPCSERVICE  "RpcService"
#define KEYWORD_ENUM        "enum"
#define KEYWORD_IMPORT      "import"

#define KEYWORD_OPTIONAL    "optional"
#define KEYWORD_REQUIRED    "required"
#define KEYWORD_REPEATED    "repeated"

#define KEYWORD_INT32       "int32"
#define KEYWORD_SINT32      "sint32"
#define KEYWORD_UINT32      "uint32"
#define KEYWORD_INT64       "int64"
#define KEYWORD_SINT64      "sint64"
#define KEYWORD_UINT64      "uint64"
#define KEYWORD_FIXED32     "fixed32"
#define KEYWORD_FIXED64     "fixed64"
#define KEYWORD_SFIXED32    "sfixed32"
#define KEYWORD_SFIXED64    "sfixed64"
#define KEYWORD_BYTES       "bytes"
#define KEYWORD_STRING      "string"

#define KEYWORD_CHAR        "char"
#define KEYWORD_INT         "int"
#define KEYWORD_LONG        "long"
#define KEYWORD_FLOAT       "float"
#define KEYWORD_DOUBLE      "double"
#define KEYWORD_BOOL        "bool"
#define KEYWORD_CLASS       "class"
#define KEYWORD_IF          "if"
#define KEYWORD_ELSE        "else"
#define KEYWORD_FOR         "for"
#define KEYWORD_WHILE       "while"
#define KEYWORD_RETURN      "return"
#define KEYWORD_USING       "using"
#define KEYWORD_TYPENAME    "typename"
#define KEYWORD_STRUCT      "struct"
#define KEYWORD_TEMPLATE    "template"

#define ROOT_STATE_NAME                                     "RootState"
#define SYNTAX_STATE_NAME                                   "SyntaxState"
#define PACKAGE_STATE_NAME                                  "PackageState"
#define MESSAGE_STATE_NAME                                  "MessageState"
#define RPCSERVICE_STATE_NAME                               "RpcServiceState"
#define ENUM_STATE_NAME                                     "EnumState"
#define IMPORT_STATE_NAME                                   "ImportState"
#define ERROR_STATE_NAME                                    "ErrorState"
#define ENUM_FIELD_STATE_NAME                               "EnumFieldState"
#define MESSAGE_FIELD_STATE_NAME                            "MessageFieldState"
#define ENUM_NAME_PARSE_STATE_NAME                          "EnumNameParseState"
#define ENUM_PARSE_BEGIN_STATE_NAME                         "EnumParseBeginState"
#define ENUM_PARSE_END_STATE_NAME                           "EnumParseEndState"
#define MESSAGE_NAME_PARSE_STATE_NAME                       "MessageNameParseState"
#define MESSAGE_PARSE_BEGIN_STATE_NAME                      "MessageParseBeginState"
#define MESSAGE_PARSE_PRE_STATE_NAME                        "MessageParsePreState"
#define MESSAGE_PARSE_END_STATE_NAME                        "MessageParseEndState"
#define ENUM_FIELD_NAME_PARSE_STATE_NAME                    "EnumFieldNameParseState"
#define ENUM_FIELD_SYMBOL_PARSE_STATE_NAME                  "EnumFieldSymbolParseState"
#define ENUM_FIELD_VALUE_PARSE_STATE_NAME                   "EnumFieldValueParseState"
#define ENUM_FIELD_PARSE_END_STATE_NAME                     "EnumFieldParseEndState"
#define MESSAGE_FIELD_ATTRIBUTE_PARSE_STATE_NAME            "MessageFieldAttributeParseState"
#define MESSAGE_FIELD_DATATYPE_PARSE_STATE_NAME             "MessageFieldDataTypeParseState"
#define MESSAGE_FIELD_NAME_PARSE_STATE_NAME                 "MessageFieldNameParseState"
#define MESSAGE_FIELD_SYMBOL_PARSE_STATE_NAME               "MessageFieldSymbolParseState"
#define MESSAGE_FIELD_VALUE_PARSE_STATE_NAME                "MessageFieldValueParseState"
#define MESSAGE_FIELD_PARSE_END_STATE_NAME                  "MessageFieldParseEndState"
#define SYNTAX_PARSE_PREPARE_STATE_NAME                     "SyntaxParsePrepareState"
#define SYNTAX_PARSE_BEGIN_STATE_NAME                       "SyntaxParseBeginState"
#define SYNTAX_NAME_PARSE_STATE_NAME                        "SyntaxNameParseState"
#define SYNTAX_PARSE_END_STATE_NAME                         "SyntaxParseEndState"
#define PACKAGE_NAME_PARSE_STATE_NAME                       "PackageNameParseState"
#define PACKAGE_PARSE_END_STATE_NAME                        "PackageParseEndState"
#define IMPORT_PATH_PARSE_BEGIN_STATE_NAME                  "ImportPathParseBeginState"
#define IMPORT_PATH_PARSE_STATE_NAME                        "ImportPathParseState"
#define IMPORT_PATH_PARSE_END_STATE_NAME                    "ImportPathParseEndState"
#define IMPORT_PARSE_END_STATE_NAME                         "ImportParseEndState"
#define RPCSERVICE_NAME_PARSE_STATE_NAME                    "RpcServiceNameParseState"
#define RPCSERVICE_PARSE_BEGIN_STATE_NAME                   "RpcServiceParseBeginState"
#define RPCSERVICE_METHOD_STATE_NAME                        "RpcServiceMethodState"
#define RPCSERVICE_METHOD_LABEL_PARSE_STATE_NAME            "RpcServiceMethodLabelParseState"
#define RPCSERVICE_METHOD_NAME_PARSE_STATE_NAME             "RpcServiceMethodNameParseState"
#define RPCSERVICE_METHOD_TYPE_PARSE_BEGIN_STATE_NAME       "RpcServiceMethodTypeParseBeginState"
#define RPCSERVICE_METHOD_REQUEST_TYPE_PARSE_STATE_NAME     "RpcServiceMethodRequestTypeParseState"
#define RPCSERVICE_METHOD_TYPE_SEPARATOR_PARSE_STATE_NAME   "RpcServiceMethodTypeSeparatorParseState"
#define RPCSERVICE_METHOD_RESPONSE_TYPE_PARSE_STATE_NAME    "RpcServiceMethodResponseTypeParseState"
#define RPCSERVICE_METHOD_TYPE_PARSE_END_STATE_NAME         "RpcServiceMethodTypeParseEndState"
#define RPCSERVICE_METHOD_PARSE_END_STATE_NAME              "RpcServiceMethodParseEndState"
#define RPCSERVICE_PARSE_END_STATE_NAME                     "RpcServiceParseEndState"

#define CLASSIFY_TASK_EVENT_NAME        "ClassifyTask"
#define PARSE_SYNTAX_EVENT_NAME         "ParseSyntax"
#define PARSE_PACKAGE_EVETN_NAME        "ParsePackage"
#define PARSE_MESSAGE_EVENT_NAME        "ParseMessage"
#define PARSE_RPCSERVICE_EVENT_NAME     "ParseRpcService"
#define PARSE_ENUM_EVENT_NAME           "ParseEnum"
#define PARSE_IMPORT_EVENT_NAME         "ParseImport"
#define PARSE_FIELD_EVENT_NAME          "ParseField"
#define PARSE_SYMBOL_EVENT_NAME         "ParseSymbol"
#define PARSE_ERROR_EVENT_NAME          "ParseError"

#define FIELD_PARSE_COMPLETE_EVENT_NAME                         "FieldParseComplete"
#define ENUM_PARSE_COMPLETE_EVENT_NAME                          "EnumParseComplete"
#define IMPORT_PARSE_COMPLETE_EVENT_NAME                        "ImportParseComplete"
#define MESSAGE_PARSE_COMPLETE_EVENT_NAME                       "MessageParseComplete"
#define ENUM_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME       "EnumParseCompleteTransitionToRoot"
#define ENUM_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME    "EnumParseCompleteTransitionToMessage"
#define MESSAGE_PARSE_COMPLETE_TRANSITION_TO_ROOT_EVENT_NAME    "MessageParseCompleteTransitionToRoot"
#define MESSAGE_PARSE_COMPLETE_TRANSITION_TO_MESSAGE_EVENT_NAME "MessageParseCompleteTransitionToMessage"
#define PARSE_SUB_MESSAGE_EVENT_NAME                            "ParseSubMessage"
#define PARSE_SUB_ENUM_EVENT_NAME                               "ParseSubEnum"
#define SYNTAX_PARSE_COMPLETE_EVENT_NAME                        "SyntaxParseComplete"
#define PACKAGE_PARSE_COMPLETE_EVENT_NAME                       "PackageParseComplete"
#define RPCSERVICE_METHOD_PARSE_COMPLETE_EVENT_NAME             "RpcServiceMethodParseComplete"
#define RPCSERVICE_PARSE_COMPLETE_EVENT_NAME                    "RpcServiceParseComplete"
#define IMPORT_PATH_PARSE_COMPLETE_EVENT_NAME                   "ImportPathParseComplete"

using StateMachine          = ::Imagine_Tool::Imagine_StateMachine::StateMachine;
using StateMachineState     = ::Imagine_Tool::Imagine_StateMachine::StateMachineState;
using StateMachineEvent     = ::Imagine_Tool::Imagine_StateMachine::StateMachineEvent;
using Logger                = ::Imagine_Tool::Imagine_Log::Logger;
using SingletonLogger       = ::Imagine_Tool::Imagine_Log::SingletonLogger;
using NonSingletonLogger    = ::Imagine_Tool::Imagine_Log::NonSingletonLogger;

#define PROTOBUF_CODE_GENERATE_COMMAND(CXX_OUTPUT_PATH, PROTO_FILE_PATH, PROTO_FILE_NAME) "protoc --cpp_out=" + CXX_OUTPUT_PATH + " --proto_path=" + PROTO_FILE_PATH + " " + PROTO_FILE_PATH + "/" + PROTO_FILE_NAME
#define INCLUDE_GENERATOR(INCLUDE_FILE_NAME) "#include \"" + INCLUDE_FILE_NAME + "\"\n"
#define NAMESPACE_TITLE_GENERATOR(NAMESPACE_NAME) "namespace " + NAMESPACE_NAME + "\n"
#define NAMESPACE_LEFT_BRACKET_GENERATOR(NAMESPACE_NAME) "{\n\n"
#define NAMESPACE_RIGHT_BRACKET_GENERATOR(NAMESPACE_NAME) "} // namespace " + NAMESPACE_NAME + "\n\n"
#define NEW_LINE "\n"
#define FUNCTION_STRING_GENERATOR(RETURN_TYPE, FUNCTION_NAME, ARGS...) std::string() + RETURN_TYPE + " " + FUNCTION_NAME + "(" + ARGS + ")"
#define CONSTRUCTOR_FUNCTION_DECLARATION_STRING_GENERATOR(FUNCTION_NAME) FUNCTION_STRING_GENERATOR("", FUNCTION_NAME) + ";\n\n"
#define CONSTRUCTOR_FUNCTION_DEFINITION_STRING_GENERATOR(FUNCTION_NAME, SERVICE_NAME) FUNCTION_STRING_GENERATOR("", FUNCTION_NAME + "::" + FUNCTION_NAME) + ": ::Imagine_Rpc::Service(\"" + SERVICE_NAME + "\")\n" \
                                                                                                                + "{\n" \
                                                                                                                + "\tInit();\n" \
                                                                                                                + "}\n\n"
#define DESTRUCTOR_FUNCTION_DECLARATION_STRING_GENERATOR(FUNCTION_NAME) FUNCTION_STRING_GENERATOR("", "~" + FUNCTION_NAME) + ";\n\n"
#define DESTRUCTOR_FUNCTION_DEFINITION_STRING_GENERATOR(FUNCTION_NAME) FUNCTION_STRING_GENERATOR("", FUNCTION_NAME + "::~" + FUNCTION_NAME) \
                                                                                                + "{\n" \
                                                                                                + "}\n\n"
#define INIT_FUNCTION_STRING_GENERATOR(GENERATOR_PTR, SERVICE_IT, SM_PTR) \
    CODE_GENERATE(GENERATOR_PTR, FUNCTION_STRING_GENERATOR("void", SERVICE_IT->first + "::Init") + "\n"); \
    CODE_GENERATE(GENERATOR_PTR, "{\n"); \
    for (auto method_it = SERVICE_IT->second.begin(); method_it != SERVICE_IT->second.end(); method_it++) { \
        std::string request_msg_type = ConvertFormatFromProtoToCXX(SM_PTR->GetCompleteCustomKeyWordsName(method_it->second.first)); \
        std::string response_msg_type = ConvertFormatFromProtoToCXX(SM_PTR->GetCompleteCustomKeyWordsName(method_it->second.second)); \
        CODE_GENERATE(GENERATOR_PTR, "\tREGISTER_MEMBER_FUNCTION(\"" + method_it->first + "\", " + request_msg_type + ", " + response_msg_type + ", &" + SERVICE_IT->first + "::" + method_it->first + ");\n"); \
    } \
    CODE_GENERATE(GENERATOR_PTR, "}\n\n");
#define SERVICE_METHOD_FUNCTION_STRING_GENERATOR(GENERATOR_PTR, SERVICE_NAME, METHOD_NAME, REQUEST_MSG_TYPE, RESPONSE_MSG_TYPE) \
    CODE_GENERATE(GENERATOR_PTR, FUNCTION_STRING_GENERATOR("::Imagine_Rpc::Status", SERVICE_NAME + "::" + METHOD_NAME, "::Imagine_Rpc::Context* context", REQUEST_MSG_TYPE + "* request_msg", RESPONSE_MSG_TYPE + "* response_msg")); \
    CODE_GENERATE(GENERATOR_PTR, "{\n"); \
    CODE_GENERATE(GENERATOR_PTR, "\t// Write Your Code Here :\n"); \
    CODE_GENERATE(GENERATOR_PTR, "}\n\n");
#define TOSTRING(ARG) #ARG
#define CODE_GENERATE(STUB, CONTENT) STUB->InputData(CONTENT)

// #define ARG_COUNT(ARGS...) ARG_COUNT_(ARGS)
// #define ARG_COUNT_(ARGS...) INTERNAL_ARG_COUNT(0, ##ARGS, 2, ERROR, 2, ERROR, 2, ERROR, 2, ERROR, 2, ERROR, 2, ERROR, 2, ERROR, 2, ERROR, 0)
// #define INTERNAL_ARG_COUNT(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, COUNT, ARGS...) COUNT
// #define EXPAND_ARG_RECURSION_0(ARGS...) ""
// #define EXPAND_ARG_RECURSION_2(ARG_TYPE, ARG_NAME, ARGS...) EXPAND_ARG_RECURSION_2_(ARG_TYPE, ARG_NAME, ARGS)
// #define EXPAND_ARG_RECURSION_2_(ARG_TYPE, ARG_NAME, ARGS...) "," + ARG_TYPE + ARG_NAME + EXPAND_ARG_RECURSION_X(ARG_COUNT(ARGS))(ARGS)
// #define EXPAND_ARG_RECURSION_X(X) EXPAND_ARG_RECURSION_X_(X)
// #define EXPAND_ARG_RECURSION_X_(X) EXPAND_ARG_RECURSION_ ## X
// #define EXPAND_ARG_0(ARGS...) ""
// #define EXPAND_ARG_2(ARG_TYPE, ARG_NAME, ARGS...) EXPAND_ARG_2_(ARG_TYPE, ARG_NAME, ARGS)
// #define EXPAND_ARG_2_(ARG_TYPE, ARG_NAME, ARGS...) ARG_TYPE + ARG_NAME + EXPAND_ARG_RECURSION_X(ARG_COUNT(ARGS))(ARGS)
// #define EXPAND_ARG_ERROR(ARGS...) throw std::exception();
// #define EXPAND_ARG(ARGS...) EXPAND_ARG_(ARGS)
// #define EXPAND_ARG_X(X) EXPAND_ARG_X_(X)
// #define EXPAND_ARG_X_(X) EXPAND_ARG_ ## X
// #define EXPAND_ARG_(ARGS...) EXPAND_ARG_X(ARG_COUNT(ARGS))(ARGS)

#define COMMAND_MKDIR(DIR_NAME) "mkdir " + DIR_NAME

} // namespace ServiceGenerator

} // namespace Imagine_Rpc


#endif