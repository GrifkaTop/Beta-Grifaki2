#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <functional>
#include <deque>
using namespace std;

#define all(v) (v).begin(), (v).end()


mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());


struct Cell {
    enum class Type {
        PLAIN, CITY, MOUNTAIN, CAPITAL, FALLEN_CAPITAL
    };


    int army, ownerId, wall, visible, owner0;
    Type type;


    friend istream& operator>>(istream& is, Cell& cell) {
        is >> cell.army >> cell.ownerId >> cell.wall >> cell.visible >> cell.owner0;
        string s; is >> s;
        if (s == "PLAIN") cell.type = Type::PLAIN;
        if (s == "CITY") cell.type = Type::CITY;
        if (s == "MOUNTAIN") cell.type = Type::MOUNTAIN;
        if (s == "CAPITAL") cell.type = Type::CAPITAL;
        if (s == "FALLEN_CAPITAL") cell.type = Type::FALLEN_CAPITAL;
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


    while (true) {
        {
            int win; cin >> win;
            if (win != 0) return 0;
        }

        vector <vector <Cell>> map(height, vector <Cell>(width));
        for (auto& x : map) for (auto& y : x) cin >> y;


        vector <pair <int, int>> moves = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        vector <vector <vec>> nx(height, vector <vec>(width, { -1, -1 }));
        deque <vec> q;
        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                if (map[x][y].type != Cell::Type::MOUNTAIN && map[x][y].ownerId != player_id) {
                    q.push_back({ x, y });
                }
            }
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();

            for (auto [dx, dy] : moves) {
                if (x + dx >= 0 && x + dx < height && y + dy >= 0 && y + dy < width && map[x + dx][y + dy].type != Cell::Type::MOUNTAIN) {
                    if (nx[x + dx][y + dy].x == -1) {
                        nx[x + dx][y + dy] = { x, y };
                        q.push_back({ x + dx, y + dy });
                    }
                }
            }
        }

        vec mx(-1, -1);
        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                if (map[x][y].ownerId == player_id) {
                    if (mx.x == -1) {
                        mx = { x, y };
                        continue;
                    }

                    int cnt = map[x][y].army;
                    int cnt1 = map[mx.x][mx.y].army;
                    if (map[x][y].type != Cell::Type::PLAIN) cnt /= 5;
                    if (map[mx.x][mx.y].type != Cell::Type::PLAIN) cnt1 /= 5;
                    else if (cnt > cnt1) mx = { x, y };
                }
            }
        }

        if (mx.x == -1 || nx[mx.x][mx.y].x == -1) cout << "EMPTY" << endl;
        else {
            cout << "MOVE\n";
            cout << mx.x << ' ' << mx.y << ' ' << nx[mx.x][mx.y].x << ' ' << nx[mx.x][mx.y].y << '\n';
            cout << map[mx.x][mx.y].army * 4 / 5 << endl;
        }
    }
}
