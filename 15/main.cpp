#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef struct node {
    pair<int, int> state;
    int path_cost;
    bool operator<(const node &rhs) const {
        // poor man's way of reversing the priority queue by using opposite inequality ;)
        return path_cost > rhs.path_cost;
    }
} node;

vector< pair<int, int> > find_neighbors(pair<int, int> state, int width, int height)
{
    vector< pair<int, int> > neighbors;

    for (int i = state.first - 1; i <= state.first + 1; i += 2) {
        if (i >= 0 && i <= width) {
            neighbors.push_back(make_pair(i, state.second));
        }
    }

    for (int i = state.second - 1; i <= state.second + 1; i += 2) {
        if (i >= 0 && i <= height) {
            neighbors.push_back(make_pair(state.first, i));
        }
    }

    return neighbors;
}

int read_cavern(const vector< vector<int> > &cavern, int x, int y, int width, int height)
{
    int inc = (x / width) + (y / height);
    int val = (cavern[y % height][x % width] + inc - 1) % 9 + 1;

    return val;
}

int solve(const vector< vector<int> > &cavern, bool expanded)
{
    int width = cavern[0].size();
    int height = cavern.size();

    pair<int, int> goal;

    if (expanded) {
        goal = make_pair(width * 5 - 1, height * 5 - 1);
    } else {
        goal = make_pair(width - 1, height - 1);
    }

    node start = { .state = make_pair(0, 0), .path_cost = 0 };
    priority_queue<node> frontier;
    frontier.push(start);

    bool explored[goal.first + 1][goal.second + 1];
    memset(explored, false, (goal.first + 1) * (goal.second * 1));

    node cur_node;

    while (!frontier.empty()) {
        cur_node = frontier.top();
        frontier.pop();

        if (cur_node.state.first == goal.first && cur_node.state.second == goal.second) {
            return cur_node.path_cost;
        }

        for (const auto &i : find_neighbors(cur_node.state, goal.first, goal.second)) {
            if (!explored[i.first][i.second]) {
                node child = { .state = i, .path_cost = cur_node.path_cost + read_cavern(cavern, i.first, i.second, width, height) };
                frontier.push(child);
                explored[i.first][i.second] = true;
            }
        }

    }
    return -1;
}

int main()
{
    vector< vector<int> > cavern;
    vector<int> tmp;
    string line;
    while (cin >> line) {
        tmp.clear();
        for (const auto &i : line) {
            tmp.push_back(i - '0');
        }
        cavern.push_back(tmp);
    }

    cout << "Part 1: " << solve(cavern, false) << endl;
    cout << "Part 2: " << solve(cavern, true) << endl;

    return 0;
}
