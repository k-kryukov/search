


find_package(GTest REQUIRED)


add_executable(tokenizer_tests tokenizer_tests.cpp)
target_link_libraries(tokenizer_tests GTest::gtest_main tokenizer)

add_executable(retriever_tests retriever_tests.cpp)
target_link_libraries(retriever_tests GTest::gtest_main tokenizer retriever)

add_executable(indexer_tests indexer_tests.cpp)
target_link_libraries(indexer_tests GTest::gtest_main tokenizer retriever indexer)
