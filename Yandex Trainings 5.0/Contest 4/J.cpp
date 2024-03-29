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

ld volume_for_level(vii& pts, int l, int r, ld level)
{
    ld cur_volume = 0;
    for (int i = l + 1; i < r; ++i)
    {
        auto [x1, y1] = pts[i - 1];
        auto [x2, y2] = pts[i];
        if (level >= max(y1, y2))
        {
            cur_volume += (level - (y1 + y2) / 2.0) * (x2 - x1);
        }
        else
        {
            if (level > min(y1, y2))
            {
                ld lvl = level - min(y1, y2);
                cur_volume += (x2 - x1) * lvl * lvl / (2 * abs(y2 - y1));
            }
        }
        
    }
    return cur_volume;
}

ld find_level(vii& pts, ld h, int l, int r)
{
    ld left = -10001, right = 1e9 + 10001;
    const ld eps = 1e-8;
    int oper = ceill(log2l(right - left) - log2l(eps));
    ld volume = h * (pts[r - 1].first - pts[l].first);
    for (int i = 0; i < oper && right - left > eps; ++i)
    {
        ld middle = (left + right) / 2;
        if (volume_for_level(pts, l, r, middle) >= volume)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }
    return right;
}

bool is_whole_reservoir(vii& pts, ld h, int l, int r)
{
    if (r - l <= 2) return true;

    // pinnacle dividing reservoir in two (if exists)
    int max_idx = -1;
    for (int i = l + 1; i < r - 1; ++i)
    {
        if (pts[i - 1].second < pts[i].second && pts[i].second > pts[i + 1].second && (max_idx == -1 || pts[max_idx].second < pts[i].second))
        {
            max_idx = i;
        }
    }
    if (max_idx == -1) return true;

    ld height = find_level(pts, h, l, r); // level of water if [l; r) was one whole reservoir

    return height >= pts[max_idx].second;
}

ld can_borrow(vii& pts, ld h, int l, int r, ld pinnacle)
{
    ld left = 0, right = (find_level(pts, h, l, r) - pinnacle) * (pts[r - 1].first - pts[l].first) + 1;
    const ld eps = 1e-5;
    int oper = ceil(log(right - left) - log2(eps));
    for (int i = 0; i < oper && right - left > eps; ++i)
    {
        ld middle = (left + right) / 2;
        if (find_level(pts, h - middle / (pts[r - 1].first - pts[l].first), l, r) >= pinnacle)
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }
    return left;
}

ld find_max_height(vii& pts, ld h, int l, int r, ld add_left, ld add_right)
{
    if (r - l <= 1) return 0;

    ld layer = (add_left + add_right) / (pts[r - 1].first - pts[l].first);
    if (is_whole_reservoir(pts, h + layer, l, r)) // [l; r) - one whole reservoir
    {
        return find_level(pts, h + layer, l, r) - min_element(pts.begin() + l, pts.begin() + r,
            [](ii lhs, ii rhs) {
                return lhs.second < rhs.second;
            }
        )->second;
    }
    else // max_ind splits reservoir into two
    {
        int max_idx = -1;
        for (int i = l + 1; i < r - 1; ++i)
        {
            if (pts[i - 1].second < pts[i].second && pts[i].second > pts[i + 1].second && (max_idx == -1 || pts[max_idx].second < pts[i].second))
            {
                max_idx = i;
            }
        }

        ld layer_left = add_left / (pts[max_idx].first - pts[l].first);
        ld left_level = find_level(pts, h + layer_left, l, max_idx + 1);
        ld layer_right = add_right / (pts[r - 1].first - pts[max_idx].first);
        ld right_level = find_level(pts, h + layer_right, max_idx, r);
        ld pinnacle = pts[max_idx].second;

        // overfill l -> r
        if (left_level > pinnacle)
        {
            ld add = can_borrow(pts, h + layer_left, l, max_idx + 1, pinnacle);
            ld right_height = find_max_height(pts, h, max_idx, r, add, add_right);
            ld sub = max(min(add, add_left), ld(0));
            add -= sub;
            add_left -= sub;
            ld left_height = find_max_height(pts, h, l, max_idx + 1, add_left, -add);
            return max(left_height, right_height);
        }
        
        // overfill l <- r
        if (right_level > pinnacle)
        {
            ld add = can_borrow(pts, h + layer_right, max_idx, r, pinnacle);
            ld left_height = find_max_height(pts, h, l, max_idx + 1, add_left, add);
            ld sub = max(min(add, add_right), ld(0));
            add -= sub;
            add_right -= sub;
            ld right_height = find_max_height(pts, h, max_idx, r, -add, add_right);
            return max(left_height, right_height);
        }

        // no overfill
        ld left_height = find_max_height(pts, h, l, max_idx + 1, add_left, 0);
        ld right_height = find_max_height(pts, h, max_idx, r, 0, add_right);
        return max(left_height, right_height);
    }
}

void solve()
{
    int n;
    ld h;
    cin >> n >> h;
    cin.get();

    vii pts(n + 1);
    for (auto& [x, y] : pts)
    {
        string in = "";
        getline(cin, in);
        for (int o = 0; o < 2; ++o)
        {
            int pos = in.find("–");
            if (pos == -1) break;
            in.replace(pos, 1, "-");
        }
        istringstream is(in);
        is >> x >> y;
    }

    cout << fixed << setprecision(6) << find_max_height(pts, h, 0, n + 1, 0, 0);
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
