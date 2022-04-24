#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include<cassert>
using namespace std;
const int INF = 0x3f3f3f3f;

class process
{
public:
    vector<int> prec;
    vector<int> succ;
    int time = 0, order = -1;
    process() = default;
    explicit process(int t): time(t){};
};

vector<process> pr;
vector<int> sorted, pi, tau;
int n;

list<int> route;
long long currtime = 0;
void dfs(int curr) // here curr is the sorted index
{
    route.emplace_back(sorted[curr]);
    currtime += pr[sorted[curr]].time;
    if (curr == n - 1 and currtime == pi[n - 1])
    {
        cout << "[";
        for (int& i : route)
        {
            if (i != n - 1) cout << i << "->";
            else cout << "end]" << endl;
        }
    }
    for (int& i : pr[sorted[curr]].succ)
        if (pi[pr[i].order] == tau[pr[i].order])
            dfs(pr[i].order);
    route.pop_back();
    currtime -= pr[sorted[curr]].time;
}
int main()
{
    cin >> n;
    getchar();
    int temp;
    string tempstr;
    for (int i = 0; i < n; i++) pr.emplace_back(process(0));
    for (int i = 0; i < n; i++)
    {
        getline(cin, tempstr);
        temp = tempstr.find(',');
        while (temp != string::npos)
        {
            tempstr.replace(temp, 1, " ");
            temp = tempstr.find(',');
        }
        tempstr += " -100";
        istringstream input(tempstr);
        input >> temp;
        assert(temp == i);
        input >> temp;
        pr[i].time = temp;
        input >> temp;
        while (temp != -100)
        {
            pr[i].prec.emplace_back(temp);
            pr[temp].succ.emplace_back(i);
            input >> temp;
        }
    }
    // push a virtual ending node in
    auto* tempproc = new process(0);
    tempproc->order = n;
    for (int i = 0; i < n; i++)
    {
        if (pr[i].succ.empty())
        {
            pr[i].succ.emplace_back(n);
            tempproc->prec.emplace_back(i);
        }
    }
    pr.emplace_back(*tempproc);
    delete tempproc;
    n++;
    // read process finished

    n = pr.size();

    //topological sorting
    vector<int> deg;
    deg.reserve(n + 5);
    sorted.reserve(n + 5);
    list<int> to_save;
    for (int i = 0; i < n; i++)
    {
        deg.emplace_back(pr[i].prec.size());
        if(pr[i].prec.empty()) to_save.emplace_back(i);
    }
    while (!to_save.empty())
    {
        int curr = to_save.front();
        to_save.pop_front();
        sorted.emplace_back(curr);
        pr[curr].order = sorted.size() - 1;
        for (auto& i : pr[curr].succ)
        {
            deg[i]--;
            if (deg[i] == 0) to_save.push_back(i);
            assert(deg[i] >= 0);
        }
    }
    // topological sorting finished

    // max route for earliest starting time
    pi.reserve(n + 5);
    for (int i = 1; i < n; i++) pi.emplace_back(0);
    long long maxtime = 0;
    for (int i = 0; i < n; i++)
    {
        for (auto& j : pr[sorted[i]].prec)
            if (pr[j].time + pi[pr[j].order] > pi[i])
                pi[i] = pr[j].time + pi[pr[j].order];
        if (pi[i] + pr[sorted[i]].time > maxtime) maxtime = pi[i] + pr[sorted[i]].time;
    }
    assert(maxtime == pi[n - 1]);
    cout << pi[n - 1] << endl;
    // max route finished

    // max route reversed for latest starting time
    tau.reserve(n + 5);
    for (int i = 0; i < n - 1; i++) tau.emplace_back(INF);
    tau.emplace_back(pi[n - 1]);
    for (int i = n - 1; i >= 0; i--)
    {
        for (auto& j : pr[sorted[i]].succ)
            if (tau[i] > tau[pr[j].order] - pr[sorted[i]].time)
                tau[i] = tau[pr[j].order] - pr[sorted[i]].time;
    }
    // max route reversed finished


    // search for key routes
    for (int i = 0; pr[sorted[i]].prec.empty(); i++)
        if (tau[i] == pi[i]) dfs(i);
    // finish search

    // output
    for (int i = 0; i < n - 1; i++)
        cout << tau[pr[i].order] - pi[pr[i].order] << endl;
    return 0;
}
