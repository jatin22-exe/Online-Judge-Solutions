#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=110;
int a[N],c[N];
int n;
inline int getint(){
	int i=0;
	char c;
	while(!isdigit(c=getchar()));
	assert(c=='1');
	while(c=getchar(),c=='0');
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
void dfs(int x,int rest,int dt,int dt2){
	if(x>n){
		if(dt==0&&dt2==0)throw 1;
		return;
	}
	for(int &i=c[x]=-rest;i<=rest;i++){
		dfs(x+1,rest-abs(i),i*a[x]+dt,dt2+i);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("num4.in","r",stdin);
	freopen("num4.out","w",stdout);
#endif
	int dt=ni;
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=getint();
	}
	cout<<"read in complete"<<endl;
	try{
		dfs(1,10,-dt,0);
	}catch(int x){
		cout<<"caught you!"<<endl;
		int sum=0;
		for(int i=1;i<=n;i++){
			sum+=abs(c[i]);
		}
		printf("%d\n",sum);
		for(int i=1;i<=n;i++){
			if(c[i]>0){
				for(int j=1;j<=c[i];j++){
					printf("%d\n",i);
				}
			}else if(c[i]<0){
				for(int j=-1;j>=c[i];j--){
					printf("-%d\n",i);
				}
			}
		}
	}
	return 0;
}
