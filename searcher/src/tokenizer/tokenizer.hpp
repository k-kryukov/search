#pragma once


#include <vector>
#include <ranges>

class Tokenizer {
    static inline std::vector<char> delms{
        ',', '.', ';', '!', '&', '*', '?'
    };

    bool isDelimeter(char c) {
        return std::isspace(c) || std::find(delms.begin(), delms.end(), c) != delms.end();
    }

public:

    std::vector<std::string> tokenize(std::string const& query) {
        std::vector<std::string> res{};

        std::string token;
        for (auto c : query) {
            if (!token.empty() && isDelimeter(c)) {
                res.push_back(std::move(token));
                token.clear();
            }
            else if (!isDelimeter(c)) {
                token.push_back(c);
            }
        }

        if (!token.empty())
            res.push_back(std::move(token));

        return res;
    }
};
