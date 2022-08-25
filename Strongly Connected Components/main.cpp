#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define inf 1>>30
using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

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

    void solve_ctc();
    void dfs_sort_top(int root, vector<int> &v, vector<vector<int>>& gr);
    vector<int> sort_top(int n, vector<vector<int>>& gr);
};

void Graph::dfs_sort_top(int root, vector<int> &v, vector<vector<int>>& gr){
    visited[root] = true;
    for(auto x: gr[root]){
        if(!visited[x]){
            dfs_sort_top(x, v, gr);
        }
    }
    v.push_back(root);
}

vector<int> Graph::sort_top(int n, vector<vector<int>>& gr){
    vector<int> ans;
    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            dfs_sort_top(i, ans, gr);
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
void Graph::solve_ctc(){
    //obtinem nodurile in ordine topologica
    int n, m, x, y;
    fin>>n>>m;

    visited.resize(n+1, false);
    adj.resize(n+1);

    for(int i = 1; i <= m; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
    }

    vector<int> ord = sort_top(n, adj);

   //for(auto x: ord) fout<<x<<' ';
  // cout<<'\n';

   //creating reverted graph
   reverted_graph.resize(n+1);
   for(int i = 1; i <= n; ++i){
        for(auto x: adj[i]){
            reverted_graph[x].push_back(i);
        }
   }

   //works
//   for(int i = 1; i <= n; ++i){
//       cout<<i<<" : ";
//       for(auto y: reverted_graph[i]){
//           cout<<y<<' ';
//       }
//       cout<<'\n';
//   }

    vector<vector<int>> ctc;
    visited.clear();
    visited.resize(n+1, false);
    for(auto x: visited) cout<<x<<'\n';
    for(auto x: ord){
        if(!visited[x]){
            vector<int> comp;
            dfs_sort_top(x, comp, reverted_graph);
            ctc.push_back(comp);
        }
    }

    fout<<ctc.size()<<'\n';
    for(auto x: ctc){
        for(auto y: x) fout<<y<<' ';
        fout<<'\n';
    }
}
int main() {
    Graph g;
    g.solve_ctc();
    return 0;
}