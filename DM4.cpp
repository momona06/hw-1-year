#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class line {
public:
    int start;
    int end;
};
int numv, nume, mid, vmid, v1mid, wmid=-1, tag, btag, wall = 0;
line midline;
vector<int>a, b, w;
vector<int>v, v1;
vector<line>tree;//点序号：0 1 2 ...numv-1
int main()
{
    cin >> numv >> nume;
    for (int i = 0; i <= numv; i++)
    {
        cin >> mid;
        a.push_back(mid);
    }
    for (int i = 0; i < nume; i++)
    {
        cin >> mid;
        b.push_back(mid);
    }
    for (int i = 0; i < nume; i++)
    {
        cin >> mid;
        w.push_back(mid);
    }

    for (int i = 1; i < numv; i++)
    {
        v.push_back(i);
    }
    v1.push_back(0);

    while (!v.empty())
    {
        //vmid,v1mid,wmid均未初始化
        for (int i = 0; i < v1.size(); i++)
        {
            for (int j = a[v1[i]]; j < a[v1[i]+1]; j++)
            {
                for (int k = 0; k < v.size(); k++)//v1[i] v[k]
                {
                    if (b[j] == v[k])
                    {
                        if (wmid < 0)
                        {
                            wmid = w[j];
                            v1mid = v1[i];
                            vmid = v[k];
                        }
                        else if (w[j] < wmid&&wmid>=0)
                        {
                            wmid = w[j];
                            v1mid = v1[i];
                            vmid =v[k];
                        }
                        break;
                    }
                }
            }
        }
        wall += wmid;
        v1.push_back(vmid);
        midline.start =v1mid;
        midline.end = vmid;
        tree.push_back(midline);
        for (auto it = v.begin(); it != v.end(); it++)
        {
            if (*it == vmid)
            {
                v.erase(it);
                break;
            }
        }
        wmid = -1;

    }
    for (int i = 0; i < tree.size(); i++)
    {
        cout << '[' << tree[i].start << "->" << tree[i].end << ']';
    }
    cout << ' ' << wall;
    return 0;

}