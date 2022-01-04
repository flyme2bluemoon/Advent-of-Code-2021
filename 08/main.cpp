#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6

int part_one(vector< vector<string> > after, int n)
{
    int answer = 0;

    int bits;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            bits = after[i][j].length();
            if (bits == 2 || bits == 3 || bits == 4 || bits == 7) {
                answer++;
            }
        }
    }

    return answer;
}

int convert(char* s, string scrambled)
{
    string fixed = "abcdefg";
    string translator[] = {"abcefg", "cf", "acdeg", "acdfg", "bcdf", "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"};

    for (int i = 0; i < scrambled.length(); i++) {
        for (int j = 0; j < 7; j++) {
            if (scrambled[i] == s[j]) {
                scrambled[i] = fixed[j];
                break;
            }
        }
    }
    sort(scrambled.begin(), scrambled.end());

    for (int i = 0; i < 10; i++) {
        if (!translator[i].compare(scrambled)) {
            // cout << scrambled << " " << i << endl;
            return i;
        }
    }

    return 0;
}

int part_two(vector< vector<string> > before, vector< vector<string> > after, int n)
{
    int answer = 0;

    int deductions[10];
    char segments[7];
    int bits;
    int missing;
    int output;
    for (int i = 0; i < n; i++) {
        memset(deductions, 0, sizeof(int) * 10);
        memset(segments, 0, sizeof(char) * 7);
        for (int j = 0; j < 10; j++) {
            bits = before[i][j].length();
            if (bits == 2) {
                deductions[1] = j;
            } else if (bits == 3) {
                deductions[7] = j;
            } else if (bits == 4) {
                deductions[4] = j;
            } else if (bits == 7) {
                deductions[8] = j;
            }
        }
        // search for segment A
        for (int j = 0; j < 3; j++) {
            if (before[i][deductions[7]][j] != before[i][deductions[1]][0] && before[i][deductions[7]][j] != before[i][deductions[1]][1]) {
                segments[A] = before[i][deductions[7]][j];
                break;
            }
        }

        // search for 6 and segments C and F
        for (int j = 0; j < 10; j++) {
            bits = before[i][j].length();
            if (bits == 6) {
                if ((find(before[i][j].begin(), before[i][j].end(), before[i][deductions[1]][0]) != before[i][j].end()) && !(find(before[i][j].begin(), before[i][j].end(), before[i][deductions[1]][1]) != before[i][j].end())) {
                    deductions[6] = j;
                    segments[C] = before[i][deductions[1]][1];
                    segments[F] = before[i][deductions[1]][0];
                    break;
                } else if ((find(before[i][j].begin(), before[i][j].end(), before[i][deductions[1]][1]) != before[i][j].end()) && !(find(before[i][j].begin(), before[i][j].end(), before[i][deductions[1]][0]) != before[i][j].end())) {
                    deductions[6] = j;
                    segments[C] = before[i][deductions[1]][0];
                    segments[F] = before[i][deductions[1]][1];
                    break;
                }
            }
        }

        // search for 2 and 5
        for (int j = 0; j < 10; j++) {
            bits = before[i][j].length();
            if (bits == 5) {
                if ((find(before[i][j].begin(), before[i][j].end(), segments[C]) != before[i][j].end()) && !(find(before[i][j].begin(), before[i][j].end(), segments[F]) != before[i][j].end())) {
                    deductions[2] = j;
                } else if ((find(before[i][j].begin(), before[i][j].end(), segments[F]) != before[i][j].end()) && !(find(before[i][j].begin(), before[i][j].end(), segments[C]) != before[i][j].end())) {
                    deductions[5] = j;
                }
            }
        }
        // search for segment B
        for (int j = 0; j < 5; j++) {
            if ((before[i][deductions[5]][j] != before[i][deductions[1]][0]) && (before[i][deductions[5]][j] != before[i][deductions[1]][1]) && !(find(before[i][deductions[2]].begin(), before[i][deductions[2]].end(), before[i][deductions[5]][j]) != before[i][deductions[2]].end())) {
                segments[B] = before[i][deductions[5]][j];
                break;
            }
        }
        // search for segment E
        for (int j = 0; j < 5; j++) {
            if ((before[i][deductions[2]][j] != before[i][deductions[1]][0]) && (before[i][deductions[2]][j] != before[i][deductions[1]][1]) && !(find(before[i][deductions[5]].begin(), before[i][deductions[5]].end(), before[i][deductions[2]][j]) != before[i][deductions[5]].end())) {
                segments[E] = before[i][deductions[2]][j];
                break;
            }
        }

        // search for segment D
        for (int j = 0; j < 4; j++) {
            if (before[i][deductions[4]][j] != segments[B] && before[i][deductions[4]][j] != segments[C] && before[i][deductions[4]][j] != segments[F]) {
                segments[D] = before[i][deductions[4]][j];
            }
        }

        // search for segment G
        missing = 'a' + 'b' + 'c' + 'd' + 'e' + 'f' + 'g';
        for (int j = 0; j < 7; j++) {
            missing -= segments[j];
        }
        segments[G] = missing;

        for (int j = 0; j < 4; j++) {
            answer += convert(segments, after[i][j]) * pow(10, 3 - j);
        }
    }


    return answer;
}

int main()
{
    vector< vector<string> > before, after;
    string tmp_str;
    vector<string> tmp_vec;
    while (cin >> tmp_str) {
        if (!tmp_str.compare("|")) {
            before.push_back(tmp_vec);
            tmp_vec.clear();
            for (int i = 0; i < 4; i++) {
                cin >> tmp_str;
                tmp_vec.push_back(tmp_str);
            }
            after.push_back(tmp_vec);
            tmp_vec.clear();
        } else {
            tmp_vec.push_back(tmp_str);
        }
    }

    int n = after.size();

    cout << "Part 1: " << part_one(after, n) << endl;
    cout << "Part 2: " << part_two(before, after, n) << endl;

    return 0;
}