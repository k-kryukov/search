#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <cstdint>


struct Posting {
    uint64_t docId_;
    uint64_t tf_;

    // tbd: positions
};

struct TermData {
    uint64_t df_;
    double idf_;
    std::vector<Posting> postingList_;
};

/* BINARY INDEX STRUCTURE
    
    total_docs: 8 bytes
    total_terms: 8 bytes
    terms[]: term -> {
        term_size: 2 bytes
        term_data: $term_size bytes
        df: 8 bytes
        idf: 8 bytes floating point
        posting_list_count: 4 bytes 
        // fixed 1 byte size for each posting element
        posting[]: posting -> {
            tf: 4 bytes
            doc_id: 8 bytes
        }
    }

*/


class Index {
    std::unordered_map<std::string, TermData> termToDoc_;
    uint64_t totalDocs{};
    uint64_t totalTerms{};

    constexpr static auto MAX_TERM_SIZE = 256;
    char termBuffer[MAX_TERM_SIZE];

    std::vector<std::string> docs;

public:
    Index(uint64_t totalDocs, uint64_t totalTerms, std::ifstream& fin)
        : totalDocs{totalDocs}, totalTerms{totalTerms}
    {
        for (int i = 0; i < totalTerms; i++) {
            auto term = TermData{};

            uint16_t termSize = 0;
            fin.read(reinterpret_cast<char*>(&termSize), sizeof(termSize));
            if (termSize > MAX_TERM_SIZE)
                throw std::logic_error{"Found term with size exceeding max allowed"};

            fin.read(termBuffer, termSize);
            std::string termData(termBuffer, termSize);

            addTerm(termData, TermData{});
        }
    }

    Index(uint64_t totalDocs, uint64_t totalTerms, std::vector<std::string> const& plainIndex)
        : totalDocs{totalDocs}, totalTerms{totalTerms}, docs{plainIndex}
    {

    }

    void addTerm(std::string const& term, TermData const& termData) {
        termToDoc_.emplace(
            term, termData
        );
    }

    std::optional<TermData> getTermData(std::string const& term) {
        if (termToDoc_.contains(term))
            return termToDoc_[term];
        return std::nullopt;
    }

    std::string getDoc(size_t idx) {
        return docs.at(idx);
    }
};
