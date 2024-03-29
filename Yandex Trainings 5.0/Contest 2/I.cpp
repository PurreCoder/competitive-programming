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
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

int dist(int ship_x, int ship_y, int dest_x, int dest_y)
{
    return abs(dest_x - ship_x) + abs(dest_y - ship_y);
}

int move_to_col(vii& ships, int col)
{
    int n = ships.size();
    int res = 0;
    for (int row = 1; row <= n; ++row)
    {
        res += dist(ships[row - 1].first, ships[row - 1].second, row, col);
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vii ships(n);
    for (auto& [a, b] : ships) cin >> a >> b;

    int ans = INT_MAX;
    for (int col = 1; col <= n; ++col)
    {
        sort(all(ships), [&](ii lhs, ii rhs) {
            if (lhs.first < rhs.first) return true;
            if (lhs.first > rhs.first) return false;
            if (abs(lhs.second - col) < abs(rhs.second - col)) return true;
            return false;
            });
        ans = min(ans, move_to_col(ships, col));
    }
    cout << ans;
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
