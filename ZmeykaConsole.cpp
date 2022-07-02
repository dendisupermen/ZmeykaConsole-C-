#include <iostream>
#include <conio.h>
#include<Windows.h>

using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int xtail[100], ytail[100], ntail;
enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
edirection dir;
void setup() {
	gameover = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;

}

void draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++)
		cout « "#";
	cout « endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout « "#";
			if (i == y && j == x)
				cout « "0";
			else if (i == fruity && j == fruitx)
				cout « "f";
			else {
				bool print = false;
				for (int k = 1; k < ntail; k++) {
					if (xtail[k] == j && ytail[k] == i) {
						print = true;
						cout « "o";
					}

				}
				if (!print)
					cout « " ";

			}



		}
		cout « endl;
	}


	for (int i = 0; i < width + 1; i++)
		cout « "#";
	cout « endl;
	cout « "Score" « score;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case'a':
		case 75:
			dir = LEFT;
			break;

		case 77:
		case 'd':
			dir = RIGHT;
			break;
		case 's':
		case 80:
			dir = DOWN;
			break;
		case 'w':
		case 72:
			dir = UP;
			break;
		case 'x':
		case 27:
			gameover = true;
			break;

		}

	}
}

void logic() {
	int prevx = xtail[0];// предыдущее значение икса
	int prevy = ytail[0];//предыдущее значение игрика
	int prev2x, prev2y;
	xtail[0] = x;
	ytail[0] = y;
	for (int i = 1; i < ntail; i++) {
		prev2x = xtail[i];
		prev2y = ytail[i];
		xtail[i] = prevx;
		ytail[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;

	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case UP:
		y--;
		break;

	}
	if (x > width || x < 0)
		gameover = true;
	if (y > height || y < 0)
		gameover = true;
	if (x == fruitx && y == fruity) {
		score += 10;
		fruitx = rand() % width;
		fruity = rand() % height;
		ntail++;
	}


}

int main() {
	setup();
	while (!gameover) {
		draw();
		input();
		logic();
		Sleep(200);

	}

	return 0;
}