#include <bits/stdc++.h>
#include <atcoder/all>

namespace my_lib
{
  using ll = long long;
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
  struct Mod
  {
    using ll = long long;
    using vl = std::vector<ll>;
    Mod(int m) : _m(m) {}
    void set_mod(int m)
    {
      _m = m;
      _F.resize(2);
      _invF.resize(2);
      _inv.resize(2);
    }
    ll pow(ll x, ll n)
    {
      assert(n >= 0);
      if (n == 0)
        return 1;
      x %= _m;
      if (n % 2)
        return x * pow(x, n - 1) % _m;
      else
        return pow(x * x, n / 2);
    }
    ll F(size_t x)
    {
      while (_F.size() <= x)
      {
        _F.push_back(_F.size() * _F.back() % _m);
      }
      return _F[x];
    }
    ll invF(size_t x)
    {
      while (_inv.size() <= x)
      {
        _inv.push_back(_m - _inv[_m % _inv.size()] * (_m / _inv.size()) % _m);
      }
      while (_invF.size() <= x)
      {
        _invF.push_back(_inv[_invF.size()] * _invF.back() % _m);
      }
      return _invF[x];
    }
    ll P(int n, int r)
    {
      if (std::min(n, r) < 0 || n < r)
        return 0;
      return F(n) * invF(n - r) % _m;
    }
    ll C(int n, int r)
    {
      if (std::min(n, r) < 0 || n < r)
        return 0;
      return F(n) * invF(r) % _m * invF(n - r) % _m;
    }
    ll H(int n, int r) { return C(n + r - 1, r); }

  private:
    int _m;
    vl _F{1, 1}, _invF{1, 1}, _inv{0, 1};
  };
  struct Sieve
  {
    using ll = long long;
    using vi = std::vector<int>;
    int n;
    vi f, primes;
    Sieve(int n = 1) : n(n), f(n + 1, 1)
    {
      f[0] = f[1] = 0;
      for (ll i = 2; i <= n; ++i)
      {
        if (!f[i])
          continue;
        primes.push_back(i);
        for (ll j = i * i; j <= n; j += i)
        {
          f[j] = 0;
        }
      }
    }
    bool isPrime(int x)
    {
      assert(0 <= x && x <= n);
      return f[x];
    }
    template <typename T>
    std::vector<std::pair<T, int>> factor(T x)
    {
      std::vector<std::pair<T, int>>
          res;
      for (int p : primes)
      {
        if (x % p != 0)
          continue;
        int c = 0;
        while (x % p == 0)
          x /= p, ++c;
        res.emplace_back(p, c);
      }
      if (x != 1)
        res.emplace_back(x, 1);
      return res;
    }
  };
  template <typename T = int>
  struct PersistentStack
  {
    PersistentStack() {}
    T top() const
    {
      assert(_n > 0);
      return _top->v;
    }
    bool empty() const
    {
      return _n == 0;
    }
    size_t size() const
    {
      return _n;
    }
    PersistentStack push(const T &v) const
    {
      Node *ntop = new Node();
      ntop->v = v;
      ntop->p = _top;
      return PersistentStack(_n + 1, ntop);
    }
    PersistentStack pop() const
    {
      assert(_n > 0);
      return PersistentStack(_n - 1, _top->p);
    }

  private:
    struct Node
    {
      T v;
      Node *p;
    };
    PersistentStack(int n, Node *top) : _n(n), _top(top){};
    size_t _n = 0;
    Node *_top = nullptr;
  };
  template <typename T = int, size_t SIZE = 10>
  struct PersistentArray
  {
    PersistentArray(size_t n = 0) : PersistentArray(n, nullptr) {}
    PersistentArray(const std::vector<T> &src) : PersistentArray(src.size())
    {
      for (size_t i = 0; i < _n; i++)
      {
        _destructive_set(_root, i, src[i]);
      }
    }
    size_t size() const { return _n; }
    PersistentArray resize(size_t n) const { return PersistentArray(n, _root); }
    void destructive_set(size_t i, const T &v)
    {
      assert(i < _n);
      _destructive_set(_root, i, v);
    }
    PersistentArray set(size_t i, const T &v) const
    {
      assert(i < _n);
      Node *nr = _set(_root, i, v);
      return PersistentArray(_n, nr);
    }
    T get(size_t i) const
    {
      assert(i < _n);
      return _get(_root, i)->v;
    }
    PersistentArray push(const T &v) const
    {
      Node *nr = _set(_root, _n, v);
      return PersistentArray(_n + 1, nr);
    }
    PersistentArray pop() const
    {
      assert(_n > 0);
      return PersistentArray(_n - 1, _root);
    }

  private:
    struct Node
    {
      T v;
      Node *ch[SIZE] = {};
    };
    size_t _n;
    Node *_root = nullptr;
    PersistentArray(size_t n, Node *root) : _n(n), _root(root) {}
    void _destructive_set(Node *t, size_t i, const T &v)
    {
      if (!t)
        t = new Node();
      if (i == 0)
        t->v = v;
      else
        _destructive_set(t->ch[i % SIZE], i / SIZE, v);
    }
    Node *_set(const Node *t, size_t i, const T &v) const
    {
      Node *res = new Node();
      if (t)
      {
        res->v = t->v;
        memcpy(res->ch, t->ch, sizeof(t->ch));
      }
      if (i == 0)
        res->v = v;
      else
        res->ch[i % SIZE] = _set(res->ch[i % SIZE], i / SIZE, v);
      return res;
    }
    Node *_get(Node *t, size_t i) const
    {
      if (!t)
        return new Node();
      if (i == 0)
        return t;
      return _get(t->ch[i % SIZE], i / SIZE);
    }
  };
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
  ll sqsum(ll a, ll b) { return a * a + b * b; }
  ll sq(ll a) { return a * a; }
  ll fact(ll n)
  {
    if (n == 1)
      return 1;
    return n * fact(n - 1);
  }
  ll com(int n, int r)
  {
    ll t = 1;
    for (ll i = 0; i < r; i++)
    {
      t *= (n - r + 1 + i);
      t /= (i + 1);
    }
    return t;
  }
  ll sqrtll(ll x)
  {
    ll r = round(sqrt((double)x));
    ll rr = r * r;
    if (rr > x)
      r--;
    return r;
  }
  template <typename T, typename U>
  bool chmax(T &a, const U &b)
  {
    if (a < b)
    {
      a = b;
      return true;
    }
    return false;
  }
  template <typename T, typename U>
  bool chmin(T &a, const U &b)
  {
    if (a > b)
    {
      a = b;
      return true;
    }
    return false;
  }
  template <typename T, typename U>
  void chgcd(T &a, const U &b) { a = std::gcd(a, b); }
  template <typename T = int>
  std::vector<T> mkiota(int n, T s = 0)
  {
    std::vector<T> res(n);
    std::iota(res.begin(), res.end(), s);
    return res;
  }
  std::vector<int> mkr(const std::vector<int> &p)
  {
    int n = p.size();
    std::vector<int> r(n);
    for (int i = 0; i < n; i++)
      r[p[i]] = i;
    return r;
  }
  template <typename T>
  std::vector<std::pair<T, int>> mkvi(const std::vector<T> &v)
  {
    int n = v.size();
    std::vector<std::pair<T, int>> res(n);
    for (int i = 0; i < n; i++)
      res[i] = {v[i], i};
    return res;
  }
  template <typename T>
  std::vector<T> mkcsum(const std::vector<T> &v)
  {
    size_t n = v.size();
    std::vector<T> res(n + 1);
    for (int i = 0; i < n; i++)
    {
      res[i + 1] = res[i] + v[i];
    }
    return res;
  }
  template <typename T>
  T vsum(const std::vector<T> &v, const T &zero = 0)
  {
    T sum = zero;
    for (const T &x : v)
      sum += x;
    return sum;
  }
  template <typename T>
  void distinct(std::vector<T> &v)
  {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
  }
  template <typename T>
  T vmax(const std::vector<T> &v) { return *max_element(v.begin(), v.end()); }
  template <typename T>
  T vmin(const std::vector<T> &v) { return *min_element(v.begin(), v.end()); }
  template <typename T>
  std::vector<T> comp(std::vector<T> &a)
  {
    std::vector<T> ret;
    std::set<T> s;
    for (const T &x : a)
      s.insert(x);
    std::map<T, int> idx;
    int i = 0;
    for (const T &x : s)
    {
      idx[x] = i;
      ret.push_back(x);
      i++;
    }
    for (T &x : a)
      x = idx[x];
    return ret;
  }
  template <typename T>
  size_t argmax(const std::vector<T> &v)
  {
    return max_element(v.begin(), v.end()) - v.begin();
  }
  template <typename T>
  size_t argmin(const std::vector<T> &v)
  {
    return min_element(v.begin(), v.end()) - v.begin();
  }
  template <typename... Args>
  void input(Args &&...args)
  {
    (std::cin >> ... >> args);
  }
  std::ostream &operator<<(std::ostream &os, const atcoder::modint &x)
  {
    os << x.val();
    return os;
  }
  std::istream &operator>>(std::istream &is, atcoder::modint &x)
  {
    int a;
    is >> a;
    x = a;
    return is;
  }
  template <typename T>
  void print(const std::vector<T> &a, std::string s = " ")
  {
    for (auto x : a)
      std::cout << x << s;
  }
  template <typename T>
  void print(const std::vector<T> &a, T add, std::string s = " ")
  {
    for (auto x : a)
      std::cout << x + add << s;
  }
  template <typename T>
  void print(std::vector<std::vector<T>> &a, std::string s = " ")
  {
    for (std::vector<T> &v : a)
    {
      print(v, s);
      std::cout << "\n";
    }
  }
  template <typename T>
  void print(std::vector<std::vector<T>> &a, T add, std::string s = " ")
  {
    for (std::vector<T> &v : a)
    {
      print(v, add, s);
      std::cout << "\n";
    }
  }
  void set_mod(int m) { atcoder::modint::set_mod(m); }
  template <typename T>
  int biti(T bit, int i)
  {
    return bit >> i & 1;
  }
  unsigned long xor128()
  {
    static unsigned long x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    unsigned long t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
  }
  template <typename T = long long, typename F>
  T nibutan(T ok, T ng, const F &valid)
  {
    while (abs(ok - ng) > 1)
    {
      T m = (ok + ng) / 2;
      if (valid(m))
        ok = m;
      else
        ng = m;
    }
    return ok;
  }
  template <typename T = double, typename F, typename Comp>
  T sanbutan(T l, T r, const F &f, const Comp &comp, size_t cnt = 1000)
  {
    while (cnt--)
    {
      T m1 = (l * 2 + r) / 3;
      T m2 = (l + r * 2) / 3;
      if (comp(f(m1), f(m2)))
        r = m2;
      else
        l = m1;
    }
    return l;
  }
  template <typename T, typename F, typename Comp>
  T fibotan(T l, T r, const F &f, const Comp &comp)
  {
    assert(r >= l);
    l--;
    r++;
    T d = r - l;
    std::vector<long long> fib{0, 1};
    int n = 2;
    while (fib.back() < d)
    {
      fib.push_back(fib[n - 1] + fib[n - 2]);
      n++;
    }
    T tl = l, tr = l + fib.back();
    T m1 = tr - fib[n - 2], m2 = tl + fib[n - 2];
    auto f1 = f(m1);
    auto f2 = f(m2);
    while (m1 != m2)
    {
      if (comp(f1, f2) || m2 >= r)
      {
        tr = m2;
        m2 = m1;
        f2 = f1;
        m1 = tr - fib[n - 3];
        f1 = f(m1);
      }
      else
      {
        tl = m1;
        m1 = m2;
        f1 = f2;
        m2 = tl + fib[n - 3];
        f2 = f(m2);
      }
      n--;
    }
    return m1;
  }
}

using namespace std;
using namespace atcoder;
using namespace my_lib;

#pragma region macro
#define LINF (ll)2e18
#define INF (ll)1e9
#define rep(i, n) for (int i = 0; i < n; ++i)
#define reps(i, s, n) for (int i = s; i < n; ++i)
#define repr(i, s) for (int i = s; i >= 0; --i)
#define repre(i, s, e) for (int i = s; i >= e; --i)
#define ALL(a) (a).begin(), (a).end()
#define cinv(a, n) rep(i, n) cin >> a[i]
#define cinvi(a, n) \
  vi a(n);          \
  rep(i, n) cin >> a[i]
#define cinvim(a, n) \
  cinvi(a, n);       \
  rep(i, n) a[i]--
#define cinvl(a, n) \
  vl a(n);          \
  rep(i, n) cin >> a[i]
#define cinvs(a, n) \
  vs a(n);          \
  rep(i, n) cin >> a[i]
#define cinvi2(a, b, n) \
  vi a(n), b(n);        \
  rep(i, n) cin >> a[i] >> b[i]
#define cinvl2(a, b, n) \
  vl a(n), b(n);        \
  rep(i, n) cin >> a[i] >> b[i]
#define cinvpi(a, n) \
  vpi a(n);          \
  rep(i, n)          \
  {                  \
    int x, y;        \
    cin >> x >> y;   \
    a[i] = {x, y};   \
  }
#define cinvpl(a, n) \
  vpl a(n);          \
  rep(i, n)          \
  {                  \
    ll x, y;         \
    cin >> x >> y;   \
    a[i] = {x, y};   \
  }
#define cinvvi(a, n, m) \
  vvi a(n, vi(m));      \
  rep(i, n) rep(j, m) cin >> a[i][j]
#define cinvvl(a, n, m) \
  vvl a(n, vl(m));      \
  rep(i, n) rep(j, m) cin >> a[i][j]
#define cint(a) \
  int a;        \
  cin >> a
#define cinl(a) \
  ll a;         \
  cin >> a
#define cins(s) \
  string s;     \
  cin >> s
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define endl "\n"
#define fast_io                \
  ios::sync_with_stdio(false); \
  cin.tie(nullptr);
#define printif(a, b, c) cout << (a ? b : c)
#define printch(a, b, c) cout << (a == b ? c : a)
#define chif(a, b, c) \
  if (a == b)         \
  a = c
#pragma endregion macro
#pragma region using
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using ul = unsigned ll;
using vul = vector<ul>;
using vvul = vector<vul>;
using vs = vector<string>;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vvpi = vector<vpi>;
using vvpl = vector<vpl>;
using mint = modint;
using vm = vector<mint>;
using vvm = vector<vm>;
using vvvm = vector<vvm>;
#pragma endregion using

//*
const int mod = 998244353;
//*/const int mod = 1e9 + 7;
ll M, N, K, Q, H, W;
string S, T;
const string yes = "Yes", no = "No";
const int dx[9] = {0, 1, 0, -1, 1, 1, -1, -1, 0}, dy[9] = {1, 0, -1, 0, 1, -1, 1, -1, 0};
// const int dx[9]={1,1,0,-1,-1,-1,0,1,0},dy[9]={0,1,1,1,0,-1,-1,-1,0};
bool canmove(int nx, int ny) { return 0 <= nx && nx < H && 0 <= ny && ny < W; }

using tpl = tuple<int, int, int>;
using vt = vector<tpl>;

int main()
{
  fast_io;
  set_mod(mod);
  input(N, M);
}
