#include<bits/stdc++.h>
using namespace std;
char p[10][10];
signed main(){
	int n;
	cin >> n;
	getchar();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			p[i][j] = getchar();
		}
		getchar();
	}
	cout << endl;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		{
			int x;
			cin >> x;
			if(p[i][j]>='0'&&p[i][j]<='9'){
				cout << p[i][j] << " ";
			}
			else if(x>0){
				cout << 'b' <<" ";
			}else{
				cout << "w " ;
			}
		}cout << endl;
	}
}
/*

6
.2....
..4.2.
......
......
.3.3..
..3...
-1 2 3 -4 5 -6 -7 8 9 10 11 -12 -13 -14 15 -16 -17 -18 -19 20 -21 22 -23 -24  -25 26 27 28 -29 -30 -31 32 33 34 -35 -36  
*/