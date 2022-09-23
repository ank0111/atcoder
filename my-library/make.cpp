#include <bits/stdc++.h>
using namespace std;

namespace make
{
    template <typename T = int>
    vector<T> iota(int n, T s = 0)
    {
        vector<T> res(n);
        std::iota(res.begin(), res.end(), s);
        return res;
    }
    vector<int> index(vector<int> p)
    {
        int n = p.size();
        vector<int> r(n);
        for (int i = 0; i < n; i++)
            r[p[i]] = i;
        return r;
    }
    template <typename T>
    vector<pair<T, int>> v_i(vector<T> v)
    {
        int n = v.size();
        vector<pair<T, int>> res(n);
        for (int i = 0; i < n; i++)
            res[i] = {v[i], i};
        return res;
    }
}
