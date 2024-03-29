#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <stack>
#include <iomanip>
#include "inttypes.h"
#include <sstream>
#include <climits>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)

using ld = long double;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;

template <typename T>
istream& operator>>(istream& in, vector<T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 31 + v.second;
    }
};

vii build_by_side(unordered_set<ii, pair_hash>& pts, int x, int y, int xd, int yd)
{
    int dx = xd - x;
    int dy = yd - y;

    vii res;

    while (xd != x || yd != y)
    {
        swap(dx, dy);
        dx = -dx;
        xd += dx, yd += dy;

        //if (abs(x) > int(1e9) || abs(y) > int(1e9)) return vii(6);

        if (!pts.contains(mp(xd, yd)))
        {
            res.push_back(mp(xd, yd));
        }
    }

    return res;
}

vii build_by_diagonal(unordered_set<ii, pair_hash>& pts, int x, int y, int xd, int yd)
{
    if ((xd + yd - x - y) % 2) return vii(6);

    int dx = xd - x;
    int dy = yd - y;

    if ((dx % 2 + dy % 2) % 2) return vii(6);

    vii res;

    if (dy < 0)
    {
        int a = (dx - dy) / 2;
        int b = (-dx - dy) / 2;
        if (!pts.contains(mp(x - b, y - a))) res.pb(mp(x - b, y - a));
        if (!pts.contains(mp(x + a, y - b))) res.pb(mp(x + a, y - b));
    }
    else
    {
        int a = (dx + dy) / 2;
        int b = (dx - dy) / 2;
        if (!pts.contains(mp(x + b, y + a))) res.pb(mp(x + b, y + a));
        if (!pts.contains(mp(x + a, y - b))) res.pb(mp(x + a, y - b));

    }

    return res;
}

void solve()
{
    int n;
    cin >> n;
    unordered_set<ii, pair_hash> pts;
    
    while (n--)
    {
        int x, y;
        cin >> x >> y;
        pts.insert({ x, y });
    }

    vii ans;
    {
        // init ans with random point
        auto [x, y] = *pts.begin();
        ans = { mp(x + 1, y), mp(x, y + 1), mp(x + 1, y + 1) };
    }

    for (auto [x, y] : pts)
    {
        for (auto [xd, yd] : pts)
        {
            if (x < xd)
            {
                // building square on square side
                vii res = build_by_side(pts, x, y, xd, yd);
                if (res.size() < ans.size()) ans = res;
                res = build_by_side(pts, xd, yd, x, y);
                if (res.size() < ans.size()) ans = res;

                // building square on square diagonal
                res = build_by_diagonal(pts, x, y, xd, yd);
                if (res.size() < ans.size()) ans = res;
            }
        }
    }

    cout << ans.size() << '\n';
    for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
        //cout << '\n';
    }
    return 0;
}
