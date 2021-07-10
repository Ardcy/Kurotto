#include<bits/stdc++.h>
using namespace std;
char p[10][10];
int dx[] = {0,1,0,-1,0};
int dy[] = {0,0,1,0,-1};
int n;
#define int long long
void prit(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%c",p[i][j]);
		}cout << endl;
	}
}

set<pair<int,int>> get(int x,int y){
	set<pair<int,int>>Ans;
	for(int i=1;i<=4;i++){
		if(x+dx[i] <=n && x + dx[i] >=1 && y + dy[i] >= 1 && y+dy[i] <= n){
			Ans.insert({x+dx[i],y+dy[i]});
		}
	}
	return Ans;
}
set<int>Ans;
vector<vector<int>>A;
int hash1(set<pair<int,int>>&sp){
	int ans = 0;
	int base = 1;
	for(auto q:sp){
		ans += base * ((q.first-1)*n+(q.second-1)+1);
		base *= (n+1)*(n+1);
	}
	return ans;
}
void dfs(int depth,int target,set<pair<int,int>>&p1,set<pair<int,int>>&st,int flag){
	if(depth==target){
		
		if(!Ans.count(flag*hash1(st)))
		{
			vector<int>now;
			for(auto q:st){
			//	cout << flag*((q.first-1)*n + (q.second -1) + 1) << " ";
				now.push_back(flag*((q.first-1)*n + (q.second -1) + 1));
			}
			//cout << endl;
			A.push_back(now);
		}
		Ans.insert(flag * hash1(st));
		
	}else{
		for(auto p:p1){
			if(!st.count(p)){
				st.insert(p);
				dfs(depth+1,target,p1,st,flag);
				st.erase(p);
			}
		}

	}

}

signed main(){
	scanf("%d",&n);
	freopen("out.cnf","w",stdout);
	cout << "p cnf " << n*n << " " ;
	getchar();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			p[i][j] = getchar();
		}
		getchar();
	}	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(p[i][j]>'0'&&p[i][j]<'9'){
				vector<int>no;
				no.push_back((i-1)*n+(j-1)+1);
				A.push_back(no);
				int num = p[i][j] - '0';
				set<pair<int,int> >p1 = get(i,j);
				if(num==(int)p1.size()){
					for(auto q:p1){
						// cout << (q.first-1)*n + (q.second -1) + 1 << endl;
						vector<int>now;now.push_back((q.first-1)*n + (q.second -1) + 1); 
						A.push_back(now);
					}
				}
				else{
					set<pair<int,int>>st;
					dfs(0,num+1,p1,st,-1);
					dfs(0,p1.size()-num+1,p1,st,1);
				}
			}
		}
	}
	cout<<A.size() << endl;
	for(auto p:A){
		for(auto q:p){
			cout << q << " ";
		}cout << 0 << endl;
	}
	
}

/*
input:
6
.2....
..4.2.
......
......
.3.3..
..3...

*/