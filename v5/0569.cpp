#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int w, h;
bool board[110][110];//trueは建物のある座標
bool flag[110][110];//trueのものは与えられた建物の外周と接する可能性のある座標
bool used[110][110];//bfsをするときのメモ
//y座標が奇数
int dx_kisuu[6] = {1, 1, 1, 0, -1, 0};
int dy_kisuu[6] = {-1, 0, 1, 1, 0, -1};
//y座標が偶数
int dx_gusuu[6] = {0, 1, 0, -1, -1, -1};
int dy_gusuu[6] = {-1, 0, 1, 1, 0, -1};

bool hantei(int nowy, int nowx){//範囲内か判定
	if(0 <= nowy && nowy <= h + 1 && 0 <= nowx && nowx <= w + 1){
		return true;
	}else{
		return false;
	}
}

int main(void){
	cin >> w >> h;
	//与えられたものの周りを0で囲む
	for (int i = 1; i <= h; ++i){
		for (int j = 1; j <= w; ++j){
			cin >> board[i][j];
		}
	}

	queue<pair<int, int> > q;
	q.push(make_pair(0, 0));
	//bfs
	while(!q.empty()){
		pair<int, int> now;//first y second x
		now = q.front(); q.pop();
		if(now.first % 2 == 0){
			rep(i, 6){
				int nowy = now.first  + dy_gusuu[i];
				int nowx = now.second + dx_gusuu[i];
				if(hantei(nowy, nowx)){
					if(!board[nowy][nowx] && !used[nowy][nowx]){
						q.push(make_pair(nowy, nowx));
						flag[nowy][nowx] = true;
						used[nowy][nowx] = true;
					}
				}
			}
		}else{
			rep(i, 6){
				int nowy = now.first  + dy_kisuu[i];
				int nowx = now.second + dx_kisuu[i];
				if(hantei(nowy, nowx)){
					if(!board[nowy][nowx] && !used[nowy][nowx]){
						q.push(make_pair(nowy, nowx));
						flag[nowy][nowx] = true;
						used[nowy][nowx] = true;
					}
				}
			}
		}
	}

	long long sum = 0;
	for (int i = 0; i <= h + 1; ++i){
		for (int j = 0; j <= w + 1; ++j){
			if(flag[i][j]){//flag=trueのマスの部分はboard=trueのマス(建物)と接しているマスの可能性がある。
				int tmp = 0;
				if(i % 2 == 0){
					for (int k = 0; k < 6; ++k){
						int nowy = i + dy_gusuu[k], nowx = j + dx_gusuu[k];
						//実際に建物と接していた場合、イルミネーションを施す必要があったということ
						if(board[nowy][nowx] && hantei(nowy, nowx)) sum++;
					}
				}else{
					for (int k = 0; k < 6; ++k){
						int nowy = i + dy_kisuu[k], nowx = j + dx_kisuu[k];
						if(board[nowy][nowx] && hantei(nowy, nowx)) sum++;
					}
				}
			}
		}
	}
	printf("%lld\n", sum);
	return 0;
}