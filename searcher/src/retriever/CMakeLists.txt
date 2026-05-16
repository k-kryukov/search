

add_library(retriever retriever.cpp)
target_include_directories(retriever PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(retriever PUBLIC index PRIVATE glog::glog)
