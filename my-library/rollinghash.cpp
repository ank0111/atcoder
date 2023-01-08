#include <bits/stdc++.h>

namespace my_lib
{
    struct RollingHash
    {
        using ull = unsigned long long;
        std::vector<ull> hash, power;
        RollingHash(const std::string &s, const ull base = 10007)
        {
            int n = s.size();
            hash.assign(n + 1, 0);
            power.assign(n + 1, 1);
            for (int i = 0; i < n; i++)
            {
                power[i + 1] = mul(power[i], base);
                hash[i + 1] = (mul(hash[i], base) + s[i]) % MOD;
            }
        }
        ull get(int l, int r)
        {
            return (hash[r] - mul(hash[l], power[r - l]) + MOD) % MOD;
        }
        ull connect(ull h1, ull h2, int h2len) const
        {
            return (mul(h1, power[h2len]) + h2) % MOD;
        }

    private:
        const ull MASK30 = (1ull << 30) - 1;
        const ull MASK31 = (1ull << 31) - 1;
        const ull MOD = (1ull << 61) - 1;
        const ull MASK61 = MOD;
        ull mul(ull a, ull b) const
        {
            ull au = a >> 31;
            ull ad = a & MASK31;
            ull bu = b >> 31;
            ull bd = b & MASK31;
            ull mid = ad * bu + au * bd;
            ull midu = mid >> 30;
            ull midd = mid & MASK30;
            return calcMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        }
        ull calcMod(ull x) const
        {
            ull xu = x >> 61;
            ull xd = x & MASK61;
            ull res = xu + xd;
            if (res >= MOD)
                res -= MOD;
            return res;
        }
    };
}
