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

bool point_fits_delay(vector<pair<ii, int>>& players, ld delay, pair<ld, ld> point)
{
    const ld EPS = 1e-6;
    auto [x, y] = point;
    for (auto [pp, v] : players)
    {
        auto [px, py] = pp;
        if ((px - x) * (px - x) + (py - y) * (py - y) + EPS < v * v * delay * delay)
        {
            return false;
        }
    }
    return true;
}

vector<pair<ld, ld>> circle_and_line_intersection(ld a, ld b, ld c, ld r)
{
    const ld EPS = 1e-6;
    ld x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        return vector<pair<ld, ld>>();
    else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        return vector<pair<ld, ld>>{ mp(x0, y0) };
    }
    else {
        ld d = r * r - c * c / (a * a + b * b);
        ld mult = sqrt(d / (a * a + b * b));
        ld ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        return vector<pair<ld, ld>>{mp(ax, ay), mp(bx, by)};
    }
}

vector<pair<ld, ld>> circle_intersection(int x1, int y1, ld r1, int x2, int y2, ld r2)
{
    x2 -= x1;
    y2 -= y1;
    auto res = circle_and_line_intersection(-2 * x2, -2 * y2, x2 * x2 + y2 * y2 + r1 * r1 - r2 * r2, r1);
    for (auto& [x, y] : res)
    {
        x += x1;
        y += y1;
    }
    return res;
}

bool can_produce_delay(vector<pair<ii, int>>& players, int max_distance, ld delay)
{
    int n = players.size();
    for (int i = 0; i < n; ++i)
    {
        auto [x1, y1] = players[i].first;
        ld r1 = players[i].second * delay;
        for (int j = i + 1; j < n; ++j)
        {
            auto [x2, y2] = players[j].first;
            ld r2 = players[j].second * delay;
            for (auto [x, y] : circle_intersection(x1, y1, r1, x2, y2, r2))
            {
                if (x * x + y * y <= max_distance * max_distance)
                {
                    if (y >= 0 && point_fits_delay(players, delay, mp(x, y))) return true;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        auto [x1, y1] = players[i].first;
        ld r1 = players[i].second * delay;
        for (auto [x, y] : circle_intersection(0, 0, max_distance, x1, y1, r1))
        {
            if (y >= 0 && point_fits_delay(players, delay, mp(x, y))) return true;
        }
    }

    for (auto [x, y] : { mp(max_distance, 0), mp(-max_distance, 0), mp(0, max_distance), mp(0, 0) })
    {
        if (point_fits_delay(players, delay, mp(x, y)))
        {
            return true;
        }
    }

    return false;
}

void print_point_to_throw(vector<pair<ii, int>>& players, int max_distance, ld delay)
{
    int n = players.size();
    for (int i = 0; i < n; ++i)
    {
        auto [x1, y1] = players[i].first;
        ld r1 = players[i].second * delay;
        for (int j = i + 1; j < n; ++j)
        {
            auto [x2, y2] = players[j].first;
            ld r2 = players[j].second * delay;
            for (auto [x, y] : circle_intersection(x1, y1, r1, x2, y2, r2))
            {
                if (y >= 0 && x * x + y * y <= max_distance * max_distance)
                {
                    if (point_fits_delay(players, delay, mp(x, y)))
                    {
                        cout << fixed << setprecision(5) << x << ' ' << y;
                        return;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        auto [x1, y1] = players[i].first;
        ld r1 = players[i].second * delay;
        for (auto [x, y] : circle_intersection(0, 0, max_distance, x1, y1, r1))
        {
            if (y >= 0 && point_fits_delay(players, delay, mp(x, y)))
            {
                cout << fixed << setprecision(5) << x << ' ' << y;
                return;
            }
        }
    }

    for (auto [x, y] : { mp(max_distance, 0), mp(-max_distance, 0), mp(0, max_distance), mp(0, 0)})
    {
        if (point_fits_delay(players, delay, mp(x, y)))
        {
            cout << fixed << setprecision(5) << x << ' ' << y;
            return;
        }
    }
}

void solve()
{
    int max_distance, n;
    cin >> max_distance >> n;

    vector<pair<ii, int>> players(n);
    for (auto& [coords, velocity] : players)
    {
        cin >> coords.first >> coords.second >> velocity;
    }

    ld l = 0, r = sqrt(5) * 1000 + 1;
    const ld eps = 1e-9;
    int oper = ceil(log2((r - l) / eps));
    for (int i = 0; i < oper && r - l > eps; ++i)
    {
        ld m = (l + r) / 2;
        if (can_produce_delay(players, max_distance, m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }
    
    cout << fixed << setprecision(5) << l << '\n';
    print_point_to_throw(players, max_distance, l);
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
