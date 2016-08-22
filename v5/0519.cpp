#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
const int INF = 1e9;

int n;//サッカーチームの数
int m;//与えられた支配の勝敗の個数
vector<int> G[5010];
bool flag[5010];
list <int> out;
void dfs(int u){
	flag[u] = true;
	for(auto v : G[u]){
		if(!flag[v]) dfs(v);
	}
	//トポロジカルソートの先頭から見つかるので、順に先頭に追加していく
	out.push_front(u);
}

int main(void){
	cin >> n;//サッカーチームの数
	cin >> m;//与えられた支配の勝敗の個数
	rep(i, m){
		int a, b; cin >> a >> b;//a勝　b負
		a--; b--;//
		G[b].push_back(a);// b -> a
	}

	rep(i, n){
		if(!flag[i]) dfs(i);
	}

	//出力
	vector<int> memo;
    for(auto itr = out.begin(); itr != out.end(); ++itr){
    	memo.push_back(*itr);
    }
    for (int i = memo.size() - 1; i >= 0; --i){
    	cout << memo[i] + 1 << endl;//1originになおして出力
    }

    for(int i; i < memo.size() - 1; i++){
    	int a = memo[i], b = memo[i + 1];
    	bool flag1 = false, flag2 = false;
    	//トポロジカルソートしたとなり通しの順序が変わることがあるかを調べる
    	for(auto tmp : G[a]){
    		if(tmp == b){//a -> bの辺が存在
    			flag1 = true; break;
    		}
    	}
    	if(flag1) continue;
    	for(auto tmp : G[b]){
    		if(tmp == a){//b -> aの辺が存在
    			flag2 = true; break;
    		}
    	}

    	if(!flag1 == !flag2){
    		printf("1\n"); return 0;
    	}
    }
    printf("0\n");
    return 0;
}