#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
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
const int N=100010;
int rt,n=0,tim=0;
inline int getrt(int x){
	for(rt=0;rt*rt<x;rt++);
	return x;
}
struct Point{
	int id;
	lint x,v;
	inline lint pos(){
		return x+v*tim;
	}
	inline friend int crs(Point &a,Point &b){
		lint dx=b.x-a.x,dv=a.v-b.v;
		assert(dv);
		lint ans=dx/dv+1;
		assert(ans>=0);
		return ans<N?ans:N-1;
	}
}pt[N];
int pos[N];
inline void ptswp(int a,int b){
	swap(pt[pos[a]],pt[pos[b]]);
	swap(pos[a],pos[b]);
}
inline bool ptless(int a,int b){
	lint xa=pt[pos[a]].pos(),xb=pt[pos[b]].pos();
	lint va=pt[pos[a]].v,vb=pt[pos[b]].v;
	return xa==xb?(va==vb?a<b:va<vb):xa<xb;
}
typedef vector<int>vi;
inline bool poscmp(int a,int b){
	return pos[a]>pos[b];
}
inline void jmp(vi &vec){
	sort(vec.begin(),vec.end(),poscmp);
	for(int i=0,ti=vec.size();i<ti;i++){
		int x=vec[i];
		for(int j=pos[x],tj=min((j/rt+1)*rt-1,n-1);j<tj;j++){
			if(ptless(pt[j+1].id,x)){
				ptswp(pt[j+1].id,x);
			}else{
				break;
			}
		}
	}
}
inline int bitchop(int l,int r,int x){
	l--;
	while(l<r){
		int mid=((l+r)>>1)+1;
		if(pt[mid].pos()>x){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	return l;
}
inline int ask(int x){
	int ans=0;
	for(int i=0;i<n;i+=rt){
		ans+=bitchop(i,min(i+rt-1,n-1),x)-i+1;
	}
	return ans;
}
vi op[N];
inline void ins(){
	pt[n]=(Point){n,nl,nl};
	pt[n].x-=pt[n].v*tim;
	pos[n]=n;
	int x=n,s=x/rt*rt;
	for(;x>s;x--){
		if(ptless(n,pt[x-1].id)){
			ptswp(n,pt[x-1].id);
		}else{
			assert(ptless(pt[x-1].id,n));
			break;
		}
	}
	for(int i=s;i<x;i++){
		assert(ptless(pt[i].id,n));
		if(pt[i].v>pt[x].v){
			op[crs(pt[i],pt[x])].push_back(pt[i].id);
		}
	}
	for(int i=x+1,ti=min(s+rt-1,n);i<=ti;i++){
		assert(ptless(n,pt[i].id));
		if(pt[i].v<pt[x].v){
			op[crs(pt[i],pt[x])].push_back(n);
		}
	}
	n++;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flea.in","r",stdin);
	freopen("flea.out","w",stdout);
#endif
	for(int tot=getrt(ni);tot--;){
		switch(ni){
			case 1:
				ins();
				break;
			case 2:
				jmp(op[++tim]);
				break;
			case 3:
				{
					int l=ni,r=ni;
					printf("%d\n",ask(r)-ask(l-1));
					break;
				}
		}
	}
	return 0;
}
