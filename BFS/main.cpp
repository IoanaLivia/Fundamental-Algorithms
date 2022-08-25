#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define inf 1>>30
using namespace std;

ifstream fin("bfs.in");
ofstream fout("bfs.out");

class Graph{
private:
    int n_nodes;
    vector<vector<int>> adj;
    vector<pair<int,pair<int,int>>> adj_w;
    vector<int> parent;
    vector<int> rank;
    vector<bool> visited;
    vector<int> sort_top;
    vector<int> ctc;
    vector<vector<int>> reverted_graph;
public:
    Graph(){
        n_nodes = 0;
        adj_w = {};
    }

    void solve_bfs();
};

void Graph::solve_bfs(){
    int n, m, x, y, s;
    fin>>n>>m>>s;

    adj.resize(n+1);
    visited.resize(n+1, false);

    vector<int> d(n+1, -1);

    for(int i = 0; i < m; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
    }

    visited[s] = true;
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        s = q.front();
        for(auto x: adj[s]){
            if(!visited[x]){
                visited[x] = true;
                if(d[x] == -1) d[x] = d[s] + 1;
                q.push(x);
            }
        }
        q.pop();
    }

    for(int i = 1; i <= n; ++i) fout<<d[i]<<' ';


}
int main() {
    Graph g;
    g.solve_bfs();
    return 0;
}
