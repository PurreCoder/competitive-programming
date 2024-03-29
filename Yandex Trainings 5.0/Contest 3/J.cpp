#define _CRT_SECURE_NO_WARNINGS

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
    int n, k;
    cin >> n >> k;

    int remaining = n - 1;
    vi ans(n);
    vi cnt(k);
    vi progress(n);
    progress[0] = k;
    vvi credit(n, vi(n));
    vector<vector<char>> loaded(n, vector<char>(k, false));
    fill(all(loaded[0]), true);

    vii parts_by_rarity(k);
    vii devices_by_progress(n);
    for (int t = 1; remaining; ++t)
    {
        for (int j = 0; j < k; ++j)
        {
            parts_by_rarity[j] = { cnt[j], j };
        }
        sort(all(parts_by_rarity));

        for (int j = 0; j < n; ++j)
        {
            devices_by_progress[j] = {progress[j], j};
        }
        sort(all(devices_by_progress));

        unordered_map<int, vi> requests_for_part;
        for (int device = 1; device < n; ++device)
        {
            if (ans[device] == 0)
            {
                for (auto& [cnt, part] : parts_by_rarity)
                {
                    if (!loaded[device][part])
                    {
                        requests_for_part[part].push_back(device);
                        break;
                    }
                }
            }
        }

        unordered_map<int, ii> requested; // <K, <D, P>> K is asked for part, D is device that asked, P is part
        for (auto& [part, contesters] : requests_for_part)
        {
            for (auto [rate, transmitter] : devices_by_progress)
            {
                if (loaded[transmitter][part])
                {
                    int precious = contesters[0];

                    auto update_precious{ [&](int precious, int other) {
                        if (credit[transmitter][precious] < credit[transmitter][other])
                        {
                            return true;
                        }
                        if (credit[transmitter][precious] > credit[transmitter][other]) return false;
                        if (progress[other] < progress[precious])
                        {
                            return true;
                        }
                        if (progress[precious] < progress[other]) return false;
                        if (other < precious)
                        {
                            return true;
                        }
                        return false;
                    }};

                    for (int other : contesters)
                    {
                        if (update_precious(precious, other))
                        {
                            precious = other;
                        }
                    }

                    if (!requested.contains(transmitter))
                    {
                        requested[transmitter] = {precious, part};
                    }
                    else
                    {
                        if (update_precious(requested[transmitter].first, precious))
                        {
                            requested[transmitter] = { precious, part };
                        }
                    }
                    break;
                }
            }
        }

        for (auto [transmitter, dest] : requested)
        {
            auto [device, part] = dest;
            loaded[device][part] = true;
            cnt[part]++;
            credit[device][transmitter]++;
            if (++progress[device] == k)
            {
                ans[device] = t;
                --remaining;
            }
        }
    }

    for (int i = 1; i < n; ++i)
    {
        cout << ans[i] << ' ';
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
