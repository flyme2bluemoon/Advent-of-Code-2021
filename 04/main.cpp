#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

#define BOARD_SIZE 5

vector<int> get_order()
{
    string csv;
    cin >> csv;

    vector<int> order;
    stringstream ss(csv);

    for (int i; ss >> i;) {
        order.push_back(i);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    cin.ignore(2);

    return order;
}

vector< vector<int> > get_board()
{
    vector< vector<int> > board;
    int tmp;
    for (int i = 0; i < BOARD_SIZE; i++) {
        vector<int> current_row;
        for (int j = 0; j < BOARD_SIZE; j++) {
            cin >> tmp;
            current_row.push_back(tmp);
        }
        board.push_back(current_row);
    }
    cin.ignore(2);

    return board;
}

bool check_board(vector< vector<int> > board)
{
    bool win = false;
    for (int a = 0; a < BOARD_SIZE && !win; a++) {
        win = true;
        for (int b = 0; b < BOARD_SIZE; b++) {
            if (board[a][b] != -1) {
                win = false;
                break;
            }
        }
    }
    for (int a = 0; a < BOARD_SIZE && !win; a++) {
        win = true;
        for (int b = 0; b < BOARD_SIZE; b++) {
            if (board[b][a] != -1) {
                win = false;
                break;
            }
        }
    }

    return win;
}

int part_one(vector<int> order, int order_len, vector< vector< vector<int> > > all_boards, int number_of_boards)
{
    bool win = false;
    int answer = 0;
    for (int i = 0; i < order_len && !win; i++) {
        for (int j = 0; j < number_of_boards; j++) {
            for (int a = 0; a < BOARD_SIZE; a++) {
                for (int b = 0; b < BOARD_SIZE; b++) {
                    if (all_boards[j][a][b] == order[i]) {
                        all_boards[j][a][b] = -1;
                    }
                }
            }
        }

        for (int j = 0; j < number_of_boards; j++) {
            if (check_board(all_boards[j])) {
                int sum = 0;
                for (int a = 0; a < BOARD_SIZE; a++) {
                    for (int b = 0; b < BOARD_SIZE; b++) {
                        if (all_boards[j][a][b] != -1) {
                            sum += all_boards[j][a][b];
                        }
                    }
                }
                return order[i] * sum;
            }
        }
    }

    return -1;
}

int part_two(vector<int> order, int order_len, vector< vector< vector<int> > > all_boards, int number_of_boards)
{
    int answer = 0;
    bool completed[number_of_boards];
    bool all_completed;
    memset(completed, false, number_of_boards*sizeof(bool));

    for (int i = 0; i < order_len; i++) {
        for (int j = 0; j < number_of_boards; j++) {
            for (int a = 0; a < BOARD_SIZE; a++) {
                for (int b = 0; b < BOARD_SIZE; b++) {
                    if (all_boards[j][a][b] == order[i]) {
                        all_boards[j][a][b] = -1;
                    }
                }
            }
        }

        for (int j = 0; j < number_of_boards; j++) {
            if (!completed[j]) {
                if (check_board(all_boards[j])) {
                    completed[j] = true;
                }
            }
            all_completed = true;
            for (int k = 0; k < number_of_boards; k++) {
                if (!completed[k]) {
                    all_completed = false;
                    break;
                }
            }
            if (all_completed) {
                int sum = 0;
                for (int a = 0; a < BOARD_SIZE; a++) {
                    for (int b = 0; b < BOARD_SIZE; b++) {
                        if (all_boards[j][a][b] != -1) {
                            sum += all_boards[j][a][b];
                        }
                    }
                }

                return order[i] * sum;
            }
        }
    }

    return -1;
}

int main()
{
    vector<int> order = get_order();
    int order_len = order.size();

    vector< vector< vector<int> > > all_boards;
    while(!cin.eof()) {
        all_boards.push_back(get_board());
    }
    int number_of_boards = all_boards.size();

    cout << "Part 1: " << part_one(order, order_len, all_boards, number_of_boards) << endl;
    cout << "Part 2: " << part_two(order, order_len, all_boards, number_of_boards) << endl;

    return 0;
}