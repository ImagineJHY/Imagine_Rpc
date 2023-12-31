cmake_minimum_required(VERSION 3.0)
project(IMAGINE_RPC)

message("[Imagine Rpc]: Starting Imagine_Rpc lib building, lib name is ${PROJECT_NAME}...")
if(NOT DEFINED IMAGINE_TARGET_LIB)

    message("[Imagine Rpc]: IMAGINE_TARGET_LIB Is Not Defined")
    set(IMAGINE_TARGET_LIB "Imagine_Rpc")

    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g -O0")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O0")

    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g  -std=c++11 -Wall -Werror")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Werror")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive -g -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -g -std=c++11")

    string(ASCII 27 Esc)
    set(R "${Esc}[0;31m")
    set(B "${Esc}[1;34m")
    set(E "${Esc}[m")

    set(IS_MAKE_PROJECT false)
    set(IMAGINE_SYSTEM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Imagine_System)
    set(IMAGINE_TOOL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Imagine_Tool)
    set(IMAGINE_LIB_WORKER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/Imagine_System/worker)
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
    
    if(EXISTS ${IMAGINE_TOOL_DIR}/CMakeLists.txt)
        add_subdirectory(${IMAGINE_TOOL_DIR})
        message("${B}[Imagine Rpc]: thirdparty Imagine_Tool exists, add subModule...${E}")
    else()
        message("${R}[Imagine Rpc]: thirdparty Imagine_Tool NOT exists, cin make init to init it!${E}")
    endif()
    
    if(EXISTS ${IMAGINE_SYSTEM_DIR}/CMakeLists.txt)
        add_subdirectory(${IMAGINE_SYSTEM_DIR})
        message("${B}[Imagine Rpc]: thirdparty Imagine_System exists, add subModule...${E}")
    else()
        message("${R}[Imagine Rpc]: thirdparty Imagine_System NOT exists, cin make init to init it!${E}")
    endif()
endif()

# 设置动态库的TARGET的头文件, 源文件, 依赖
file(GLOB IMAGINE_RPC_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
add_library(imagine_rpc SHARED ${IMAGINE_RPC_SRC_LIST})
target_include_directories(imagine_rpc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(imagine_rpc protobuf imagine_zookeeper)

if(TARGET imagine_zookeeper)
    target_link_libraries(imagine_rpc imagine_zookeeper)
else()
    message("${R}[Imagine Rpc]: No Target Imagine_ZooKeeper!${E}")
endif()