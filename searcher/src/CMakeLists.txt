

find_package(GTest REQUIRED)
find_package(CLI11 REQUIRED)


add_subdirectory(tokenizer)
add_subdirectory(retriever)
add_subdirectory(index)
add_subdirectory(indexer)

add_executable(searcher main.cpp)
target_link_libraries(searcher PUBLIC tokenizer retriever indexer PRIVATE CLI11::CLI11 glog::glog)
