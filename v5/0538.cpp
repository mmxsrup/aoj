#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main(void){
	while(1){
		int n, m; cin >> n;
		if(n == 0) return 0;
		cin >> m;
		string s; cin >> s;
		string ans;
		rep(i, n) ans += "IO";
		ans += "I";
		int sum = 0;
		for (int i = 0; i < m; ++i){
			if(s[i] != 'I') continue;
			if(ans == s.substr(i, 2 * n + 1))
				sum++;
		}
		printf("%d\n", sum);
	}
}