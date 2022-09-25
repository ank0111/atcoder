#include <bits/stdc++.h>
using namespace std;

namespace vec
{
    template <typename T = int>
    vector<T> mkiota(int n, T s = 0)
    {
        vector<T> res(n);
        std::iota(res.begin(), res.end(), s);
        return res;
    }
    vector<int> mkr(vector<int> p)
    {
        int n = p.size();
        vector<int> r(n);
        for (int i = 0; i < n; i++)
            r[p[i]] = i;
        return r;
    }
    template <typename T>
    vector<pair<T, int>> mkvi(vector<T> v)
    {
        int n = v.size();
        vector<pair<T, int>> res(n);
        for (int i = 0; i < n; i++)
            res[i] = {v[i], i};
        return res;
    }
    template <typename T>
    T vsum(const vector<T> &v)
    {
        T sum = 0;
        for (const T &x : v)
            sum += x;
        return sum;
    }
    template <typename T>
    void distinct(vector<T> &v)
    {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    template <typename T>
    T vmax(const vector<T> &v) { return *max_element(v.begin(), v.end()); }
    template <typename T>
    T vmin(const vector<T> &v) { return *min_element(v.begin(), v.end()); }
    template <typename T>
    vector<T> comp(vector<T> &a)
    {
        vector<T> ret;
        set<T> s;
        for (const T &x : a)
            s.insert(x);
        map<T, int> idx;
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
}
