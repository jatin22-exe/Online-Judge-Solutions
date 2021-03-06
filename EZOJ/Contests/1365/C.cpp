#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=100010;
int prime[N],ps=0;
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps++]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0)break;
		}
	}
}
inline int bfind(int n){//find first p^2>n
	int l=0,r=ps-1;
	while(l<r){
		int m=(l+r)>>1;
		if(sqr((lint)prime[m])>n){
			r=m;
		}else{
			l=m+1;
		}
	}
	return l;
}
inline void Main(){
	int n=ni;
	if(n<=130){
		for(int i=1;i<n;i++){
			for(int j=1;j<n;j++){
				for(int k=1;k<n;k++){
					int a[10],as=0;
					int cur=i*j*k;
					for(int l=n-1;l>1;){
						if(cur%l==0){
							cur/=l;
							a[as++]=l;
							apmin(l,cur);
						}else l--;
					}
					assert(cur==1);
					if(as<3)continue;
					bool flag=as>3;
					if(!flag){
						int b[3]={k,j,i};
						for(int t=2;t>=0;t--){
							if(a[t]!=b[t]){
								flag=a[t]>b[t];
								break;
							}
						}
					}
					if(flag){
						printf("3 %d %d %d\n",i,j,k);
						return;
					}
				}
			}
		}
		puts("-1");
		return;
	}
	int b=prime[bfind(n-1)];
	int a=prime[bfind(b)];
	if((lint)a*a*a>=n)return puts("-1"),void();
	a*=b;
	printf("3 %d %d %d\n",a,a,a);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hafen.in","r",stdin);
	freopen("hafen.out","w",stdout);
#endif
	sieve(N-1);
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
