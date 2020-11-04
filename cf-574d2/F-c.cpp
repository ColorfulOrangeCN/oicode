#include<algorithm>
#include<cstdio>
#include<cctype>
using namespace std;
const int maxn=3e5;
int n,k,x,y,ans,totq,totn,lastx,lasty,firstx,firsty,BIT[maxn+1],last[maxn+1],belong[maxn+1],res[maxn+1],cnt[maxn+1],start[maxn+1],ending[maxn+1];
struct frac
{
	int x,y,no;
}a[maxn+1],t[maxn+1];
inline bool cmp1(const frac &t1,const frac &t2)
{
	return t1.x==t2.x?t1.y<t2.y:t1.x<t2.x;
}
struct query
{
	int l,r,no;
}q[maxn+1];
inline bool cmp2(const query &t1,const query &t2)
{
	return t1.r<t2.r;
}
int gcd(int x,int y)
{
	return y?gcd(y,x%y):abs(x);
}
void read(int &x)
{
	int signum=1;
	x=0;
	char t=getchar();
	while(!isdigit(t))
	{
		if(t=='-')
			signum=-1;
		t=getchar();
	}
	while(isdigit(t))
	{
		x=x*10+t-'0';
		t=getchar();
	}
	x*=signum;
	return;
}
inline int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int value)
{
	for(int i=x;i<=totn;i+=lowbit(i))
		BIT[i]+=value;
	return;
}
int sum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=BIT[i];
	return res;
}
int main()
{
	read(n); 
	for(int i=1;i<=n;++i)
	{
		start[i]=totn;
		read(k);
		for(int j=1;j<=k;++j)
		{
			read(x);
			read(y);
			if(j>1)
			{
				int d=gcd(x-lastx,y-lasty);
				++totn;
				a[totn].x=(x-lastx)/d;
				a[totn].y=(y-lasty)/d;
				belong[totn]=i;
				t[totn]=a[totn];
			}
			else
			{
				firstx=x;
				firsty=y;
			}
			if(j==k)
			{
				int d=gcd(firstx-x,firsty-y);
				++totn;
				a[totn].x=(firstx-x)/d;
				a[totn].y=(firsty-y)/d;
				belong[totn]=i;
				t[totn]=a[totn];
			}
			lastx=x;
			lasty=y;
		}
		ending[i]=totn;
	}
	sort(t+1,t+totn+1,cmp1);
	for(int i=1;i<=totn;++i)
		a[i].no=lower_bound(t+1,t+totn+1,a[i],cmp1)-t;
	read(totq);
	for(int i=1;i<=totq;++i)
	{
		read(q[i].l);
		read(q[i].r);
		q[i].no=i;
	}
	sort(q+1,q+totq+1,cmp2);
	for(int i=1,j=1;i<=totq;++i)
	{
		while(j<=totn&&belong[j]<=q[i].r)
		{
			if(last[a[j].no])
				add(last[a[j].no],-1);
			last[a[j].no]=j;
			add(j++,1);
		}
		res[q[i].no]=sum(ending[q[i].r])-sum(start[q[i].l]);
	}
	for(int i=1;i<=totq;++i)
		printf("%d\n",res[i]);
	return 0;
}
