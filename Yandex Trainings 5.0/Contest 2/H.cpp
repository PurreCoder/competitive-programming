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

int get_max_without(vvi&a, int n, int m, int i, int j)
{
    int mx = 0;
    for (int u = 0; u < n; ++u)
    {
        if (u != i)
        {
            for (int v = 0; v < m; ++v)
            {
                if (v != j) mx = max(mx, a[u][v]);
            }
        }
    }
    return mx;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vvi a(n, vi(m));
    int mx = 0;
    int i = 0, j = 0;
    for (int u = 0; u < n; ++u)
    {
        for (int v = 0; v < m; ++v)
        {
            cin >> a[u][v];
            if (a[u][v] > mx)
            {
                mx = a[u][v];
                i = u, j = v;
            }
        }
    }

    int row = 0;
    int row_mx = 0;
    for (int u = 0; u < n; ++u)
    {
        int cur_mx = 0;
        for (int y = 0; y < m; ++y) if (y != j) cur_mx = max(cur_mx, a[u][y]);
        if (cur_mx > row_mx)
        {
            row_mx = cur_mx;
            row = u;
        }
    }

    int col = 0;
    int col_mx = 0;
    for (int u = 0; u < m; ++u)
    {
        int cur_mx = 0;
        for (int y = 0; y < n; ++y) if (y != i) cur_mx = max(cur_mx, a[y][u]);
        if (cur_mx > col_mx)
        {
            col_mx = cur_mx;
            col = u;
        }
    }

    if (get_max_without(a, n, m, row, j) < get_max_without(a, n, m, i, col))
    {
        cout << row + 1 << ' ' << j + 1;
    }
    else
    {
        cout << i + 1 << ' ' << col + 1;
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
