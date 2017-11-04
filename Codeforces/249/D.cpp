#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
inline int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void set(int x,int v){
		for(;x;apmax(c[x],v),x^=x&-x);
	}
	inline int ask(int x){//from x
		int ans=0;
		for(;x<=n;apmax(ans,c[x]),x+=x&-x);
		return ans;
	}
}
struct Pt{
	lint x,y;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.y!=b.y?a.y>b.y:a.x<b.x;
	}
}pt[N];
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("donkey.in","r",stdin);
	freopen("donkey.out","w",stdout);
#endif
	int n=ni;
	lint a=ni,b=ni,c=ni,d=ni;
	{
		int g=gcd(a,b);
		a/=g,b/=g;
		g=gcd(c,d);
		c/=g,d/=g;
	}
	{
		int mx=0;
		for(int i=1;i<=n;i++){
			int x=ni,y=ni;
			pt[i]=(Pt){(b*c+a*d)*x-b*d*y,-a*c*x+b*c*y};
			if(pt[i].x<=0||pt[i].y<=0){
				n--,i--;
			}else{
				apmax(mx,pt[i].x);
			}
		}
		B::init(mx);
	}
	sort(pt+1,pt+n+1);
	for(int i=1;i<=n;i++){
		B::set(pt[i].x,f[i]=B::ask(pt[i].x+1)+1);
	}
	printf("%d\n",B::ask(1));
	return 0;
}
