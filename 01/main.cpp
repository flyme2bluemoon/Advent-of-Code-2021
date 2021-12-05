#include <iostream>
#include <vector>
using namespace std;

int part_one(vector<int> inp, int n)
{
    int answer = 0;
    for (int i = 1; i < n; i++) {
        if (inp[i] > inp[i - 1]) {
            answer++;
        }
    }

    return answer;
}

int part_two(vector<int> inp, int n)
{
    int answer = 0;
    for (int i = 3; i < n; i++) {
        if (inp[i] > inp[i - 3]) {
            answer++;
        }
    }

    return answer;
}

int main()
{
    vector<int> depths;
    int buffer;
    while (cin >> buffer) {
        depths.push_back(buffer);
    }
    int n = depths.size();

    cout << "Part 1: " << part_one(depths, n) << endl;
    cout << "Part 2: " << part_two(depths, n) << endl;

    return 0;
}
