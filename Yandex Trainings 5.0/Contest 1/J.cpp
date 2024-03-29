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

const int EMBEDDED = 1;
const int SURROUNDED = 2;
const int FLOATING = 3;

class Document
{
    int w, h, c;
    bool occupied[1000]; // projection of surrounded
    set<pair<int, ii>> images; // surrounded images
    int pos_x = 0, pos_y = 0;
    int cur_h = h; // height of current string
    int last_x = 0, last_y = 0; // top right point of last object (for floating)
    bool need_ws = false; // do we need to set ws next time (for words and embedded)

public:
    Document(int w, int h, int c) : w(w), h(h), c(c) {
        fill(occupied, occupied + 1000, 0);
    }

    void update_surroundings()
    {
        while (!images.empty() && images.begin()->first <= pos_y) {
            auto [l, r] = images.begin()->second;
            fill(occupied + l, occupied + r, 0);
            images.erase(images.begin());
        }
    }

    void skip_to_fit(int word_len)
    {
        while (word_len)
        {
            int free_cnt = 0;
            for (int i = pos_x; i < w; ++i)
            {
                if (occupied[i]) {
                    free_cnt = 0;
                    need_ws = false;
                }
                else
                {
                    ++free_cnt;
                    if (free_cnt >= word_len)
                    {
                        pos_x = i - word_len + 1;
                        return;
                    }
                }
            }
            pos_x = 0;
            pos_y += cur_h;
            update_surroundings();
            cur_h = h;
            need_ws = false;
        }
    }

    int get_image_type(string read_value)
    {
        int value = 0;
        if (read_value == "embedded")
        {
            value = EMBEDDED;
        }
        else {
            if (read_value == "surrounded")
            {
                value = SURROUNDED;
            }
            else
            {
                if (read_value == "floating")
                {
                    value = FLOATING;
                }
                else
                {
                    value = atoi(read_value.c_str());
                }
            }
        }
        return value;
    }

    void skip_ws()
    {
        // ws in current segment
        int free_space = 0;
        for (int i = pos_x; i < w && !occupied[i]; ++i)
        {
            if (++free_space >= c)
            {
                pos_x += c;
                return;
            }
        }

        // ws in another segment
        bool another_section = false;
        for (int i = pos_x; i < w; ++i)
        {
            if (occupied[i])
            {
                another_section = true;
            }
            else
            {
                if (another_section)
                {
                    pos_x = i;
                    return;
                }
            }
        }

        pos_x = w;
    }

    void add_word(int word_len)
    {
        if (need_ws) skip_ws();
        skip_to_fit(word_len);
        pos_x += word_len;
        last_x = pos_x, last_y = pos_y;
        need_ws = true;
    }

    void add_image(map<string, int>& params)
    {
        int width = params["width"];
        int height = params["height"];

        if (params["layout"] == FLOATING)
        {
            int dx = params["dx"];
            int dy = params["dy"];

            int x_start = std::min(std::max(last_x + dx, 0), w - width);
            int y_start = last_y + dy;

            std::cout << x_start << ' ' << y_start << '\n';

            last_x = x_start + width, last_y = y_start;
            return;
        }

        if (params["layout"] == EMBEDDED)
        {
            if (need_ws) skip_ws();
            skip_to_fit(width);

            std::cout << pos_x << ' ' << pos_y << '\n';

            pos_x += width;
            last_x = pos_x, last_y = pos_y;
            cur_h = std::max(cur_h, height);
            need_ws = true;
            return;
        }

        if (params["layout"] == SURROUNDED)
        {
            skip_to_fit(width);
            std::cout << pos_x << ' ' << pos_y << '\n';
            images.insert({ pos_y + height, {pos_x, pos_x + width} });
            fill_n(occupied + pos_x, width, 1);
            pos_x += width;
            last_x = pos_x, last_y = pos_y;
            need_ws = false;
            return;
        }
    }

    void add_paragraph(string input)
    {
        if (input == "")
        {
            need_ws = false;
            pos_x = 0;
            pos_y += cur_h;
            cur_h = h;
            while (!images.empty())
            {
                pos_y = std::max(pos_y, images.begin()->first);
                auto [l, r] = images.begin()->second;
                fill(occupied + l, occupied + r, 0);
                images.erase(images.begin());
            }
            last_x = pos_x, last_y = pos_y;
            return;
        }

        int ind = 0;
        while (ind < input.length())
        {
            while (ind < input.length() && input[ind] == ' ') ++ind;
            if (ind < input.length())
            {
                if (input[ind] != '(')
                {
                    int word_len = ind;
                    while (ind < input.length() && input[ind] != ' ') ++ind;
                    word_len = (ind - word_len) * c;
                    add_word(word_len);
                }
                else
                {
                    // "(image " shift
                    ++ind;
                    while (ind < input.length() && input[ind] == ' ') ++ind;
                    while (ind < input.length() && input[ind] != ' ') ++ind;
                    while (ind < input.length() && input[ind] == ' ') ++ind;

                    map<string, int> params;
                    {
                        while (ind < input.length() && input[ind] != ')')
                        {
                            while (ind < input.length() && input[ind] == ' ') ++ind;
                            string keyword = "";
                            while (input[ind] != '=') keyword += input[ind++];
                            ++ind; // skipping "="
                            string read_value = "";
                            while (ind < input.length() && input[ind] != ' ' && input[ind] != ')') read_value += input[ind++]; 
                            params[keyword] = get_image_type(read_value);
                        }
                        ++ind;
                    }

                    add_image(params);
                }
            }
        }
    }
};

void solve()
{
    int w, h, c;
    std::cin >> w >> h >> c;
    std::cin.get();

    Document doc(w, h, c);

    string input_data = "";
    string input;
    while (std::getline(std::cin, input))
    {
        {
            int ws_index = 0;
            while (ws_index < input.length() && input[ws_index] == ' ') ++ws_index;
            input = input.substr(ws_index);
        }
        if (input == "")
        {
            doc.add_paragraph(input_data);
            doc.add_paragraph("");
            input_data = "";
        }
        else
        {
            input_data += " " + input;
        }
    }
    doc.add_paragraph(input_data);
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
