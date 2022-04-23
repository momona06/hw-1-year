#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int numv,nume,n,mid,minu,minuj,kmid;
vector<int>a;
vector<int>b;
vector<int>w;
vector<int>ns;
vector<int>ne;
vector<int>path;
vector<int>S;
vector<int>pi;
vector<int>port;

int main()
{

//////赋值
cin >> numv;
cin >> nume;
	int mid;
    for (int k = 0; k <= numv; k++)
	{
		cin >> mid;
		a.push_back(mid);
	}
	for (int k = 0; k <= nume - 1; k++)
	{
		cin >> mid;
		b.push_back(mid);
	}
    for (int k = 0; k <= nume - 1; k++)
	{
		cin >> mid;
		w.push_back(mid);
	}
    cin>>n;
    for(int k=0;k<=n-1;k++)
	{
	    cin>>mid;
	    ns.push_back(mid);
		cin>>mid;
	    ne.push_back(mid);
	}


	for(int i=0;i<=numv-1;i++)
	{
		pi.push_back(0);
	}
	for (int i = 0; i <= numv - 1; i++)
	{
		path.push_back(ns[0]);
	}


///////主体部分

for(int j=0;j<=n-1;j++)
{
	for (int i = 0; i <= numv - 1; i++)
	{
		path.push_back(ns[j]);
	}

    for(int i=0;i<=numv-1;i++)
    {
    if(i!=ns[j])
    S.push_back(i);
    }

for(int d=0;d<=numv-1;d++)
pi[d]=-1;

pi[ns[j]]=0;
for(int s=a[ns[j]];s<=a[ns[j]+1]-1;s++)
    pi[b[s]]=w[s];
//步骤a


while(true)//
{
	minu=-1;
	minuj=-1;

for(int p=0;p<=S.size()-1;p++)
{
    if(pi[S[p]]>=0)
    {
        minu=pi[S[p]];
		minuj=S[p];
        break;
    }
}//minu赋初值

for(int p=0;p<=S.size()-1;p++)
{
if(minu>=0&&pi[S[p]]>=0&&pi[S[p]]<minu)
{
    minu=pi[S[p]];
    minuj=S[p];
}
}//minu找最小值



for(int q=0;q<=S.size()-1;q++)
{
    if(minuj==S[q])
    {
       swap(S[q],*(end(S)-1));////pay attention
	   S.pop_back();
	   break;
    }
}//删除S中j元素

if (minu < 0)
{
	if (pi[ne[j]] < 0)
	{
		cout << "NO PATH" << endl;
		break;
	}
	else
		break;
}

if(S.empty())
break;//结束判断

/*if (count1 == numv - 1 && pi[ne[j]] < 0)
{
	cout << "NO PATH" << endl;
	break;
}*/

//步骤b

for(int d=0;d<=S.size()-1;d++)
{
    for(int g=a[minuj];g<=a[minuj+1]-1;g++)
    {
	if(b[g]==S[d])
	{
		if (pi[b[g]] < 0)
		{
			pi[b[g]] = pi[minuj] + w[g];
			path[b[g]] = minuj;
		}
		else
		{
			if (pi[b[g]] > pi[minuj] + w[g])
			{
				pi[b[g]] = pi[minuj] + w[g];
				path[b[g]] = minuj;
			}
			}
    }
    }
}

}//某次查找结束
if (pi[ne[j]] >= 0)
{
	cout << '[';
	port.clear();
	mid = path[ne[j]];
	port.push_back(path[ne[j]]);
	while(true)
	{
		if (mid == ns[j])
			break;
		mid = path[mid];
		port.push_back(mid);
	}
	for (int g = port.size() - 1; g >= 0; g--)
		cout << port[g] << "->";
	cout << ne[j];
	cout << ' ' << pi[ne[j]] << ']' << endl;
}

for(int j=0;j<=numv-1;j++)
pi[j]=0;

path.clear();


S.clear();

}//n次查找结束



return 0;


}
