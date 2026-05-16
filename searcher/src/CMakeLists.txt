

add_subdirectory(tokenizer)
add_subdirectory(retriever)
add_subdirectory(index)
add_subdirectory(indexer)

add_executable(searcher main.cpp)
target_link_libraries(searcher PUBLIC tokenizer retriever)
