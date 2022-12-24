#include <bits/stdc++.h>
#include <atcoder/all>

namespace my_lib
{
    template <typename... Args>
    void input(Args &&...args)
    {
        (std::cin >> ... >> args);
    }
    std::ostream &operator<<(std::ostream &os, const atcoder::modint &x)
    {
        os << x.val();
        return os;
    }
    std::istream &operator>>(std::istream &is, atcoder::modint &x)
    {
        int a;
        is >> a;
        x = a;
        return is;
    }
    template <typename T>
    void print(const std::vector<T> &a, std::string s = " ")
    {
        for (auto x : a)
            std::cout << x << s;
    }
    template <typename T>
    void print(const std::vector<T> &a, T add, std::string s = " ")
    {
        for (auto x : a)
            std::cout << x + add << s;
    }
    template <typename T>
    void print(std::vector<std::vector<T>> &a, std::string s = " ")
    {
        for (std::vector<T> &v : a)
        {
            print(v, s);
            std::cout << "\n";
        }
    }
    template <typename T>
    void print(std::vector<std::vector<T>> &a, T add, std::string s = " ")
    {
        for (std::vector<T> &v : a)
        {
            print(v, add, s);
            std::cout << "\n";
        }
    }
    void set_mod(int m) { atcoder::modint::set_mod(m); }
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
    T nibutan(T ok, T ng, const F &valid)
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
    template <typename T = double, typename F, typename Comp>
    T sanbutan(T l, T r, const F &f, const Comp &comp, size_t cnt = 1000)
    {
        while (cnt--)
        {
            T m1 = (l * 2 + r) / 3;
            T m2 = (l + r * 2) / 3;
            if (comp(f(m1), f(m2)))
                r = m2;
            else
                l = m1;
        }
        return l;
    }
    template <typename T, typename F, typename Comp>
    T fibotan(T l, T r, const F &f, const Comp &comp)
    {
        assert(r >= l);
        l--;
        r++;
        T d = r - l;
        std::vector<long long> fib{0, 1};
        int n = 2;
        while (fib.back() < d)
        {
            fib.push_back(fib[n - 1] + fib[n - 2]);
            n++;
        }
        T tl = l, tr = l + fib.back();
        T m1 = tr - fib[n - 2], m2 = tl + fib[n - 2];
        n--;
        auto f1 = f(m1);
        auto f2 = f(m2);
        while (m1 != m2)
        {
            if (comp(f1, f2) || m2 >= r)
            {
                tr = m2;
                m2 = m1;
                f2 = f1;
                m1 = tr - fib[n - 2];
                f1 = f(m1);
            }
            else
            {
                tl = m1;
                m1 = m2;
                f1 = f2;
                m2 = tl + fib[n - 2];
                f2 = f(m2);
            }
            n--;
        }
        return m1;
    }
}
