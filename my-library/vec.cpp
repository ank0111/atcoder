#include <bits/stdc++.h>

namespace my_lib
{
    template <typename T = int>
    std::vector<T> mkiota(int n, T s = 0)
    {
        std::vector<T> res(n);
        std::iota(res.begin(), res.end(), s);
        return res;
    }
    std::vector<int> mkr(std::vector<int> p)
    {
        int n = p.size();
        std::vector<int> r(n);
        for (int i = 0; i < n; i++)
            r[p[i]] = i;
        return r;
    }
    template <typename T>
    std::vector<std::pair<T, int>> mkvi(std::vector<T> v)
    {
        int n = v.size();
        std::vector<std::pair<T, int>> res(n);
        for (int i = 0; i < n; i++)
            res[i] = {v[i], i};
        return res;
    }
    template <typename T>
    T vsum(const std::vector<T> &v, const T &zero = 0)
    {
        T sum = zero;
        for (const T &x : v)
            sum += x;
        return sum;
    }
    template <typename T>
    void distinct(std::vector<T> &v)
    {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    template <typename T>
    T vmax(const std::vector<T> &v) { return *max_element(v.begin(), v.end()); }
    template <typename T>
    T vmin(const std::vector<T> &v) { return *min_element(v.begin(), v.end()); }
    template <typename T>
    std::vector<T> comp(std::vector<T> &a)
    {
        std::vector<T> ret;
        std::set<T> s;
        for (const T &x : a)
            s.insert(x);
        std::map<T, int> idx;
        int i = 0;
        for (const T &x : s)
        {
            idx[x] = i;
            ret.pb(x);
            i++;
        }
        for (T &x : a)
            x = idx[x];
        return ret;
    }
    template <typename T>
    size_t argmax(std::vector<T> v)
    {
        return max_element(v.begin(), v.end()) - v.begin();
    }
    template <typename T>
    size_t argmin(std::vector<T> v)
    {
        return min_element(v.begin(), v.end()) - v.begin();
    }
}
