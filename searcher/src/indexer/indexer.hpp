#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "index.hpp"
#include "tokenizer.hpp"

class Indexer {
    Tokenizer tkzr;

    static double inverseDocumentFrequency(size_t docFreq, size_t docCnt) {
        return log(1 + docCnt / docFreq);
    }

public:
    Indexer() {}

    std::shared_ptr<Index> buildIndex(std::vector<std::string> plainIndex) {
        auto docsCnt = plainIndex.size();
        size_t terms = 0;
        std::unordered_map<std::string, size_t> df;
        std::unordered_map<std::string, TermData> termsData;
        size_t docId = 0;

        for (auto doc : plainIndex) {
            auto tokens = tkzr.tokenize(doc);
            std::unordered_map<std::string, size_t> tf;

            for (auto token : tokens) {
                tf[token] += 1;
            }

            for (auto [token, freq] : tf) {
                df[token] += 1;
            
                termsData[token].postingList_.push_back(
                    Posting{docId, freq}
                );
            }

            docId++;
        }

        for (auto& [term, docFreq] : df) {
            auto& termData = termsData[term];
            termData.df_ = docFreq;
            termData.idf_ = inverseDocumentFrequency(docFreq, docsCnt);
        }

        auto index = std::make_shared<Index>(docsCnt, termsData.size(), std::move(plainIndex));
        for (auto [term, termData] : termsData) {
            index->addTerm(term, termData);
        }

        return index;
    }
};


