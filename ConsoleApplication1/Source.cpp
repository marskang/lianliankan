#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

int map[8][8];
int visited[8][8];
bool flag = false;
int dir[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
int tx, ty;

typedef struct Point {
	int x;
	int y;
};
Point points[64];
int num = 0;

void dfs(int x, int y, int turnCount, int d, int n)  {
	if (turnCount > 2 || visited[x][y] || flag) {
		return;
	}
	visited[x][y] = true;
	for (int i = 0; i < 4; i++) {
		if (flag) return;
		int rx = dir[i][0] + x;
		int ry = dir[i][1] + y;
		if (rx < 0 || rx >= 8 || ry < 0 || ry >= 9) {
			continue;
		}
		int t;
		if (d != i) {
			t = turnCount + 1;
		} else {
			t = turnCount;
		}
		if (tx == rx && ty == ry && t <= 2) {
			flag = true;
			num = n;
			return;
		}
		if (t > 2) {
			continue;
		}
		if (!map[rx][ry] && !visited[rx][ry]) {
			points[n].x = rx;
			points[n].y = ry;
			dfs(rx, ry, t, i, n+1);
		}
	}
	visited[x][y] = false;
}

const int row = 7;
const int col = 10;
int gameMap[row][col];
int objCount = 7;

void initData() {
	for (int i = 0; i < row; i++) {
		memset(gameMap[i], 0, sizeof(gameMap[i]));
	}
	srand((unsigned)time(NULL));
	int num = row * col / objCount /2;
	for (int i = 1; i <= objCount; i++) {
		for (int j = 0; j < num; j++) {
			int count = 0;
			while (count < 2) {
				int r = rand() % row;
				int c = rand() % col;
				if (!gameMap[r][c]) {
					gameMap[r][c] = i;
					count++;
				}
			}
		}
	}
}

int main() {
	memset(visited, false, sizeof(visited));
	memset(map, -1, sizeof(map));
	tx = 5;
	ty = 3;
	map[1][1] = 2;
	map[5][3] = 2;
	map[2][1] = 0;
	map[2][2] = 0;
	map[2][3] = 0;
	map[3][3] = 0;
	map[4][3] = 0;
	//map[5][3] = 0;
	map[6][3] = 0;
	map[6][4] = 0;
	map[6][5] = 0;
	/*for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%2d ", map[i][j]);
		}
		printf("\n");
	}*/
	dfs(1,1,-1,-1, 0);
	if (flag) {
		for (int i = 0; i < num; i++) {
			printf("%d %d\n", points[i].x, points[i].y);
		}
	} else {
		printf("no\n");
	}
	printf("===============================\n");
	initData();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%2d ", gameMap[i][j]);
		}
		printf("\n");
	}
	system("pause");
}