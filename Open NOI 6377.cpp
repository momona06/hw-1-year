#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int>month,day;
vector<string>name;
vector<int>list;//the picked list each time
//vector<int>relist;//the cout list
vector<bool>check;//check whether the student is selected
int n,count1;
bool rej=false;
string midname;
int mid,midmon,midday,minmon=13,minday=32,forelist=0;
int main()
{
cin>>n;
count1=n;
for(int i=0;i<n;i++)
{
    cin>>midname;
    name.push_back(midname);
    cin>>midmon;
    month.push_back(midmon);
    cin>>midday;
    day.push_back(midday);
    check.push_back(false);
}

while(count1!=0)
{
    for(int i=0;i<n;i++)
    {
        if(check[i]==false)
        {
            if(month[i]<minmon)
            {
                minmon=month[i];
            }
        }
    }
        for(int i=0;i<n;i++)
    {
        if(check[i]==false)
        {
            if(month[i]==minmon&&day[i]<minday)
            {
                minday=day[i];
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(month[i]==minmon&&day[i]==minday&&check[i]==false)
        {
            check[i]=true;
            list.push_back(i);
            count1--;
        }
    }//selection mode


if(list.size()>1)
{
for(int i=0;i<list.size()-1;i++)
{
for(int j=0;j<list.size()-1-i;j++)
{
    if(name[list[j]].size()>name[list[j+1]].size())
    {
        mid=list[j];
        list[j]=list[j+1];
        list[j+1]=mid;
    }
}
}

for(int i=0;i<list.size()-1;i++)
{
    if(name[list[i]].size()!=name[list[i+1]].size())
    {
        for(int j=forelist;j<i-1+1;j++)
        {
            for(int k=forelist;k<i-1-j+1;k++)
            {
                if(name[list[j]].compare(name[list[j+1]])<0)
                {
                    mid=list[j];
                    list[j]=list[j+1];
                    list[j+1]=mid;
                }
            }
        }
        forelist=i+1;
    }
}
//resort mode
//ps: if the list is more, then pass this mode


    rej=true;
cout<<minmon<<' '<<minday;
for(int i=0;i<list.size();i++)
{
    cout<<' '<<name[list[i]];
}
cout<<endl;
}//cout mode, only if the list or the relist is more

    list.clear();
    minday=32;
    minmon=13;//reinitialization

}
if(rej==false)
cout<<"None";
return 0;
}
