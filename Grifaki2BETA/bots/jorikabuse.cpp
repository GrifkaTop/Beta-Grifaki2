#include <iostream>
#include <vector>

using namespace std;

struct ViewCell {
    int army, ownerId;
    bool wall, visible;
    int originalOwner;
    string type;

    friend istream& operator>>(istream& is, ViewCell& a) {
        return is >> a.army >> a.ownerId >> a.wall >> a.visible >> a.originalOwner >> a.type;
    }
};

using pii = pair <int, int>;

signed main() {
    int n, m, npl, id;
    cin >> n >> m >> npl >> id;
    srand(time(nullptr));
    int firstMove = 1;
    while (true) {
        int win;
        cin >> win;
        if (win) {
            return 0;
        }
        vector <vector <ViewCell> > v(n, vector <ViewCell> (m));
        for (auto &i : v) {
            for (auto& cell : i) {
                cin >> cell;
            }
        }
        vector <pii> moves = {
            {0, 1},
            {-1, 0},
            {1, 0},
            {0, -1}
        };
        vector <tuple <int, int, int, int> > allmv;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (v[i][j].ownerId != id) {
                    continue;
                }
                for (auto [dx, dy] : moves) {
                    int x = i + dx, y = j + dy;
                    if (min(x, y) >= 0 && x < n && y < m && v[x][y].type != "MOUNTAIN") {
                        allmv.emplace_back(i, j, x, y);
                    }
                }
            }
        }
        if (allmv.empty()) {
            std::cout << "EMPTY" << std::endl;
            continue;
        }
        if (firstMove) {
            auto [a, b, c, d] = allmv[0];
            std::cout << "MOVE " << a << " " << b << " " << c << " " << d << " " << v[a][b].army << endl;
            firstMove = 0;
            continue;
        }
        bool f = false;
        for (auto [a, b, c, d] : allmv) {
            if (v[a][b].army > v[c][d].army && v[c][d].type == "FALLEN_CAPITAL" && v[c][d].ownerId && v[c][d].ownerId != id) {
                std::cout << "MOVE " << a << " " << b << " " << c << " " << d << " " << v[a][b].army << endl;
                f = true;
                break;
            }
        }
        if (!f) {
            std::cout << "EMPTY" << std::endl;
        }
    }
}