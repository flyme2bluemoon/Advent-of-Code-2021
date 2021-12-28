#include <iostream>
#include <vector>
#include <map>

using namespace std;

void count_paths(const string &current_cave, vector<string> visited, const map<string, vector<string> > &actions, int &path_count, bool used)
{
    if (current_cave[0] > 'a' && current_cave.compare("start") && current_cave.compare("end")) {
        visited.push_back(current_cave);
    }

    if (!current_cave.compare("end")) {
        path_count++;
    } else {
        for (const auto &neighbor : actions.at(current_cave)) {
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                count_paths(neighbor, visited, actions, path_count, used);
            } else if (!used) {
                count_paths(neighbor, visited, actions, path_count, true);
            }
        }
    }
}

int part_one(const map<string, vector<string> > &actions)
{
    int path_count = 0;

    vector<string> visited;
    string current_cave = "start";

    count_paths(current_cave, visited, actions, path_count, true);

    return path_count;
}

int part_two(const map<string, vector<string> > &actions)
{
    int path_count = 0;

    vector<string> visited;
    string current_cave = "start";

    count_paths(current_cave, visited, actions, path_count, false);

    return path_count;
}

int main()
{
    map<string, vector<string> > actions;
    string tmp, a, b;
    while (cin >> tmp) {
        if (tmp.length() == 5) {
            a = tmp.substr(0,2);
            b = tmp.substr(3, 2);
        } else if (tmp.length() == 8) {
            a = "start";
            b = tmp.substr(6, 2);
        } else {
            a = "end";
            b = tmp.substr(4, 2);
        }
        if (actions.find(a) == actions.end()) {
            actions.insert(pair<string, vector<string> >(a, vector<string>()));
        }
        if (a.compare("end")) {
            actions[a].push_back(b);
        }
        if (actions.find(b) == actions.end()) {
            actions.insert(pair<string, vector<string> >(b, vector<string>()));
        }
        if (a.compare("start")) {
            actions[b].push_back(a);
        }
    }

    cout << "Part 1: " << part_one(actions) << endl;
    cout << "Part 2: " << part_two(actions) << endl;

    return 0;
}
