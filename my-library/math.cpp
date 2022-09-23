#include <bits/stdc++.h>
using namespace std;

namespace math
{
    using ll = long long;
    ll sqsum(ll a, ll b) { return a * a + b * b; }
    ll sq(ll a) { return a * a; }
    ll fact(ll n)
    {
        if (n == 1)
            return 1;
        return n * fact(n - 1);
    }
    ll com(int n, int r)
    {
        ll t = 1;
        for (ll i = 0; i < r; i++)
        {
            t *= (n - r + 1 + i);
            t /= (i + 1);
        }
        return t;
    }
    ll sqrtll(ll x)
    {
        ll r = round(sqrt((double)x));
        ll rr = r * r;
        if (rr > x)
            r--;
        return r;
    }
    template <typename T, typename U>
    bool chmax(T &a, const U &b)
    {
        if (a < b)
        {
            a = b;
            return true;
        }
        return false;
    }
    template <typename T, typename U>
    bool chmin(T &a, const U &b)
    {
        if (a > b)
        {
            a = b;
            return true;
        }
        return false;
    }
    template <typename T, typename U>
    void chgcd(T &a, const U &b) { a = gcd(a, b); }
}
