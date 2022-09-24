#include <bits/stdc++.h>
using namespace std;

struct Graph : vector<vector<int>>
{
    using vi = vector<int>;
    using vvi = vector<vi>;
    Graph(int n = 0, int m = 0, bool d = false) : _n(n), vvi(n) { load(m, d); }
    Graph(int n, vector<pair<int, int>> e, bool d = false) : Graph(n) { load(e, d); }
    Graph(vvi g) : vvi(g) { _n = g.size(); }
    void resize(int n)
    {
        _n = n;
        vvi::resize(n);
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
        (*this)[from].push_back(to);
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
            for (int n : (*this)[t])
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
            for (int j : (*this)[i])
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
            for (int n : (*this)[t])
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
            for (int n : (*this)[t])
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
    vi _dis, _prev, _c;
};

struct Tree : Graph
{
    Tree(int n = 0) : Graph(n, n - 1) {}
    Tree(vvi t) : Graph(t) {}
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
            std::swap(a, b);
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
    vi preorder(int r)
    {
        assert(0 <= r && r < _n);
        vi idx(_n);
        function<int(int, int)> dfs = [&](int t, int p)
        {
            int i = idx[t];
            for (int n : (*this)[t])
            {
                if (n == p)
                    continue;
                idx[n] = i + 1;
                i = dfs(n, t);
            }
            return i;
        };
        dfs(r, -1);
        return idx;
    }
    vi postorder(int r)
    {
        assert(0 <= r && r < _n);
        vi idx(_n);
        int i = 0;
        function<int(int, int)> dfs = [&](int t, int p)
        {
            for (int n : (*this)[t])
            {
                if (n == p)
                    continue;
                dfs(n, t);
            }
            return idx[t] = i++;
        };
        dfs(r, -1);
        return idx;
    }
    vi dis(int s) { return Graph::dis(s); }
    int dis(int u, int v)
    {
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        int a = lca(u, v);
        return _dis[u] + _dis[v] - 2 * _dis[a];
    }

protected:
    vvi _parent;
};

struct CGraph : vector<vector<pair<int, long long>>>
{
    using ll = long long;
    using vl = vector<ll>;
    using vi = vector<int>;
    using vvp = vector<vector<pair<int, ll>>>;
    using edge = tuple<int, int, ll>;

    CGraph(int n = 0, int m = 0, bool d = false) : _n(n), vvp(n) { load(m, d); }
    CGraph(int n, vector<edge> e, bool d = false) : CGraph(n) { load(e, d); }
    CGraph(vvp g) : vvp(g) { _n = g.size(); }
    void resize(int n)
    {
        _n = n;
        vvp::resize(n);
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
        (*this)[from].push_back({to, cost});
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
            for (auto [n, c] : (*this)[t])
            {
                assert(c >= 0);
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
                for (auto [n, c] : (*this)[t])
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
};
