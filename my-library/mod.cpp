#include <bits/stdc++.h>

namespace my_lib
{
    struct Mod
    {
        using ll = long long;
        using vl = std::vector<ll>;
        Mod(int m) : _m(m) {}
        void set_mod(int m)
        {
            _m = m;
            _F.resize(2);
            _invF.resize(2);
            _inv.resize(2);
        }
        ll pow(ll x, ll n)
        {
            assert(n >= 0);
            if (n == 0)
                return 1;
            x %= _m;
            if (n % 2)
                return x * pow(x, n - 1) % _m;
            else
                return pow(x * x, n / 2);
        }
        ll F(size_t x)
        {
            while (_F.size() <= x)
            {
                _F.push_back(_F.size() * _F.back() % _m);
            }
            return _F[x];
        }
        ll invF(size_t x)
        {
            while (_inv.size() <= x)
            {
                _inv.push_back(_m - _inv[_m % _inv.size()] * (_m / _inv.size()) % _m);
            }
            while (_invF.size() <= x)
            {
                _invF.push_back(_inv[_invF.size()] * _invF.back() % _m);
            }
            return _invF[x];
        }
        ll P(int n, int r)
        {
            if (std::min(n, r) < 0 || n < r)
                return 0;
            return F(n) * invF(n - r) % _m;
        }
        ll C(int n, int r)
        {
            if (std::min(n, r) < 0 || n < r)
                return 0;
            return F(n) * invF(r) % _m * invF(n - r) % _m;
        }
        ll H(int n, int r) { return C(n + r - 1, r); }

    private:
        int _m;
        vl _F{1, 1}, _invF{1, 1}, _inv{0, 1};
    };
}
