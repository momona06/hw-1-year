#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
//#include<iterator>
using namespace std;

bool judge(vector<int> a);
void calcu();

class line 
{
public:
	int x;
	int y;
};
int numx,numy,numl,midx,midy,mid0,k;
line midl;
vector<int>x, y;//´æx,y×´Ì¬
set<int>u,cu,v;//u,taou,v´æ´¢¼¯
vector<int>midcu;
vector<line>tline;//´æ¶þ·ÖÍ¼µÄ±ß
vector<line>match;//´æ×î´óÆ¥Åä

int main()
{
	cin >> numx >> numy >> numl;
	for (int i = 0; i < numl; i++)
	{
		cin >> midx >> midy;
		midl.x = midx;
		midl.y = midy;
		tline.push_back(midl);
	}
	for (int i = 0; i < numx; i++)
		x.push_back(0);
	for (int i = 0; i < numy; i++)
		y.push_back(0);
	

	while (judge(x))
	{
		cu.clear();
		u.clear();
		v.clear();
		midcu.clear();
		u.insert(mid0);
		while (1)
		{
			calcu();
			if (cu == v)
			{
				x[mid0] = 2;
				break;
			}
			else
			{
				set_difference(cu.begin(), cu.end(), v.begin(), v.end(),back_inserter(midcu));
				int d = midcu[0];
				if (y[d] == 1)
				{
					for (int i = 0; i < match.size(); i++)
					{
						if (match[i].y = d)
							k = match[i].x;
						break;
					}
					u.insert(k);
					v.insert(d);
				}
				else
				{
					midl.x = mid0;
					midl.y = d;
					x[mid0] = 1;
					y[d] = 1;
					match.push_back(midl);
					break;
				}
			}
		}
	}


	for (int i = 0; i < match.size(); i++)
		cout << match[i].x << ' ' << match[i].y << endl;


	return 0;
}

bool judge(vector<int> a)
{
	bool jud = false;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == 0)
		{
			jud = true;
			mid0 = i;
			break;
		}
	}
	return jud;
}
void calcu()
{
	cu.clear();
	auto it = u.begin();
	for (int i = 0; i < u.size(); i++,it++)
	{
		for (int j = 0; j < tline.size(); j++)
		{
			if (tline[j].x == *it)
				cu.insert(tline[j].y);
		}
	}
}