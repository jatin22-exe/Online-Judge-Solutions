#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 20000
using namespace std;
int f[N],stonepos[110];
bool stone[N];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
inline int mins(int a,int b){
	int i=max(a,0);
	int minn=f[i];
	for(;i<=b;i++){
		if(minn==-1||(f[i]<minn&&f[i]!=-1)){
			minn=f[i];
		}
	}
	return minn;
}
int main(){
	int l,s,t,m,last=0,space;
	cin>>l>>s>>t>>m;
	if(s==t){
		int cnt=0;
		for(int i=1;i<=m;i++){
			cin>>stonepos[i];
			if(stonepos[i]%s==0){
				cnt++;
			}
		}
		cout<<cnt;
		return 0;
	}
	space=s/gcd(s,t)*t;
	memset(f,-1,sizeof(f));
	memset(stone,0,sizeof(stone));
	for(int i=1;i<=m;i++){
		cin>>stonepos[i];
	}
	sort(stonepos+1,stonepos+m+1);//sorting is 1...m!
//	cout<<"Disperse!"<<endl;
	stonepos[0]=0;
	for(int i=1;i<=m;i++){
		last+=min(space,stonepos[i]-stonepos[i-1]);
		stone[last]=true;
//		cout<<"Stone #"<<i<<" :\t"<<stonepos[i]<<"\t->\t"<<last<<endl;
	}
	f[0]=0;
	for(int i=s;i<last+t;i++){
		if((f[i]=mins(i-t,i-s))!=-1){
			f[i]+=stone[i];
		}
//		cout<<"f["<<i<<"]="<<f[i]<<endl;
	}
	cout<<mins(last,last+t-1);
}
