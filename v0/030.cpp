#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)

int cnt = 0;
// n := 残りの選択する数字の数 s := 残りの合計 now := 現在選択可能な数字
void dfs(int n, int s, int now){
	if(now > 9){
		//n個選択して、合計s
		if(n == 0 && s == 0) cnt++;
		return;
	}
	dfs(n - 1, s - now, now + 1);//数字nowを選択する
	dfs(n, s, now + 1);//数字nowを選択しない
	return;
}
int main(void){
	while(1){
		int n, s; cin >> n >> s;
		if(n == 0 && s == 0) return 0;
		cnt = 0;
		dfs(n, s, 0);
		printf("%d\n", cnt);
	}
}