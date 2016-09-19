#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);i++)
const int INF = 1e9;
const int MAX_V = 300000;

int n, m;
struct Flow{
    struct edge{
        int to, cap, rev;
    };
    vector<edge> G[MAX_V];//隣接リスト
    bool used[MAX_V];

    void add_edge(int from, int to, int cap){
        G[from].push_back((edge){to, cap, (int)G[to].size()});//from -> to
        G[to].push_back((edge){from, 0, (int)G[from].size() - 1});//to -> from
    }

    //増加パスを探す
    int dfs(int v, int t, int f){
        if(v == t) return f;
        used[v] = true;
        for (int i = 0; i < G[v].size(); ++i){
            edge &e = G[v][i];
            if(!used[e.to] && e.cap > 0){
                int d = dfs(e.to, t, min(f, e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    //sからtへの最大流
    int max_flow(int s, int t){
        int flow = 0;
        while(1){
            memset(used, 0, sizeof(used));
            int f = dfs(s, t, INF);
            if(f == 0) return flow;
            flow += f;
        }
    }
};

int main(void){
    cin >> n >> m;
    int s = n + m, t = n + m + 1;
    Flow mf;
    //s -> A
    rep(i, n){
        mf.add_edge(s, i, 1);
    }
    //B -> t
    rep(i, m){
        mf.add_edge(n + i, t, 1);
    }

    rep(i, n){
        int k; cin >> k;
        rep(j, k){
            int d; cin >> d; d--;
            mf.add_edge(i, n + d, 1);
        }
    }
    //最大マッチング数が m の時だけBob勝利
    if(mf.max_flow(s, t) == m) printf("Bob\n");
    else printf("Alice\n");
    return 0;
}