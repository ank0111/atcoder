#include <bits/stdc++.h>

namespace my_lib
{
    struct RollingHash
    {
        using ull = unsigned long long;
        using vull = std::vector<ull>;
        using vvull = std::vector<vull>;
        vvull hash, power;
        const vull mod;
        RollingHash(const std::string &s, vull mod = {(int)1e9 + 7, (int)1e9 + 9}, vull base = {10007, 10009}) : hash(mod.size()), power(mod.size()), mod(mod)
        {
            assert(mod.size() == base.size());
            int n = s.size();
            for (int i = 0; i < mod.size(); i++)
            {
                hash[i].assign(n + 1, 0);
                power[i].assign(n + 1, 1);
                for (int j = 0; j < n; j++)
                {
                    power[i][j + 1] = power[i][j] * base[i] % mod[i];
                    hash[i][j + 1] = (hash[i][j] * base[i] % mod[i] + s[j]) % mod[i];
                }
            }
        }
        vull get(int l, int r)
        {
            vull res;
            for (int i = 0; i < mod.size(); i++)
            {
                res.push_back((hash[i][r] - hash[i][l] * power[i][r - l] % mod[i] + mod[i]) % mod[i]);
            }
            return res;
        }
        vull connect(const vull h1, const vull h2, const int h2len) const
        {
            vull res;
            for (int i = 0; i < mod.size(); i++)
            {
                res.push_back((h1[i] * power[i][h2len] + h2[i]) % mod[i]);
            }
            return res;
        }
    };
}
