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

class StatsCounter
{
    unordered_map<string, string> player_team;
    unordered_map<string, int> team_games;
    unordered_map<string, int> player_total;
    unordered_map<string, int> team_total;
    unordered_map<string, int> player_opens;
    unordered_map<string, int> team_opens;
    unordered_map<string, vi> player_goals;
    string cur_team;
    int goals_left;
    string next_team;
    int next_goals;
    string player_open;
    int minute_open;

    void add_match(string& input)
    {
        char team1[35];
        char team2 [35];
        int score1 = 0, score2 = 0;
        sscanf(input.c_str(), "\"%[^\"]\" - \"%[^\"]\" %d:%d", team1, team2, &score1, &score2);
        cur_team = "\"" + string(team1) + "\"";
        goals_left = score1;
        next_team = "\"" + string(team2) + "\"";
        next_goals = score2;

        team_games[cur_team]++;
        team_games[next_team]++;
        team_total[cur_team] += score1;
        team_total[next_team] += score2;
        player_open = "";
        minute_open = 91;
    }

    int get_total_goals_for_team(string team)
    {
        return team_total[team];
    }

    double get_mean_goals_for_team(string team)
    {
        return 1.0 * team_total[team] / team_games[team];
    }

    int get_total_goals_by_player(string player)
    {
        return player_total[player];
    }

    double get_mean_goals_by_player(string player)
    {
        return 1.0 * player_total[player] / team_games[player_team[player]];
    }

    int goals_on_minute_by_player(int minute, string player)
    {
        if (!player_goals.contains(player)) return 0;
        return player_goals[player][minute];
    }

    int goals_on_first_minutes_by_player(int minute, string player)
    {
        if (!player_goals.contains(player)) return 0;
        int res = 0;
        for (int i = 1; i <= minute; ++i) res += player_goals[player][i];
        return res;
    }

    int goals_on_last_minutes_by_player(int minute, string player)
    {
        if (!player_goals.contains(player)) return 0;
        int res = 0;
        for (int i = 91 - minute; i <= 90; ++i) res += player_goals[player][i];
        return res;
    }

    int get_team_opens(string team)
    {
        return team_opens[team];
    }

    int get_player_opens(string player)
    {
        return player_opens[player];
    }

    void add_goal(string& input)
    {
        char player[31];
        int minute = 0;
        sscanf(input.c_str(), "%[^0123456789]%d'", player, &minute);
        string player_name = string(player);
        player_name.pop_back();

        if (goals_left == 0)
        {
            cur_team = next_team;
            goals_left = next_goals;
            next_goals = 0;
        }

        player_team[player_name] = cur_team;
        player_total[player_name]++;
        if (!player_goals.contains(player_name))
        {
            player_goals[player_name] = vi(91);
        }
        player_goals[player_name][minute]++;
        if (minute < minute_open)
        {
            minute_open = minute;
            player_open = player_name;
        }

        if (--goals_left <= 0 && next_goals == 0)
        {
            player_opens[player_open]++;
            team_opens[player_team[player_open]]++;
        }
    }

public:
    void add_line(string& input)
    {
        string first_word = input.substr(0, input.find(' '));
        if (first_word[0] == '\"')
        {
            add_match(input);
            return;
        }
        
        if (first_word == "Total")
        {
            if (input.find("Total goals for") != std::string::npos)
            {
                string team_name = input.substr(string("Total goals for ").size());
                cout << get_total_goals_for_team(team_name) << '\n';
                return;
            }
            if (input.find("Total goals by") != std::string::npos)
            {
                string player_name = input.substr(string("Total goals by ").size());
                cout << get_total_goals_by_player(player_name) << '\n';
                return;
            }
            return;
        }

        if (first_word == "Mean")
        {
            if (input.find("Mean goals per game for") != std::string::npos)
            {
                string team_name = input.substr(string("Mean goals per game for ").size());
                cout << fixed << setprecision(5) << get_mean_goals_for_team(team_name) << '\n';
                return;
            }
            if (input.find("Mean goals per game by") != std::string::npos)
            {
                string player_name = input.substr(string("Mean goals per game by ").size());
                cout << fixed << setprecision(5) << get_mean_goals_by_player(player_name) << '\n';
                return;
            }
            return;
        }

        if (first_word == "Goals")
        {
            int minute;
            char player[35];
            if (input.find("Goals on minute") != std::string::npos)
            {
                sscanf(input.c_str(), "Goals on minute %d by %[^\t\n]", &minute, player);
                string player_name = string(player);
                cout << goals_on_minute_by_player(minute, player_name) << '\n';
                return;
            }
            if (input.find("Goals on first") != std::string::npos)
            {
                sscanf(input.c_str(), "Goals on first %d minutes by %[^\t\n]", &minute, player);
                string player_name = string(player);
                cout << goals_on_first_minutes_by_player(minute, player_name) << '\n';
                return;
            }
            if (input.find("Goals on last") != std::string::npos)
            {
                sscanf(input.c_str(), "Goals on last %d minutes by %[^\t\n]", &minute, player);
                string player_name = string(player);
                cout << goals_on_last_minutes_by_player(minute, player_name) << '\n';
                return;
            }
            return;
        }

        if (first_word == "Score")
        {
            char name[35];
            sscanf(input.c_str(), "Score opens by %[^\t\n]", name);
            string team_or_player = string(name);
            if (team_or_player[0] == '\"')
            {
                cout << get_team_opens(team_or_player) << '\n';
            }
            else
            {
                cout << get_player_opens(team_or_player) << '\n';
            }
            return;
        }

        add_goal(input);
    }
};

void solve()
{   
    StatsCounter scnt;
    string input;
    while (getline(cin, input))
    {
        if (input != "")
        {
            scnt.add_line(input);
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
