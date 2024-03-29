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

map<string, int> leap_year_days {
    {"January", 31},
    {"February", 29},
    {"March", 31},
    {"April", 30},
    {"May", 31},
    {"June", 30},
    {"July", 31},
    {"August", 31},
    {"September", 30},
    {"October", 31},
    {"November", 30},
    {"December", 31}
};

map<string, int> nonleap_year_days = {
    {"January", 31},
    {"February", 28},
    {"March", 31},
    {"April", 30},
    {"May", 31},
    {"June", 30},
    {"July", 31},
    {"August", 31},
    {"September", 30},
    {"October", 31},
    {"November", 30},
    {"December", 31}
};

const vector<string> months = { "January", "February", "March", "April", "May",
                                "June", "July", "August", "September", "October",
                                "November", "December" };

const vector<string> week_days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

bool is_leap_year(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

void solve()
{
    int n, year;
    cin >> n >> year;
   
    map<string, vector<bool>> year_map;
    for (string month : months)
    {
        int days = (is_leap_year(year) ? leap_year_days[month] : nonleap_year_days[month]);
        year_map[month] = vector<bool>(days, true);
    }

    while (n--)
    {
        int day;
        string month;
        cin >> day >> month;
        year_map[month][day - 1] = false;
    }

    string day_of_week;
    cin >> day_of_week;

    int cur_day = find(all(week_days), day_of_week) - week_days.begin();
    vector<int> cnt(week_days.size());

    for (string month : months)
    {
        for (bool work : year_map[month])
        {
            cnt[cur_day] += work;
            cur_day = (cur_day + 1) % week_days.size();
        }
    }

    vector<pair<int, string>> stats;
    for (int i = 0; i < cnt.size(); ++i)
    {
        stats.push_back({ cnt[i], week_days[i] });
    }
    std::sort(all(stats));
    cout << stats[stats.size() - 1].second << ' ' << stats[0].second;
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
