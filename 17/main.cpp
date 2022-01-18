#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

int part_one(pair<int, int> y_target)
{
    int max_height = (y_target.first * (y_target.first + 1)) / 2;
    return max_height;
}

int part_two(pair<int, int> x_target, pair<int, int> y_target)
{
    int count = 0;

    int min_vx = (-1 + sqrt(1 - (4 * (-2) * x_target.first))) / 2;
    int min_vy = y_target.first;
    int max_vx = x_target.second;
    int max_vy = y_target.first * -1;
    int max_steps = y_target.first * -2;

    for (int i = min_vx; i <= max_vx; i++) {
        for (int j = min_vy; j <= max_vy; j++) {
            int x = 0;
            int y = 0;
            int vx = i;
            int vy = j;
            for (int k = 0; k <= max_steps; k++) {
                x += vx;
                y += vy;
                if (vx > 0)
                    vx -= 1;
                vy -= 1;
                if (x >= x_target.first && x <= x_target.second && y >= y_target.first && y <= y_target.second) {
                    count++;
                    break;
                } else if (x > x_target.second || y < y_target.first) {
                    break;
                }
            }
        }
    }

    return count;
}

int main()
{
    cin.ignore(13);
    string target;
    int lower_bound, upper_bound;
    pair<int, int> x_target, y_target;
    for (int i = 0; i < 2; i++) {
        cin >> target;
        stringstream ss(target);
        ss.ignore(2);
        ss >> lower_bound;
        ss.ignore(2);
        ss >> upper_bound;

        if (!i) {
            x_target = make_pair(lower_bound, upper_bound);
        } else {
            y_target = make_pair(lower_bound, upper_bound);
        }
    }

    cout << "Part 1: " << part_one(y_target) << endl;
    cout << "Part 2: " << part_two(x_target, y_target) << endl;

    return 0;
}