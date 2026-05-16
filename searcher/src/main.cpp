#include <iostream>

#include <tokenizer.hpp>
#include <retriever.hpp>

/*

Tasks on application start:
1) Fetch index
2) Fetch synonims file

Tasks on query handle:
1) Tokenize query
2) Stemming? Lemmatization?
3) Apply synonyms ?
4) Go through reversed index
5) Output results

*/



int main() {
    auto tokenizer = std::make_unique<Tokenizer>();

    std::string query{"Hello, world! How're you doing today?"};
    auto tokens = tokenizer->tokenize(query);

    std::cout << "Hello, world!" << std::endl;
    return 0;
}
