#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

double K, R, L;
double P, E, T;

double solve(double l, double r, double k){
	double h = (l + r) / 2;

	if(k == K){//k回二分探索した後の結果
		if(abs(h - T) < E) return 1.0;
		else return 0.0;
	}

	//枝狩り
	//この後どうやって二分探索しても絶対時誤差がEの範囲に収まる
	if(T - E <= l && r <= T + E) return 1;
	//この後どうやって二分探索しても絶対時誤差がEの範囲に収まらない
	if(r < T - E || T + E < l) return 0;

	double tmpp = 0;//確率の合計(独立事象なので和)
	if(h >= T){//時間が長すぎる
		tmpp += (1 - P) * solve(l, h, k + 1);//correct
		tmpp += P * solve(h, r, k + 1);//mistake
	}else{//時間が短すぎる
		tmpp += (1 - P) * solve(h, r, k + 1);//correct
		tmpp += P * solve(l, h, k + 1);//mistake
	}
	return tmpp;
}

int main(void){
	cin >> K >> R >> L >> P >> E >> T;
	swap(R, L);
	printf("%.9f\n", solve(L, R, 0));
	return 0;
}