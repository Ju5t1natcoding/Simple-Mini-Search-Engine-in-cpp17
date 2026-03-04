#pragma once
#include <string>
#include <vector>
#include <cstdint>

class KMP {
private:
    int32_t m;
    std::string pattern;
    std::vector<int32_t> lps;

    void precompute_lps() {
        if (m == 0) {
            return;
        }

        int32_t q = 0;
        lps.resize(m);
        lps[0] = 0;

        for (int32_t i = 1; i < m; ++i) {
            while (q && pattern[q] != pattern[i]) {
                q = lps[q - 1];
            }

            if (pattern[q] == pattern[i]) {
                q++;
            }

            lps[i] = q;
        }
    }

public:
    KMP(const std::string& pat) {
        pattern = pat;
        m = (int32_t)pattern.size();
        precompute_lps();
    }

    ~KMP() = default;

    std::vector<int32_t> search(const std::string& s) {
        if (m == 0) {
            return std::vector<int32_t>();
        }

        std::vector<int32_t> starting_positions;
        int32_t q = 0, n = (int32_t)s.size();

        for (int32_t i = 0; i < n; ++i) {
            while (q && pattern[q] != s[i]) {
                q = lps[q - 1];
            }

            if (pattern[q] == s[i]) {
                q++;
            }

            if (q == m) {
                q = lps[m - 1];
                starting_positions.push_back(i - m + 1);
            }
        }

        return starting_positions;
    }
};
