cmake_minimum_required(VERSION 3.4.1)
project("math_work")
set(CMAKE_CXX_STANDARD 17)

#--------------------------------------------------
# 1. 编译参数
#--------------------------------------------------

# 是否生成调试文件
option(ENABLE_GENRATE_PDB "option for genrate pdb file" ON)

# 编译平台 Windows / Android
option(COMPILE_WINDOWS  "Set to switch to build windows lib"  OFF)
option(COMPILE_LINUX  "Set to switch to build android lib"  OFF)

# 是否生成 python module
option(ENABLE_LOCAL_RITM_DEBUG  "Set to switch to enable local RITM debug module" OFF)

#--------------------------------------------------
# 2. 项目编译环境配置
#--------------------------------------------------

# 检测编译平台
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "build Linux lib")
    add_definitions(-D__LINUX)
    option(COMPILE_LINUX  "Set to switch to build android lib"  ON)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "build Windows lib")
    add_definitions(-D__WINDOWS)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    option(COMPILE_WINDOWS  "Set to switch to build windows lib"  ON)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif()

# 检测 x86/x64 或是 x64 设置 PATH_SUFFIX 值为 x86 或者 x64
if(CMAKE_CL_64)
    message(STATUS "build lib with x64")
    add_definitions(-D_WIN64) 
    set(ARCH_NAME x64)
else()
    message(STATUS "build lib with x86/x64")
    add_definitions(-D_WIN32)
    set(ARCH_NAME x86)
endif()

# 生成调试文件
if(ENABLE_GENRATE_PDB)
    message(STATUS "Enable genrate pdp file ... ")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()


# 依赖库后缀
message(STATUS "Complied with ${CMAKE_BUILD_TYPE}")
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(DEBUG_LIB_POSTFIX "d")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Od -Ob0")
    add_definitions(-D__DEBUG)
else ()
    set(DEBUG_LIB_POSTFIX "")
endif()

# 初始化其他 CMake 变量值
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})   # 项目根目录绝对路径
set(THIRD_DIR ${PROJECT_ROOT_DIR}/3rdparty) # 三方库目录

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#--------------------------------------------------
# 3. 附加库目录 & 附加包含目录 & 附加依赖项
#--------------------------------------------------

## eigen3
set(EIGEN_DIR  ${THIRD_DIR}/eigen3)
include_directories ( ${EIGEN_DIR} )

#--------------------------------------------------
# 4. 设置输出路径
#--------------------------------------------------

# 设置 动态库 和 exe 输出路径
set(RELEASE_PATH    ${PROJECT_ROOT_DIR}/build/bin/${ARCH_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${RELEASE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${RELEASE_PATH})

# 设置 静态库 输出路径
set(LIB_Path        ${PROJECT_ROOT_DIR}/build/lib/bin/${ARCH_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${LIB_Path})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${LIB_Path})
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(BIN_OUT_PUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}) 
else ()
    set(BIN_OUT_PUT_PATH ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE}) 
endif()


#--------------------------------------------------
# 5. 项目编译
#--------------------------------------------------
add_subdirectory( ${PROJECT_ROOT_DIR}/test )
