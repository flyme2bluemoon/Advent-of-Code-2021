#include <iostream>
#include <vector>

using namespace std;

unsigned long int solve(vector<int> fish, int days)
{
    unsigned long int answer = 0;
    vector<unsigned long int> age_counter;
    for (int i = 0; i <= 8; i++) {
        age_counter.push_back(count(fish.begin(), fish.end(), i));
    }
    for (int i = 0; i < days; i++) {
        age_counter.push_back(age_counter[0]);
        age_counter[7] += age_counter[0];
        age_counter.erase(age_counter.begin());
    }

    for (int i = 0; i <= 8; i++) {
        answer += age_counter[i];
    }

    return answer;
}

int main()
{
    vector<int> fish;
    int tmp;
    while(cin >> tmp) {
        fish.push_back(tmp);
        cin.ignore(1);
    }

    cout << "Part 1: " << solve(fish, 80) << endl;
    cout << "Part 2: " << solve(fish, 256) << endl;

    return 0;
}
