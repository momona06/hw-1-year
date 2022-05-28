#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int numx, numy, numl,midx,midy;
vector<int>x, y;
vector<bool>visit;
vector<bool>base;
vector<vector<bool>>match;

bool dfs(int n);

int main()
{
	cin >> numx >> numy>>numl;
	for (int i = 0; i < numx; i++)
		x.push_back(0);
	for (int i = 0; i < numy; i++)
		y.push_back(0);
	for (int i = 0; i < numx; i++)
	{
		match.push_back(base);
		for (int j = 0; j < numy; j++)
			match[i].push_back(false);
	}
	for (int i = 0; i < numl; i++)
	{
		cin >> midx >> midy;
		match[midx][midy] = 1;
	}
	for (int i = 0; i < numx; i++)
		x[i] = -1;
	for (int i = 0; i < numy; i++)
		y[i] = -1;
	for (int i = 0; i < numx; i++)
	{
		if (x[i] == -1)
			visit.clear();
		for (int j = 0; j < numy; j++)
			visit.push_back(false);
		dfs(i);
	}
	for (int i = 0; i < numx; i++)
	{
		if (x[i] != -1)
			cout << i << ' ' << x[i] << endl;
	}
	return 0;
}


bool dfs(int n)
{
	for (int i = 0; i < numy; i++)
	{
		if (match[n][i]==true && visit[i]==false)
		{
			visit[i] = 1;
			if (y[i] == -1 || dfs(y[i]))
			{
				x[n] = i;
				y[i] = n;
				return true;
			}
		}
	}
	return false;
}