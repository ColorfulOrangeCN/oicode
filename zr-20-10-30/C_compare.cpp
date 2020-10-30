#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int N=400005,mod=1e9+7;
int k,n,m,hc;
int ls[N],rs[N],lt[N],rt[N],h[N],ms[N],mt[N];
int fs[N],ft[N],g[N],ss[N],st[N],sg[N];
int ksm(int a,int b){int x=1;for(;b>0;b&1?x=1ll*x*a%mod:0,a=1ll*a*a%mod,b>>=1);return x;}
inline int m1(int x){return x>=mod?x-mod:x;}
inline int input()
{
	int x=0,F=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')F=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=x*10+c-'0';c=getchar();}
	return x*F;
}
int main()
{
	k=input();n=input();m=input();
	for(int i=1;i<=n;i++)
		ls[i]=input(),rs[i]=input(),h[++hc]=ls[i]-1,h[++hc]=rs[i];
	for(int i=1;i<=m;i++)
		lt[i]=input(),rt[i]=input(),h[++hc]=lt[i]-1,h[++hc]=rt[i];
	h[++hc]=0;h[++hc]=k;
	sort(h+1,h+hc+1);hc=unique(h+1,h+hc+1)-h-1;
	for(int i=1;i<=n;i++)
	{
		int L=lower_bound(h+1,h+hc+1,ls[i]-1)-h,R=lower_bound(h+1,h+hc+1,rs[i])-h;
		ms[R]=max(ms[R],L+1);
	}
	for(int i=1;i<=m;i++)
	{
		int L=lower_bound(h+1,h+hc+1,lt[i]-1)-h,R=lower_bound(h+1,h+hc+1,rt[i])-h;
		mt[R]=max(mt[R],L+1);
	}
	g[1]=sg[1]=1;
	ms[1]=mt[1]=1;
	for(int i=2;i<=hc;i++)
	{
		ms[i]=max(ms[i-1],ms[i]);mt[i]=max(mt[i-1],mt[i]);
		fs[i]=m1(m1(sg[i-1]-sg[mt[i]-1]+mod)+m1(st[i-1]-st[mt[i]-1]+mod));
		ft[i]=m1(m1(sg[i-1]-sg[ms[i]-1]+mod)+m1(ss[i-1]-ss[ms[i]-1]+mod));
		g[i]=1ll*m1(m1(fs[i-1]+ft[i-1])+g[i-1])*(ksm(2,h[i]-h[i-1])-2+mod)%mod;
		ss[i]=m1(ss[i-1]+fs[i]);st[i]=m1(st[i-1]+ft[i]);sg[i]=m1(sg[i-1]+g[i]);
	}
    copy(fs + 1, fs + hc + 1, ostream_iterator<int>(cout, " "));
	printf("%d",m1(m1(fs[hc]+ft[hc])+g[hc]));
	return 0;
}