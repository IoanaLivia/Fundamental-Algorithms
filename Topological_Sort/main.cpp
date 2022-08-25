#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

class Graph{
private:
    int n_nodes;
    vector<vector<int>> adj;
    vector<pair<int,pair<int,int>>> adj_w;
    vector<int> parent;
    vector<int> rank;
    vector<bool> visited;
    vector<int> sort_top;
public:
    Graph(){
        n_nodes = 0;
        adj_w = {};
    }

    void solve_comp_conexe();
    void solve_sort_top();

    void dfs(int root);
    void dfs_sort_top(int root);
};

void Graph::dfs(int root){
    visited[root] = true;
    for(auto x: adj[root]){
        if(!visited[x]){
            dfs(x);
        }
    }
}

void Graph::dfs_sort_top(int root){
    visited[root] = true;
    for(auto x: adj[root]){
        if(!visited[x]){
            dfs_sort_top(x);
        }
    }
    sort_top.push_back(root);
}

void Graph::solve_comp_conexe(){
    int n, m, x, y, conexe = 0;
    fin>>n>>m;

    adj.resize(n+1);
    visited.resize(n+1, false);

    for(int i = 0; i < m; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            ++conexe;
            dfs(i);
        }
    }

    fout<<conexe;

}

void Graph::solve_sort_top(){
    int n, m, x, y;
    fin>>n>>m;

    adj.resize(n+1);
    visited.resize(n+1, false);

    for(int i = 0; i < m; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
    }

    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            dfs_sort_top(i);
        }
    }


    for(int i = n-1; i >= 0; i--) fout<<sort_top[i]<<' ';

}

int main() {
    Graph g;
    g.solve_sort_top();
    return 0;
}
