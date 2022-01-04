#include <iostream>
#include <cstring>
#include <map>

using namespace std;

map<string, unsigned long> create_new_counter(const map<string, string> &pair_insertion_rules)
{
    map<string, unsigned long> counter;
    for (const auto &pair : pair_insertion_rules) {
        counter[pair.first] = 0;
    }

    return counter;
}

map<string, unsigned long> step(const map<string, unsigned long> &old_counter, const map<string, string> &pair_insertion_rules)
{
    map<string, unsigned long> counter = create_new_counter(pair_insertion_rules);
    string product;
    for (const auto &i : old_counter) {
        product = pair_insertion_rules.at(i.first);
        counter[i.first[0] + product] += i.second;
        counter[product + i.first[1]] += i.second;
    }

    return counter;
}

unsigned long solve(unsigned long step_count, string polymer_template, const map<string, string> &pair_insertion_rules)
{
    map<string, unsigned long> counter = create_new_counter(pair_insertion_rules);
    for (int i = 0; i < polymer_template.length() - 1; i++) {
        counter[polymer_template.substr(i, 2)]++;
    }

    for (int i = 0; i < step_count; i++) {
        counter = step(counter, pair_insertion_rules);
    }

    unsigned long histogram[26];
    memset(histogram, 0, sizeof(unsigned long) * 26);

    for (const auto &i : counter) {
        // histogram[i.first[0] - 'A'] += i.second;
        histogram[i.first[1] - 'A'] += i.second;
    }

    unsigned long maximum = 0;
    unsigned long minimum = ULONG_MAX;

    for (const auto &i : histogram) {
        if (i > maximum) {
            maximum = i;
        }
        if (i < minimum && i != 0) {
            minimum = i;
        }
    }

    unsigned long answer = maximum - minimum;

    return answer;
}

int main()
{
    string polymer_template;
    map<string, string> pair_insertion_rules;
    string reactants;
    string product;

    cin >> polymer_template;
    while (cin >> reactants) {
        cin.ignore(4);
        cin >> product;

        pair_insertion_rules[reactants] = product;
    }

    cout << "Part 1: " << solve(10, polymer_template, pair_insertion_rules) << endl;
    cout << "Part 2: " << solve(40, polymer_template, pair_insertion_rules) << endl;

    return 0;
}
