#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
//#include<sstream>
using namespace std;
vector<int>bom;
vector<int>line;       //有n个元素
vector<int>time1;      //有n个元素
vector<vector<int>>pre;//有n个元素
vector<int>newline;
vector<int>pi;
vector<int>tao;
vector<int>t;
vector<int>count1;
vector<int>result;
vector<vector<int>>repo;
int n,cal,k,prek,num,num0,midnum,midnum2,cut,x,length;
string mid,numstr;
bool c;

void dfs(int l);

int main()
{	
    //输入
	cin>>n;
	getchar();
	for(int i = 0; i < n; i++)
		pre.push_back(bom);
	for(int i=0;i<n;i++)
	{
		getline(cin,mid);
		midnum = 0;
		while(mid[midnum]!=' ')
		{
			midnum++;
		}
		for (int d = 0; d <midnum; d++)
		{
			numstr+= mid[d];
		}
		num = atoi(numstr.c_str());
		numstr.clear();
		line.push_back(num);

		midnum2 = midnum;
		midnum++;
		while (mid[midnum]!= ' '&&midnum!=mid.size())
		{
			midnum++;
		}
		for (int d =midnum2+1;d <= midnum - 1;d++)
		{
			numstr+= mid[d];
		}
		num = atoi(numstr.c_str());
		numstr.clear();
		time1.push_back(num);
		cal = midnum+1;
		cut = cal;
		for(;cal<mid.size();cal++)
		{
				if(mid[cal]==',')
				{
					k=cal;
					prek=k-1;
					while((mid[prek]!=',')&&(mid[prek]!=' '))
						{
							prek--;
						}
					for(int d=prek+1;d<=k-1;d++)
					{
						numstr+=mid[d];
					}
				num=atoi(numstr.c_str());
				numstr.clear();
				pre[i].push_back(num);
				}
		}
		if((mid[mid.size()-1]=='0'||mid[mid.size()-1]=='1'||mid[mid.size()-1]=='2'||mid[mid.size()-1]=='3'||mid[mid.size()-1]=='4'||mid[mid.size()-1]=='5'||mid[mid.size()-1]=='6'||mid[mid.size()-1]=='7'||mid[mid.size()-1]=='8'||mid[mid.size()-1]=='9')&&(mid.size()>cut))//cut为time后空格
		{
			k=mid.size()-1;
			prek=k-1;
		while((mid[prek]!=',')&&(mid[prek]!=' '))
		{
			prek--;
		}
		for(int d=prek+1;d<=k;d++)
		{
			numstr+=mid[d];
		}
		num=atoi(numstr.c_str());
		numstr.clear();
		pre[i].push_back(num);
		}
		mid.clear();
	}


	//排序算法
	for(int i=0;i<n;i++)
		count1.push_back(pre[i].size());
	for(int i=0;i<n;i++)
	{
		c = false;
		for(int j=0;j<n;j++)
		{
			if(count1[j]==0)
			{
			newline.push_back(j);
			count1[j]--;
			num = j;
			c = true;
			break;
			}
		}
		if (c == true)
		{
			for (int g= 0; g < n; g++)
			{
				for (int d = 0; d <pre[g].size(); d++)
				{
					if (pre[g][d] == num)
					{
						count1[g]--;
						break;
					}
				}
			}
		}
	}

    //最长路径算法
    for(int i=0;i<=n;i++)
	pi.push_back(0);
	//pi[newline[0]]=0;

	line.push_back(n);
	time1.push_back(0);
	newline.push_back(n);
	pre.push_back(bom);
	for (int i = 0; i < n; i++)
		pre[n].push_back(i);
	//虚拟节点n
	/*line.push_back(n + 1);
	time1.push_back(0);
	newline.push_back(n+1);
	pre.push_back(bom);
	for (int i = 0; i <= n; i++)
		pre[i].push_back(n + 1);*/
	//虚拟节点n+1

	for(int j=1;j<=n;j++)
	{
		for(int i=0;i<=j-1;i++)
		{
			c=false;
			for(int k=0;k<pre[newline[j]].size();k++)
			{
				if(pre[newline[j]][k]==newline[i])
				{
					c=true;
					break;
				}
			}
			if((pi[newline[j]]<(pi[newline[i]]+time1[newline[i]]))&&c==true)
			pi[newline[j]]=pi[newline[i]]+time1[newline[i]];
		}
	}

	//关键路径
	/*for (int i = 0; i <= n; i++)
	{
		if (pre[i].size() == 0)
			dfs(i);
	}*/


	//工序延误时间算法
	for(int i=0;i<=n;i++)
	tao.push_back(-1);////max
	tao[newline[n]]=pi[newline[n]];
	for(int j=n-1;j>=0;j--)
	{
		for(int i=n;i>=j+1;i--)
		{
			c=false;
			for(int k=0;k<pre[newline[i]].size();k++)
			{
				if(pre[newline[i]][k]==newline[j])
				{
					c=true;
					break;
				}
			}
			if(tao[newline[j]]<0&&c==true)
			tao[newline[j]]=tao[newline[i]]-time1[newline[j]];
			else if((tao[newline[j]]>(tao[newline[i]]-time1[newline[j]]))&&c==true&&tao[newline[j]]>=0)
			tao[newline[j]]=tao[newline[i]]-time1[newline[j]];
		}
	}
	for(int i=0;i<=n;i++)
	t.push_back(tao[i]-pi[i]);

	dfs(newline[n]);

	//输出
	cout<<pi[newline[n]] << endl;	
	for (int i = 0; i < repo.size(); i++)
	{
		cout << '[';
		for (int d = repo[i].size()-1; d >=1; d--)
		{
			cout << repo[i][d] << "->";
		}
		cout << "end]"<<endl;
	}	
	for(int i=0;i<=n-1;i++)
	cout<<t[i]<<endl;

}


void dfs(int l)//l为原始编号
{
	result.push_back(l);
	if (pre[l].size()==0)
	{	
		length = 0;
		for (int j = 0; j <result.size(); j++)
			length += time1[result[j]];
		if(length==pi[newline[n]])
			repo.push_back(result); 
		result.pop_back();
		return;
	}
	
	/*else
	{
		for (int i = 0; i< n; i++)
		{	
			
			//int count3 = 0;
			//if(count3 == newline[l] - 1)
			//break;
			//c = false;
			for (int d = 0; d < pre[l].size(); d++)
			{
				if (pre[l][d] == i)
				{
				//	count3++;
				//	c = true;					
				//	break;
					dfs(i);
				}
			}
		//	if (c == true)
		//		dfs(i);
			//result.pop_back();
		}
		result.pop_back();
	}*/

	else {
		for (int d = 0; d < pre[l].size(); d++)
		{
			if(t[pre[l][d]]==0)
			dfs(pre[l][d]);
		}
		result.pop_back();
	}
	//result.pop_back();
}