#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    using vi = vector<int>;
    using vvi = vector<vi>;
    Graph(int n = 0, int m = 0, bool d = false) : _n(n), _g(n) { load(m, d); }
    Graph(int n, vector<pair<int, int>> e, bool d = false) : _n(n), _g(n) { load(e, d); }
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
            add_edge(u, v);
            if (!d)
                add_edge(v, u);
        }
    }
    void load(vector<pair<int, int>> e, bool d = false)
    {
        for (auto [u, v] : e)
        {
            add_edge(u, v);
            if (!d)
                add_edge(v, u);
        }
    }
    void add_edge(int from, int to)
    {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        _g[from].push_back(to);
    }
    int size()
    {
        return _n;
    }
    vvi graph()
    {
        return _g;
    }
    vi dis(int s)
    {
        assert(0 <= s && s < _n);
        queue<int> q;
        _dis.assign(_n, INT_MAX);
        _prev.assign(_n, -1);
        _dis[s] = 0;
        q.push(s);
        while (q.size())
        {
            int t = q.front();
            q.pop();
            for (int n : _g[t])
            {
                if (_dis[n] > _dis[t] + 1)
                {
                    _dis[n] = _dis[t] + 1;
                    _prev[n] = t;
                    q.push(n);
                }
            }
        }
        return _dis;
    }
    vi prev()
    {
        return _prev;
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
    vi color()
    {
        return _c;
    }

protected:
    int _n;
    vvi _g;
    vi _dis, _prev, _c;
};

struct Tree : Graph
{
    Tree(int n = 0) : Graph(n, n - 1) {}
    tuple<int, int, int> dia()
    {
        dis(0);
        int s = max_element(_dis.begin(), _dis.end()) - _dis.begin();
        dis(s);
        int t = max_element(_dis.begin(), _dis.end()) - _dis.begin();
        return {_dis[t], s, t};
    }
    vvi doubling(int r)
    {
        assert(0 <= r && r < _n);
        _parent.assign(_n, vi(30, -1));
        dis(r);
        for (int i = 0; i < _n; i++)
            _parent[i][0] = _prev[i];
        for (int j = 0; j < 30; j++)
            for (int i = 0; i < _n; i++)
            {
                int tp = _parent[i][j];
                if (tp != -1)
                    _parent[i][j + 1] = _parent[tp][j];
            }
        return _parent;
    }
    int lca(int a, int b)
    {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        if (_dis[a] > _dis[b])
            swap(a, b);
        for (int i = 0; i < 30; i++)
        {
            if ((_dis[b] - _dis[a]) >> i & 1)
                b = _parent[b][i];
        }
        if (a == b)
            return a;
        while (_parent[a][0] != _parent[b][0])
        {
            int l = 0, r = 30;
            while (r - l > 1)
            {
                int m = (l + r) / 2;
                if (_parent[a][m] == _parent[b][m])
                    r = m;
                else
                    l = m;
            }
            a = _parent[a][l];
            b = _parent[b][l];
        }
        return _parent[a][0];
    }

protected:
    vvi _parent;
};

struct CGraph
{
    using ll = long long;
    using vl = vector<ll>;
    using vi = vector<int>;
    using vvp = vector<vector<pair<int, ll>>>;
    using edge = tuple<int, int, ll>;

    CGraph(int n = 0, int m = 0, bool d = false) : _n(n), _g(n) { load(m, d); }
    CGraph(int n, vector<edge> e, bool d = false) : CGraph(n) { load(e, d); }
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
            ll c;
            cin >> u >> v >> c;
            u--, v--;
            add_edge(u, v, c);
            if (!d)
                add_edge(v, u, c);
        }
    }
    void load(vector<edge> e, bool d = false)
    {
        for (auto [u, v, c] : e)
        {
            add_edge(u, v, c);
            if (!d)
                add_edge(v, u, c);
        }
    }
    void add_edge(int from, int to, ll cost)
    {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        _g[from].push_back({to, cost});
    }
    int size()
    {
        return _n;
    }
    vvp graph()
    {
        return _g;
    }
    vl dijk(int s)
    {
        vl dis(_n, LLONG_MAX);
        _prev.assign(_n, -1);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
        dis[s] = 0;
        q.push({0, s});
        while (q.size())
        {
            auto [tc, t] = q.top();
            q.pop();
            if (tc != dis[t])
                continue;
            for (auto [n, c] : _g[t])
            {
                if (dis[n] > tc + c)
                {
                    dis[n] = tc + c;
                    _prev[n] = t;
                    q.push({dis[n], n});
                }
            }
        }
        return dis;
    }
    vl bellfo(int s)
    {
        vl dis(_n, LLONG_MAX);
        dis[s] = 0;
        for (int i = 0; i < 2 * _n; i++)
        {
            for (int t = 0; t < _n; t++)
            {
                if (dis[t] == LLONG_MAX)
                    continue;
                for (auto [n, c] : _g[t])
                {
                    if (dis[t] == LLONG_MIN)
                    {
                        dis[n] = LLONG_MIN;
                        _prev[n] = t;
                    }
                    else if (dis[n] > dis[t] + c)
                    {
                        if (i >= _n - 1)
                        {
                            dis[n] = LLONG_MIN;
                            _prev[n] = t;
                        }
                        else
                        {
                            dis[n] = dis[t] + c;
                            _prev[n] = t;
                        }
                    }
                }
            }
        }
        return dis;
    }
    vi prev()
    {
        return _prev;
    }

private:
    int _n;
    vi _prev;
    vvp _g;
};
