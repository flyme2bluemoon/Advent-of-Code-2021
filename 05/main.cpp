#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

vector< pair< pair<int,int>, pair<int, int> > > get_input()
{
    vector< pair< pair<int,int>, pair<int, int> > > vents;
    string buffer;
    int x1, y1, x2, y2;

    while (getline(cin, buffer)) {
        stringstream buf(buffer);
        buf >> x1;
        buf.ignore(1);
        buf >> y1;
        buf.ignore(4);
        buf >> x2;
        buf.ignore(1);
        buf>> y2;
        vents.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
    }

    return vents;
}

pair<int, int> get_max(vector< pair< pair<int,int>, pair<int, int> > > vents, int n) {
    int x = 0;
    int y = 0;

    for (int i = 0; i < n; i++) {
        if (vents[i].first.first > x) {
            x = vents[i].first.first;
        }
        if (vents[i].second.first > x) {
            x = vents[i].second.first;
        }
        if (vents[i].first.second > x) {
            y = vents[i].first.second;
        }
        if (vents[i].second.second > x) {
            y = vents[i].second.second;
        }
    }

    return make_pair(x + 1, y + 1);
}

int solve(int part_num, vector< pair< pair<int,int>, pair<int, int> > > vents, int n, int x, int y)
{
    int answer = 0;

    int x1, x2, y1, y2, diagonal_start, diagonal_end;

    int sea_floor[x][y];
    fill_n(*sea_floor, x*y, 0);

    for (int i = 0; i < n; i++) {
        if (vents[i].first.first == vents[i].second.first) {
            x1 = vents[i].first.first;
            y1 = vents[i].first.second;
            y2 = vents[i].second.second;
            for (int j = min(y1, y2); j <= max(y1, y2); j++) {
                sea_floor[x1][j]++;
            }
        } else if (vents[i].first.second == vents[i].second.second) {
            y1 = vents[i].first.second;
            x1 = vents[i].first.first;
            x2 = vents[i].second.first;
            for (int j = min(x1, x2); j <= max(x1, x2); j++) {
                sea_floor[j][y1]++;
            }
        } else if (part_num == 2) {
            x1 = vents[i].first.first;
            x2 = vents[i].second.first;
            y1 = vents[i].first.second;
            y2 = vents[i].second.second;
            if ((x1 - x2) * (y1 - y2) > 0) {
                for (int j = min(x1, x2), k = min(y1, y2); j <= max(x1, x2); j++, k++) {
                    sea_floor[j][k]++;
                }
            } else {
                for (int j = min(x1, x2), k = max(y1, y2); j <= max(x1, x2); j++, k--) {
                    sea_floor[j][k]++;
                }
            }
        }
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (sea_floor[i][j] >= 2) {
                answer++;
            }
        }
    }

    return answer;
}

int main()
{
    vector< pair< pair<int,int>, pair<int, int> > > vents = get_input();
    int n = vents.size();

    pair<int, int> max = get_max(vents, n);

    cout << "Part 1: " << solve(1, vents, n, max.first, max.second) << endl;
    cout << "Part 2: " << solve(2, vents, n, max.first, max.second) << endl;

    return 0;
}