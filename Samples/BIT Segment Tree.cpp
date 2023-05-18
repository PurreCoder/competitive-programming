#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <cmath>
#include <string>
#include <ctime>
#include <chrono>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using ld = long double;

template <typename T>
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

struct Segtree
{
    struct Node
    {
        vii a;
        vll t;
        vll coords;
        int maxy;

        void build()
        {
            sort(all(a));
            for (auto& [y, w] : a)
            {
                coords.push_back(y);
            }
            coords.erase(unique(all(coords)), coords.end());
            maxy = coords.size();
            t.resize(maxy + 1, 0);
            /*for (int i = 0; i < a.size(); ++i)
            {
                int ind = lower_bound(all(coords), a[i].first) - coords.begin() + 1;
                t[ind] += a[i].second;
                if (ind + (ind & -ind) <= t.size())
                {
                    t[ind + (ind & -ind)] += t[ind];
                }
            }*/
            for (int i = 0; i < a.size(); ++i)
            {
                inc(a[i].first, a[i].second);
            }
        }

        ll sum(int y)
        {
            y = upper_bound(all(coords), y) - coords.begin();
            ll ans = 0;
            for (int i = y; i > 0; i -= i & -i)
            {
                ans += t[i];
            }
            return ans;
        }

        void inc(int y, ll val)
        {
            y = lower_bound(all(coords), y) - coords.begin() + 1;
            for (int i = y; i <= maxy; i += i & -i)
            {
                t[i] += val;
            }
        }
    };

    const Node ZERO = { vii(), vll() };

    vector<Node> tree;
    int length;

    void init(int n)
    {
        length = 1;
        while (length < n)
            length <<= 1;
        tree.assign(2 * length - 1, ZERO);
    }

    void build(vector<vii>& a, int x, int lx, int rx)
    {
        if (lx + 1 == rx)
        {
            if (lx < a.size())
            {
                tree[x] = { a[lx], vll() };
                tree[x].build();
            }
        }
        else
        {
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            merge(tree[2 * x + 1].a.begin(), tree[2 * x + 1].a.end(), tree[2 * x + 2].a.begin(), tree[2 * x + 2].a.end(),
                back_inserter(tree[x].a));
            tree[x].build();
        }
    }

    Segtree(vector<vii>& a)
    {
        init(a.size());
        build(a, 0, 0, length);
    }

    Segtree(int n)
    {
        init(n);
    }

    void add(int pos_x, int pos_y, int val, int x, int lx, int rx)
    {
        tree[x].inc(pos_y, val);
        if (lx + 1 == rx)
        {
            return;
        }
        int m = (lx + rx) / 2;
        if (pos_x < m)
        {
            add(pos_x, pos_y, val, 2 * x + 1, lx, m);
        }
        else
        {
            add(pos_x, pos_y, val, 2 * x + 2, m, rx);
        }
    }

    void add(int pos_x, int pos_y, int val)
    {
        add(pos_x, pos_y, val, 0, 0, length);
    }

    ll calc(int X, int Y, int v, int lx, int rx)
    {
        if (lx >= rx || lx > X)
        {
            return 0;
        }
        if (rx <= X + 1)
        {
            return tree[v].sum(Y);
        }
        int m = (lx + rx) / 2;
        ll s1 = calc(X, Y, 2 * v + 1, lx, m);
        ll s2 = calc(X, Y, 2 * v + 2, m, rx);
        return s1 + s2;
    }

    ll calc(int X, int Y)
    {
        return calc(X, Y, 0, 0, length);
    }
};

void solve()
{
    int n;
    cin >> n;
    vii dots(n);
    vi cur_val(n); // of points weights
    vi coordx(n), coordy(n); // for coordinate compression
    for (int i = 0; i < n; ++i)
    {
        cin >> dots[i].first >> dots[i].second >> cur_val[i];
        coordx[i] = dots[i].first;
        coordy[i] = dots[i].second;
    }
    sort(all(coordx));
    sort(all(coordy));
    coordx.erase(unique(all(coordx)), coordx.end());
    coordy.erase(unique(all(coordy)), coordy.end());
    int maxx = coordx.size();
    int maxy = coordy.size();

    // compression
    for (int u = 0; u < n; ++u)
    {
        dots[u].first = lower_bound(all(coordx), dots[u].first) - coordx.begin();
        dots[u].second = lower_bound(all(coordy), dots[u].second) - coordy.begin() + 1;
    }

    // adding points
    vector<vii> dots_by_x(maxx);
    for (int i = 0; i < n; ++i)
    {
        dots_by_x[dots[i].first].push_back({ dots[i].second, cur_val[i] });
    }
    Segtree seg(dots_by_x);

    int m;
    cin >> m;
    while (m--)
    {
        string type;
        int a, b;
        cin >> type >> a >> b;
        if (type[0] == 'g') // get
        {
            a = upper_bound(all(coordx), a) - coordx.begin() - 1;
            b = upper_bound(all(coordy), b) - coordy.begin();
            cout << seg.calc(a, b) << '\n';
        }
        else // change
        {
            --a;
            seg.add(dots[a].first, dots[a].second, b - cur_val[a]);
            cur_val[a] = b;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
