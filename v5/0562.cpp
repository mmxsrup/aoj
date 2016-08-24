#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

const int INF = 1e9;
const int MAX_N = 3010, MAX_E = 10000;
int n, m; //町の数 道路の本数
vector<pair<int, int> > G[MAX_N];//グラフを表す隣接リスト fi:to se:cost
int d[MAX_N]; //sからの最短経路
typedef pair<int, int> P;//firstは最短距離,secondは頂点の番号
int k; vector<int> shop;//店を記録

void dijkstra(void){
	priority_queue<P, vector<P>, greater<P> > que;//firstが小さい順に
    rep(i, n)d[i] = INF;//初期化
    
    //k個のスタート地点を登録
    for(auto i : shop){
    	d[i] = 0;
    	que.push(make_pair(0, i));
    }
  
    while(!que.empty()){
       	auto p = que.top(); que.pop();
       	int v = p.second;
       	if(d[v] < p.first) continue;
       	for(auto e : G[v]){//e.fi:隣接している頂点の番号 e.se:その頂点までのコスト
       		if(d[e.first] > d[v] + e.second){//最短距離が更新されるとき
       			d[e.first] = d[v] + e.second;
       			que.push(make_pair(d[e.first], e.first));
       		}
       	}
    }
}

int main(void){
    cin >> n >> m >> k;
    rep(i, m){
        int a, b, l; cin >> a >> b >> l;
        a--; b--;
       	G[a].push_back(make_pair(b, l)); G[b].push_back(make_pair(a, l));
    }
    rep(i, k){
    	int s; cin >> s; s--;
    	shop.push_back(s);
    }
    dijkstra();//店から他の町への最小値を出す
    //道路の間の家も考えた最小値を出す
    double ans = 0.0;
    //x-yのどちらかが店の時
    rep(i, n) ans = max(ans, (double)d[i]);
    //辺の両端の最短距離を利用して、その辺に家がある場合の店からの最長距離を出す
   	for (int x = 0; x < n; ++x){
   		for(auto y : G[x]){
   			if(d[x] == 0 || d[y.first] == 0) continue;
   			double tmp = (d[x] + d[y.first] + y.second) / 2.0;//+1は四捨五入用
   			ans = max(tmp, ans);
   		}
   	}
   	cout << round(ans) << endl;
   	return 0;
}