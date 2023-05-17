#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <functional>
#include <cmath>
#include <string>
#include <ctime>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <cstring>

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

#define pb push_back
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using ld = long double;

template <typename T>
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int maxx = 1, maxy = 1;

inline ll hashfunc(ll x, ll y)
{
    return (x << 17) | y;
}

using gpt = gp_hash_table<
    ll, ll, custom_hash, equal_to<ll>, direct_mask_range_hashing<>, linear_probe_fn<>,
    hash_standard_resize_policy<hash_exponential_size_policy<>,
                                hash_load_check_resize_trigger<>, true>>;
gpt t;

ll sum(int x, int y)
{
    ll ans = 0;
    for (int i = x; i > 0; i -= i & -i)
    {
        for (int j = y; j > 0; j -= j & -j)
        {
            auto it = t.find(hashfunc(i, j));
            ans += (it != t.end() ? it->second : 0);
        }
    }
    return ans;
}

void inc(int x, int y, ll val)
{
    for (int i = x; i <= maxx; i += i & -i)
    {
        for (int j = y; j <= maxy; j += j & -j)
        {
            t[hashfunc(i, j)] += val;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    vii dots(n);
    int cur_val [(int) 1e5]; // of points weights
    memset(cur_val, '\0', sizeof cur_val);
    vi coordx(n), coordy(n); // for coordinate compression
    for (int i = 0; i < n; ++i)
    {
        cin >> dots[i].first >> dots[i].second >> cur_val[i];
        coordx[i] = dots[i].first;
        coordy[i] = dots[i].second;
    }
    sort(all(coordx));
    sort(all(coordy));
    coordx.erase(unique(all(coordx)), coordx.end());
    coordy.erase(unique(all(coordy)), coordy.end());
    maxx = coordx.size();
    maxy = coordy.size();

    // compression
    for (int u = 0; u < n; ++u)
    {
        dots[u].first = lower_bound(all(coordx), dots[u].first) - coordx.begin() + 1;
        dots[u].second = lower_bound(all(coordy), dots[u].second) - coordy.begin() + 1;
    }

    // adding points
    t = gpt({}, {}, {}, {}, {1 << 23});
    for (int i = 0; i < n; ++i)
    {
        inc(dots[i].first, dots[i].second, cur_val[i]);
    }


    int m;
    cin >> m;
    while (m-- > 0)
    {
        string type;
        int a, b;
        cin >> type >> a >> b;
        if (type[0] == 'g') // get
        {
            a = upper_bound(all(coordx), a) - coordx.begin();
            b = upper_bound(all(coordy), b) - coordy.begin();
            cout << sum(a, b) << '\n';
        }
        else // change
        {
            --a;
            inc(dots[a].first, dots[a].second, b - cur_val[a]);
            cur_val[a] = b;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    FILE* fin;
    freopen_s(&fin, "input.txt", "r", stdin);
    FILE* fout;
    freopen_s(&fin, "output.txt", "w", stdout);
#endif
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
