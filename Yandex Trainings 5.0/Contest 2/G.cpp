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
    vi a(n);
    cin >> a;

    vi ans;
    int cur_len = 1;
    int len = a[0];
    for (int i = 1; i < n; ++i)
    {
        if (cur_len >= len)
        {
            ans.push_back(cur_len);
            len = a[i];
            cur_len = 1;
        }
        else
        {
            if (a[i] < len)
            {
                if (a[i] < cur_len + 1)
                {
                    ans.push_back(cur_len);
                    len = a[i];
                    cur_len = 1;
                }
                else
                {
                    len = a[i];
                    ++cur_len;
                }
            }
            else
            {
                ++cur_len;
            }
        }
    }
    ans.push_back(cur_len);

    cout << ans.size() << '\n';
    for (int num : ans) cout << num << ' ';
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
        cout << '\n';
    }
    return 0;
}
