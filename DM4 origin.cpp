#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class line{
    public:
    int start;
    int end;
};
int numv,nume,mid,vmid,v1mid,wmid,tag,btag,wall=0;
line midline;
bool bl;
vector<int>a,b,w;
vector<int>v,v1;
vector<line>tree;//点序号：0 1 2 ...numv-1
int main()
{
    cin>>numv>>nume;
    for(int i=0;i<=numv;i++)
        {
            cin>>mid;
            a.push_back(mid);
        }
    for(int i=0;i<nume;i++)
        {
            cin>>mid;
            b.push_back(mid);
        }
    for(int i=0;i<nume;i++)
        {
            cin>>mid;
            w.push_back(mid);
        }

    for(int i=1;i<numv;i++)
    {
        v.push_back(i);
    }
    v1.push_back(0);

    while(!v.empty())
    {
        v1mid=v1[0];
        for(int i=a[v1mid];i<a[v1mid+1];i++)
        {
            vmid=b[i];
            btag = 1;
            tag = 1;
            break;
        }
        for(int i=0;i<b.size();i++)
        {
            if(b[i]==v1mid)
            {
                for(int j=0;j<numv-1;j++)
                {
                    if (i < a[j + 1] && i >= a[j])
                    {
                        vmid = j;
                        break;
                    }
                }
                btag = 0;
                tag = 0;
                break;
            }
        }
        //tag=0: vmid->v1mid
        //tag=1: v1mid->vmid
        for(int i=0;i<v.size();i++)
        {
            for(int j=0;j<v1.size();j++)
            {
                bl=false;
                for(int k=a[v[i]];k<a[v[i]+1];k++)
                    if(b[k]==v1[j])
                    {
                    bl=true;
                    wmid=w[k];
                    tag=0;
                    break;
                    }
                for(int d=a[v1[j]];d<a[v1[j]+1];d++)
                    if(b[d]==v[i])
                    {
                    bl=true;
                    wmid=w[d];
                    tag=1;
                    break;
                    }
                if(bl==true)
                {
                    if(btag==0)
                    {
                        if(wmid<w[a[vmid]])
                        {
                            vmid=v[i];
                            v1mid=v1[j];
                        }
                    }
                    else if(btag==1)
                    {
                        if(wmid<w[a[v1mid]])
                        {
                            vmid=v[i];
                            v1mid=v1[j];
                        }
                    }
                    btag=tag;
                }
                
            }
        }
    v1.push_back(vmid);
    for(auto it=v.begin();it!=v.end();it++)
    {
        if(*it==vmid)
        {
            v.erase(it);
            break;
        }
    }
    if(btag==0)
    {
        midline.start=vmid;
        midline.end=v1mid;
        tree.push_back(midline);
        wall+=w[a[vmid]];
    }
    else if(btag==1)
        {
        midline.start=v1mid;
        midline.end=vmid;
        tree.push_back(midline);
        wall+=w[a[v1mid]];
        }
    }//main structure


    for(int i=0;i<tree.size();i++)
    {
        cout<<'['<<tree[i].start<<"->"<<tree[i].end<<']';
    }
    cout<<' '<<wall;
    return 0;
}
