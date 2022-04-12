#include<iostream>
using namespace std;
void print(int a);
void print(int *a);
void printd(int &a);
int main()
{
  int (*pa)[3];
  int a[3]={1,3,4},b=3,c=2,d=1;
  int *pd[3];
  int *pb;
  int *pc=nullptr;
  pb=a;
  pa=&a;
  pd[0]=&b,pd[1]=&c,pd[2]=&d;
  cout<<*(*pa+1)<<endl;
  cout<<*a+2<<endl;
  cout<<*pb<<endl;
  cout<<pc<<endl;

  cout<<endl;
  int t=0;
  int *pt=&t;
  int &yt=t;
  print(t);
  cout<<t<<endl;
  print(pt);
  cout<<t<<endl;
  t=0;
  print(yt);
  cout<<t<<endl;

  return 0;

}

void print(int a)
{
	a=3;
	cout<<a<<endl;
}

void print(int *a)
{
	*a=3;
	cout<<*a<<endl;
}

void print(int &a)
{
	a=3;
	cout<<a<<endl;
}
