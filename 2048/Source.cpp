#include <iostream>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

const int field_size = 4;
int field[field_size][field_size];

char step_left_key = 'a';
char step_right_key = 'd';
char step_up_key = 'w';
char step_down_key = 's';
char step_restart_key = 'r';
char step_quit_key = 'q';

bool is_played = false;

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void print_color(int i, int j) {
	if (field[i][j] == 0) {
		color(0); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 2) {
		color(7); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 4) {
		color(2); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 8) {
		color(1); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 16 || field[i][j] == 32) {
		color(5); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 64 || field[i][j] == 128) {
		color(6); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 256 || field[i][j] == 512) {
		color(9); cout << field[i][j]; color(7);
	}
	else if (field[i][j] == 1024 || field[i][j] == 2048) {
		color(8); cout << field[i][j]; color(7);
	}
	else {
		color(3); cout << field[i][j]; color(7);
	}
}

void set_pos(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void set_start_field() {
	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			field[i][j] = 0;
		}
	}

	int two_or_four = rand() % 10;
	int start_x_1 = rand() % field_size;
	int start_y_1 = rand() % field_size;
	int start_x_2 = rand() % field_size;
	int start_y_2 = rand() % field_size;
	if (start_x_2 == start_x_1) {
		for (;;) {
			start_x_2 = rand() % field_size;
			if (start_x_2 != start_x_1) {
				break;
			}
		}
	}
	if (start_y_2 == start_y_1) {
		for (;;) {
			start_y_2 = rand() % field_size;
			if (start_y_2 != start_y_1) {
				break;
			}
		}
	}
	if (two_or_four == 9) {
		field[start_x_1][start_y_1] = 4;
		field[start_x_2][start_y_2] = 2;
	}
	else {
		field[start_x_1][start_y_1] = 2;
		field[start_x_2][start_y_2] = 2;
	}
}

int score_count() {
	int total_score = 0;
	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			total_score += field[i][j];
		}
	}
	return total_score;
}

int x1(int i, int j) {
	if (field[i][j] == 0 || field[i][j] == 2 || field[i][j] == 4 || field[i][j] == 8) {
		return 3;
	}
	else if (field[i][j] == 16 || field[i][j] == 32 || field[i][j] == 64) {
		return 3;
	}
	else if (field[i][j] == 128 || field[i][j] == 256 || field[i][j] == 512) {
		return 2;
	}
	else if (field[i][j] == 1024 || field[i][j] == 2048) {
		return 2;
	}
}

int x2(int i, int j) {
	if (field[i][j] == 0 || field[i][j] == 2 || field[i][j] == 4 || field[i][j] == 8) {
		return 10;
	}
	else if (field[i][j] == 16 || field[i][j] == 32 || field[i][j] == 64) {
		return 10;
	}
	else if (field[i][j] == 128 || field[i][j] == 256 || field[i][j] == 512) {
		return 9;
	}
	else if (field[i][j] == 1024 || field[i][j] == 2048) {
		return 9;
	}
}

int x3(int i, int j) {
	if (field[i][j] == 0 || field[i][j] == 2 || field[i][j] == 4 || field[i][j] == 8) {
		return 17;
	}
	else if (field[i][j] == 16 || field[i][j] == 32 || field[i][j] == 64) {
		return 17;
	}
	else if (field[i][j] == 128 || field[i][j] == 256 || field[i][j] == 512) {
		return 16;
	}
	else if (field[i][j] == 1024 || field[i][j] == 2048) {
		return 16;
	}
}

int x4(int i, int j) {
	if (field[i][j] == 0 || field[i][j] == 2 || field[i][j] == 4 || field[i][j] == 8) {
		return 24;
	}
	else if (field[i][j] == 16 || field[i][j] == 32 || field[i][j] == 64) {
		return 24;
	}
	else if (field[i][j] == 128 || field[i][j] == 256 || field[i][j] == 512) {
		return 23;
	}
	else if (field[i][j] == 1024 || field[i][j] == 2048) {
		return 23;
	}
}

void print_field() {
	char right_high_corner = 201;
	char line_horizontal = 205;
	char left_high_corner = 187;
	char line_vertical = 186;
	char low_left_corner = 188;
	char low_right_corner = 200;
	char line_left = 185;
	char line_right = 204;
	char line_down = 203;
	char line_up = 202;
	char cross = 206;
	char space = ' ';
	cout << right_high_corner << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_down << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_down << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_down << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << left_high_corner << endl <<

		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<

		line_right << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_left << endl <<

		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<

		line_right << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_left << endl <<

		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<

		line_right << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << cross << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_left << endl <<

		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<
		line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << space << space << space << space << space << space << line_vertical << endl <<

		low_right_corner << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_up << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_up << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_up << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << low_left_corner << endl;

	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			if (i == 0 && j == 0) {
				set_pos(x1(i, j), 2);
				print_color(i, j);
			}
			else if (i == 0 && j == 1) {
				set_pos(x2(i, j), 2);
				print_color(i, j);
			}
			else if (i == 0 && j == 2) {
				set_pos(x3(i, j), 2);
				print_color(i, j);
			}
			else if (i == 0 && j == 3) {
				set_pos(x4(i, j), 2);
				print_color(i, j);
			}

			else if (i == 1 && j == 0) {
				set_pos(x1(i, j), 6);
				print_color(i, j);
			}
			else if (i == 1 && j == 1) {
				set_pos(x2(i, j), 6);
				print_color(i, j);
			}
			else if (i == 1 && j == 2) {
				set_pos(x3(i, j), 6);
				print_color(i, j);
			}
			else if (i == 1 && j == 3) {
				set_pos(x4(i, j), 6);
				print_color(i, j);
			}

			else if (i == 2 && j == 0) {
				set_pos(x1(i, j), 10);
				print_color(i, j);
			}
			else if (i == 2 && j == 1) {
				set_pos(x2(i, j), 10);
				print_color(i, j);
			}
			else if (i == 2 && j == 2) {
				set_pos(x3(i, j), 10);
				print_color(i, j);
			}
			else if (i == 2 && j == 3) {
				set_pos(x4(i, j), 10);
				print_color(i, j);
			}

			else if (i == 3 && j == 0) {
				set_pos(x1(i, j), 14);
				print_color(i, j);
			}
			else if (i == 3 && j == 1) {
				set_pos(x2(i, j), 14);
				print_color(i, j);
			}
			else if (i == 3 && j == 2) {
				set_pos(x3(i, j), 14);
				print_color(i, j);
			}
			else if (i == 3 && j == 3) {
				set_pos(x4(i, j), 14);
				print_color(i, j);
			}
		}
	}
	set_pos(35, 4);
	cout << right_high_corner << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_down << line_horizontal << line_horizontal << line_horizontal << line_horizontal << left_high_corner << endl;
	set_pos(35, 5);
	cout << line_vertical << "score" << line_vertical << space << space << space << space << line_vertical << endl;
	set_pos(35, 6);
	cout << low_right_corner << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_horizontal << line_up << line_horizontal << line_horizontal << line_horizontal << line_horizontal << low_left_corner << endl;
	int total_score = score_count();
	int pos_x_score;
	if (total_score < 100) {
		pos_x_score = 43;
	}
	else if (total_score >= 100) {
		pos_x_score = 42;
	}
	set_pos(pos_x_score, 5);
	cout << total_score;
	set_pos(3, 18); cout << step_up_key << " - up";
	set_pos(3, 19); cout << step_left_key << " - left";
	set_pos(3, 20); cout << step_down_key << " - down";
	set_pos(3, 21); cout << step_right_key << " - right";
	set_pos(3, 22); cout << step_restart_key << " - restart";
	set_pos(3, 23); cout << step_quit_key << " - quit to menu";
	set_pos(0, 17);
}

void add_number() {
	int x = rand() % field_size;
	int y = rand() % field_size;
	if (field[x][y] != 0) {
		for (;;) {
			x = rand() % field_size;
			y = rand() % field_size;
			if (field[x][y] == 0) {
				break;
			}
		}
	}
	int two_or_four = rand() % 10;
	if (two_or_four == 9) {
		field[x][y] = 4;
	}
	else {
		field[x][y] = 2;
	}
}

void step_left() {
	for (int i = 0; i < field_size; ++i) {

		for (int t = 0; t < field_size - 1; ++t) {
			for (int j = field_size - 1; j > 0; --j) {
				if (field[i][j - 1] == 0) {
					field[i][j - 1] = field[i][j];
					field[i][j] = 0;
				}
			}
		}
		for (int j = 0; j < field_size - 1; ++j) {
			if (field[i][j] == field[i][j + 1]) {
				field[i][j] *= 2;
				field[i][j + 1] = 0;
			}
		}
		for (int t = 0; t < field_size - 1; ++t) {
			for (int j = field_size - 1; j > 0; --j) {
				if (field[i][j - 1] == 0) {
					field[i][j - 1] = field[i][j];
					field[i][j] = 0;
				}
			}
		}

	}
}

void step_right() {
	for (int i = 0; i < field_size; ++i) {

		for (int t = 0; t < field_size - 1; ++t) {
			for (int j = 0; j < field_size - 1; ++j) {
				if (field[i][j + 1] == 0) {
					field[i][j + 1] = field[i][j];
					field[i][j] = 0;
				}
			}
		}
		for (int j = field_size - 1; j > 0; --j) {
			if (field[i][j] == field[i][j - 1]) {
				field[i][j] *= 2;
				field[i][j - 1] = 0;
			}
		}
		for (int t = 0; t < field_size - 1; ++t) {
			for (int j = 0; j < field_size - 1; ++j) {
				if (field[i][j + 1] == 0) {
					field[i][j + 1] = field[i][j];
					field[i][j] = 0;
				}
			}
		}

	}
}

void step_up() {
	for (int j = 0; j < field_size; ++j) {

		for (int t = 0; t < field_size - 1; ++t) {
			for (int i = field_size - 1; i > 0; --i) {
				if (field[i - 1][j] == 0) {
					field[i - 1][j] = field[i][j];
					field[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < field_size - 1; ++i) {
			if (field[i][j] == field[i + 1][j]) {
				field[i][j] *= 2;
				field[i + 1][j] = 0;
			}
		}
		for (int t = 0; t < field_size - 1; ++t) {
			for (int i = field_size - 1; i > 0; --i) {
				if (field[i - 1][j] == 0) {
					field[i - 1][j] = field[i][j];
					field[i][j] = 0;
				}
			}
		}

	}
}

void step_down() {
	for (int j = 0; j < field_size; ++j) {

		for (int t = 0; t < field_size - 1; ++t) {
			for (int i = 0; i < field_size - 1; ++i) {
				if (field[i + 1][j] == 0) {
					field[i + 1][j] = field[i][j];
					field[i][j] = 0;
				}
			}
		}
		for (int i = field_size - 1; i > 0; --i) {
			if (field[i][j] == field[i - 1][j]) {
				field[i][j] *= 2;
				field[i - 1][j] = 0;
			}
		}
		for (int t = 0; t < field_size - 1; ++t) {
			for (int i = 0; i < field_size - 1; ++i) {
				if (field[i + 1][j] == 0) {
					field[i + 1][j] = field[i][j];
					field[i][j] = 0;
				}
			}
		}
	}

}

void win() {
	system("cls");
	cout << "*   *    ***    *   *      *   *   *   *   *\n";
	Sleep(200);
	cout << " * *    *   *   *   *      *   *   *   **  *\n";
	Sleep(200);
	cout << "  *     *   *   *   *      * * *   *   * * *\n";
	Sleep(200);
	cout << "  *     *   *   *   *      * * *   *   *  **\n";
	Sleep(200);
	cout << "  *      ***     ***       *****   *   *   *\n";
	is_played = false;
}

bool check_win() {
	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			if (field[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}

void lose() {
	system("cls");
	cout << "*   *    ***    *   *      *        ***     ****   *****\n";
	Sleep(200);
	cout << " * *    *   *   *   *      *       *   *   *       *\n";
	Sleep(200);
	cout << "  *     *   *   *   *      *       *   *    ***    *****\n";
	Sleep(200);
	cout << "  *     *   *   *   *      *       *   *       *   *\n";
	Sleep(200);
	cout << "  *      ***     ***       *****    ***    ****    *****\n";
	is_played = false;
}

bool check_cells() {
	int count = 0;
	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			if (field[i][j] != 0) {
				++count;
			}
		}
	}
	if (count == 16) {
		return true;
	}
	else {
		return false;
	}
}

bool check_lose() {
	if (check_cells() == true) {
		for (int i = 0; i < field_size; ++i) {
			for (int j = 0; j < field_size; ++j) {
				if (i < 3 and j < 3) if ((field[i][j] == field[i][j + 1]) or (field[i][j] == field[i + 1][j])) return false;
				if (j == 3) if (field[i][j] == field[i + 1][j]) return false;
				if (i == 3) if (field[i][j] == field[i][j + 1]) return false;
				//if (i == 3 and j == 3) if ((field[i][j] == field[i - 1][j]) or (field[i][j] == field[i][j - 1])) return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void restart() {
	system("cls");
	set_start_field();
	print_field();
}

void start_screen() {
	Sleep(200);
	set_pos(3, 1);
	cout << "*****   *****   *   *   *****";
	Sleep(200);
	set_pos(3, 2);
	cout << "    *   *   *   *   *   *   *";
	Sleep(200);
	set_pos(3, 3);
	cout << "*****   *   *   *****   *****";
	Sleep(200);
	set_pos(3, 4);
	cout << "*       *   *       *   *   *";
	Sleep(200);
	set_pos(3, 5);
	cout << "*****   *****       *   *****";
	Sleep(200);
	set_pos(5, 7);
	cout << "s - start game";
	if (is_played == false) {
		Sleep(200);
		set_pos(5, 8);
		cout << "m - manual & settings";
		Sleep(200);
		set_pos(5, 9);
		cout << "q - quit\n";
	}
	else if (is_played == true) {
		Sleep(200);
		set_pos(5, 8);
		cout << "c - continue game";
		Sleep(200);
		set_pos(5, 9);
		cout << "m - manual & settings";
		Sleep(200);
		set_pos(5, 10);
		cout << "q - quit\n";
	}
}

void left_game() {
	system("cls");
	start_screen();
}

bool if_stepable(char a) {
	int amount = 0;
	int counter = 0;
	for (int i = 0; i < field_size; ++i) {
		for (int j = 0; j < field_size; ++j) {
			if (field[i][j] != 0) {
				++amount;
			}
		}
	}
	if (a == step_down_key) {
		for (int i = 0; i < field_size; ++i) {
			for (int j = 0; j < field_size; ++j) {
				if (i != 3) {
					if (field[i][j] != 0 and field[i + 1][j] != 0 and field[i][j] != field[i + 1][j]) {
						++counter;
					}
				}
				if (i == 3) {
					if (field[i][j] != 0) {
						++counter;
					}
				}
			}
		}
	}
	else if (a == step_up_key) {
		for (int i = 0; i < field_size; ++i) {
			for (int j = 0; j < field_size; ++j) {
				if (i != 0) {
					if (field[i][j] != 0 and field[i - 1][j] != 0 and field[i][j] != field[i - 1][j]) {
						++counter;
					}
				}
				if (i == 0) {
					if (field[i][j] != 0) {
						++counter;
					}
				}
			}
		}
	}
	else if (a == step_left_key) {
		for (int i = 0; i < field_size; ++i) {
			for (int j = 0; j < field_size; ++j) {
				if (j != 0) {
					if (field[i][j] != 0 and field[i][j - 1] != 0 and field[i][j] != field[i][j - 1]) {
						++counter;
					}
				}
				if (j == 0) {
					if (field[i][j] != 0) {
						++counter;
					}
				}
			}
		}
	}
	else if (a == step_right_key) {
		for (int i = 0; i < field_size; ++i) {
			for (int j = 0; j < field_size; ++j) {
				if (j != 3) {
					if (field[i][j] != 0 and field[i][j + 1] != 0 and field[i][j] != field[i][j + 1]) {
						++counter;
					}
				}
				if (j == 3) {
					if (field[i][j] != 0) {
						++counter;
					}
				}
			}
		}
	}

	if (amount == counter) {
		return false;
	}
	else {
		return true;
	}
}

int step() {
	for (;;) {
		char step = _getch();
		if (step == step_left_key) {
			if (if_stepable(step_left_key) == true) {
				step_left();
				return 1;
			}
			else {
				continue;
			}
		}
		else if (step == step_right_key) {
			if (if_stepable(step_right_key) == true) {
				step_right();
				return 1;
			}
			else {
				continue;
			}
		}
		else if (step == step_up_key) {
			if (if_stepable(step_up_key) == true) {
				step_up();
				return 1;
			}
			else {
				continue;
			}
		}
		else if (step == step_down_key) {
			if (if_stepable(step_down_key) == true) {
				step_down();
				return 1;
			}
			else {
				continue;
			}
		}
		else if (step == step_restart_key) {
			restart();
			return 0;
		}
		else if (step == step_quit_key) {
			left_game();
			return 2;
		}
		else if (step == 'p') { //to test win func
			field[0][0] = 1024;
			field[0][1] = 1024;
			return 0;
		}
		else if (step == 'o') { //to test lose func
			for (int i = 0; i < field_size; ++i) {
				for (int j = 0; j < field_size; ++j) {
					if (i == 0 or i == 2) {
						if (j % 2 == 0) {
							field[i][j] = 2;
						}
						else {
							field[i][j] = 4;
						}
					}
					else if (i == 1 or i == 3) {
						if (j % 2 == 0) {
							field[i][j] = 4;
						}
						else {
							field[i][j] = 2;
						}
					}
				}
			}
			return 0;
		}
	}
}

void refresh_field() {
	system("cls");
	print_field();
}

void gameplay() {
	system("cls");
	if (is_played == false) {
		is_played = true;
		set_start_field();
		print_field();
	}
	else if (is_played == true) {
		print_field();
	}
	for (;;) {
		int a = step();
		if (a == 1) {
			add_number();
		}
		if (a == 2) {
			break;
		}
		refresh_field();
		if (check_win() == true) {
			Sleep(2000);
			win();
			Sleep(2000);
			system("cls");
			start_screen();
			break;
		}
		if (check_lose() == true) {
			Sleep(2000);
			lose();
			Sleep(2000);
			system("cls");
			start_screen();
			break;
		}
	}
}

void change_controls() {
	system("cls");
	cout << "choose step:\n  1 - up\n  2 - left\n  3 - down\n  4 - right\n  5 - restart\n  6 - back to menu\n";
	char choose = _getch();
	char* to_change = nullptr;
	for (;;) {
		if (choose == '1' or choose == '2' or choose == '3' or choose == '4' or choose == '5' or choose == '6') {
			switch (choose) {
			case '1':
				to_change = &step_up_key;
				break;
			case '2':
				to_change = &step_left_key;
				break;
			case '3':
				to_change = &step_down_key;
				break;
			case '4':
				to_change = &step_right_key;
				break;
			case '5':
				to_change = &step_restart_key;
				break;
			case '6':
				to_change = &step_quit_key;
				break;
			}
			break;
		}
		else {
			choose = _getch();
		}
	}
	for (;;) {
		cout << "\nenter a new step key: ";
		char new_key;
		cin >> new_key;
		char agreement;
		if (new_key == step_down_key or new_key == step_left_key or new_key == step_quit_key or new_key == step_restart_key or new_key == step_right_key or new_key == step_up_key or new_key == 'p' or new_key == 'o') {
			cout << "\naccess denied. try again\n";
		}
		else {
			cout << "\ndo you really want to change step key (y/n): ";
			for (;;) {
				agreement = _getch();
				if (agreement == 'y') {
					*to_change = new_key;
					break;
				}
				else if (agreement == 'n') {
					break;
				}
			}
			break;
		}
	}
}

void manual() {
	system("cls");
	cout << "controls in game:\n  " << step_up_key << " - up\n  " << step_left_key << " - left\n  " << step_down_key << " - down\n  " << step_right_key << " - right\n  "
		<< step_restart_key << " - restart\n  " << step_quit_key << " - back to menu\n\nclick z to change\nclick q to quit\n";
	char choose = _getch();
	for (;;) {
		if (choose == 'z' or choose == 'q') {
			if (choose == 'z') {
				change_controls();
			}
			break;
		}
		else {
			choose = _getch();
		}
	}

	system("cls");
	start_screen();
}

void quit() {
	system("cls");
	exit(0);
}

void main() {
	srand(time(0));

	start_screen();
	for (;;) {
		char choose = _getch();
		switch (choose) {
		case 's':
			is_played = false;
			gameplay();
			break;
		case 'c':
			gameplay();
			break;
		case 'm':
			manual();
			break;
		case 'q':
			quit();
			break;
		default:
			continue;
		}
	}
}