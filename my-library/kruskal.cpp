#include <bits/stdc++.h>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

struct Kruskal
{
    struct Edge
    {
        long long a, b, c;
        bool operator<(Edge b)
        {
            return c < b.c;
        }
    };
    Kruskal(int n, vector<Edge> e) : _uf(n), _e(e) {}
    long long sum()
    {
        long long res = 0;
        sort(_e.begin(), _e.end());
        for (Edge t : _e)
        {
            if (_uf.same(t.a, t.b))
                continue;
            _uf.merge(t.a, t.b);
            res += t.c;
        }
        return res;
    }
    dsu uf()
    {
        return _uf;
    }
    vector<Edge> e()
    {
        return _e;
    }

private:
    vector<Edge> _e;
    dsu _uf;
};
