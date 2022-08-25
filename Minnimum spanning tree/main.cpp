#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

class Graph{
private:
    int n_nodes;
    vector<pair<int,pair<int,int>>> adj_w;
    vector<int> parent;
    vector<int> rank;
public:
    Graph(){
        n_nodes = 0;
        adj_w = {};
    }
    Graph(int n,  vector<pair<int,pair<int,int>>>& gr){
        n_nodes = n;
        adj_w = gr;
    }

    void solve_apm();
    //APM: Kruskal union/find
    int find(int root);
    void unite(int a, int b);

    static bool f(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b ){
        return a.first < b.first;
    }
};

int Graph::find(int root){
    if(parent[root] != root){
       parent[root] = find(parent[root]);
    }
    return parent[root];
}


void Graph::unite(int a, int b){
    int rank_old_tree;

    a = find(a);
    b = find(b);

    if(rank[a] > rank[b]){
        rank_old_tree = rank[b];
        parent[b] = a;
        rank[a] += rank_old_tree;
    }
    else
    {
        rank_old_tree = rank[a];
        parent[a] = b;
        rank[b] += rank_old_tree;
    }
}


void Graph::solve_apm(){
    int n, m, a, b, c;
    fin>>n>>m;

    n_nodes = n;

    for(int i = 0; i < m; ++i){
        fin>>a>>b>>c;
        adj_w.push_back({c,{a,b}});
    }

    parent.resize(n+1);
    rank.resize(n+1);

    for(int i = 1; i <= n; ++i){
        parent[i] = i;
        rank[i] = 1;
    }

    sort(adj_w.begin(), adj_w.end());

//    for(int i = 0; i < m; ++i){
//        fout<<adj_w[i].first<<' '<<adj_w[i].second.first<<' '<<adj_w[i].second.second<<'\n';
//    }

    int cost = 0;
    vector<pair<int,int>> ans;

    for(int i = 0; i < m; ++i){
        if(find(adj_w[i].second.first) != find(adj_w[i].second.second)){
            unite(adj_w[i].second.first, adj_w[i].second.second);
            cost += adj_w[i].first;
            ans.push_back({adj_w[i].second.first, adj_w[i].second.second});
        }
    }


    fout<<cost<<'\n';
    fout<<ans.size()<<'\n';

    for(auto x: ans){
        fout<<x.first<<' '<<x.second<<'\n';
    }


}

int main() {
    Graph g;
    g.solve_apm();
    return 0;
}
