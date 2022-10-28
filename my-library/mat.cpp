#include <bits/stdc++.h>

namespace my_lib
{
    template <typename T = long long>
    struct Mat : std::vector<std::vector<T>>
    {
        using ll = long long;
        using vt = std::vector<T>;
        using vvt = std::vector<vt>;
        Mat() {}
        Mat(size_t r, T id = 1) : vvt(r), _r(r), _id(id) {}
        Mat(size_t r, vt v, T id = 1) : vvt(r, v), _r(r), _c(v.size()), _id(id) {}
        Mat(vvt m, T id = 1) : vvt(m), _r(m.size()), _c(m[0].size()), _id(id) {}
        Mat(size_t r, size_t c, T id = 1) : vvt(r, vt(c)), _r(r), _c(c), _id(id) {}
        Mat operator*(const Mat &b)
        {
            assert(_c == b._r);
            Mat res(_r, b._c, _id);
            for (size_t i = 0; i < _r; i++)
                for (size_t j = 0; j < b._c; j++)
                    for (size_t k = 0; k < _c; k++)
                    {
                        res[i][j] = res[i][j] + (*this)[i][k] * b[k][j];
                    }
            return res;
        }
        Mat operator*=(const Mat &b)
        {
            return *this = (*this) * b;
        }
        Mat pow(ll n)
        {
            assert(n >= 0);
            assert(_r == _c);
            Mat res(_r, _c, _id);
            for (size_t i = 0; i < _r; i++)
                res[i][i] = _id;
            Mat x = *this;
            while (n)
            {
                if (n & 1)
                {
                    res *= x;
                }
                x *= x;
                n >>= 1;
            }
            return res;
        }

    private:
        size_t _r, _c;
        T _id;
    };
}
