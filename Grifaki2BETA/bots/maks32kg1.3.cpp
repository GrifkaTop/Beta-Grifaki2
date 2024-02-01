#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
using namespace std;

#define all(v) (v).begin(), (v).end()


mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());


struct Cell {
    enum class Type {
        PLAIN, CITY, MOUNTAIN, CAPITAL
    };


    int army, ownerId, wall, visible;
    Type type;
    

    friend istream& operator>>(istream& is, Cell& cell) {
        is >> cell.army >> cell.ownerId >> cell.wall >> cell.visible;
        string s; is >> s;
        if (s == "PLAIN") cell.type = Type::PLAIN;
        if (s == "CITY") cell.type = Type::CITY;
        if (s == "MOUNTAIN") cell.type = Type::MOUNTAIN;
        if (s == "CAPITAL") cell.type = Type::CAPITAL;
        return is;
    }
};

struct vec {
    int x, y;
    vec(int x = 0, int y = 0):x(x), y(y) {}
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int height, width, players, player_id;
    cin >> height >> width >> players >> player_id;


    vec cur(-1, -1);
    vector <vec> path;
    while (true) {
        {
            int win; cin >> win;
            if (win != 0) return 0;
        }

        vector <vector <Cell>> map(height, vector <Cell>(width));
        for (auto& x : map) for (auto& y : x) cin >> y;


        if (cur.x == -1 || map[cur.x][cur.y].ownerId != player_id) {
            for (int x = 0; x < height; ++x) {
                for (int y = 0; y < width; ++y) {
                    if (map[x][y].ownerId == player_id && map[x][y].type == Cell::Type::CAPITAL) {
                        cur = { x, y };
                    }
                }
            }
        }


        vec target;
        vector <vec> pos;
        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                if (map[x][y].ownerId != player_id && map[x][y].type != Cell::Type::MOUNTAIN) {
                    pos.push_back({ x, y });
                }
            }
        }
        shuffle(all(pos), rnd);
        if (pos.empty()) {
            cout << "EMPTY" << endl;
            continue;
        }
        target = pos[0];

        vector <pair <int, int>> moves = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        vector <vector <bool>> used(height, vector <bool>(width, false));
        vec nxt(-1, -1);
        function <bool(int, int)> dfs = [&](int x, int y) {
            if (x == target.x && y == target.y) return true;
            used[x][y] = true;

            for (auto [dx, dy] : moves) {
                if (x + dx >= 0 && x + dx < height && y + dy >= 0 && y + dy < width && map[x + dx][y + dy].type != Cell::Type::MOUNTAIN) {
                    if (!used[x + dx][y + dy]) {
                        if (dfs(x + dx, y + dy)) {
                            path.push_back({ x + dx, y + dy });
                            return true;
                        }
                    }
                }
            }

            return false;
        };
        dfs(cur.x, cur.y);

        if (!path.empty()) {
            cout << "MOVE\n";
            cout << cur.x << ' ' << cur.y << ' ' << path.back().x << ' ' << path.back().y << '\n';
            cout << map[cur.x][cur.y].army - 1 << endl;
            cur = path.back();
            path.pop_back();
            continue;
        }
        else {
            cout << "EMPTY" << endl;
        }
    }
}
