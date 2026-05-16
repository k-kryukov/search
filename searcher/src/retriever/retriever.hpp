#pragma once

#include <filesystem>
#include <unordered_set>
#include <fstream>
#include <iostream>

#include "index.hpp"
#include "document.hpp"
#include "tokenizer.hpp"


class Retriever {
    Tokenizer tkzr_;
    std::unique_ptr<Index> index_;

public:
    Retriever(std::unique_ptr<Index> index) {
        index_ = std::move(index);
    }

    auto retrieve(std::string query, size_t docCnt) {
        auto terms = tkzr_.tokenize(query);
        std::unordered_map<size_t, double> candidatesIds;
        candidatesIds.reserve(docCnt);

        for (auto term : terms) {
            std::cout << "Processing term " << term << std::endl;
            index_->getTermData(term).and_then([&candidatesIds] (TermData termData) -> std::optional<TermData> {
                auto idf = termData.idf_;

                for (auto posting : termData.postingList_) {
                    std::cout << "adding up " << posting.tf_ * idf << std::endl;
                    candidatesIds[posting.docId_] += posting.tf_ * idf;
                }

                return std::nullopt;
            });
        }

        std::vector<std::pair<double, size_t>> res;
        res.reserve(candidatesIds.size());
        for (auto [id, score] : candidatesIds) {
            res.push_back(
                std::make_pair(score, id)
            );
        }

        return res;
    }
};
