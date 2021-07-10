#include<bits/stdc++.h>
using namespace std;
int dx[] = {0,1,0,-1,0};
int dy[] = {0,0,1,0,-1};
set< set<pair<int,int> > >P[7];


set<set<pair<int,int>>> get( set<set<pair<int,int>>> Pre){
	set<set<pair<int,int>>> Now;
	for(auto link:Pre){
		for(auto node:link){
			for(int i=1;i<=4;i++){
				pair<int,int> now_node = make_pair(node.first+dx[i],node.second + dy[i]);
				if(link.count(now_node)==0){
					link.insert(now_node);
					if(Now.count(link)==0){
						Now.insert(link);
					}
					link.erase(now_node);
				}
			}
		}
	}
	return Now;
}


void solve(){
	pair<int,int>ini = make_pair(0,0);
	set<pair<int,int>>link;
	link.insert(ini);
	P[1].insert(link);
	set< set<pair<int,int> > > pre = P[1];
	P[2] = get(P[1]);
	P[3] = get(P[2]);
	P[4] = get(P[3]);
	P[5] = get(P[4]);
	P[6] = get(P[5]);
}

int p;// 代表谜题的长宽
int grid[20][20];
// 最大的谜题限制长宽均为20， grid[i][j] 代表第i行第j列的初始数字，
// 其中0表示可染色可不染色，-1表示不可染色，数字表示带数字的圆圈
int m = 0;
int vnum = 0;
// 总共有vum个变量，变量名表示为 1-vnm;
int length[30]; // 总共只有n个点，每个点有length[i]条链，
int lengthlink[30][1000];// 第i个点的第j条链的长度为多少，即圆圈内数字的大小
int link[30][1000][1000]; // 第i个点的第j条链上的第k个点的坐标是什么，包括正负，这里的意思是 +13 表示这个点在这条链中必须选
int hash1[30][1000];// 第i个点的第j条链对应的变量是哪一个
// 找到一个点满足条件的多条链，并且给出每个链的集合
int linknum  = 0;
int nownum = 0;// 当前处理到了第几个节点

// linknum++;
// length[nownum] = linknum;
// lengthlink[nownum][linknum] = num;
// for(int i=1;i<=num;i++){
// 	link[nownum][linknum][i] = (nowx[i]-1)*p+nowy[i];
// 	
bool check(int x,int y){
	if(x<1||x>p||y<1||y>p)return false;else return true;
}
void solve1(int x,int y,int num){
	linknum = 0;
	int flag = 1;
	
	for(auto Link: P[num]){
		
		flag = 1;
		for(auto node:Link){
			//cout << "node : " << node.first << " " << node.second << endl;
			if(node.first==0&&node.second==0){

				continue;
			}
			if(check(x+node.first,y+node.second)){
				if(grid[x+node.first][y+node.second]!=0){
					flag = 0;
					//cout << "case 1 " << endl;
				}
				//else cout << " case 2" << endl;
			}else{
				//cout << "case 3" << endl;
				flag = 0;
			}
		}
		//cout << flag << endl;
		if(flag){
			linknum++;
			//cout << nownum << " " << linknum << endl;
			length[nownum] = linknum;
			lengthlink[nownum][linknum] = num;
			int ccnt = 0;
			for(auto node:Link){
				ccnt++;
				link[nownum][linknum][ccnt] = (x+node.first-1)*p+y+node.second;
			}
			for(int i=1;i<=p;i++){
				for(int j=1;j<=p;j++){
					if(grid[i][j]==0&&Link.count(make_pair(i,j))==0){
						int flag1 = 0;
						for(int w=1;w<=4;w++)
						if(Link.count(make_pair(i-x+dx[w],j-y+dy[w])) )flag1 = 1;
						if(flag1) {
							ccnt++;
							link[nownum][linknum][ccnt] = -1*((i-1)*p+j);
							lengthlink[nownum][linknum]++;
						}	
					}
					
				}
			}

		}
	}

}


void give0(){
	for(int i=1;i<=m;i++){
		vnum+=length[i];
	}
	printf("p cnf %d %d\n",vnum,m+p*p*m*(m-1)/2);
}
void gives1(){
	int cnt = 0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=length[i];j++){
			printf("%d ",++cnt);
			hash1[i][j]=cnt;
		}printf("0\n");
	}
}
// 第i行第j列的格点记为 (i-1)*p+j
void gives2(){
	// 第i,j个格点的第k和第w个点的链中必须不包含该格点的链至少存在一条
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			for(int k=1;k<=m;k++){
				for(int w=k+1;w<=m;w++){

					// case 1:
					for(int g=1;g<=length[k];g++){
						int flag = 1;
						for(int u=1;u<=lengthlink[k][g];u++){
							if(link[k][g][u]==(i-1)*p+j){
								flag = 0;
							}
						}
						if(flag){
							printf("%d ",hash1[k][g]);
						}
					}



					// case 2:
					for(int g=1;g<=length[w];g++){
						int flag = 1;
						for(int u=1;u<=lengthlink[w][g];u++){
							if(link[w][g][u]==(i-1)*p+j){
								flag = 0;
							}
						}
						if(flag){
							printf("%d ",hash1[w][g]);
						}
					}

					// case 3:
					printf("0\n");
				}
			}
		}
	}
}

signed main(){
	solve();
	scanf("%d",&p);
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			scanf("%d",&grid[i][j]);
			if(grid[i][j] > 0){
				m++;
			}
		}
	}
	printf("m = %d\n",m);

	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			if(grid[i][j]>0&&grid[i][j]<=9){
				nownum++;
				solve1(i,j,grid[i][j]);
			}
		}
	}	
	for(int i=1;i<=m;i++){
		printf("第%d个点的链有%d条\n",i,length[i]);
	}
	give0();
	gives1();
	gives2();

	return 0;
}


