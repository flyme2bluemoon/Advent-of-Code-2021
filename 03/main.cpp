#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

int part_one(vector<string> conditions, int number_of_conditions, int bit_count)
{
    int zero[bit_count];
    int ones[bit_count];
    memset(zero, 0, bit_count * sizeof(int));
    memset(ones, 0, bit_count * sizeof(int));

    for (int i = 0; i < bit_count; i++) {
        for (int j = 0; j < number_of_conditions; j++) {
            if (conditions[j][i] == '0') {
                zero[i]++;
            } else {
                ones[i]++;
            }
        }
    }

    int gamma = 0;
    int epsilon = 0;

    for (int i = 0; i < bit_count; i++) {
        if (zero[i] > ones[i]) {
            gamma += pow(2, bit_count - i - 1);
        } else {
            epsilon += pow(2, bit_count - i - 1);
        }
    }

    return gamma * epsilon;
}

int part_two(vector<string> conditions, int number_of_conditions, int bit_count)
{
    vector<int> oxygen_previous, oxygen_current_zero, oxygen_current_one, co2_previous, co2_current_zero, co2_current_one;
    for (int i = 0; i < number_of_conditions; i++) {
        oxygen_previous.push_back(i);
        co2_previous.push_back(i);
    }

    int oxygen_zero, oxygen_one, oxygen_size, co2_zero, co2_one, co2_size;
    for (int i = 0; i < bit_count; i++) {
        oxygen_zero = 0;
        oxygen_one = 0;
        oxygen_size = oxygen_previous.size();
        co2_zero = 0;
        co2_one = 0;
        co2_size = co2_previous.size();
        
        if (oxygen_size > 1) {
            for (int j = 0; j < oxygen_size; j++) {
                if (conditions[oxygen_previous[j]][i] == '0') {
                    oxygen_zero++;
                    oxygen_current_zero.push_back(oxygen_previous[j]);
                } else {
                    oxygen_one++;
                    oxygen_current_one.push_back(oxygen_previous[j]);
                }
            }
            if (oxygen_one >= oxygen_zero) {
                oxygen_previous = oxygen_current_one;
            } else {
                oxygen_previous = oxygen_current_zero;
            }
            oxygen_current_zero.clear();
            oxygen_current_one.clear();
        }

        if (co2_size > 1) {
            for (int j = 0; j < co2_size; j++) {
                if (conditions[co2_previous[j]][i] == '0') {
                    co2_zero++;
                    co2_current_zero.push_back(co2_previous[j]);
                } else {
                    co2_one++;
                    co2_current_one.push_back(co2_previous[j]);
                }
            }
            if (co2_zero <= co2_one) {
                co2_previous = co2_current_zero;
            } else {
                co2_previous = co2_current_one;
            }
            co2_current_zero.clear();
            co2_current_one.clear();
        }
    }

    int oxygen_generator_rating = 0;
    int co2_scrubber_rating = 0;
    for (int i = 0; i < bit_count; i++) {
        if (conditions[oxygen_previous[0]][i] == '1') {
            oxygen_generator_rating += pow(2, bit_count - i - 1);
        }
        if (conditions[co2_previous[0]][i] == '1') {
            co2_scrubber_rating += pow(2, bit_count - i - 1);
        }
    }

    return oxygen_generator_rating * co2_scrubber_rating;
}

int main()
{
    vector<string> conditions;
    string tmp;
    while (cin >> tmp) {
        conditions.push_back(tmp);
    }
    int number_of_conditions = conditions.size();
    int bit_count = conditions[0].size();

    cout << "Part 1: " << part_one(conditions, number_of_conditions, bit_count) << endl;
    cout << "Part 2: " << part_two(conditions, number_of_conditions, bit_count) << endl;

    return 0;
}
