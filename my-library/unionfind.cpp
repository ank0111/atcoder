#include <bits/stdc++.h>

namespace my_lib
{
    template <typename T = long long, T ZERO = 0>
    struct UnionFind
    {
        using vi = std::vector<int>;
        using vt = std::vector<T>;
        UnionFind(int n = 0) : _p(n, -1), _w(n, ZERO) {}
        size_t root(size_t x)
        {
            if (_p[x] < 0)
                return x;
            else
            {
                int r = root(_p[x]);
                _w[x] += _w[_p[x]];
                return _p[x] = r;
            }
        }
        T weight(size_t x)
        {
            root(x);
            return _w[x];
        }
        bool same(size_t x, size_t y)
        {
            return root(x) == root(y);
        }
        bool merge(size_t x, size_t y, T w = ZERO)
        {
            w += weight(x);
            w -= weight(y);
            x = root(x);
            y = root(y);
            if (x == y)
                return false;
            if (_p[x] > _p[y])
            {
                std::swap(x, y);
                w = -w;
            }
            _p[x] += _p[y];
            _p[y] = x;
            _w[y] = w;
            return true;
        }
        size_t size(size_t x)
        {
            return -_p[root(x)];
        }

    private:
        vi _p;
        vt _w;
    };
}
