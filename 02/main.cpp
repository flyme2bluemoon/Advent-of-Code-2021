#include <iostream>
#include <vector>

using namespace std;

int part_one(vector< pair<string, int> > inp, int n)
{
    int horizontal = 0;
    int depth = 0;
    for (int i = 0; i < n; i++) {
        if (!inp[i].first.compare("up")) {
            depth -= inp[i].second;
        } else if (!inp[i].first.compare("down")) {
            depth += inp[i].second;
        } else {
            horizontal += inp[i].second;
        }
    }

    return horizontal * depth;
}

int part_two(vector< pair<string, int> > inp, int n)
{
    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    for (int i = 0; i < n; i++) {
        if (!inp[i].first.compare("up")) {
            aim -= inp[i].second;
        } else if (!inp[i].first.compare("down")) {
            aim += inp[i].second;
        } else {
            horizontal += inp[i].second;
            depth += (aim * inp[i].second);
        }
    }

    return horizontal * depth;
}

int main()
{
    vector< pair<string, int> > instructions;
    pair<string, int> tmp;
    while (cin >> tmp.first >> tmp.second) {
        instructions.push_back(tmp);
    }
    int n = instructions.size();

    cout << "Part 1: " << part_one(instructions, n) << endl;
    cout << "Part 2: " << part_two(instructions, n) << endl;

    return 0;
}
