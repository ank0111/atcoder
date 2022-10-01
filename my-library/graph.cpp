#include <bits/stdc++.h>
using namespace std;

struct Graph : vector<vector<int>>
{
    using vi = vector<int>;
    using vvi = vector<vi>;
    Graph(int n = 0, int m = 0, bool d = false) : vvi(n), _n(n) { load(m, d); }
    Graph(int n, vector<pair<int, int>> e, bool d = false) : Graph(n) { load(e, d); }
    Graph(vvi g) : vvi(g), _n(g.size()) {}
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
    vi path(int u, int v)
    {
        dis(v);
        vi res;
        int t = u;
        while (true)
        {
            res.push_back(t);
            if (t == v)
                break;
            t = _prev[t];
        }
        return res;
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
    template <typename T>
    vector<T> rerooting(const function<T(T, T)> f1, const function<T(T, T)> f2, const T &id)
    {
        vector<T> dp(_n, id);
        const function<void(int, int)> dfs1 = [&](int t, int p)
        {
            for (int n : (*this)[t])
            {
                if (n == p)
                    continue;
                dfs1(n, t);
                dp[t] = f1(dp[t], dp[n]);
            }
        };
        const function<void(int, int, T)> dfs2 = [&](int t, int p, const T dp_p)
        {
            if (p != -1)
                dp[t] = f1(dp[t], dp_p);
            int n = (*this)[t].size();
            vector<T> l(n, id), r(n, id);
            for (int i = 0; i < n - 1; i++)
            {
                int c = (*this)[t][i];
                T a = c == p ? dp_p : dp[c];
                l[i + 1] = f1(l[i], a);
            }
            for (int i = n - 2; i >= 0; i--)
            {
                int c = (*this)[t][i + 1];
                T a = c == p ? dp_p : dp[c];
                r[i] = f1(r[i + 1], a);
            }
            for (int i = 0; i < n; i++)
            {
                int c = (*this)[t][i];
                if (c == p)
                    continue;
                dfs2(c, t, f2(l[i], r[i]));
            }
        };
        dfs1(0, -1);
        dfs2(0, -1, id);
        return dp;
    }

protected:
    vvi _parent;
};

template <typename T = long long>
struct CGraph : vector<vector<pair<int, T>>>
{
    using vt = vector<T>;
    using vi = vector<int>;
    using vvp = vector<vector<pair<int, T>>>;
    using edge = tuple<int, int, T>;
    struct Edge
    {
        int to, from;
        T cost;
        bool operator<(const Edge b)
        {
            return cost < b.cost;
        }
    };

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
            T c;
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
    void add_edge(int from, int to, T cost)
    {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        (*this)[from].push_back({to, cost});
        _e.push_back({from, to, cost});
    }
    vt dijk(int s, T zero = 0, T unreachable = LLONG_MAX)
    {
        assert(0 <= s && s < _n);
        vt dis(_n, unreachable);
        _prev.assign(_n, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> q;
        dis[s] = zero;
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
    vt bellfo(int s, T zero = 0, T unreachable = LLONG_MAX, T inf = LLONG_MIN)
    {
        assert(0 <= s && s < _n);
        vt dis(_n, unreachable);
        _prev.assign(_n, -1);
        dis[s] = zero;
        for (int i = 0; i < 2 * _n; i++)
        {
            for (int t = 0; t < _n; t++)
            {
                if (dis[t] == unreachable)
                    continue;
                for (auto [n, c] : (*this)[t])
                {
                    if (dis[t] == inf)
                    {
                        dis[n] = inf;
                        _prev[n] = t;
                    }
                    else if (dis[n] > dis[t] + c)
                    {
                        if (i >= _n - 1)
                        {
                            dis[n] = inf;
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
    vi path(int u, int v, bool n = false)
    {
        if (n)
            bellfo(v);
        else
            dijk(v);
        vi res;
        int t = u;
        while (true)
        {
            res.push_back(t);
            if (t == v)
                break;
            t = _prev[t];
        }
        return res;
    }
    template <typename U>
    T kruskal(U &uf, T zero = 0)
    {
        T res = zero;
        sort(_e.begin(), _e.end());
        for (Edge t : _e)
        {
            if (uf.same(t.from, t.to))
                continue;
            uf.merge(t.from, t.to);
            res += t.cost;
        }
        return res;
    }

private:
    int _n;
    vi _prev;
    vector<Edge> _e;
};
