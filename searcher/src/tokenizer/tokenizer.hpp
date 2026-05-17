#pragma once


#include <vector>
#include <ranges>
#include <iostream>

#include <boost/locale.hpp>

class Tokenizer {
    static inline std::vector<char> delms{
        ',', '.', ';', '!', '&', '*', '?'
    };

    static bool isDelimeter(char c) {
        return std::isspace(c) || std::find(delms.begin(), delms.end(), c) != delms.end();
    }

public:
    std::vector<std::string> tokenize(std::string const& query) {
        std::vector<std::string> tokens{};

        std::string token;
        for (auto c : query) {
            if (!token.empty() && isDelimeter(c)) {
                tokens.push_back(std::move(token));
                token.clear();
            }
            else if (!isDelimeter(c)) {
                token.push_back(c);
            }
        }

        if (!token.empty())
            tokens.push_back(std::move(token));

        for (auto& token : tokens) {
            token = boost::locale::to_lower(token);
        }

        return tokens;
    }
};
