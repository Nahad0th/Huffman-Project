cmake_minimum_required(VERSION 3.7)
project(Assignment_8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES huffman.cpp trace.cpp trace.h tree.h unhuffman.cpp binary.h binary1.cpp binary2.cpp pqueue.cpp pqueue.h)
add_executable(Assignment_8 ${SOURCE_FILES})