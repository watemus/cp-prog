//
// Created by watemus on 13.06.2020.
//

#include <bits/stdc++.h>

using namespace std;

template<class T>
using vec = vector<T>;

const char* NAME = "SemyonTsekhenko";
const vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

class Strategy {
public:
    string player;
    int width, height, cnt_colors;
    vec<vec<int>> field;
    void init() {
        cout << NAME << endl;
        cin >> player >> height >> width >> cnt_colors;
        field.resize(height, vec<int>(width));
    }
    string can_turn() {
        string res;
        cin >> res;
        return res;
    }
    void make_turn() {
        for (auto &row : field) {
            for (auto &elem : row) {
                cin >> elem;
            }
        }
        usd.assign(height, vec<int>(width, 0));
        color(0, 0, 1);
        color(height - 1, width - 1, 2);
        map<int, int> color_cnt;
        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                if (usd[x][y] != 1) continue;
                for (auto [dx, dy] : DD) {
                    if (x + dx >= height || x + dx < 0) continue;
                    if (y + dy >= width || y + dy < 0) continue;
                    if (!usd[x + dx][y + dy]) {
                        color_cnt[field[x + dx][y + dy]] += color(x + dx, y + dy, 3);
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < cnt_colors; i++) {
            if (i != field[0][0] && i != field[height - 1][width - 1]) {
                ans = i;
                break;
            }
        }
        int ans_cnt = 0;
        for (auto [col, cnt] : color_cnt) {
            if (col == field[0][0]) continue;
            if (col == field[height - 1][width - 1]) continue;
            if (cnt > ans_cnt) {
                ans = col;
                ans_cnt = cnt;
            }
        }
        cout << ans << endl;
    }
private:
    vec<vec<int>> usd;
    int color(int x, int y, int col) {
        usd[x][y] = col;
        queue<pair<int, int>> q;
        q.push({x, y});
        int ans = 0;
        while (q.size()) {
            auto [cx, cy] = q.front();
            q.pop();
            ans++;
            for (auto [dx, dy] : DD) {
                if (cx + dx >= height || cx + dx < 0 ||
                    cy + dy >= width || cy + dy < 0 ||
                    usd[cx + dx][cy + dy] != 0 ||
                    field[cx + dx][cy + dy] != field[cx][cy])
                {
                    continue;
                }
                usd[cx + dx][cy + dy] = col;
                q.push({cx + dx, cy + dy});
            }
        }
        return ans;
    }
};

int main() {
    Strategy s;
    s.init();
    while (true) {
        auto res = s.can_turn();
        if (res == "close") break;
        //if (res == "play")
        s.make_turn();
    }
    return 0;
}