#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
const int INF = 1e9;

int n, k; //町の数 道路の本数
int c[5010], r[5010]; //運賃　連続して通れる道路の本数
vector<int> d[5010];//道路を隣接
int G[5010][5010];//rの制限を満たしていける町を隣接リストで記録

int dist[5010]; //0->iへの最小コスト
bool used[5010]; //使った町を記録

void dijkstra(int start){
	rep(i, n) dist[i] = INF;//初期化
	dist[start] = 0;
	while(1){
		int v = -1;
		//まだ使われていない頂点のうち距離が最小のものを探す
		for (int u = 0; u < n; ++u){
			if(!used[u] && (v == -1 || dist[u] < dist[v])) v = u;
		}
		//最終的に距離が最小の町の番号がvに
		if(v == -1) break;
		used[v] = true;//使用した
		for (int u = 0; u < n; ++u){
			dist[u] = min(dist[u], dist[v] + G[v][u]);//この時に隣接リストのGだとできない
		}
	}
}

int main(void){
	cin >> n >> k;
	rep(i, n) cin >> c[i] >> r[i];
	rep(i, k){
		int a, b; cin >> a >> b;
		a--; b--;
		d[a].push_back(b);
		d[b].push_back(a);
	}

	rep(i, 5010)rep(j, 5010) G[i][j] = INF;
	//幅優先探索を用いて、i町->j町に行くことができるかを記録する。O(nk)
	for (int i = 0; i < n; ++i){
		queue<pair<int, int> > q; q.push(make_pair(i, 0));//<町, 何本目>
		int cnt = 0;
		while(!q.empty()){
			auto now = q.front(); q.pop();
			if(now.second >= r[i]) continue;
			for(auto j : d[now.first]){
				if(G[i][j] != INF) continue;
				q.push(make_pair(j, now.second + 1));
				G[i][j] = c[i];//隣接行列を使ってコストを記録
			}
		}
	}
	dijkstra(0);
	printf("%d\n", dist[n - 1]);
}