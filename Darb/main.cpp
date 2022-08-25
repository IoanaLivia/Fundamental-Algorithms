#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define inf 1>>30
using namespace std;

ifstream fin("darb.in");
ofstream fout("darb.out");

class Graph{
private:
    int n_nodes;
    vector<vector<int>> adj;
    vector<pair<int,pair<int,int>>> adj_w;
    vector<int> parent;
    vector<int> rank;
    vector<bool> visited;
    vector<int> ctc;
    vector<vector<int>> reverted_graph;
public:
    Graph(){
        n_nodes = 0;
        adj_w = {};
    }

    void solve_darb();
    void dfs(int node, int& last_node, vector<int>& lvl, int& lvl_max);
};

void Graph::dfs(int node, int& last_node, vector<int>& lvl, int& lvl_max){
    visited[node] = true;
    for(auto x: adj[node]){
        if(!visited[x]){
            lvl[x] = lvl[node] + 1;
            if(lvl[x] > lvl_max){
                last_node = x;
                lvl_max = lvl[x];
            }
            dfs(x, last_node, lvl, lvl_max);
        }
    }

}
void Graph::solve_darb(){
    int n, x, y;
    fin>>n;

    visited.resize(n+1, false);
    adj.resize(n+1);

    for(int i = 1; i < n; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int last_node = 0, ultimate_node = 0, lvl_max = 0;
    vector<int> level(n+1, 1);

    dfs(1,last_node, level, lvl_max);

    visited.clear();
    visited.resize(n+1, false);

    level.clear();
    level.resize(n+1, 1);
    lvl_max = 0;

    dfs(last_node,ultimate_node, level, lvl_max);
    fout<<level[ultimate_node];

}
int main() {
    Graph g;
    g.solve_darb();
    return 0;
}
