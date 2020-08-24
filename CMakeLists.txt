cmake_minimum_required(VERSION 3.17)
project(FunnyTranslate)

set(CMAKE_CXX_STANDARD 11)
set(INC_DIR /include)
set(LINK_DIR /lib)

link_directories(${LINK_DIR})
include_directories(${INC_DIR})
link_libraries(crypto-1_1-x64 ssl-1_1-x64 curl)

add_executable(FunnyTranslate main.cpp main.h Translate.cpp Translate.h curlpost.cpp curlpost.h)
target_link_libraries(FunnyTranslate crypto-1_1-x64 ssl-1_1-x64 curl)