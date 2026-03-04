#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "Trie.hpp"
#include "KMP.hpp"

class Indexer {
private:
    std::vector<std::string> documents;
    Trie dictionary;
    std::unordered_map<std::string, std::vector<int32_t>> inverted_index;

public:
    Indexer() = default;

    ~Indexer() = default;

    void loadFile(const std::string& path) {
        std::ifstream fin(path);

        if (!fin) {
            return;
        }

        std::stringstream buffer;
        buffer << fin.rdbuf();
        std::string text = buffer.str();
        int32_t doc_id = (int32_t)documents.size();
        documents.push_back(text);
        std::string word;
        std::unordered_set<std::string> unique_words_in_doc;

        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                word += c;
            } else {
                if (!word.empty()) {
                    dictionary.insert(word);
                    unique_words_in_doc.insert(word);
                    word.clear();
                }
            }
        }

        if (!word.empty()) {
            dictionary.insert(word);
            unique_words_in_doc.insert(word);
        }

        for (const auto& w : unique_words_in_doc) {
            inverted_index[w].push_back(doc_id);
        }
    }

    std::vector<int32_t> search(const std::string& word) const {
        auto it = inverted_index.find(word);

        if (it == std::end(inverted_index)) {
            return std::vector<int32_t>();
        }

        return it->second;
    }

    std::vector<std::vector<int32_t>> searchSubstring(const std::string& pattern) const {
        std::vector<std::vector<int32_t>> positions(documents.size());
        KMP kmp(pattern);

        for (int32_t i = 0; i < (int32_t)documents.size(); ++i) {
            positions[i] = kmp.search(documents[i]);
        }

        return positions;
    }

    std::vector<std::string> prefixSearch(const std::string& prefix) const {
        return dictionary.autocomplete(prefix);
    }
};
