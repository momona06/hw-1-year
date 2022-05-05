#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long long  numv, nume;
vector<long long>a;
vector<long long>b;
vector<long long>result;
vector<long long>visit;
vector<vector<long long>>print;
vector<long long>::iterator it;
long long d,sl=0;
//bool key = false;

void dfs(long long step);

int main()
{
	cin >> numv >> nume;
	long long mid;
	visit.push_back(1);
	for (long long k = 0; k <= numv - 2; k++)
	{
		visit.push_back(0);
	}
	for (long long k = 0; k <= numv; k++)
	{
		cin >> mid;
		a.push_back(mid);
	}
	for (long long k = 0; k <= nume - 1; k++)
	{
		cin >> mid;
		b.push_back(mid);
	}

	for (long long k = 0; k <= numv-1; k++)
		sort(b.begin()+a[k], b.begin()+a[k+1]);

	for(long long i=0;i<=numv-1;i++)
	{
		for(long long j=a[i];j<=a[i+1]-2;j++)
		{
			for(long long k=j+1;k<=a[i+1]-1;k++)
			{
				if(b[j]==b[k])
					b[k]=-1;
			}
		}
	}
	result.push_back(0);
	dfs(0);
	cout << sl<<endl;
	for (long long p = 0; p <= sl - 1; p++)
	{
		for (long long l = 0; l <= print[p].size() - 2; l++)
		{
			cout << print[p][l] << '-' << '>';
		}
		cout << print[p][print[p].size() - 1] << endl;
	}

	return 0;
}


void dfs(long long step)
{   
	it = result.end() - 1;
	d = *it;
	if (d == numv - 1)
	{
		/*for (long long l = 0; l <= result.size() - 2; l++)
			cout << result[l] << '-' << '>';
		cout << result[result.size() - 1] << endl;*/

		sl++;
		print.push_back(result);

		result.pop_back();
		return;
	}
	else
	{
		for (long long i = a[step]; i <= a[step + 1] - 1; i++)
		{
		//	key = false;
			if (visit[b[i]] == 0 && b[i]>=0)
			{
		//		key = true;
				visit[b[i]] = 1;
				result.push_back(b[i]);
				dfs(b[i]);
				visit[b[i]] = 0;
			}
		}
		//if(key == true)
		//result.pop_back();
		result.pop_back();
	}
}




