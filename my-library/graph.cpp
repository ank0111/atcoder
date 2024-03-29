#include <bits/stdc++.h>

namespace my_lib
{
    struct Graph : std::vector<std::vector<int>>
    {
        using vi = std::vector<int>;
        using vvi = std::vector<vi>;
        Graph(int n = 0, int m = 0, bool d = false) : vvi(n), _n(n) { load(m, d); }
        Graph(int n, std::vector<std::pair<int, int>> e, bool d = false) : Graph(n) { load(e, d); }
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
                std::cin >> u >> v;
                u--, v--;
                add_edge(u, v);
                if (!d)
                    add_edge(v, u);
            }
        }
        void load(std::vector<std::pair<int, int>> e, bool d = false)
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
        vi dis(int s, vi *pp = nullptr) const
        {
            assert(0 <= s && s < _n);
            std::queue<int> q;
            vi dis(_n, INT_MAX);
            vi prev(_n, -1);
            dis[s] = 0;
            q.push(s);
            while (q.size())
            {
                int t = q.front();
                q.pop();
                for (int n : (*this)[t])
                {
                    if (dis[n] > dis[t] + 1)
                    {
                        dis[n] = dis[t] + 1;
                        prev[n] = t;
                        q.push(n);
                    }
                }
            }
            if (pp != nullptr)
            {
                *pp = prev;
            }
            return dis;
        }
        vi path(int u, int v) const
        {
            vi prev;
            dis(v, &prev);
            vi res;
            int t = u;
            while (true)
            {
                res.push_back(t);
                if (t == v)
                    break;
                t = prev[t];
            }
            return res;
        }
        vi tpsort() const
        {
            vi in(_n);
            for (int i = 0; i < _n; i++)
                for (int j : (*this)[i])
                    in[j]++;
            std::queue<int> q;
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
        bool isBG(vi *cp = nullptr) const
        {
            vi c(_n, -1);
            for (int i = 0; i < _n; i++)
            {
                if (c[i] == -1)
                {
                    std::queue<int> q;
                    c[i] = 0;
                    q.push(i);
                    while (q.size())
                    {
                        int t = q.front();
                        q.pop();
                        for (int n : (*this)[t])
                        {
                            if (c[n] == c[t])
                                return false;
                            if (c[n] == -1)
                            {
                                c[n] = !c[t];
                                q.push(n);
                            }
                        }
                    }
                }
            }
            if (cp != nullptr)
            {
                *cp = c;
            }
            return true;
        }

    protected:
        int _n;
    };

    struct Tree : Graph
    {
        Tree(int n = 0) : Graph(n, n - 1) {}
        Tree(vvi t) : Graph(t) {}
        bool operator==(const Tree &b) const
        {

            for (int ac : cen())
                for (int bc : b.cen())
                {
                    std::map<vi, int> hm;
                    if (hash(ac, -1, hm) == b.hash(bc, -1, hm))
                        return true;
                }
            return false;
        }
        int hash(int t, int p, std::map<vi, int> &hm) const
        {
            vi c;
            for (int n : (*this)[t])
            {
                if (n == p)
                    continue;
                c.push_back(hash(n, t, hm));
            }
            std::sort(c.begin(), c.end());
            if (!hm.count(c))
            {
                hm[c] = hm.size();
            }
            return hm[c];
        }
        std::tuple<int, int, int> dia(vi *dp = nullptr, vi *pp = nullptr) const
        {
            vi dis = this->dis(0);
            int s = max_element(dis.begin(), dis.end()) - dis.begin();
            dis = this->dis(s, pp);
            int t = max_element(dis.begin(), dis.end()) - dis.begin();
            if (dp != nullptr)
            {
                *dp = dis;
            }
            return {dis[t], s, t};
        }
        std::vector<int> cen() const
        {
            vi dis, prev;
            auto [d, s, t] = dia(&dis, &prev);
            while (dis[t] > (d + 1) / 2)
            {
                t = prev[t];
            }
            std::vector<int> c{t};
            if (d % 2)
            {
                c.push_back(prev[t]);
            }
            return c;
        }
        vvi doubling(int r)
        {
            assert(0 <= r && r < _n);
            _parent.assign(_n, vi(30, -1));
            vi prev;
            _dis = dis(r, &prev);
            for (int i = 0; i < _n; i++)
                _parent[i][0] = prev[i];
            for (int j = 0; j < 30; j++)
                for (int i = 0; i < _n; i++)
                {
                    int tp = _parent[i][j];
                    if (tp != -1)
                        _parent[i][j + 1] = _parent[tp][j];
                }
            return _parent;
        }
        int lca(int a, int b) const
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
        vi preorder(int r) const
        {
            assert(0 <= r && r < _n);
            vi idx(_n);
            auto dfs = [&](auto &&f, int t, int p) -> int
            {
                int i = idx[t];
                for (int n : (*this)[t])
                {
                    if (n == p)
                        continue;
                    idx[n] = i + 1;
                    i = f(f, n, t);
                }
                return i;
            };
            dfs(dfs, r, -1);
            return idx;
        }
        vi postorder(int r) const
        {
            assert(0 <= r && r < _n);
            vi idx(_n);
            int i = 0;
            auto dfs = [&](auto &&f, int t, int p) -> void
            {
                for (int n : (*this)[t])
                {
                    if (n == p)
                        continue;
                    f(f, n, t);
                }
                idx[t] = i++;
            };
            dfs(dfs, r, -1);
            return idx;
        }
        vvi euler_tour(int r = 0) const
        {
            assert(0 <= r && r < _n);
            vvi res(_n, vi(2));
            int i = 0;
            auto dfs = [&](auto &&f, int t, int p) -> void
            {
                res[t][0] = i++;
                for (int n : (*this)[t])
                {
                    if (n == p)
                        continue;
                    f(f, n, t);
                }
                res[t][1] = i++;
            };
            dfs(dfs, r, -1);
            return res;
        }
        vi dis(int s, vi *pp = nullptr) const { return Graph::dis(s, pp); }
        int dis(int u, int v) const
        {
            assert(0 <= u && u < _n);
            assert(0 <= v && v < _n);
            int a = lca(u, v);
            return _dis[u] + _dis[v] - 2 * _dis[a];
        }
        template <typename T, typename F1, typename F2>
        std::vector<T> rerooting(const F1 &merge, const F2 &f, const T &id) const
        {
            std::vector<T> dp(_n, id);
            const auto dfs1 = [&](auto &&rf, int t, int p) -> void
            {
                for (int n : (*this)[t])
                {
                    if (n == p)
                        continue;
                    rf(rf, n, t);
                    dp[t] = merge(dp[t], f(dp[n]));
                }
            };
            const auto dfs2 = [&](auto &&rf, int t, int p, const T dp_p) -> void
            {
                if (p != -1)
                    dp[t] = merge(dp[t], f(dp_p));
                int n = (*this)[t].size();
                std::vector<T> l(n, id), r(n, id);
                for (int i = 0; i < n - 1; i++)
                {
                    int c = (*this)[t][i];
                    T a = c == p ? dp_p : dp[c];
                    l[i + 1] = merge(l[i], f(a));
                }
                for (int i = n - 2; i >= 0; i--)
                {
                    int c = (*this)[t][i + 1];
                    T a = c == p ? dp_p : dp[c];
                    r[i] = merge(r[i + 1], f(a));
                }
                for (int i = 0; i < n; i++)
                {
                    int c = (*this)[t][i];
                    if (c == p)
                        continue;
                    rf(rf, c, t, merge(l[i], r[i]));
                }
            };
            dfs1(dfs1, 0, -1);
            dfs2(dfs2, 0, -1, id);
            return dp;
        }

    protected:
        vi _dis;
        vvi _parent;
    };

    template <typename T = long long>
    struct CGraph : std::vector<std::vector<std::pair<int, T>>>
    {
        using vt = std::vector<T>;
        using vi = std::vector<int>;
        using vvp = std::vector<std::vector<std::pair<int, T>>>;
        using edge = std::tuple<int, int, T>;
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
        CGraph(int n, std::vector<edge> e, bool d = false) : CGraph(n) { load(e, d); }
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
                std::cin >> u >> v >> c;
                u--, v--;
                add_edge(u, v, c);
                if (!d)
                    add_edge(v, u, c);
            }
        }
        void load(std::vector<edge> e, bool d = false)
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
            std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> q;
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
        vi path(int u, int v, bool n = false, T zero = 0, T unreachable = LLONG_MAX, T inf = LLONG_MIN)
        {
            if (n)
                bellfo(v, zero, unreachable, inf);
            else
                dijk(v, zero, unreachable);
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
        std::vector<Edge> _e;
    };
}
