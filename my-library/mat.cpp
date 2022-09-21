#include <bits/stdc++.h>
using namespace std;

struct Mat : vector<vector<long long>>
{
    using ll = long long;
    using vl = vector<ll>;
    using vvl = vector<vl>;
    Mat() {}
    Mat(int r) : vvl(r) { _r = r; }
    Mat(int r, vl v) : vvl(r, v)
    {
        _r = r;
        _c = v.size();
    }
    Mat(vvl hoge) : vvl(hoge)
    {
        _r = hoge.size();
        _c = hoge[0].size();
    }
    Mat(int r, int c) : vector(r, vl(c))
    {
        _r = r, _c = c;
    }

    Mat operator=(const Mat &b)
    {
        vvl::operator=(b);
        _r = b._r;
        _c = b._c;
        return *this;
    }
    Mat operator*(const Mat &b)
    {
        assert(_c == b._r);
        Mat res(_r, b._c);
        for (int i = 0; i < _r; i++)
            for (int j = 0; j < b._c; j++)
                for (int k = 0; k < _c; k++)
                {
                    res[i][j] += (*this)[i][k] * b[k][j];
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
        Mat res(_r, _c);
        for (int i = 0; i < _r; i++)
            res[i][i] = 1;
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
    int _r, _c;
};
