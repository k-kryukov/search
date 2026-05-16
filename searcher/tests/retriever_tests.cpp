#include <cmath>
#include <ranges>
#include <algorithm>

#include <gtest/gtest.h>

#include "retriever.hpp"

auto buildIndex() {
    std::vector<std::string> plainIndex{
        "мама мыла раму",
        "мама, ты мыла?",
        "мама привет!"
    };
    auto docCnt = plainIndex.size();
    auto termsCnt = 5;

    auto index = std::make_unique<Index>(
        docCnt, termsCnt, plainIndex
    );

    index->addTerm(
        "мама", TermData{
            3, log10(1 + 3 / 3), std::vector{
                Posting{0, 1},
                Posting{1, 1},
                Posting{2, 1},
            }
        }
    );
    index->addTerm(
        "раму", TermData{
            1, log10(1 + 3 / 1), std::vector{
                Posting{0, 1},
            }
        }
    );
    index->addTerm(
        "мыла", TermData{
            2, log10(1 + 3 / 2), std::vector{
                Posting{0, 1},
                Posting{1, 1},
            }
        }
    );
    index->addTerm(
        "привет", TermData{
            1, log10(1 + 3 / 1), std::vector{
                Posting{2, 1},
            }
        }
    );
    index->addTerm(
        "ты", TermData{
            1, log10(1 + 3 / 1), std::vector{
                Posting{1, 1},
            }
        }
    );

    return index;
}

TEST(RetrieverTest, RetrieverTest) {
    auto index = buildIndex();
    Retriever rtvr{std::move(index)};

    auto res = rtvr.retrieve("мама мыла раму?", 5);
    std::sort(res.begin(), res.end(), [] (auto x, auto y) { return x > y; } );

    std::vector<size_t> expectedOrder{};

    for (auto [score, id] : res) {
        std::cout << id  << " with score " << score << std::endl;
    }
}
