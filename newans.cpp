

// 基本思路，

// 限制1. 每个点的n种不同的联通块必须选择1条 
// 第一个点有p种不同的联通块，反映到实际逻辑语言中就是：
// 起码选一种 && 每两种最多选一种
// 等价于
// 起码选一种：  a1 V a2 V ... V ap
// 每两种最多选一种：
// -a1 V -a2 
// -a1 V -a3
// ...
// -a_{p-1} V -ap


 
// 限制2. 选择的每两个块互相不冲突。

// 对于每个块，我们处理得到了必须填充的点以及必须不填充的点
// 只要两个块满足 
// 第一个块填充的点不在第二个块必定不填的位置 
// 第二个块填充的点不在第一个块必定不填的位置

// 答案一定成立


// // 至此得到答案：
//   假设点有m个，每个点的块大小分别是 size_i ，格子数量为p * p

// 变量个数为 /sum size_i
// 语句个数为 m + 必须一种 + 不冲突的所有数量 



#include<bits/stdc++.h>
using namespace std;

// dx dy 代表方向 上下左右
int dx[] = {0,1,0,-1,0};
int dy[] = {0,0,1,0,-1};

// 求解 从一个固定点出发的联通块为n的所有情形
set< set< pair<int,int> > >P[10];
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

// P[i] 表示联通块大小为i的所有不同联通块的集合
void solve(){
	pair<int,int>ini = make_pair(0,0);
	set<pair<int,int>>link;
	link.insert(ini);
	P[0].insert(link);
	set< set<pair<int,int> > > pre = P[0];
	P[1] = get(P[0]);
	P[2] = get(P[1]);
	P[3] = get(P[2]);
	P[4] = get(P[3]);
	P[5] = get(P[4]);
	P[6] = get(P[5]);
	P[7] = get(P[6]);
	P[8] = get(P[7]);
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
// 注意 坐标的话我进行了 二维变一维处理
// 5×5的表格 第二行第三列 对应的数字是 8

int hash1[30][1000];// 第i个点的第j条链对应的实际cnf文件中的变量是哪一个
// 找到一个点满足条件的多条链，并且给出每个链的集合
int linknum  = 0;
int nownum = 0;// 当前处理到了第几个节点

// 检测是否超出边界
bool check(int x,int y){
	if(x<1||x>p||y<1||y>p)return false;else return true;
}

// sollve1 
// input : 传出带圆圈数字的点的坐标，数字为num,坐标为（x,y)
// 然后从所有可能的联通块集合中寻找可以满足的联通块
// output: 最后得到 该点适合的所有联通块，并且给出了该点联通块如果要成立，必须有哪些位置一定不能涂色


void solve1(int x,int y,int num){
	linknum = 0;
	int flag = 1;
	if(num==-2){
		num = 0;
	}
	// 寻找适合的联通块
	for(auto Link: P[num]){
		flag = 1;
		for(auto node:Link){
			if(node.first==0&&node.second==0){
				continue;
			}
			if(check(x+node.first,y+node.second)){
				if(grid[x+node.first][y+node.second]!=0){
					flag = 0;
				}
			}else{
				flag = 0;
			}
		}
		// cout << x << " " << y << num << endl;
		// cout << " " << flag << endl;
		// 如果联通块可以，判断哪些点一定不能填充
		if(flag){
			linknum++;
			length[nownum] = linknum;
			lengthlink[nownum][linknum] = num;
			int ccnt = 0;
			for(auto node:Link){
				if(node.first==0&&node.second==0){}
				else {
					ccnt++;
					link[nownum][linknum][ccnt] = (x+node.first-1)*p+y+node.second;	
				}
			}
			for(int i=1;i<=p;i++){
				for(int j=1;j<=p;j++){
					if(grid[i][j]==0&&Link.count(make_pair(i-x,j-y))==0){
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

// 给出cnf文件第一行
void give0(){
	int pnum = 0;
	for(int i=1;i<=m;i++){
		vnum+=length[i];
		pnum += length[i] * (length[i]-1)/2 + 1;
	}
	int cnt = 0;
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			cnt += length[i]*length[j];
		}
	}
	printf("p cnf %d %d\n",vnum+1,pnum+cnt);
}

// 给出第一个限制条件的所有语句
void gives1(){
	int cnt = 0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=length[i];j++){
			printf("%d ",++cnt);
			hash1[i][j]=cnt;
		}printf("0\n");
		for(int j=1;j<=length[i];j++){
			for(int w=j+1;w<=length[i];w++){
				printf("%d %d 0\n",-hash1[i][j],-hash1[i][w]);
			}
		}
	}
}
// 给出第二个限制条件的所有语句

int pnum[600];

void gives2(){
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			int x1,x2,y1,y2;
			int pcntt = 0;
			for(int i1=1;i1<=p;i1++){
				for(int j1=1;j1<=p;j1++){
					if(grid[i1][j1]>0&&grid[i1][j1]<=9){
						pcntt++;
						if(pcntt==i){
							x1 = i1,y1 = j1;
						}
						if(pcntt==j){
							x2 = i1,y2 = j1;
						}
					}
				}
			}	
			for(int k=1;k<=length[i];k++){
				for(int w=1;w<=length[j];w++){
					int flag = 1;
					for(int u=1;u<=590;u++)pnum[u] = 0;
					for(int u=1;u<=lengthlink[i][k];u++){
						//cout << link[i][k][u] << " ";
						if( ((x1-1)*p + y1) !=link[i][k][u])
						pnum[300+link[i][k][u]]=1;
					}//cout << endl;
					for(int u=1;u<=lengthlink[j][w];u++){
						//cout << link[j][w][u] << " ";
						if(pnum[300-link[j][w][u]] && ((x2-1)*p + y2)!=link[j][w][u]){
							flag = 0;
						}
					}//cout << endl;
					if(flag==0){
						printf("%d %d 0\n",-hash1[i][k],-hash1[j][w]);	
					}else{	
						printf("%d 0\n",-vnum-1);
					}
				}
			}
		}
	}
}


// 根据最终的答案进行解码
int decode[10000];
int new_grid[20][20];
void deco(){
	int pnu = 0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=length[i];j++){
			pnu++;
			if(decode[pnu]==1){
				for(int w=1;w<=lengthlink[i][j];w++){
					if(link[i][j][w]>0){
						int x = (link[i][j][w] - 1)/p + 1;
						int y = link[i][j][w]%p==0?p:link[i][j][w]%p;
						new_grid[x][y] = 1;
					}
				}
			}
		}
	}
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			if(new_grid[i][j]==1){
				cout << "1 ";
			}else{
				cout << "0 ";
			}
		}cout << endl;
	}
}

signed main(){
	freopen("in.txt","r",stdin);
	freopen("out.cnf","w",stdout);
	solve();
	scanf("%d",&p);
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			scanf("%d",&grid[i][j]);
			if(grid[i][j] > 0 || grid[i][j]==-2){
				m++;
			}
		}
	}
	for(int i=1;i<=p;i++){
		for(int j=1;j<=p;j++){
			if((grid[i][j]>0&&grid[i][j]<=9)||grid[i][j]==-2){
				nownum++;
				solve1(i,j,grid[i][j]);
			}
			
		}
	}	
	// for(int i=1;i<=m;i++){
	// 	printf("第%d个点的链有%d条\n",i,length[i]);
	// }
	give0();
	gives1();
	gives2();
	// decode

	
	return 0;
}
