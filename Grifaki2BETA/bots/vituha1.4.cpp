#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

struct kletka
{
    long long army, own_id, wall, visible, zxc;
    string tp;
};

struct kletka_own
{
    kletka z;
    int i, j;
};

void secret(vector<vector<kletka>> &mapp, vector<kletka_own> &z)
{
    int h = mapp.size(), w = mapp[0].size();
    int a = rnd() % z.size();
    int x = z[a].j, y = z[a].i;
    int x1 = x, y1 = y;
    for(int dir = 0; dir < 4; dir++)
    {
        x = x1;
        y = y1;
        if(dir == 0)
        {
            x++;
        }
        if(dir == 1)
        {
            y--;
        }
        if(dir == 2)
        {
            x--;
        }
        if(dir == 3)
        {
            y++;
        }
        if((x >= 0 && y >= 0 && x < w && y < h && mapp[y][x].tp != "MOUNTAIN" && mapp[y][x].own_id == 0))
        {
           cout << "MOVE" << endl;
           cout << y1 << ' ' << x1 << ' ' << y << ' ' << x << ' ' << (rnd() % z[a].z.army) << endl;
           return;
        }
    }
    std::cout << "EMPTY" << endl;
}

void secret2(vector<vector<kletka>> &mapp, vector<kletka_own> &z)
{
    int h = mapp.size(), w = mapp[0].size();
    int a = rnd() % z.size();
    int x = z[a].j, y = z[a].i;
    int x1 = x, y1 = y;
    for(int dir = 0; dir < 4; dir++)
    {
        x = x1;
        y = y1;
        if(dir == 0)
        {
            x++;
        }
        if(dir == 1)
        {
            y--;
        }
        if(dir == 2)
        {
            x--;
        }
        if(dir == 3)
        {
            y++;
        }
        if((x >= 0 && y >= 0 && x < w && y < h && mapp[y][x].tp != "MOUNTAIN"))
        {
            cout << "MOVE" << endl;
            cout << y1 << ' ' << x1 << ' ' << y << ' ' << x << ' ' << (rnd() % z[a].z.army) << endl;
            return;
        }
    }
    std::cout << "EMPTY" << endl;
}

int main()
{
    long long h, w, pl, id;
    cin >> h >> w >> pl >> id;
    int win;
    while(cin >> win)
    {
        if(win != 0)
        {
            return 0;
        }
        vector<kletka_own> z;
        vector<kletka_own> z_zah;
        vector<vector<kletka>> mapp(h, vector<kletka> (w));
        std::cerr << "START" << endl;
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                cin >> mapp[i][j].army;
                cin >> mapp[i][j].own_id;
                cin >> mapp[i][j].wall;
                cin >> mapp[i][j].visible;
                cin >> mapp[i][j].zxc;
                cin >> mapp[i][j].tp;
                if (mapp[i][j].own_id == id) {
                    std::cerr << i << " " << j << "\n";
                }
                if(mapp[i][j].own_id == id && mapp[i][j].army > 1)
                {
                    z.push_back({mapp[i][j], i, j});
                }
            }
        }
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                if(mapp[i][j].own_id != id || mapp[i][j].army <= 1)
                {
                    continue;
                }
                if(i > 0 && mapp[i - 1][j].own_id == 0)
                {
                    z_zah.push_back({mapp[i][j], i, j});
                }
                else if(j > 0 && mapp[i][j - 1].own_id == 0)
                {
                    z_zah.push_back({mapp[i][j], i, j});
                }
                else if(j < w - 1 && mapp[i][j + 1].own_id == 0)
                {
                    z_zah.push_back({mapp[i][j], i, j});
                }
                else if(i < h - 1 && mapp[i + 1][j].own_id == 0)
                {
                    z_zah.push_back({mapp[i][j], i, j});
                }
            }
        }
        std::cerr << "ASDASD\n";
        std::cerr << z_zah.size() << " " << z.size() << std::endl;
        std::cerr << h << " " << w << endl;
        if(z_zah.size() != 0)
        {
            secret(mapp, z_zah);
        }
        else if(z.size() != 0)
        {
            secret2(mapp, z);
        }
        else
        {
            cout << "EMPTY" << endl;
        }
    }
    return 0;
}
