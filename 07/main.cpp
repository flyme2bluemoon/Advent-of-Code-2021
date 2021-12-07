#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int part_one(vector<int> positions, int n)
{
    int median = positions[n / 2];
    int answer = 0;

    for (int i = 0; i < n; i++) {
        answer += abs(positions[i] - median);
    }

    return answer;
}

int part_two(vector<int> positions, int n)
{
    int mean = accumulate(positions.begin(), positions.end(), 0) / n;
    int answer = 0;
    int k;

    for (int i = 0; i < n; i++) {
        k = abs(positions[i] - mean);
        answer += (k * (k + 1)) / 2;
    }

    return answer;
}

int main()
{
    vector<int> positions;
    int tmp;
    while(cin >> tmp) {
        positions.push_back(tmp);
        cin.ignore(1);
    }
    sort(positions.begin(), positions.end());
    int n = positions.size();

    cout << "Part 1: " << part_one(positions, n) << endl;
    cout << "Part 2: " << part_two(positions, n) << endl;

    return 0;
}