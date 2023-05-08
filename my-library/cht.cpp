#include <bits/stdc++.h>

namespace my_lib
{
  using ll = long long;
  template <typename Comp = std::less<ll>>
  struct CHT
  {
    CHT()
    {
      s.insert({L(INF, 0), L(-INF, 0)});
      c.insert(CP(L(INF, 0), L(-INF, 0)));
    }
    void add(ll a, ll b)
    {
      const L p(a, b);
      It pos = s.insert(p).first;
      if (!need(*prev(pos), p, *next(pos)))
      {
        // 直線(a,b)が不要
        s.erase(pos);
        return;
      }
      c.erase(CP(*prev(pos), *next(pos)));
      {
        // 左側の削除
        It it = prev(pos);
        while (it != s.begin() && !need(*prev(it), *it, p))
          --it;
        cerase(it, prev(pos));
        s.erase(++it, pos);
        pos = s.find(p);
      }
      {
        // 右側の削除
        It it = next(pos);
        while (next(it) != s.end() && !need(p, *it, *next(it)))
          ++it;
        cerase(++pos, it);
        s.erase(pos, it);
        pos = s.find(p);
      }
      c.insert(CP(*prev(pos), *pos));
      c.insert(CP(*pos, *next(pos)));
    }
    ll query(ll x)
    {
      const L &p = (--c.lower_bound(CP(x, 1, L(0, 0))))->p;
      return p.a * x + p.b;
    }

  private:
    struct L
    {
      ll a, b;
      L(ll a, ll b) : a(a), b(b) {}
      bool operator<(const L &rhs) const
      {
        return a != rhs.a ? comp(rhs.a, a) : comp(b, rhs.b);
      }
    };
    struct CP
    {
      ll n, d;
      L p;
      CP(ll _n, ll _d, const L &p) : n(_n), d(_d), p(p)
      {
        if (d < 0)
        {
          n *= -1;
          d *= -1;
        }
      }
      CP(const L &p1, const L &p2) : CP(p1.b - p2.b, p2.a - p1.a, p2)
      {
        if (abs(p1.a) == INF)
        {
          this->n = -INF;
          this->d = 1;
          return;
        }
        if (abs(p2.a) == INF)
        {
          this->n = INF;
          this->d = 1;
          return;
        }
      }
      bool operator<(const CP &rhs) const
      {
        if (abs(n) == INF || abs(rhs.n) == INF)
          return n < rhs.n;
        return n * rhs.d < rhs.n * d;
      }
    };

    typedef typename std::set<L>::iterator It;
    It next(It a) { return ++a; }
    It prev(It a) { return --a; }
    void cerase(It a, It b)
    {
      for (It it = a; it != b; ++it)
        c.erase(CP(*it, *next(it)));
    }
    bool need(const L &p1, const L &p2, const L &p3)
    {
      if (p1.a == p2.a && !comp(p2.b, p1.b))
        return false;
      if (abs(p1.a) == INF || abs(p3.a) == INF)
        return true;
      return (p2.a - p1.a) * (p3.b - p2.b) < (p2.b - p1.b) * (p3.a - p2.a);
    }

    std::set<L> s;
    std::set<CP> c;
    static const ll INF = 2e18;
    static const Comp comp;
  };
}
