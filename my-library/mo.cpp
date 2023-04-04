#include <bits/stdc++.h>

namespace my_lib
{
    struct Mo
    {
        Mo(int n = 0) : n(n){};
        void add(int l, int r)
        {
            lr.emplace_back(l, r);
            if (r > n)
                n = r;
        }
        template <typename AL, typename AR, typename EL, typename ER, typename O>
        void solve(AL &al, AR &ar, EL &el, ER &er, O &out)
        {
            int q = (int)lr.size();
            int bs = n / std::min<int>(n, sqrt(q));
            std::vector<int> ord(q);
            std::iota(ord.begin(), ord.end(), 0);
            std::sort(ord.begin(), ord.end(), [&](int l, int r)
                      { int lb = lr[l].first / bs, rb = lr[r].first / bs;
                      if (lb!=rb)return lb<rb;
                      if(lb&1)return lr[l].second>lr[r].second;
                      return lr[l].second<lr[r].second; });
            int l = 0, r = 0;
            for (int idx : ord)
            {
                auto [ql, qr] = lr[idx];
                while (l > ql)
                    al(--l);
                while (r < qr)
                    ar(r++);
                while (l < ql)
                    el(l++);
                while (r > qr)
                    er(--r);
                out(idx);
            }
        }

        template <typename A, typename E, typename O>
        void solve(A &add, E &erase, O &out)
        {
            solve(add, add, erase, erase, out);
        }

    private:
        int n;
        std::vector<std::pair<int, int>> lr;
    };
}
