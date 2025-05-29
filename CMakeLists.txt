cmake_minimum_required(VERSION 3.22)
project(algorithm)

include_directories(/Users/ustcyyw/CLionProjects/algorithm/base)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 获取 SDK 路径
execute_process(
        COMMAND xcrun --show-sdk-path
        OUTPUT_VARIABLE SYSROOT
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Using SDK path: ${SYSROOT}")

# 给所有目标添加 isysroot 参数
add_compile_options(-isysroot ${SYSROOT})
add_link_options(-isysroot ${SYSROOT})

# 如果用 target 写法，建议用下面这种（CLion 最新推荐）
add_executable(luogu test/luogu.cpp)
target_compile_options(luogu PRIVATE -isysroot ${SYSROOT})
target_link_options(luogu PRIVATE -isysroot ${SYSROOT})

add_executable(solve test/solve.cpp)
target_compile_options(solve PRIVATE -isysroot ${SYSROOT})
target_link_options(solve PRIVATE -isysroot ${SYSROOT})
