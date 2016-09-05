#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
int dy[] = {1, 0, 0, -1};
int dx[] = {0, 1, -1, 0};
vector<string> s(12);

void dfs(int y, int x){
	s[y][x] = '0';
	rep(i, 4){
		int ny = y + dy[i], nx = x + dx[i];
		if(!(0 <= ny && ny < 12 && 0 <= nx && nx < 12)) continue;
		if(s[ny][nx] == '0') continue;
		dfs(ny, nx);
	}
	return;//さらに深く探すことができるない時
}

int main(void){
	while(1){
		int cnt = 0;
		rep(i, 12){
			if(!(cin >> s[i])) return 0;//読み込み失敗した場合
		}

		rep(y, 12)rep(x, 12){
			if(s[y][x] == '1'){
				dfs(y, x);
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}