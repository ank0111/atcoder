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
const int mod=998244353;
//*/const int mod = 1e9 + 7;
#pragma region library
#pragma region math
ll sqsum(ll a, ll b)
{
  return a * a + b * b;
}
ll sq(ll a) { return a * a; }
struct Sieve
{
  int n;
  vi f, primes;
  Sieve(int n = 1) : n(n), f(n + 1, 1)
  {
    f[0] = f[1] = 0;
    for (ll i = 2; i <= n; ++i)
    {
      if (!f[i])
        continue;
      primes.pb(i);
      for (ll j = i * i; j <= n; j += i)
      {
        f[j] = 0;
      }
    }
  }
  bool isPrime(int x) { return f[x]; }
  template <typename T>
  vector<pair<T, int>> factor(T x)
  {
    vector<pair<T, int>> res;
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
template <typename T>
vector<vector<T>> mat_mul(const vector<vector<T>> &a, const vector<vector<T>> &b)
{
  int n = a.size(), m = b[0].size(), l = b.size();
  vector res(n, vector<T>(m));
  rep(i, n) rep(j, m) rep(k, l)
  {
    res[i][j] += a[i][k] * b[k][j];
  }
  return res;
}
template <typename T, typename U>
vector<vector<T>> mat_pow(const vector<vector<T>> &m, U n)
{
  if (n == 1)
    return m;
  if (n % 2 == 0)
    return mat_pow(mat_mul(m, m), n / 2);
  return mat_mul(m, mat_pow(m, n - 1));
}
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
  ll rr=r*r;
  if(rr>x)r--;
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
ll powmod(ll x, ll n, const ll m = mod)
{
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  x %= m;
  if (n % 2)
    return x * powmod(x, n - 1, m) % m;
  else
    return powmod(x * x % m, n / 2, m);
}
ll F(int x)
{
  static vl f(1, 1);
  while ((int)f.size() <= x)
  {
    f.pb(f.back() * f.size() % mod);
  }
  return f[x];
}
ll iF(int x)
{
  static vl invf;
  while ((int)invf.size() <= x)
  {
    invf.pb(powmod(F(invf.size()), mod - 2));
  }
  return invf[x];
}
ll cmod(int n, int r)
{
  if (min(n, r) < 0 || n < r)
    return 0;
  return F(n) * iF(r) % mod * iF(n - r) % mod;
}
ll hmod(int n, int r) { return cmod(n + r - 1, r); }
#pragma endregion math
#pragma region graph
vvi mkgraph(int n, int m, bool d = false)
{
  vvi g(n);
  rep(i, m)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    g[a].push_back(b);
    if (!d)
      g[b].push_back(a);
  }
  return g;
}
vvi mkgraph(int n, vpi e, bool d = false)
{
  vvi g(n);
  rep(i, (int)e.size())
  {
    auto [a, b] = e[i];
    g[a].push_back(b);
    if (!d)
      g[b].push_back(a);
  }
  return g;
}
vvpl mkcgraph(int n, int m, bool d = false)
{
  vvpl g(n);
  rep(i, m)
  {
    ll a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    g[a].push_back({b, c});
    if (!d)
      g[b].push_back({a, c});
  }
  return g;
}
vvi mktree(int n) { return mkgraph(n, n - 1); }
vl dijk(const vvpl &g, int s, vi &prev, bool d = false)
{
  vl cost(g.size(), LLONG_MAX);
  prev.resize(g.size(), -1);
  prev[s] = -1;
  if (!d)
    cost[s] = 0;
  priority_queue<pl, vpl, greater<pl>> q;
  q.push({0, s});
  while (q.size())
  {
    auto [tc, t] = q.top();
    q.pop();
    if (cost[t] != tc && cost[t] != LLONG_MAX)
      continue;
    for (auto [n, c] : g[t])
      if (chmin(cost[n], tc + c))
      {
        q.push({tc + c, n});
        prev[n] = t;
      }
  }
  return cost;
}
vl dijk(const vvpl &g, int s, bool d = false)
{
  vi prev;
  return dijk(g, s, prev, d);
}
vl bellfo(const vvpl &g, int s)
{
  int N = g.size();
  vl res(N, LLONG_MAX);
  res[s] = 0;
  rep(i, 2 * N)
  {
    rep(t, N)
    {
      if (res[t] == LLONG_MAX)
        continue;
      for (auto [n, c] : g[t])
      {
        if (res[t] == LLONG_MIN)
          res[n] = LLONG_MIN;
        else if (chmin(res[n], res[t] + c) && i >= N - 1)
        {
          res[n] = LLONG_MIN;
        }
      }
    }
  }
  return res;
}
vi tpsort(const vvi &g)
{
  int n = g.size();
  vi in(n);
  rep(i, n) for (int j : g[i]) in[j]++;
  queue<int> q;
  rep(i, n) if (!in[i]) q.push(i);
  vi res;
  while (q.size())
  {
    int t = q.front();
    q.pop();
    for (int n : g[t])
    {
      in[n]--;
      if (!in[n])
        q.push(n);
    }
    res.pb(t);
  }
  rep(i, n) if (in[i]) res.pb(i);
  return res;
}
bool bg(const vvi &g, vi &c)
{
  c.assign(g.size(), -1);
  c[0] = 0;
  queue<int> q;
  q.push(0);
  while (q.size())
  {
    int t = q.front();
    q.pop();
    for (int n : g[t])
    {
      if (c[n] == c[t])
        return false;
      if (c[n] == -1)
      {
        c[n] = 1 - c[t];
        q.push(n);
      }
    }
  }
  return true;
}
bool bg(const vvi &g)
{
  vi c;
  return bg(g, c);
}
vi dep(const vvi &g, int s, vi &prev)
{
  queue<int> q;
  vi res(g.size(), INT_MAX);
  prev.resize(g.size());
  prev[s] = -1;
  res[s] = 0;
  q.push(s);
  while (q.size())
  {
    int t = q.front();
    q.pop();
    for (int n : g[t])
      if (chmin(res[n], res[t] + 1))
      {
        q.push(n);
        prev[n] = t;
      }
  }
  return res;
}
vi dep(const vvi &g, int s)
{
  vi prev;
  return dep(g, s, prev);
}
int tdia(const vvi &t)
{
  vi dis = dep(t, 0);
  int s = max_element(ALL(dis)) - dis.begin();
  dis = dep(t, s);
  return *max_element(ALL(dis));
}
int gdia(const vvi &g)
{
  int res = 0;
  rep(i, (int)g.size())
  {
    vi dis = dep(g, i);
    chmax(res, *max_element(ALL(dis)));
  }
  return res;
}
vvi dbling(const vvi &g, const vi &prev, int r = -1)
{
  int n = g.size();
  if (r == -1)
    rep(i, n) if (prev[i] == -1)
    {
      r = i;
      break;
    }
  vvi p(n, vi(30, -1));
  rep(i, n)
  {
    if (i == r)
      continue;
    p[i][0] = prev[i];
  }
  rep(j, 30) rep(i, n)
  {
    int tp = p[i][j];
    if (tp == -1)
      continue;
    p[i][j + 1] = p[tp][j];
  }
  return p;
}
int lca(const vvi &p, const vi &dis, int a, int b)
{
  if (dis[a] > dis[b])
    swap(a, b);
  rep(i, 30)
  {
    if ((dis[b] - dis[a]) >> i & 1)
      b = p[b][i];
  }
  if (a == b)
    return a;
  while (p[a][0] != p[b][0])
  {
    int l = 0, r = 30;
    while (r - l > 1)
    {
      int m = (l + r) / 2;
      if (p[a][m] == p[b][m])
        r = m;
      else
        l = m;
    }
    a = p[a][l];
    b = p[b][l];
  }
  return p[a][0];
}
#pragma endregion graph
#pragma region make
vi mkiota(int n, int s = 0)
{
  vi res(n);
  iota(ALL(res), s);
  return res;
}
vi mkr(const vi &p)
{
  int n = p.size();
  vi r(n);
  rep(i, n) r[p[i]] = i;
  return r;
}
template <typename T>
vector<pair<T, int>> mkvi(vector<T> &v)
{
  int n = v.size();
  vector<pair<T, int>> res(n);
  rep(i, n) res[i] = {v[i], i};
  return res;
}
#pragma endregion make
#pragma region vector
template <typename T>
T vsum(const vector<T> &v)
{
  T sum = 0;
  for (T x : v)
    sum += x;
  return sum;
}
template <typename T>
void distinct(vector<T> &v)
{
  sort(ALL(v));
  v.erase(unique(ALL(v)), v.end());
}
template <typename T>
T vmax(const vector<T> &v) { return *max_element(ALL(v)); }
template <typename T>
T vmin(const vector<T> &v) { return *min_element(ALL(v)); }
template <typename T>
vector<T> comp(vector<T> &a)
{
  vector<T> ret;
  set<T> s;
  rep(i, a.size()) s.insert(a[i]);
  map<T, int> idx;
  int i = 0;
  for (auto x : s)
  {
    idx[x] = i;
    ret.pb(x);
    i++;
  }
  rep(i, a.size()) a[i] = idx[a[i]];
  return ret;
}
#pragma endregion vector
#pragma region util
ostream &operator<<(ostream &os, const mint &x)
{
  os << x.val();
  return os;
}
istream &operator>>(istream &is, mint &x)
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
#pragma endregion util
#pragma endregion library
ll M, N, K, Q, H, W;
string S, T;
const string yes = "Yes", no = "No";
const int dx[9] = {0, 1, 0, -1, 1, 1, -1, -1, 0}, dy[9] = {1, 0, -1, 0, 1, -1, 1, -1, 0};
// const int dx[9]={1,1,0,-1,-1,-1,0,1,0},dy[9]={0,1,1,1,0,-1,-1,-1,0};
bool canmove(int nx, int ny) { return 0 <= nx && nx < H && 0 <= ny && ny < W; }

using tpl = tuple<int,int,int>;
using vt = vector<tpl>;

int main()
{
  fast_io;
  set_mod(mod);
}
