#include <iostream>
#include <vector>

using namespace std;

const int MAX_D = 100;
const int MAX_T = 50;

int n_town, n_day, prison, Q;

double cache[MAX_D+1][MAX_T+1];
vector<vector<int> > graph;

void init()
{
    // initialize the cache
    for(int days = 0; days <= MAX_D; ++days)
        for(int towns = 0; towns <= MAX_T; ++towns)
            cache[days][towns] = -1;
    
    cin >> n_town >> n_day >> prison;

    graph.clear();
    
    // initialize the graph
    graph.reserve(n_town);
    for(int towns = 0; towns < n_town; ++towns)
    {
        vector<int> graph_row;
        graph_row.reserve(n_town);
        for(int i = 0; i < n_town; ++i)
        {
            int temp; cin >> temp;
            if(temp)
                graph_row.push_back(i);   
        }
        graph.push_back(graph_row);
    }
}

double solve(int day, int c_town)
{
    // base case
    if(day == 0) return (c_town == prison ? 1.0 : 0.0);
    
    // memoization
    double& ret = cache[day][c_town];
    if(ret > -0.5) return ret;
    ret = 0.0;
    for(int i = 0; i < graph[c_town].size(); ++i)
    {
        int next_town = graph[c_town][i];
        ret += solve(day - 1, next_town) / graph[next_town].size();
    }
    return ret;
}

// void print_graph()
// {
//     for(auto e: graph)
//     {
//         for(auto e_: e)
//             cout << e_ << "\t";
//         cout << endl;
//     }
// }

int main()
{
    int C; cin >> C;
    for(int i = 0; i < C; ++i)
    {
        init();
        int T; cin >> T;
        for(int j = 0; j < T; ++j)
        {
            cin >> Q;
            cout.precision(8);
            cout << solve(n_day, Q) << " ";
        }
        cout << endl;
    }

    return 0;
}