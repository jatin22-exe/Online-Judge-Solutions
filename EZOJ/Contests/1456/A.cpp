#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int qr;
	// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a integer
	template <class I>
		inline void gi (I &x) {
			for (c = gc(); c < '0' || c > '9'; c = gc());
			for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
		}
	// print a integer
	template <class I>
		inline void print (I &x) {
			if (!x) putc ('0');
			while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
			while (qr) putc (qu[qr --]);
		}
}
const int N=1000010;
namespace bit_util{
	const int SH=16,N=1<<SH;
	int cc[N];
	inline void init(){
		cc[0]=-1;
		for(int i=1;i<N;i++){
			cc[i]=cc[i-1]+(i==(i&-i));
		}
	}
	inline int hb(unsigned x){
		assert(x);
		return x>>SH?cc[x>>SH]+SH:cc[x];
	}
}
struct Query{
	int id,l,r;
	unsigned d;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.l!=b.l?a.l>b.l:a.r<b.r;
	}
}qry[N];
unsigned a[N];
int ans[N];
namespace lb{
	const int logN=32;
	int b[N];
	inline void init(){
		mset(b,0,logN);
	}
	inline void ins(int x){
		for(int i=logN-1;i>=0&&a[x];i--){
			if(((a[x]>>i)&1)==0)continue;
			if(b[i]){
				if(x<b[i]){
					swap(x,b[i]);
				}
				a[x]^=a[b[i]];
			}else{
				b[i]=x;
				return;
			}
		}
	}
	inline unsigned ask(unsigned x,const int r){
		for(int i=logN-1;i>=0;i--){
			if(((x>>i)&1)==0&&b[i]&&b[i]<=r){
				x^=a[b[i]];
			}
		}
		return x;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	bit_util::init();
	int n;
	io::gi(n);
	for(int i=1;i<=n;i++){
		io::gi(a[i]);
	}
	int q;
	io::gi(q);
	for(int i=1;i<=q;i++){
		qry[i].id=i;
		io::gi(qry[i].l);
		io::gi(qry[i].r);
		io::gi(qry[i].d);
	}
	sort(qry+1,qry+q+1);
	lb::init();
	for(int i=n,j=1;i>=1;i--){
		lb::ins(i);
		for(;j<=q&&qry[j].l==i;j++){
			ans[qry[j].id]=lb::ask(qry[j].d,qry[j].r);
		}
	}
	for(int i=1;i<=q;i++){
		io::print(ans[i]);
		io::putc('\n');
	}
	io::flush();
	return 0;
}
