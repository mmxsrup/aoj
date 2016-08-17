#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main(void){
	while(1){
		int d, n, m; cin >> d;
		if(d == 0) return 0;
		cin >> n >> m;
		vector<int> store;
		rep(i, n - 1){
			int tmp; cin >> tmp;
			store.push_back(tmp);
		}
		store.push_back(0); store.push_back(d); //本店の位置を追加する
		sort(store.begin(), store.end());

		vector<int> k(m);
		rep(i, m) cin >> k[i];

		int sum = 0;
		rep(i, m){
			//２分探索でk[i]の前後の店舗の位置を見つける
			int l = *(lower_bound(store.begin(), store.end(), k[i]) - 1);
			int r = *(lower_bound(store.begin(), store.end(), k[i]));
			int ans = min(k[i] - l, r - k[i]);
			sum += ans;
		}
		printf("%d\n", sum);
	}
	return 0;
}