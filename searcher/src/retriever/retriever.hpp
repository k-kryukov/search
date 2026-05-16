#pragma once

#ifndef GLOG_USE_GLOG_EXPORT
    #define GLOG_USE_GLOG_EXPORT
#endif

#include <filesystem>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <glog/logging.h>

#include "index.hpp"
#include "document.hpp"
#include "tokenizer.hpp"


class Retriever {
    Tokenizer tkzr_;
    std::shared_ptr<Index> index_;

public:
    Retriever(std::shared_ptr<Index> index) {
        index_ = std::move(index);
    }

    auto retrieve(std::string query, size_t docCnt) {
        auto terms = tkzr_.tokenize(query);
        std::unordered_map<size_t, double> candidatesIds;
        candidatesIds.reserve(docCnt);

        for (auto term : terms) {
            DLOG(INFO) << "Processing term " << term << std::endl;
            index_->getTermData(term).and_then([&candidatesIds] (TermData termData) -> std::optional<TermData> {
                auto idf = termData.idf_;

                for (auto posting : termData.postingList_) {
                    DLOG(INFO) << "adding up " << posting.tf_ * idf << std::endl;
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

        std::sort(res.begin(), res.end(), [] (auto x, auto y) { return x > y; });
        if (res.size() > docCnt)
            res.resize(docCnt);

        return res;
    }
};
