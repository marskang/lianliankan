#define ROW 7
#define COL 10


struct  Point {
	int x;
	int y;
};

extern int startX;
extern int startY;
extern int width;
extern int height;
extern int eachWidth;
extern int endX;
extern int endY;
extern int gameMap[ROW + 2][COL + 2];
extern Point animationPath[(ROW + 2) * (COL + 2)];
extern int animationNum;
extern Point nowPoint;
extern bool flag;
extern int tx, ty;
void initData();
void initVisited();
void dfs(int x, int y, int turnCount, int d, int n);