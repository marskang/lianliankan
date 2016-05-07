#include "GameControl.h"
#include "GameEntity.h"
#include <stdlib.h>
#include <stdio.h>

GameControl::GameControl() {
}


GameControl::~GameControl() {
}

void GameControl::MouseLClickEvent(POINT p) {
	int x = p.x;
	int y = p.y;
	int nx = nowPoint.x;
	int ny = nowPoint.y;
	int ry;
	int rx;
	if (x >= startX && x <= endX && y >= startY && y <= endY) {
		ry = ((x - startX) / eachWidth) + 1;
		rx = ((y - startY) / eachWidth) + 1;
	} else {
		return;
	}
	if (nowPoint.x == -1 || nowPoint.y == -1) {
		nowPoint.x = rx;
		nowPoint.y = ry;
		return;
	}
	if (nx == rx && ny == ry) {
		return;
	}
	//如果在边缘，可以直接消除
	/*if ((nx == 0 && rx == 0) || 
		(ny == 0 && ry == 0) || 
		((nx == ROW - 1) && (rx == ROW - 1 )) || 
		((ny == COL - 1) && (ry == COL - 1))) {
		if (gameMap[nx][ny] == gameMap[rx][ry]) {
			flag = false;
			OutputDebugString("可以消除\n");
			gameMap[nx][ny] = 0;
			gameMap[rx][ry] = 0;
			nowPoint.x = -1;
			nowPoint.y = -1;
			return;
		}
	}*/
	if (gameMap[rx][ry] != gameMap[nx][ny]) {
		nowPoint.x = rx;
		nowPoint.y = ry;
		return;
	}
	tx = rx;
	ty = ry;
	initVisited();
	animationPath[0].x = nx;
	animationPath[0].y = ny;
	dfs(nx, ny, -1 , -1, 1);
	if (flag) {
		flag = false;
		OutputDebugString("可以消除\n");
		gameMap[nx][ny] = 0;
		gameMap[rx][ry] = 0;
		nowPoint.x = -1;
		nowPoint.y = -1;
		for (int i = 0; i < animationNum; i++) {
			char cx[256];
			char cy[256];
			sprintf_s(cx, "%ld", animationPath[i].x);
			sprintf_s(cy, "%ld", animationPath[i].y);
			OutputDebugString(cx);
			OutputDebugString(" ");
			OutputDebugString(cy);
			OutputDebugString("\n");
		}
	} else {
		nowPoint.x = rx;
		nowPoint.y = ry;
	}
}

void GameControl::initData() {
	initData();
}