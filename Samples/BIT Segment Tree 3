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
            maxy = coords.size();
            t.resize(maxy + 1, 0);
            int pos = 1;
            for (int i = 0; i < a.size(); ++i)
            {
                if (pos < maxy && coords[pos] <= a[i].first)
                {
                    if (pos + (pos & -pos) < t.size())
                    {
                        t[pos + (pos & -pos)] += t[pos];
                    }
                    ++pos;
                }
                t[pos] += a[i].second;
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

    int n;
    vector<Node> tree;

    Segtree(vector<vii>& a)
    {
        n = a.size();
        tree.resize(2 * n);
        tree.shrink_to_fit();
        for (int i = n - 1; i >= 0; --i)
        {
            tree[i + n].a = a[i];
            for (auto [y, w] : a[i])
            {
                tree[i + n].coords.push_back(y);
            }
            tree[i + n].coords.erase(unique(all(tree[i + n].coords)), tree[i + n].coords.end());
            tree[i + n].build();
            if ((i + n) & 1)
            {
                move(all(tree[i + n].a), back_inserter(tree[(i + n) >> 1].a)); 
            }
            else
            {
                int pos = tree[(i + n) >> 1].a.size();
                move(all(tree[i + n].a), back_inserter(tree[(i + n) >> 1].a));
                inplace_merge(tree[(i + n) >> 1].a.begin(), tree[(i + n) >> 1].a.begin() + pos, tree[(i + n) >> 1].a.end());
            }
        }
        for (int i = n - 1; i > 0; --i)
        {
            set_union(all(tree[i << 1].coords), all(tree[i << 1 | 1].coords), back_inserter(tree[i].coords));
            tree[i].build();
            if (i != 1)
            {
                if (i & 1)
                {
                    move(all(tree[i].a), back_inserter(tree[i >> 1].a));
                }
                else
                {
                    int pos = tree[i >> 1].a.size();
                    move(all(tree[i].a), back_inserter(tree[i >> 1].a));
                    inplace_merge(tree[i >> 1].a.begin(), tree[i >> 1].a.begin() + pos, tree[i >> 1].a.end());
                }
            }
        }
    }

    void add(int pos_x, int pos_y, int val)
    {
        tree[pos_x += n].inc(pos_y, val);
        for (; pos_x > 1; pos_x >>= 1)
        {
            tree[pos_x >> 1].inc(pos_y, val);
        }
    }

    ll query(int X, int Y)
    {
        int l = 0, r = X + 1;
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) res += tree[l++].sum(Y);
            if (r & 1) res += tree[--r].sum(Y);
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vii dots(n);
    vi cur_val(n); // of points weights
    vi coordx(n); // for coordinate compression
    for (int i = 0; i < n; ++i)
    {
        cin >> dots[i].first >> dots[i].second >> cur_val[i];
        coordx[i] = dots[i].first;
    }
    sort(all(coordx));
    coordx.erase(unique(all(coordx)), coordx.end());
    int maxx = coordx.size();

    // compression
    for (int u = 0; u < n; ++u)
    {
        dots[u].first = lower_bound(all(coordx), dots[u].first) - coordx.begin();
    }

    // adding points
    vector<vii> dots_by_x(maxx);
    for (int i = 0; i < n; ++i)
    {
        dots_by_x[dots[i].first].push_back({ dots[i].second, cur_val[i] });
    }
    for (auto& vi : dots_by_x)
    {
        sort(all(vi));
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
            cout << seg.query(a, b) << '\n';
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
