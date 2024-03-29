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
    int n;
    cin >> n;
    unordered_map<string, int> likes;

    for (int i = 0; i < n; ++i)
    {
        int favs;
        cin >> favs;
        while (favs--)
        {
            string song;
            cin >> song;
            likes[song]++;
        }
    }

    vector<string> ans;
    for (auto [song, props] : likes)
    {
        if (props == n)
        {
            ans.push_back(song);
        }
    }
    sort(all(ans));
    cout << ans.size() << '\n';
    for (string song : ans) cout << song << ' ';
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
