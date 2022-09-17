#include <bits/stdc++.h>
using namespace std;

struct Mod
{
    using ll = long long;
    using vl = vector<ll>;
    Mod(int m) : _m(m) {}
    void set_mod(int m)
    {
        _m = m;
        _F.resize(1);
        _invF.resize(0);
    }
    ll pow(ll x, ll n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return 1;
        x %= _m;
        if (n % 2)
            return x * pow(x, n - 1) % _m;
        else
            return pow(x * x, n / 2);
    }
    ll F(int x)
    {
        while (_F.size() <= x)
        {
            _F.push_back(_F.size() * _F.back() % _m);
        }
        return _F[x];
    }
    ll invF(int x)
    {
        while (_invF.size() <= x)
        {
            _invF.push_back(pow(F(_invF.size()), _m - 2));
        }
        return _invF[x];
    }
    ll c(int n, int r)
    {
        if (min(n, r) < 0 || n < r)
            return 0;
        return F(n) * invF(r) % _m * invF(n - r) % _m;
    }
    ll h(int n, int r) { return c(n + r - 1, r); }

private:
    int _m;
    vl _F{1}, _invF;
};
