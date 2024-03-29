#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <stack>
#include <iomanip>
#include "inttypes.h"

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
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

ld dist(ll x, ll v, ll L, ld t)
{
    ld pos = x + v * t;
    ld k = floorl(pos / L);
    pos = pos - k * L;
    return std::min(pos, L - pos);
}

bool equals(ld a, ld b)
{
    return abs(a - b) <= 1e-9;
}

void solve()
{
    ll L, x1, v1, x2, v2;
    cin >> L >> x1 >> v1 >> x2 >> v2;

    if (equals(dist(x1, v1, L, 0), dist(x2, v2, L, 0)))
    {
        cout << "YES\n";
        cout << std::fixed << std::setprecision(12) << 0.0;
        return;
    }

    if (v1 == 0 && v2 == 0)
    {
        cout << "NO";
        return;
    }

    vector<ld> times;
    
    if (v1 != v2)
    {
        ll dx = x2 - x1;
        ll dv = v1 - v2;
        if (dv < 0)
        {
            dv *= -1;
            dx *= -1;
        }
        ld k = floorl(ld(dx) / L);
        ld T = ld(dx - L * k) / dv;
        if (equals(dist(x1, v1, L, T), dist(x2, v2, L, T)))
        {
            times.push_back(T);
        }
    }

    if (v1 + v2)
    {
        ll dx = L + x1 + x2;
        ll dv = v1 + v2;
        if (dv < 0)
        {
            dv *= -1;
            dx *= -1;
        }
        ld k = ceill(ld(dx) / (2 * L));
        ld T = ld(2 * L * k - dx) / dv;
        if (equals(dist(x1, v1, L, T), dist(x2, v2, L, T)))
        {
            times.push_back(T);
        }
    }

    if (v1 + v2)
    {
        ll dx = x1 + x2;
        ll dv = v1 + v2;
        if (dv < 0)
        {
            dv *= -1;
            dx *= -1;
        }
        ld k = ceill(ld(dx) / (2 * L));
        ld T = ld(2 * L * k - dx) / dv;
        if (equals(dist(x1, v1, L, T), dist(x2, v2, L, T)))
        {
            times.push_back(T);
        }
    }

    if (times.empty())
    {
        cout << "NO";
    }
    else
    {
        cout << "YES\n" << std::fixed << std::setprecision(12) << *min_element(all(times));
    }
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
