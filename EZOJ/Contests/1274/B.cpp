#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <complex>
#include <set>
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
const int N=27,MOD=998244353;
const double EPS=1e-4;
typedef complex<double> comp;
int n,p2[N],pool[32768][N];
inline bool is_zero(double x){
	return x>=-EPS&&x<=EPS;
}
inline bool palin(int *p){
	for(int i=1,j=n-1;i<j;i++,j--){
		if(p[i]!=p[j]){
			return false;
		}
	}
	return true;
}
comp wpool[N][N],tmp[N],rt[N],cur[N],*w;
inline void dft(comp *a){
	memcpy(tmp,a,sizeof(comp)*n);
	memset(a,0,sizeof(comp)*n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			a[i]+=tmp[j]*w[(i*j)%n];
		}
	}
}
inline bool check(int *p1){
	for(int i=0;i<n;i++){
		int t=0;
		for(int j=0;j<n;j++){
			t+=p1[(i-j+n)%n]*p1[j];
			if(t>p2[i]){
				return false;
			}
		}
		if(t!=p2[i]){
			return false;
		}
	}
	return true;
}
inline bool les(int *a,int *b){
	for(int i=0;i<n;i++){
		if(a[i]!=b[i]){
			return a[i]<b[i];
		}
	}
	return false;
}
struct Ans{
	int *p;
};
inline bool operator < (const Ans &a,const Ans &b){
	for(int i=0;i<n;i++){
		if(a.p[i]!=b.p[i]){
			return a.p[i]<b.p[i];
		}
	}
	return false;
}
int main(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			double angle=(2*M_PI*j)/i;
			wpool[i][j]=comp(cos(angle),sin(angle));
		}
	}
	for(int tot=ni();tot--;){
		n=ni();
		w=wpool[n];
		int sum=0;
		for(int i=0;i<n;i++){
			p2[i]=ni();
			rt[i]=p2[i];
			sum+=p2[i];
		}
		if(!is_zero(sum-sqr(sqrt(sum)))||!palin(p2)){
			puts("0");
			continue;
		}
		dft(rt);
		for(int i=0;i<n;i++){
			rt[i]=sqrt(rt[i]);
		}
		set<Ans>ans;
		int *p1=pool[0],stop=1;
		for(int state=(1<<(n+2>>1))-1;state>=0;state--){
			for(int i=0;i<n;i++){
				if((state>>min(i,n-i))&1){
					cur[i]=-rt[i];
				}else{
					cur[i]=rt[i];
				}
			}
			dft(cur);
			bool flag=true;
			for(int i=0;i<n;i++){
				cur[i]/=n;
				p1[i]=round(cur[i].real());
				if(!is_zero(cur[i].real()-p1[i])||p1[i]<0){
					flag=false;
					break;
				}
			}
			if(flag&&palin(p1)&&check(p1)){
				ans.insert((Ans){p1});
				p1=pool[stop++];
			}
		}
		printf("%d",ans.size());
		if(ans.size()){
			int *p=ans.begin()->p;
			for(int i=0;i<n;i++){
				printf(" %d",p[i]);
			}
		}
		putchar('\n');
		for(int i=0;i<n;i++){
			w[i]=comp(w[i].real(),-w[i].imag());
		}
	}
}
