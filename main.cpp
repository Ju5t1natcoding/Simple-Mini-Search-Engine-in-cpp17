#include <iostream>
#include <string>
#include <sstream>
#include "Indexer.hpp"

void printHelp() {
    std::cout << "\nAvailable commands:\n";
    std::cout << "  load <file_path>\n";
    std::cout << "  search <word>\n";
    std::cout << "  substring <pattern>\n";
    std::cout << "  prefix <prefix>\n";
    std::cout << "  help\n";
    std::cout << "  exit\n\n";
}

int main() {
    Indexer indexer;
    std::string line;

    std::cout << "Simple Mini Search Engine\n";
    std::cout << "Type 'help' for available commands.\n";

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        }
        else if (command == "help") {
            printHelp();
        }
        else if (command == "load") {
            std::string path;
            ss >> path;

            if (path.empty()) {
                std::cout << "Usage: load <file_path>\n";
                continue;
            }

            indexer.loadFile(path);
            std::cout << "File loaded successfully.\n";
        }
        else if (command == "search") {
            std::string word;
            ss >> word;

            if (word.empty()) {
                std::cout << "Usage: search <word>\n";
                continue;
            }

            auto results = indexer.search(word);

            if (results.empty()) {
                std::cout << "No documents found.\n";
            } else {
                std::cout << "Found in documents:\n";
                for (auto doc_id : results) {
                    std::cout << "  Document " << doc_id << "\n";
                }
            }
        }
        else if (command == "substring") {
            std::string pattern;
            ss >> pattern;

            if (pattern.empty()) {
                std::cout << "Usage: substring <pattern>\n";
                continue;
            }

            auto results = indexer.searchSubstring(pattern);

            bool found = false;
            for (size_t i = 0; i < results.size(); ++i) {
                if (!results[i].empty()) {
                    found = true;
                    std::cout << "Document " << i << " positions: ";
                    for (auto pos : results[i]) {
                        std::cout << pos << " ";
                    }
                    std::cout << "\n";
                }
            }

            if (!found) {
                std::cout << "Pattern not found.\n";
            }
        }
        else if (command == "prefix") {
            std::string prefix;
            ss >> prefix;

            if (prefix.empty()) {
                std::cout << "Usage: prefix <prefix>\n";
                continue;
            }

            auto results = indexer.prefixSearch(prefix);

            if (results.empty()) {
                std::cout << "No suggestions.\n";
            } else {
                std::cout << "Suggestions:\n";
                for (const auto& word : results) {
                    std::cout << "  " << word << "\n";
                }
            }
        }
        else {
            std::cout << "Unknown command. Type 'help' for instructions.\n";
        }
    }

    std::cout << "Exiting...\n";
    return 0;
}
