#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <deque>

using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;

template <typename T>
istream& operator>>(istream& in, vector <T>& arr)
{
    for (T& i : arr) in >> i;
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, vector <T>& arr)
{
    for (T& i : arr) out << i << ' ';
    out << '\n';
    return out;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vii cameras(k);
    for (auto& [l, r]: cameras)
    {
        cin >> l >> r;
        --l; --r;
    }

    vi cnt(n); // cameras covering the section
    int ind = 0;
    for (int j = 0; j < k; ++j)
    {
        for (int u = cameras[j].first; u <= cameras[j].second; ++u)
        {
            ++cnt[u];
        }
    }

    int ans = 0;
    for (int i = 0; i < k; ++i) // first camera to remove
    {
        vi one_camera = cnt;
        for (int u = cameras[i].first; u <= cameras[i].second; ++u)
        {
            --one_camera[u];
        }

        int covered = 0;
        for (int& x : one_camera)
        {
            covered += (x != 0);
            x = (x == 1);
        }

        vi pref(one_camera.size() + 1);
        for (int u = 1; u <= one_camera.size(); ++u)
        {
            pref[u] = pref[u - 1] + one_camera[u - 1];
        }

        for (int j = i + 1; j < k; ++j) // second camera to remove
        {
            int r = cameras[j].second;
            int l = cameras[j].first;
            ans = max(ans, covered - (pref[r + 1] - pref[l]));
        }
    }
    cout << ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    #ifndef ONLINE_JUDGE
        FILE* fin;
        freopen_s(&fin, "input.txt", "r", stdin);
    #endif
    int t = 1;
    //cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
