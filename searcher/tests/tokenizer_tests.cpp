#include <gtest/gtest.h>

#include <tokenizer.hpp>


struct TestCase {
    std::string query;
    std::vector<std::string> expected;
};

class TokenizerTest : public testing::TestWithParam<TestCase> {};

TEST_P(TokenizerTest, TokenizerTestCode) {
    TestCase param = GetParam();
    Tokenizer tok;

    auto res = tok.tokenize(param.query);

    EXPECT_EQ(res, param.expected);
}


INSTANTIATE_TEST_SUITE_P(
    TokenizerTestMultiple, TokenizerTest,
    testing::Values(
        TestCase{"hello", std::vector<std::string>{"hello"}},
        TestCase{"hello, world!", std::vector<std::string>{"hello", "world"}},
        TestCase{"hello world", std::vector<std::string>{"hello", "world"}},
        TestCase{"hello world;have a good day!!!", std::vector<std::string>{"hello", "world", "have", "a", "good", "day"}}
    )
);
