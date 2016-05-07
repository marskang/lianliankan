#include "GameEntity.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

int startX = 70;
int startY = 70;
int eachWidth = 50;
int width = eachWidth * COL;
int height = eachWidth * ROW;
int endX = startX + width;
int endY = startY + height;
int gameMap[ROW + 2][COL + 2];
int objCount = 7;
Point nowPoint;
Point animationPath[(ROW + 2) * (COL + 2)];

int visited[ROW + 2][COL + 2];
bool flag = false;
int dir[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };
int tx, ty;
//¼ÇÂ¼Â·¾¶
int animationNum = 0;

void initData() {
	nowPoint.x = -1;
	nowPoint.y = -1;
	for (int i = 0; i < ROW + 2; i++) {
		memset(gameMap[i], 0, sizeof(gameMap[i]));
	}
	initVisited();
	srand((unsigned)time(NULL));
	int num = ROW * COL / objCount / 2;
	for (int i = 1; i <= objCount; i++) {
		for (int j = 0; j < num; j++) {
			int count = 0;
			while (count < 2) {
				int r = (rand() % ROW) + 1;
				int c = (rand() % COL) + 1;
				if (!gameMap[r][c]) {
					gameMap[r][c] = i;
					count++;
				}
			}
		}
	}
	for (int i = 0; i < ROW + 2; i++) {
		gameMap[i][0] = 0;
		gameMap[i][COL + 1] = 0;
	}
	for (int i = 0; i < COL + 2; i++) {
		gameMap[0][i] = 0;
		gameMap[ROW + 1][i] = 0;
	}
}

void initVisited() {
	for (int i = 0; i < ROW + 2; i++) {
		memset(visited[i], false, sizeof(visited[i]));
	}
	animationNum = 0;
}

void dfs(int x, int y, int turnCount, int d, int n) {
	if (turnCount > 2 || visited[x][y] || flag) {
		return;
	}

	visited[x][y] = true;
	for (int i = 0; i < 4; i++) {
		if (flag) {
			return;
		}
		int rx = dir[i][0] + x;
		int ry = dir[i][1] + y;
		if (rx < 0 || rx >= ROW + 2 || ry < 0 || ry >= COL + 2) {
			continue;
		}
		int t;
		if (d != i) {
			t = turnCount + 1;
		} else {
			t = turnCount;
		}
		if (t > 2) {
			continue;
		}
		if (tx == rx && ty == ry && t <= 2) {
			flag = true;
			animationPath[n].x = rx;
			animationPath[n].y = ry;
			animationNum = n + 1;
			return;
		}
		if (!gameMap[rx][ry] && !visited[rx][ry]) {
			animationPath[n].x = rx;
			animationPath[n].y = ry;
			dfs(rx, ry, t, i, n + 1);
		}
	}
	visited[x][y] = false;
}