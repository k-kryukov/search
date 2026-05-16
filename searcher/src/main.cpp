#include <iostream>

#include <tokenizer.hpp>
#include <retriever.hpp>
#include <indexer.hpp>

#include <CLI/CLI.hpp>
#include <glog/logging.h>

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

static std::vector<std::string> fetchPlainIndex(std::filesystem::path path) {
    std::ifstream fin(path);
    std::vector<std::string> plainIndex;
    
    std::string doc;
    while (std::getline(fin, doc)) {
        plainIndex.push_back(doc);
    }

    return plainIndex;
}


int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    // FLAGS_logtostderr = 1;

    CLI::App app{"Simple term-based search engine"};
    argv = app.ensure_utf8(argv);

    std::string indexPath;
    std::string query;
    size_t maxDocs = 5;
    app.add_option("-f,--file", indexPath, "path to file with plain index");
    app.add_option("-q,--query", query, "search query");
    app.add_option("-M,--max-docs", maxDocs, "max docs restriction");

    CLI11_PARSE(app, argc, argv);

    if (!std::filesystem::exists(indexPath)) {
        LOG(ERROR) << std::format("{}: no such file", indexPath);
        return 1;
    }

    if (query.empty()) {
        LOG(ERROR) << "query is not specified!";
        return 1;
    }

    auto plainIndex = fetchPlainIndex(indexPath);
    auto indexer = std::make_unique<Indexer>();

    auto index = indexer->buildIndex(plainIndex);
    auto retriever = std::make_unique<Retriever>(index);

    auto serp = retriever->retrieve(query, maxDocs);
    for (auto [score, id] : serp) {
        std::print("Document {}\n", index->getDoc(id));
    }

    return 0;
}
