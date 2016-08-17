#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main(void){
	while(1){
		int n, m; cin >> n >> m;
		if(n == 0 && m == 0) return 0;
		vector<int> p(n);
		rep(i, n) cin >> p[i];
		p.push_back(0);//矢を使わないを入れる
		vector<int> pp((n + 1) * (n + 1));
		int cnt = 0;
		rep(i, n + 1)rep(j, n + 1){
			pp[cnt] = p[i] + p[j];
			cnt++;
		}
	
		sort(pp.begin(), pp.end());
		int ans = 0;
		//計算量(n^2*logn)
		rep(i, (n + 1) * (n + 1)){
			int tmp = pp[i];
			int aim = m - tmp;
			if(aim < 0) continue;
			tmp += *(upper_bound(pp.begin(), pp.end(), aim) - 1);
			if(tmp <= m) ans = max(ans, tmp);
		}
		printf("%d\n", ans);
	}
	return 0;
}