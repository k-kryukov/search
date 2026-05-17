

add_library(tokenizer tokenizer.cpp)
target_link_libraries(tokenizer PRIVATE Boost::locale)
target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
