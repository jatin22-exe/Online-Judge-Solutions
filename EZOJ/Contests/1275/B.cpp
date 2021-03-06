#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline int sqr(int x){
	return x*x;
}
const int MOD=1000000007,N=100010,Q=200010,D=10000010,E=2000000;
inline int mul(int a,int b){
	return (long long)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
int n,c[Q],d[Q];
#define lson(x) son[x][0]
#define rson(x) son[x][1]
int root[N],son[D][2],prod[D],tag[D],tim,ntop=1;
inline void push_up(int x){
	prod[x]=mul(prod[lson(x)],prod[rson(x)]);
}
inline int renew(int x){
	if(tag[x]==tim){
		return x;
	}
	if(x){
		lson(ntop)=lson(x),rson(ntop)=rson(x);
	}
	tag[ntop]=tim;
	prod[ntop]=prod[x];
	return ntop++;
}
int assign(int x,int p,int val,int l=1,int r=n){
	x=renew(x);
	if(l==r){
		prod[x]=val;
		return x;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		lson(x)=assign(lson(x),p,val,l,mid);
	}else{
		rson(x)=assign(rson(x),p,val,mid+1,r);
	}
	push_up(x);
	return x;
}
int divide(int x,int p,int val,int l=1,int r=n){
	x=renew(x);
	if(l==r){
		assert(prod[x]%val==0);
		prod[x]/=val;
		return x;
	}
	int mid=(l+r)>>1;
	if(p<=mid){
		lson(x)=divide(lson(x),p,val,l,mid);
	}else{
		rson(x)=divide(rson(x),p,val,mid+1,r);
	}
	push_up(x);
	return x;
}
int ask_prod(int x,int a,int b,int l=1,int r=n){
	if(a==l&&b==r){
		return prod[x];
	}
	int mid=(l+r)>>1;
	if(b<=mid){
		return ask_prod(lson(x),a,b,l,mid);
	}else if(a>mid){
		return ask_prod(rson(x),a,b,mid+1,r);
	}
	return mul(ask_prod(lson(x),a,mid,l,mid),ask_prod(rson(x),mid+1,b,mid+1,r));
}
int to[E],bro[E],amt[E],head[N];
inline void init_stk(){
	memset(head,-1,sizeof(head));
	head[0]=0;
	for(int i=0;i<E;i++){
		bro[i]=i+1;
	}
	bro[E-1]=-1;
}
inline void push(int p,int exp){
	int e=head[0];
	head[0]=bro[e];
	to[e]=tim;
	bro[e]=head[p];
	amt[e]=exp;
	head[p]=e;
}
inline void pop(int p,int e){
	for(int i=head[p],*pt=head+p;e&&(~i);){
		int delta=min(e,amt[i]);
		e-=delta,amt[i]-=delta;
		divide(root[tim],to[i],fpow(p,delta));
		if(amt[i]==0){
			*pt=bro[i];
			bro[i]=head[0];
			head[0]=i;
			i=*pt;
		}
	}
}
int prime[N],ptop=0;
bool np[N];
int ans;
inline void putans(int n,int k){
	printf("%d\n",ans=ask_prod(root[n],n-k+1,n));
}
int main(){
	int tot=ni();
	c[1]=ni(),d[1]=ni();
	int a=ni(),b=ni();
	n=ni();
	for(int i=2;i<=tot;i++){
		c[i]=ni();
	}
	for(int i=2;i<=tot;i++){
		d[i]=ni();
	}
	memset(np,0,sizeof(np));
	np[1]=true;
	root[0]=tag[0]=0;
	prod[0]=1;
	memset(son,0,sizeof(son));
	init_stk();
	for(int i=1;i<=n;i++){
		if(!np[i]){
			prime[ptop++]=i;
		}
		for(int j=0,cur=2;j<ptop&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				break;
			}
		}
		tim=i;
		root[i]=assign(root[i-1],i,i);
		int p=i;
		for(int j=0,cur=2;j<ptop&&sqr(cur)<=p;cur=prime[++j]){
			if(p%cur==0){
				int e=0;
				for(;p%cur==0;e++,p/=cur);
				pop(cur,e);
				push(cur,e);
			}
		}
		if(p>1){
			pop(p,1);
			push(p,1);
		}
	}
	putans(c[1],d[1]);
	for(int i=2;i<=tot;i++){
		c[i]=((long long)a*ans+c[i])%n+1;
		d[i]=((long long)b*ans+d[i])%c[i]+1;
		putans(c[i],d[i]);
	}
}
