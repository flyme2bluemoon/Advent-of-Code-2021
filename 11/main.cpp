#include <iostream>

using namespace std;

#define SIZE 10

void copy_matrix(int src[SIZE][SIZE], int dest[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void flash(int mat[SIZE][SIZE], int x, int y, int &flashes)
{
    flashes++;
    mat[x][y] = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if ((dx == 0 && dy == 0) || x + dx < 0 || x + dx >= SIZE || y + dy < 0 || y + dy >= SIZE || mat[x+dx][y+dy] == 0) {
                continue;
            }
            mat[x+dx][y+dy]++;
            if (mat[x+dx][y+dy] > 9) {
                flash(mat, x+dx, y+dy, flashes);
            }
        }
    }
}

int part_one(int octopus[SIZE][SIZE])
{
    int flashes = 0;
    int simulation[SIZE][SIZE];
    copy_matrix(octopus, simulation);

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                simulation[j][k]++;
            }
        }
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (simulation[j][k] > 9) {
                    flash(simulation, j, k, flashes);
                }
            }
        }
    }

    return flashes;
}

int part_two(int octopus[SIZE][SIZE])
{
    int flashes;
    int simulation[SIZE][SIZE];
    copy_matrix(octopus, simulation);

    for (int step_count = 1; ; step_count++) {
        flashes = 0;
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                simulation[j][k]++;
            }
        }
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (simulation[j][k] > 9) {
                    flash(simulation, j, k, flashes);
                }
            }
        }
        if (flashes == 100) {
            return step_count;
        }
    }
}

int main()
{
    int octopus[SIZE][SIZE];
    char tmp;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> tmp;
            octopus[i][j] = tmp - '0';
        }
        cin.ignore(1);
    }

    cout << "Part 1: " << part_one(octopus) << endl;
    cout << "Part 2: " << part_two(octopus) << endl;

    return 0;
}
