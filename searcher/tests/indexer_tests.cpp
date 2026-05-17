#include <map>

#include <gtest/gtest.h>

#include "indexer.hpp"


TEST(IndexerTest, IndexerTest) {
    Indexer indxr;
    std::vector<std::string> plainIdx{
        "мама мыла раму???", "Мама, привет", "всем привет!", "Hello!!!"
    };

    boost::locale::generator gen;
    std::locale loc=gen(""); 
    std::locale::global(loc); 
    std::cout.imbue(loc);

    auto termsData = indxr.buildIndex(plainIdx)->dumpTermsData();
    std::map termsDataSorted{termsData.begin(), termsData.end()};
    std::map<std::string, TermData> expectedTerms{
        std::make_pair("всем", TermData{.df_=1, .postingList_={Posting{2, 1}}}),
        std::make_pair("мама", TermData{.df_=2, .postingList_={Posting{0, 1}, Posting{1, 1}}}),
        std::make_pair("мыла", TermData{.df_=1, .postingList_={Posting{0, 1}}}),
        std::make_pair("привет", TermData{.df_=2, .postingList_={Posting{1, 1}, Posting{2, 1}}}),
        std::make_pair("раму", TermData{.df_=1, .postingList_={Posting{0, 1}}}),
        std::make_pair("hello", TermData{.df_=1, .postingList_={Posting{3, 1}}}),
    };

    ASSERT_EQ(termsDataSorted.size(), expectedTerms.size());

    for (auto [expectedTerm, expectedTermData] : expectedTerms) {
        auto termDataIt = termsDataSorted.find(expectedTerm);
        ASSERT_NE(termDataIt, termsDataSorted.end());

        auto termData = termDataIt->second;
        ASSERT_EQ(termData.df_, expectedTermData.df_);
        ASSERT_EQ(termData.postingList_, expectedTermData.postingList_);
    }
}
