#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)


int main(void){
	int n1, n2; cin >> n1 >> n2;
	vector<int> a(n1), b(n2);
	rep(i, n1) cin >> a[i];
	rep(i, n2) cin >> b[i];

	int ans = 0;
	for (int i = 0; i < n2; ++i){//bの連続部分列topの位置に来るカードを決める
		int tmp = 0, next = 0;
		bool flag = false;
		for (int j = i; j < n2; ++j){
			for (int k = next; k < n1; ++k){//aの中で一致していくものを調べている
				if(b[j] == a[k]){
					tmp++; next = k + 1;
					ans = max(ans, tmp);
					break;
				}
				if(k == n1 - 1){ flag = true; break; }
			}
			if(flag) break;
		}
	}
	printf("%d\n", ans);
	return 0;
}

