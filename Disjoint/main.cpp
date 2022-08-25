#include <iostream>
#include <fstream>
#include <vector>
#define inf 1>>30
using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

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

    void solve_pad_mult_disjuncte();
    void unite(int a, int b);
    int find(int node);
};

int Graph:: find(int node){
    if(parent[node] != node){
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

void Graph:: unite(int a, int b){
    a = find(a);
    b = find(b);
    int old_value;
    if(rank[a] > rank[b]){
        old_value = rank[b];
        parent[b] = a;
        rank[a] += old_value;
    }
    else
    {
        old_value = rank[a];
        parent[a] = b;
        rank[b] += old_value;
    }
}

void Graph::solve_pad_mult_disjuncte(){
    int n, m, x, y, cod;
    fin>>n>>m;

    parent.resize(n+1);
    rank.resize(n+1);

    for(int i = 1; i <= n; ++i){
        parent[i] = i;
        rank[i] = 1;
    }

    for(int i = 1; i <= m; ++i){
        fin>>cod>>x>>y;
        if(cod == 1){
            unite(x, y);
        }
        if(cod == 2){
            if(find(x) != find(y)) fout<<"NU\n";
            else fout<<"DA\n";
        }
    }
}

int main() {
    Graph g;
    g.solve_pad_mult_disjuncte();
    return 0;
}
