#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<typename T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=5000010,SIGMA=26;
struct PAM{
	int lnk[N],len[N],pool,tail,n;
	map<char,int>go[N];
	char s[N];
	PAM(){
		memset(lnk,0,sizeof(lnk));
		memset(len,0,sizeof(len));
		lnk[0]=1,len[1]=s[0]=-1,n=tail=0,pool=2;
	}
	inline int nn(int val){
		len[pool]=val;
		return pool++;
	}
	inline int fail(int p){
		for(;s[n]!=s[n-len[p]-1];p=lnk[p]);
		return p;
	}
	inline void add(int c){
		s[++n]=c;
		tail=fail(tail);
		if(go[tail].find(c)==go[tail].end()){
			int p=nn(len[tail]+2);
			lnk[p]=go[fail(lnk[tail])][c];
			go[tail][c]=p;
		}
		tail=go[tail][c];
	}
}pam;
char s[N];
int main(){
	scanf("%s",s);
	for(int i=0,last=2;s[i];i++){
		pam.add(s[i]-'a');
		putchar(pam.pool-last+'0');
		last=pam.pool;
	}
}
