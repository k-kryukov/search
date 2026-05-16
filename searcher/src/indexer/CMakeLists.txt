

add_library(indexer indexer.cpp)
target_link_libraries(indexer PUBLIC index)
target_include_directories(indexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
