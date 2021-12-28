#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void horizontal_fold(vector< vector<bool> > &paper, int x_max, int &y_max, int fold_line)
{
    for (int i = 0; i < x_max; i++) {
        for (int j = 1; j < y_max - fold_line; j++) {
            paper[i][fold_line - j] = paper[i][fold_line + j] || paper[i][fold_line - j];
        }
    }

    y_max = fold_line;
}

void vertical_fold(vector< vector<bool> > &paper, int &x_max, int y_max, int fold_line)
{
    for (int i = 1; i < x_max - fold_line; i++) {
        for (int j = 0; j < y_max; j++) {
            paper[fold_line - i][j] = paper[fold_line + i][j] || paper[fold_line - i][j];
        }
    }

    x_max = fold_line;
}

void fold(pair<char, int> fold, vector< vector<bool> > &paper, int &x_max, int &y_max) {
    if (fold.first == 'x') {
        vertical_fold(paper, x_max, y_max, fold.second);
    } else {
        horizontal_fold(paper, x_max, y_max, fold.second);
    }
}

int part_one(vector< vector<bool> > paper, const vector< pair<char, int> > &folds)
{
    int answer = 0;

    int x_max = paper.size();
    int y_max = paper[0].size();

    fold(folds[0], paper, x_max, y_max);

    for (int i = 0; i < x_max; i++) {
        for (int j = 0; j < y_max; j++) {
            if (paper[i][j]) {
                answer++;
            }
        }
    }

    return answer;
}

void part_two(vector< vector<bool> > paper, const vector< pair<char, int> > &folds)
{
    int x_max = paper.size();
    int y_max = paper[0].size();

    for (const auto &current_fold : folds) {
        fold(current_fold, paper, x_max, y_max);
    }

    for (int i = 0; i < y_max; i++) {
        for (int j = 0; j < x_max; j++) {
            if (paper[j][i]) {
                cout << "\u2588";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return;
}

int main()
{
    string line;
    int x, y, fold_line;
    int x_max = 0;
    int y_max = 0;
    vector< pair<int, int> > dots;
    vector< pair<char, int> > folds;

    while (cin >> line) {
        if (!line.compare("fold") || !line.compare("along")) {
            continue;
        }

        stringstream ss(line);

        if (isdigit(line[0])) {
            ss >> x;
            ss.ignore(1);
            ss >> y;
            if (x > x_max) {
                x_max = x;
            }
            if (y > y_max) {
                y_max = y;
            }
            dots.push_back(make_pair(x, y));
        } else {
            ss.ignore(2);
            ss >> fold_line;
            folds.push_back(make_pair(line[0], fold_line));
        }
    }

    x_max++;
    y_max++;

    vector< vector<bool> > paper(x_max, vector<bool>(y_max, false));
    for (const auto &i : dots) {
        paper[i.first][i.second] = true;
    }

    cout << "Part 1: " << part_one(paper, folds) << endl;
    cout << "Part 2: \n";
    part_two(paper, folds);

    return 0;
}
