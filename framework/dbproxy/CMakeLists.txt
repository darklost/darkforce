PROJECT(gate)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6) 

file(GLOB db_head_file ./ ./*.h)

set(db_src
    ./dbproxy.cpp
)
ADD_LIBRARY(db ${db_src} ${db_head_file})