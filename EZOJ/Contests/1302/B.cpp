#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=11,M=22;
int a[N],na[N],n,m;
inline int encode(int a[]){
	int hash=0;
	for(int i=0;i<=n;i++){
		hash|=a[i]<<(i<<1);
	}
	return hash;
}
inline void decode(int a[],int x){
	for(int i=0;i<=n;i++){
		a[i]=(x>>(i<<1))&3;
	}
}
inline int anscnt(int a[]){
	int ans=0,sum=0;
	for(int i=0;i<=n;i++){
		if(a[i]==1){sum++;}
		else if(a[i]==2){sum--;}
		else if(a[i]==3&&sum==0){ans++;}
	}
	return ans;
}
struct HashTable{
	const static int MOD=3121,E=100000;
	int magic;
	HashTable(){
		magic=rand();
	}
	int head[MOD],to[E],bro[E],etop;
	inline void clear(){
		etop=0;
		memset(head,-1,sizeof(head));
	}
	inline void push(int val){
		int x=(val^magic)%MOD;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]==val){return;}
		}
		to[etop]=val;
		bro[etop]=head[x];
		head[x]=etop++;
	}
	inline bool nxt(int a[]){
		return etop?(decode(a,to[--etop]),true):false;
	}
}*h1,*h2;
int mat[N][M];
inline void del(int a[],int x){
	if(a[x]==1){
		int sum=0;
		for(int i=x+1;;i++){
			if(a[i]==1){sum++;}
			else if(a[i]==2){sum--;}
			else if(a[i]==3&&sum==0){
				a[i]=1;
				break;
			}
			if(sum<0){
				assert(a[i]==2);
				a[i]=0;
				break;
			}
		}
	}else if(a[x]==2){
		int sum=0;
		for(int i=x-1;;i--){
			if(a[i]==1){sum--;}
			else if(a[i]==2){sum++;}
			else if(a[i]==3&&sum==0){
				a[i]=2;
				break;
			}
			if(sum<0){
				assert(a[i]==1);
				a[i]=0;
				break;
			}
		}
	}
	a[x]=0;
}
int turn[16];
inline int getright(int a[],int i){
	assert(a[i]==1);
	int sum=0;
	while(sum>=0){
		if(a[++i]==1){sum++;}
		else if(a[i]==2){sum--;}
	}
	return i;
}
inline int getleft(int a[],int i){
	assert(a[i]==2);
	int sum=0;
	while(sum>=0){
		if(a[--i]==2){sum++;}
		else if(a[i]==1){sum--;}
	}
	return i;
}
inline int merge(int t[],int i){
	int a=t[i-1],b=t[i];
	if(a==0||b==0){return a|b;}
	if(a==1&&b==2){return 0;}
	if(a==2&&b==1){return 3;}
	if(a==1&&b==3){return 1;}
	if(a==3&&b==2){return 2;}
	if(a==3&&b==1){t[getright(t,i)]=3;return 3;}
	if(a==2&&b==3){t[getleft(t,i-1)]=3;return 3;}
	if(a==1&&b==1){t[getright(t,i)]=3;return 1;}
	if(a==2&&b==2){t[getleft(t,i-1)]=3;return 2;}
	if(a==3&&b==3){return 3;}
	assert(false);
	return -1;
}
inline int hmdis(int x){
	int cnt=0;
	for(;x;cnt++,x^=x&(-x));
	return cnt;
}
inline void trans(int x,int t){//push to h2
	if(anscnt(a)==0){
		return;
	}
	if(hmdis(t)<=1){
		for(int i=0;i<=n;i++){na[i]=a[i];}
		del(na,x-1);
		del(na,x);
		h2->push(encode(na));
		return;
	}
	bool vis[16];
	memset(vis,0,sizeof(vis));
	for(;!vis[t];t=turn[t]){
		vis[t]=true;
		bool u=t&1,r=(t>>1)&1,d=(t>>2)&1,l=(t>>3)&1;
		for(int i=0;i<=n;i++){na[i]=a[i];}
		if(!u){del(na,x-1);}
		if(!l){del(na,x);}
		switch(merge(na,x)){
			case 0:{na[x-1]=1,na[x]=2;break;}
			case 1:{na[x-1]=1,na[x]=3;break;}
			case 2:{na[x-1]=3,na[x]=2;break;}
			case 3:{na[x-1]=na[x]=3;break;}
		}
		if(!d)del(na,x);
		if(!r)del(na,x-1);
		h2->push(encode(na));
	}
}
int main(){
	srand(time(NULL));
	h1=new HashTable,h2=new HashTable;
	for(int i=0;i<16;i++){
		turn[i]=i>>1;
		if(i&1)turn[i]|=8;
	}
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=1;i<=n;i++){
			for(int j=2;j<m;j++){
				mat[i][j]=ni;
			}
		}
		{
			a[0]=0;
			for(int i=1;i<=n;i++)a[i]=3;
			h1->clear(),h2->clear();
			h1->push(encode(a));
		}
		for(int j=2;j<m;j++){
			for(int i=1;i<=n;i++){
				for(;h1->nxt(a);trans(i,mat[i][j]));
				swap(h1,h2);
				h2->clear();
			}
			for(;h1->nxt(a);del(a,n),h2->push(encode(a)<<2));
			swap(h1,h2);
			h2->clear();
		}
		{
			int ans=0;
			for(;h1->nxt(a);apmax(ans,anscnt(a)));
			printf("%d\n",ans);
		}
	}
}