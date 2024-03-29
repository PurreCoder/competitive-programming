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

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    cin >> a;

    string ans = "";
    int i = 0;
    while (i < n)
    {
        if (i) ans += char(43);
        if (a[i] % 2) break;
        ++i;
    }

    if (i == n - 1)
    {
        cout << ans;
        return;
    }

    bool even = false;
    for (int j = i + 1; j < n; ++j)
    {
        if (a[j] % 2 == 0)
        {
            even = true;
            break;
        }
    }

    if (even)
    {
        ans += char(43) + string(n - i - 2, char(120));
    }
    else
    {
        ans += char(120) + string(n - i - 2, char(120));
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
