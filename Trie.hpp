#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Trie {
private:
    struct node {
        node* next[256] = {nullptr};
        int32_t count = 0;
        int32_t ends = 0;
    } *root;

    void dfs(node* curr, std::string& s, std::vector<std::string>& result, int32_t limit) const {
        if (!curr || (int32_t)result.size() >= limit) {
            return;
        }

        if (curr->ends > 0) {
            result.push_back(s);
        }

        for (int16_t i = 0; i < 256; ++i) {
            if (curr->next[i]) {
                s.push_back(static_cast<char>(i));
                dfs(curr->next[i], s, result, limit);
                s.pop_back();

                if ((int32_t)result.size() >= limit) {
                    return;
                }
            }
        }
    }

    void clear(node* curr) {
        if (!curr) {
            return;
        }

        for (int16_t i = 0; i < 256; ++i) {
            if (curr->next[i]) {
                clear(curr->next[i]);
            }
        }

        delete curr;
    }

public:
    Trie() {
        root = new node();
    }

    ~Trie() {
        clear(root);
    }

    void insert(const std::string& s) {
        node* curr = root;
        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                curr->next[uc] = new node();
            }

            curr = curr->next[uc];
            curr->count++;
        }

        curr->ends++;
    }

    void erase(const std::string& s) {
        node* curr = root;
        std::vector<std::pair<node*, unsigned char>> path;

        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return;
            }

            path.push_back({curr, uc});
            curr = curr->next[uc];
        }

        if (curr->ends == 0) {
            return;
        }

        curr->ends--;
        for (int32_t i = s.size() - 1; i >= 0; --i) {
            node* parent = path[i].first;
            unsigned char uc = path[i].second;
            node* child = parent->next[uc];
            child->count--;

            if (child->count == 0 && child->ends == 0) {
                delete child;
                parent->next[uc] = nullptr;
            } else {
                break;
            }
        }
    }

    bool search(const std::string& s) const {
        node* curr = root;
        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return false;
            }

            curr = curr->next[uc];
        }

        return curr->ends > 0;
    }

    bool startsWith(const std::string& prefix) const {
        node* curr = root;
        for (char c : prefix) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return false;
            }

            curr = curr->next[uc];
        }

        return true;
    }

    int32_t countWord(const std::string& s) const {
        node* curr = root;
        for (char c : s) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return 0;
            }

            curr = curr->next[uc];
        }

        return curr->ends;
    }

    int32_t countPrefix(const std::string& prefix) const {
        node* curr = root;
        for (char c : prefix) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return 0;
            }

            curr = curr->next[uc];
        }

        return curr->count;
    }

    std::vector<std::string> autocomplete(const std::string& prefix, int32_t limit = 10) const {
        node* curr = root;
        for (char c : prefix) {
            unsigned char uc = static_cast<unsigned char>(c);

            if (!curr->next[uc]) {
                return std::vector<std::string>();
            }

            curr = curr->next[uc];
        }

        std::vector<std::string> result;
        std::string s = prefix;
        dfs(curr, s, result, limit);
        return result;
    }
};
