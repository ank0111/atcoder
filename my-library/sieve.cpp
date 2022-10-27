#include <bits/stdc++.h>

namespace my_lib
{
    struct Sieve
    {
        using ll = long long;
        using vi = std::vector<int>;
        int n;
        vi f, primes;
        Sieve(int n = 1) : n(n), f(n + 1, 1)
        {
            f[0] = f[1] = 0;
            for (ll i = 2; i <= n; ++i)
            {
                if (!f[i])
                    continue;
                primes.push_back(i);
                for (ll j = i * i; j <= n; j += i)
                {
                    f[j] = 0;
                }
            }
        }
        bool isPrime(int x)
        {
            assert(0 <= x && x <= n);
            return f[x];
        }
        template <typename T>
        std::vector<std::pair<T, int>> factor(T x)
        {
            std::vector<std::pair<T, int>>
                res;
            for (int p : primes)
            {
                if (x % p != 0)
                    continue;
                int c = 0;
                while (x % p == 0)
                    x /= p, ++c;
                res.emplace_back(p, c);
            }
            if (x != 1)
                res.emplace_back(x, 1);
            return res;
        }
    };
}
