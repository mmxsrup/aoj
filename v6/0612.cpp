#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

string board[1001];
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int h, w;
bool hantei(int y, int x){
	if(0 <= y && y < h && 0 <= x && x < w) return true;
	else return false;
}

int main(void){
	cin >> h >> w;
	rep(i, h) cin >> board[i];
	queue<pair<int, int> > q1, q2;
	rep(i, h)rep(j, w){
		if(board[i][j] != '.') q1.push(make_pair(i, j));
	}

	int ans = -1, cnt = 0, nowy, nowx;
	bool flag = true;
	while(flag){
		flag = false; ans++;
		vector<pair<int, int> > memo;//一回の波で城が潰れる位置座標を記録しておく
		set<pair<int, int> > s;
		if(cnt % 2 == 0){
			while(!q1.empty()){//q1を使うとき
				pair<int, int> now = q1.front(); q1.pop();
				if(board[now.first][now.second] == '.') continue;
				int tmp = 0;
				rep(i, 8){
					int nowy = now.first + dy[i], nowx = now.second + dx[i];
					if(!hantei(nowy, nowx)) continue;
					if(board[nowy][nowx] == '.')tmp++;
				}
				if(tmp >= board[now.first][now.second] - '0'){
					memo.push_back(make_pair(now.first, now.second));
					rep(k, 8){//城が崩れた周りの城は次の波で崩れる可能性があるので
						int ny = now.first + dy[k], nx = now.second + dx[k];
						if(!hantei(ny, nx)) continue;
						if(board[ny][nx] != '.'){
							s.insert(make_pair(ny, nx));
						}
					}
					flag = true;
				}
			}
		}else{
			while(!q2.empty()){//q2を使うとき
				pair<int, int> now = q2.front(); q2.pop();
				if(board[now.first][now.second] == '.') continue;
				int tmp = 0;
				rep(i, 8){
					int nowy = now.first + dy[i], nowx = now.second + dx[i];
					if(!hantei(nowy, nowx)) continue;
					if(board[nowy][nowx] == '.')tmp++;
				}
				if(tmp >= board[now.first][now.second] - '0'){
					memo.push_back(make_pair(now.first, now.second));
					rep(k, 8){//城が崩れた周りの城は次の波で崩れる可能性があるので
						int ny = now.first + dy[k], nx = now.second + dx[k];
						if(!hantei(ny, nx)) continue;
						if(board[ny][nx] != '.'){
							s.insert(make_pair(ny, nx));
						}
					}
					flag = true;
				}
			}
		}
		//城を潰す
		rep(k, memo.size()){
			board[memo[k].first][memo[k].second] = '.';
		}
		if(cnt % 2 == 0){
			for(auto x : s) q2.push(make_pair(x.first, x.second));
		}else{
			for(auto x : s) q1.push(make_pair(x.first, x.second));
		}
		cnt++;
	}
	printf("%d\n", ans);
	return 0;
}