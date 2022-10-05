#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

namespace util
{
    template <typename... Args>
    void input(Args &&...args)
    {
        (cin >> ... >> args);
    }
    ostream &operator<<(ostream &os, const modint &x)
    {
        os << x.val();
        return os;
    }
    istream &operator>>(istream &is, modint &x)
    {
        int a;
        is >> a;
        x = a;
        return is;
    }
    template <typename T>
    void print(const vector<T> &a, string s = " ")
    {
        for (auto x : a)
            cout << x << s;
    }
    template <typename T>
    void print(const vector<T> &a, T add, string s = " ")
    {
        for (auto x : a)
            cout << x + add << s;
    }
    template <typename T>
    void print(vector<vector<T>> &a, string s = " ")
    {
        for (vector<T> &v : a)
        {
            print(v, s);
            cout << endl;
        }
    }
    template <typename T>
    void print(vector<vector<T>> &a, T add, string s = " ")
    {
        for (vector<T> &v : a)
        {
            print(v, add, s);
            cout << endl;
        }
    }
    void set_mod(int m) { modint::set_mod(m); }
    template <typename T>
    int biti(T bit, int i)
    {
        return bit >> i & 1;
    }
    unsigned long xor128()
    {
        static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
        unsigned long t = (x ^ (x << 11));
        x = y;
        y = z;
        z = w;
        return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
    }
    template <typename T = long long, typename F>
    T nibutan(T ok, T ng, F valid)
    {
        while (abs(ok - ng) > 1)
        {
            T m = (ok + ng) / 2;
            if (valid(m))
                ok = m;
            else
                ng = m;
        }
        return ok;
    }
}
