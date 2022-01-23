#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int binary_to_integer(string bin)
{
    int answer = 0;
    int n = bin.length();
    int digit;

    for (int i = 0; i < n; i++) {
        if (bin[i] == '#') {
            answer += pow(2, n - i - 1);
        }
    }

    return answer;
}

vector<string> enhance(vector<string> image, string &algo, char infinite_bit)
{
    vector<string> enhanced;
    string binary;
    string next;

    int m = image.size();
    int n = image[0].length();

    for (int i = -1; i <= m; i++) {
        next = "";
        for (int j = -1; j <= n; j++) {
            binary = "";
            for (int dx = i-1; dx <= i+1; dx++) {
                for (int dy = j-1; dy <= j+1; dy++) {
                    if (dx >= 0 && dx < m && dy >= 0 && dy < n) {
                        binary.push_back(image[dx][dy]);
                    } else {
                        binary.push_back(infinite_bit);
                    }
                }
            }
            next.push_back(algo[binary_to_integer(binary)]);
        }
        enhanced.push_back(next);
    }

    return enhanced;
}

int solve(int count, vector<string> image, string algo)
{
    int answer = 0;

    for (int i = 0; i < count; i++) {
        image = enhance(image, algo, ((i & 1 & algo[0]) ? '#' : '.'));
    }

    for (const auto &i : image) {
        for (const auto &j : i) {
            if (j == '#') {
                answer++;
            }
        }
    }

    return answer;
}

int main()
{
    string algo;
    cin >> algo;

    string line;
    vector<string> image;
    while (cin >> line) {
        image.push_back(line);
    }

    cout << "Part 1: " << solve(2, image, algo) << endl;
    cout << "Part 2: " << solve(50, image, algo) << endl;

    return 0;
}