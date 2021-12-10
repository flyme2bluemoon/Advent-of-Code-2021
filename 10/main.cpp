#include <iostream>
#include <vector>
#include <map>

using namespace std;

int part_one(vector<string> program, int n)
{
    int answer = 0;

    map<char, int> points_system = {
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137}
    };
    
    vector<char> buffer;
    int prog_len;
    char last;
    for (int i = 0; i < n; i++) {
        buffer.clear();
        prog_len = program[i].length();
        for (int j = 0; j < prog_len; j++) {
            if (program[i][j] == '(' || program[i][j] == '[' || program[i][j] == '{' || program[i][j] == '<') {
                buffer.push_back(program[i][j]);
            } else {
                last = buffer.back();
                buffer.pop_back();
                if ((program[i][j] == ')' && last != '(') || (program[i][j] == ']' && last != '[') || (program[i][j] == '}' && last != '{') || (program[i][j] == '>' && last != '<')) {
                    answer += points_system[program[i][j]];
                    break;
                }
            }
        }
    }

    return answer;
}

unsigned long part_two(vector<string> program, int n)
{
    unsigned long answer = 0;

    map<char, int> points_system = {
        {'(', 1},
        {'[', 2},
        {'{', 3},
        {'<', 4}
    };
    
    vector<char> buffer;
    int prog_len;
    char last;
    bool corrupted;
    unsigned long score;
    vector<unsigned long> all_scores;
    int missing_len;
    for (int i = 0; i < n; i++) {
        buffer.clear();
        prog_len = program[i].length();
        corrupted = false;
        for (int j = 0; j < prog_len; j++) {
            if (program[i][j] == '(' || program[i][j] == '[' || program[i][j] == '{' || program[i][j] == '<') {
                buffer.push_back(program[i][j]);
            } else {
                last = buffer.back();
                buffer.pop_back();
                if ((program[i][j] == ')' && last != '(') || (program[i][j] == ']' && last != '[') || (program[i][j] == '}' && last != '{') || (program[i][j] == '>' && last != '<')) {
                    corrupted = true;
                    break;
                }
            }
        }
        if (!corrupted) {
            score = 0;
            missing_len = buffer.size();
            for (int j = missing_len - 1; j >= 0; j--) {
                score *= 5;
                score += points_system[buffer[j]];
            }
            all_scores.push_back(score);
        }
    }

    sort(all_scores.begin(), all_scores.end());

    return all_scores[(all_scores.size() / 2)];
}

int main()
{
    vector<string> program;
    string tmp;
    while (cin >> tmp) {
        program.push_back(tmp);
    }
    int n = program.size();

    cout << "Part 1: " << part_one(program, n) << endl;
    cout << "Part 2: " << part_two(program, n) << endl;

    return 0;
}
