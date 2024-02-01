#include <iostream>
#include <vector>

using namespace std;

struct Cell {
    int army, ownerId;
    bool wall;
    string type;

    friend istream& operator>>(istream& is, Cell& a) {
        return is >> a.army >> a.ownerId >> a.wall >> a.type;
    }
};

struct ViewCell {
    int army, ownerId;
    bool wall, visible;
    string type;

    friend istream& operator>>(istream& is, ViewCell& a) {
        return is >> a.army >> a.ownerId >> a.wall >> a.visible >> a.type;
    }
};

using pii = pair <int, int>;

signed main() {
    int n, m, npl, id;
    cin >> n >> m >> npl >> id;
    srand(time(nullptr));
    while (true) {
        int win;
        cin >> win;
        if (win > 0) {
            cerr << "player " << win << " won!";
            return 0;
        }
        if (win == -1) {
            cerr << "you died";
            return 0;
        }
        vector <vector <ViewCell> > v(n, vector <ViewCell> (m));
        for (auto &i : v) {
            for (auto& cell : i) {
                cin >> cell;
            }
        }
        vector <pii> moves = {
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1}
        };
        vector <tuple <int, int, int, int> > allmv;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (v[i][j].army <= 1 || v[i][j].ownerId != id) {
                    continue;
                }
                for (auto [dx, dy] : moves) {
                    int x = i + dx, y = j + dy;
                    if (min(x, y) >= 0 && x < n && y < m && v[x][y].type != "MOUNTAIN" ) {
                        allmv.emplace_back(i, j, x, y);
                    }
                }
            }
        }
        std::cerr << allmv.size() << std::endl;
        int id = rand() % allmv.size();
        auto [a, b, c, d] = allmv[id];
        std::cout << "MOVE " << a << " " << b << " " << c << " " << d << " " << rand() % (v[a][b].army - 1) + 1 << endl;
    }
}