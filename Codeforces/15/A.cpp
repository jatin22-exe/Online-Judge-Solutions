#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct house{
	int x,a;
};
bool diycomp(struct house a,struct house b){
	return a.x<b.x;
}
int main(){
	int n,t,cnt=2,tmp;
	cin>>n>>t;
	house h[n];
	for(int i=0;i<n;i++){
		cin>>h[i].x>>h[i].a;
	}
	sort(h,h+n,diycomp);
	for(int i=0;i<n-1;i++){
		tmp=2*h[i+1].x-h[i+1].a-2*h[i].x-h[i].a;
		if(2*t==tmp){
			cnt++;
		}else if(2*t<tmp){
			cnt+=2;
		}
	}
	cout<<cnt;
}