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
istream& operator>>(istream& in, vector<T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

void solve()
{
    unordered_map<int, int> mark;

    for (int t = 0; t < 3; ++t)
    {
        int n;
        cin >> n;
        while (n--)
        {
            int num;
            cin >> num;
            mark[num] |= (1 << t);
        }
    }

    vi ans;
    for (auto [num, cnt] : mark)
    {
        if (((cnt & 1) != 0) + ((cnt & 2) != 0) + ((cnt & 4) != 0) >= 2)
        {
            ans.push_back(num);
        }
    }
    sort(all(ans));
    for (int num : ans) cout << num << ' ';
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
