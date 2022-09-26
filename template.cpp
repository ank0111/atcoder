#include <bits/stdc++.h>
#include <regex>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

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

struct Sieve
{
  using ll = long long;
  using vi = vector<int>;
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
  vector<pair<T, int>> factor(T x)
  {
    vector<pair<T, int>>
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
struct Mod
{
  using ll = long long;
  using vl = vector<ll>;
  Mod(int m) : _m(m) {}
  void set_mod(int m)
  {
    _m = m;
    _F.resize(1);
    _invF.resize(0);
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
  ll F(int x)
  {
    while (_F.size() <= x)
    {
      _F.push_back(_F.size() * _F.back() % _m);
    }
    return _F[x];
  }
  ll invF(int x)
  {
    while (_invF.size() <= x)
    {
      _invF.push_back(pow(F(_invF.size()), _m - 2));
    }
    return _invF[x];
  }
  ll P(int n, int r)
  {
    if (min(n, r) < 0 || n < r)
      return 0;
    return F(n) * invF(n - r) % _m;
  }
  ll C(int n, int r)
  {
    if (min(n, r) < 0 || n < r)
      return 0;
    return F(n) * invF(r) % _m * invF(n - r) % _m;
  }
  ll H(int n, int r) { return C(n + r - 1, r); }

private:
  int _m;
  vl _F{1}, _invF;
};
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

private:
  int _n;
  vi _prev;
};
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
namespace math
{
  using ll = long long;
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
  void chgcd(T &a, const U &b) { a = gcd(a, b); }
}
using namespace math;
namespace vec
{
  template <typename T = int>
  vector<T> mkiota(int n, T s = 0)
  {
    vector<T> res(n);
    std::iota(res.begin(), res.end(), s);
    return res;
  }
  vector<int> mkr(vector<int> p)
  {
    int n = p.size();
    vector<int> r(n);
    for (int i = 0; i < n; i++)
      r[p[i]] = i;
    return r;
  }
  template <typename T>
  vector<pair<T, int>> mkvi(vector<T> v)
  {
    int n = v.size();
    vector<pair<T, int>> res(n);
    for (int i = 0; i < n; i++)
      res[i] = {v[i], i};
    return res;
  }
  template <typename T>
  T vsum(const vector<T> &v)
  {
    T sum = 0;
    for (const T &x : v)
      sum += x;
    return sum;
  }
  template <typename T>
  void distinct(vector<T> &v)
  {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
  }
  template <typename T>
  T vmax(const vector<T> &v) { return *max_element(v.begin(), v.end()); }
  template <typename T>
  T vmin(const vector<T> &v) { return *min_element(v.begin(), v.end()); }
  template <typename T>
  vector<T> comp(vector<T> &a)
  {
    vector<T> ret;
    set<T> s;
    for (const T &x : a)
      s.insert(x);
    map<T, int> idx;
    int i = 0;
    for (const T &x : s)
    {
      idx[x] = i;
      ret.pb(x);
      i++;
    }
    for (T &x : a)
      x = idx[x];
    return ret;
  }
}
using namespace vec;
namespace util
{
  template <typename... Args>
  void input(Args &&...args)
  {
    (std::cin >> ... >> args);
  }
  ostream &operator<<(ostream &os, const modint &x)
  {
    os << x.val();
    return os;
  }
  istream &operator>>(istream &is, modint &x)
  {
    int a;
    is >> a;
    x = a;
    return is;
  }
  template <typename T>
  void print(const vector<T> &a, string s = " ")
  {
    for (auto x : a)
      cout << x << s;
  }
  template <typename T>
  void print(const vector<T> &a, T add, string s = " ")
  {
    for (auto x : a)
      cout << x + add << s;
  }
  template <typename T>
  void print(vector<vector<T>> &a, string s = " ")
  {
    for (vector<T> &v : a)
    {
      print(v, s);
      cout << endl;
    }
  }
  template <typename T>
  void print(vector<vector<T>> &a, T add, string s = " ")
  {
    for (vector<T> &v : a)
    {
      print(v, add, s);
      cout << endl;
    }
  }
  void set_mod(int m) { modint::set_mod(m); }
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
  template <typename T = long long>
  T nibutan(T ok, T ng, function<bool(T)> valid)
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
}
using namespace util;

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
  cin >> N >> M;
}
