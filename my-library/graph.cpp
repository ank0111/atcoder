#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    using vi = vector<int>;
    using vvi = vector<vi>;
    Graph(int n = 0) : _n(n), _g(n) {}
    void resize(int n)
    {
        _n = n;
        _g.resize(n);
    }
    void load(int m, bool d = false)
    {
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            u--, v--;
            assert(0 <= u && u < _n);
            assert(0 <= v && v < _n);
            _g[u].push_back(v);
            if (!d)
                _g[v].push_back(u);
        }
    }
    void load(vector<pair<int, int>> e, bool d = false)
    {
        for (auto [u, v] : e)
        {
            assert(0 <= u && u < _n);
            assert(0 <= v && v < _n);
            _g[u].push_back(v);
            if (!d)
                _g[v].push_back(u);
        }
    }
    int size()
    {
        return _n;
    }
    vvi graph()
    {
        return _g;
    }
    vi dis(int s = 0)
    {
        assert(0 <= s && s < _n);
        queue<int> q;
        vi dis(_n, INT_MAX);
        _prev.assign(_n, -1);
        dis[s] = 0;
        q.push(s);
        while (q.size())
        {
            int t = q.front();
            q.pop();
            for (int n : _g[t])
            {
                if (dis[n] > dis[t] + 1)
                {
                    dis[n] = dis[t] + 1;
                    _prev[n] = t;
                    q.push(n);
                }
            }
        }
        return dis;
    }
    vi prev()
    {
        return _prev;
    }
    tuple<int, int, int> tdia()
    {
        vi d = dis();
        int s = max_element(d.begin(), d.end()) - d.begin();
        d = dis(s);
        int t = max_element(d.begin(), d.end()) - d.begin();
        return {d[t], s, t};
    }
    vi tpsort()
    {
        vi in(_n);
        for (int i = 0; i < _n; i++)
            for (int j : _g[i])
                in[j]++;
        queue<int> q;
        for (int i = 0; i < _n; i++)
            if (!in[i])
                q.push(i);
        vi res;
        while (q.size())
        {
            int t = q.front();
            q.pop();
            for (int n : _g[t])
            {
                in[n]--;
                if (!in[n])
                    q.push(n);
            }
            res.push_back(t);
        }
        return res;
    }
    bool isBG()
    {
        _c.assign(_n, -1);
        queue<int> q;
        _c[0] = 0;
        q.push(0);
        while (q.size())
        {
            int t = q.front();
            q.pop();
            for (int n : _g[t])
            {
                if (_c[n] == _c[t])
                    return false;
                if (_c[n] == -1)
                {
                    _c[n] = !_c[t];
                    q.push(n);
                }
            }
        }
        return true;
    }
    vi c()
    {
        return _c;
    }

private:
    int _n;
    vvi _g;
    vi _prev, _c;
};
