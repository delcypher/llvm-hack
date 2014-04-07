project(llvmhack)
cmake_minimum_required(VERSION 2.8)

# set LLVM_DIR to something like /home/dan/dev/llvm/bin/share/llvm/cmake
find_package(LLVM)

# Needed to use support library
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

add_definitions(${LLVM_DEFINITIONS})

# hack, from llvm-config excutable
add_definitions(-fPIC -fvisibility-inlines-hidden -Wall -W -Wno-unused-parameter -Wwrite-strings -Wno-missing-field-initializers -pedantic -Wno-long-long -Wno-maybe-uninitialized -Wnon-virtual-dtor -std=c++11 -ffunction-sections -fdata-sections -g  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS )


include_directories(${LLVM_INCLUDE_DIRS})
add_executable(hack main.cpp)
#target_link_libraries(hack LLVMSupport LLVMIRReader)
target_link_libraries(hack ${LLVM_AVAILABLE_LIBS})
