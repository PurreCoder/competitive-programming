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

bool check(vi& indices, vii& pref_minmax, vii& suf_minmax, int width)
{
    auto iter = lower_bound(all(indices), indices[0] + width);
    if (iter == indices.end()) return true;
    int right = iter - indices.begin();
    if (suf_minmax[right].second - suf_minmax[right].first + 1 <= width) return true;

    while (right < indices.size() && indices[right] < indices[1] + width) ++right;

    for (int left = 1; right <= indices.size(); )
    {
        if (right == indices.size()) return pref_minmax[left - 1].second - pref_minmax[left - 1].first + 1 <= width;
        int mx = max(pref_minmax[left - 1].second, suf_minmax[right].second);
        int mn = min(pref_minmax[left - 1].first, suf_minmax[right].first);
        if (mx - mn + 1 <= width) return true;

        ++left;
        while (right < indices.size() && indices[right] < indices[left] + width) ++right;
    }

    return false;
}

void solve()
{
    int w, h, n;
    cin >> w >> h >> n;

    map<int, vi> hor;
    while (n--)
    {
        int x, y;
        cin >> x >> y;
        hor[x].push_back(y);
    }

    for (auto& [k, v] : hor) sort(all(v));

    vii pref_minmax;
    {
        int mn = 2e9, mx = 0;
        for (auto iter = hor.begin(); iter != hor.end(); ++iter)
        {
            mn = min(mn, *(iter->second).begin());
            mx = max(mx, *(iter->second).rbegin());
            pref_minmax.push_back(mp(mn, mx));
        }
    }

    vii suf_minmax;
    {
        int mn = 2e9, mx = 0;
        for (auto iter = hor.rbegin(); iter != hor.rend(); ++iter)
        {
            mn = min(mn, *(iter->second).begin());
            mx = max(mx, *(iter->second).rbegin());
            suf_minmax.push_back(mp(mn, mx));
        }
        reverse(all(suf_minmax));
    }

    vi indices;
    for (auto iter = hor.begin(); iter != hor.end(); ++iter)
    {
        indices.push_back(iter->first);
    }

    int l = 0, r = min(w, h);
    while (r - l > 1)
    {
        int m = (l + r) / 2;
        if (check(indices, pref_minmax, suf_minmax, m))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    cout << r;
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
