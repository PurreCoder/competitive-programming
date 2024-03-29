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
    unordered_set<string> shorts;
    {
        string input;
        getline(cin, input);
        istringstream in(input);

        string st;
        while (in >> st)
        {
            shorts.insert(st);
        }
    }
    
    string st;
    while (cin >> st)
    {
        bool success = false;
        string short_copy = "";
        for (int i = 0; i < min((int) st.length(), 100); ++i)
        {
            short_copy += st[i];
            if (shorts.find(short_copy) != shorts.end())
            {
                success = true;
                cout << short_copy << ' ';
                break;
            }
        }
        if (!success)
        {
            cout << st << ' ';
        }
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
