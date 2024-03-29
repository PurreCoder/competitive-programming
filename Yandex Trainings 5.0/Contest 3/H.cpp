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

void solve()
{   
    int n;
    cin >> n;
    vector<pair<ii, ii>> pic1;
    for (int i = 0; i < n; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 < x2 || x1 == x2 && y1 < y2)
        {
            pic1.push_back({ mp(x1, y1), mp(x2, y2) });
        }
        else
        {
            pic1.push_back({ mp(x2, y2), mp(x1, y1) });
        }
    }

    vector<pair<ii, ii>> pic2;
    for (int i = 0; i < n; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 < x2 || x1 == x2 && y1 < y2)
        {
            pic2.push_back({ mp(x1, y1), mp(x2, y2) });
        }
        else
        {
            pic2.push_back({ mp(x2, y2), mp(x1, y1) });
        }
    }

    map<ii, int> matches_for_shift;
    for (auto [p1, p2] : pic1)
    {
        auto [x1, y1] = p1;
        auto [x2, y2] = p2;
        for (auto [p3, p4] : pic2)
        {
            auto [x3, y3] = p3;
            auto [x4, y4] = p4;
            if (x2 - x1 == x4 - x3 && y2 - y1 == y4 - y3)
            {
                matches_for_shift[mp(x3 - x1, y3 - y1)]++;
            }
        }
    }
    
    int ans = n;
    for (auto [shift, cnt] : matches_for_shift)
    {
        ans = min(ans, n - cnt);
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
