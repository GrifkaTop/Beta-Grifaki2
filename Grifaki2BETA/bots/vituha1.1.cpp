    #include <bits/stdc++.h>

    using namespace std;

    mt19937 rnd(time(0));

    struct kletka
    {
        long long army, own_id, wall, visible;
        string tp;
    };

    struct kletka_own
    {
        kletka z;
        int i, j;
    };

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
            vector<vector<kletka>> mapp(h, vector<kletka> (w));
            for(int i = 0; i < h; i++)
            {
                for(int j = 0; j < w; j++)
                {
                    cin >> mapp[i][j].army;
                    cin >> mapp[i][j].own_id;
                    cin >> mapp[i][j].wall;
                    cin >> mapp[i][j].visible;
                    cin >> mapp[i][j].tp;
                    if(mapp[i][j].own_id == id)
                    {
                        z.push_back({mapp[i][j], i, j});
                    }
                }
            }
            int a = rnd() % z.size();
            int x = z[a].j, y = z[a].i;
            int x1 = x, y1 = y;
            int dir = rnd() % 4;
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
            if(x >= 0 && y >= 0 && x < h && y < w && mapp[y][x].tp != "MOUNTAIN")
            {
                cout << "MOVE" << endl;
                cout << y1 << ' ' << x1 << ' ' << y << ' ' << x << ' ' << z[a].z.army - 1 << endl;
            }
            else
            {
                cout << "EMPTY" << endl;
            }
        }
        return 0;
    }
