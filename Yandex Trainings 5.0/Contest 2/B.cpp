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

const int MAXN = 10001;
int lg[MAXN];

vvi sparse_table(vi& a)
{
    lg[1] = 0;
    for (int i = 2; i < MAXN; ++i)
    {
        lg[i] = lg[i / 2] + 1;
    }

    int n = a.size();
    int k = lg[n];
    vvi st(k + 1, vi(n));

    for (int u = 0; u < n; ++u)
    {
        st[0][u] = a[u];
    }
    for (int j = 1; j <= k; ++j)
    {
        for (int i = 0; i + (1 << j) <= n; ++i)
        {
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        }
    }
    return st;
}

int get_min(vvi& st, int l, int r)
{
    int j = lg[r - l + 1];
    return min(st[j][l], st[j][r - (1 << j) + 1]);
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vi a(n);
    cin >> a;

    int profit = 0;
    vvi st = sparse_table(a);
    for (int i = 1; i < n; ++i) // day to sell
    {
        profit = std::max(profit, a[i] - get_min(st, std::max(i - k, 0), i - 1));
    }
    cout << profit;
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
