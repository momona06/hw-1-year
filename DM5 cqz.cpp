#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
using namespace std;

class node
{
public:
    node() = default;
    set<int> conn;
    int mark = 0;
};

bool cmp(tuple<int, int>a, tuple<int, int>b) {return get<0>(a) < get<0>(b);}

vector<node> x, y;
map<int, int> match; // note that the y-element happen first here, e.g. <1, 2> stands for the match between x_2 and y_1
vector<int> pathx, pathy; // store the dfs path

void dfs(int x0)
{
    for (auto& nde : x[x0].conn) // for each side the last-visited node is connected to,
    {
        if (y[nde].mark == 1) // if the node connected is already in the match,
        {
            if (find(pathx.begin(), pathx.end(), match[nde]) != pathx.end()) // unless that node is matched with another node in question,
                continue; // under which circumstances we just go and seek the next;
            pathy.emplace_back(nde); // we add that node to our path-to-be,
            pathx.emplace_back(match[nde]); // as well as the node's image, which is an x-element.
            dfs(match[nde]);
            pathy.pop_back();
            pathx.pop_back();
        }
        else // if that node hasn't been dealt with, then our path is complete and legal,
        {
            pathy.emplace_back(nde); // we still add that node to our path (no longer path-to-be).
            for (int t = 0; t < pathx.size(); t++) // Then we try to put the path into effect,
            {
                match[pathy[t]] = pathx[t]; // dealing with a pair of elements, one x and one y, at a time.
            }
            x[pathx.front()].mark = 1; // Let's mark them,
            y[pathy.back()].mark = 1; // to be newlyweds.
            throw 1; // Then we go and deal with the next x.
        }
    }
}

int main()
{
    int nx, ny; // size of X and Y
    cin >> nx >> ny;
    int i, j, k;
    for (i = 0; i < nx; i++) x.emplace_back(node());
    for (i = 0; i < ny; i++) y.emplace_back(node());

    // input section
    cin >> i;
    while (i--)
    {
        cin >> j >> k;
        x[j].conn.emplace(k);
        y[k].conn.emplace(j);
    }
    // input section finished

    // start working
    while (true)
    {
        for (i = 0; i < nx and x[i].mark != 0; i++) ; // we find the first x-element that hasn't been dealt with
        if (i == nx) break; // if all x-elements has been dealt with, we are done
        pathx.emplace_back(i); // we add the beginning of the journey.
        try
        {
            dfs(i);
        }
        catch(...)
        {
            pathx.clear();
            pathy.clear();
            continue;
        }
        x[i].mark = 2;
        pathx.clear();
    }
    // working finished

    // output
    vector<tuple<int, int>> ans;
    ans.reserve(match.size());
    for (auto& pr : match) ans.emplace_back(tuple<int, int>(pr.second, pr.first));
    sort(ans.begin(), ans.end(), cmp);
    for (auto& pr : ans) cout << get<0>(pr) << ' ' << get<1>(pr) << endl;
    return 0;
}
