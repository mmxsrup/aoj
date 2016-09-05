#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
int dy[] = {1, 0, 0, -1};
int dx[] = {0, 1, -1, 0};
int b[110][110];
int w, h;
int xs, ys, xg, yg;
int color;
bool flag = false;
bool used[110][110];

void dfs(int y, int x, int py, int px){
	rep(i, 4){
		int ny = y + dy[i], nx = x + dx[i];
		if(used[ny][nx]) continue;//調べたところはもう調べない
		if(!(0 <= ny && ny < h && 0 <= nx && nx < w)) continue;
		if(b[ny][nx] != color) continue;
		if(ny == py && nx == px) continue;//戻るの禁止
		if(ny == yg && nx == xg){
			used[ny][nx] = true;
			flag = true; return;//見つけた
		}
		used[ny][nx] = true;
		dfs(ny, nx, y, x);
	}
	return;//もう探すところがない
}

int main(void){
	while(1){
		rep(i, 110)rep(j, 110){
			b[i][j] = -1; used[i][j] = false;
		}
		cin >> w >> h;
		if(w == 0 && h == 0) return 0;
		cin >> xs >> ys >> xg >> yg;
		xs--; ys--; xg--; yg--;
		int n; cin >> n;
		rep(i, n){
			int c, d, x, y;
			cin >> c >> d >> x >> y;
			x--; y--;
			if(d == 0){//横
				b[y][x] = b[y][x + 1] = b[y][x + 2] = b[y][x + 3] = c;
				b[y + 1][x] = b[y + 1][x + 1] = b[y + 1][x + 2] = b[y + 1][x + 3] = c;
			}else{//縦
				b[y][x] = b[y][x + 1] = c;
				b[y + 1][x] = b[y + 1][x + 1] = c;
				b[y + 2][x] = b[y + 2][x + 1] = c;
				b[y + 3][x] = b[y + 3][x + 1] = c;
			}
		}
		color = b[ys][xs];
		if(color == -1) {//スタートにブロックなし
			printf("NG\n"); continue;
		}
		used[ys][xs] = true; flag = false;
		dfs(ys, xs, -1, -1);
		if(flag) printf("OK\n");
		else printf("NG\n");
	}
}