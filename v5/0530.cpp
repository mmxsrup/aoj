#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
#define fi first
#define se second
const int INF = 1e9;
int n, m; 
int bmemo[160][1010];//b[y][x]
vector<pair<int, int> > b[160];//
int dp[160][1010][80];//dp[y座標][x座標][1つ飛ばしジャンプの回数] = この時の最小値
int main(void){
	while(1){
		//input
		cin >> n >> m;
		if(n == 0 && m == 0) return 0;
		rep(i, 160)rep(j, 1010) bmemo[i][j] = INF;
		rep(i, 160) b[i].clear();//初期化
		rep(i, n){
			int k; cin >> k;
			rep(j, k){//k個分の座標
				int x, s; cin >> x >> s; x--;
				b[i].push_back(make_pair(x, s));
				bmemo[i][x] = s;
			}
		}

		rep(i, 160)rep(j, 1010)rep(k, 80) dp[i][j][k] = INF;
		for(auto start1 : b[0]){//初めに普通のジャンプ
			dp[0][start1.fi][0] = 0;
		}

		for(auto start2 : b[1]){//初めに１つ飛ばしジャンプ
			dp[1][start2.fi][1] = 0;
		}

		//配るdp
		for (int i = 0; i <  n - 1; ++i){
			for (int j = 0; j < 1010; ++j){
				for (int k = 0; k <= m; ++k){
					if(dp[i][j][k] == INF) continue;
					//普通のジャンンプ
					for(auto next : b[i + 1]){
						int score = (bmemo[i][j] + next.se) * abs(j - next.fi);//追加される危険度
						dp[i + 1][next.fi][k] = min(dp[i + 1][next.fi][k], dp[i][j][k] + score);
					}
					if(k == m || i == n - 2) continue;
					//１つ飛ばしジャンプ
					for(auto next : b[i + 2]){
						int score = (bmemo[i][j] + next.se) * abs(j - next.fi);//追加される危険度
						dp[i + 2][next.fi][k + 1] = min(dp[i + 2][next.fi][k + 1], dp[i][j][k] + score);
					}
				}
			}
		}

		//最小値をさがす
		int ans = INF;
		for (int j = 0; j < 1010; ++j){//最後が普通のジャンプ
			for (int k = 0; k <= m; ++k){
				ans = min(ans, dp[n - 1][j][k]);
			}
		}

		for (int j = 0; j < 1010; ++j){//最後が1つ飛ばしのジャンプ
			for (int k = 0; k <= m - 1; ++k){
			 	ans = min(ans, dp[n - 2][j][k]);
			}
		}
		cout << ans << endl;
	}
}