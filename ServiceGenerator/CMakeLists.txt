cmake_minimum_required(VERSION 3.0)
project(IMAGINE_RPC_SERVICE_GENERATOR)

message("${G}[Imagine Rpc ServiceGenerator]: Starting Imagine_Rpc_ServiceGenerator lib building, lib name is ${PROJECT_NAME}...${E}")

# 设置动态库的TARGET的头文件, 源文件, 依赖
file(GLOB IMAGINE_RPC_SERVICEGENERATOR_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/ServiceGenerator.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
add_executable(imagine_rpc_service_generator ${IMAGINE_RPC_SERVICEGENERATOR_SRC_LIST})
target_include_directories(imagine_rpc_service_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${IMAGINE_TOOL_DIR}/Imagine_StateMachine/include ${IMAGINE_TOOL_DIR}/Imagine_Log/include ${IMAGINE_TOOL_DIR}/thirdparty/yaml-cpp/include)
target_link_libraries(imagine_rpc_service_generator imagine_statemachine)
add_dependencies(imagine_rpc_service_generator imagine_tool)