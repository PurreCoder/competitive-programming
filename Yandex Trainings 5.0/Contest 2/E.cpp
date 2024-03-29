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

void solve()
{
    int n;
    cin >> n;
    vii berries(n);
    for (auto& [a, b] : berries) cin >> a >> b;

    int highest_pos = -1;
    int highest_val = -1;
    for (int i = 0; i < n; ++i) {
        int mn = min(berries[i].first, berries[i].second);
        if (highest_pos == -1 || mn > highest_val)
        {
            highest_pos = i;
            highest_val = mn;
        }
    }

    ll ans = 0;
    vi useless;
    vi certificate;
    for (int i = 0; i < n; ++i)
    {
        if (i != highest_pos)
        {
            auto [a, b] = berries[i];
            if (a > b)
            {
                ans += a - b;
                certificate.push_back(i + 1);
            }
            else
            {
                useless.push_back(i + 1);
            }
        }
        
    }

    certificate.push_back(highest_pos + 1);
    ans += berries[highest_pos].first;

    cout << ans << '\n';
    for (int num : certificate) cout << num << ' ';
    for (int num : useless) cout << num << ' ';
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
