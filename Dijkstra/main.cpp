#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#define inf 1<<30
#include <queue>
using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

class Graph{
private:
    int n_nodes;
    vector<vector<int>> adj;
    vector<vector<pair<int,int>>> adj_w;
    vector<int> parent;
    vector<int> rank;
    vector<bool> visited;
    vector<int> lvl;
    vector<int> lvl_min;
    vector<vector<int>> reverted_graph;
    vector<int> ans;
public:
    Graph(){
        n_nodes = 0;
        adj_w = {};
    }

    void solve_dijkstra();

};


void Graph::solve_dijkstra(){
    int n, m, x, y, w;
    fin>>n>>m;

    adj_w.resize(n+1);
    visited.resize(n+1, false);

    vector<int> d(n+1, inf);

    for(int i = 0; i < m; ++i){
        fin>>x>>y>>w;
        adj_w[x].push_back({y,w});
    }

    d[1] = 0;

//    for(auto y : adj_w){
//        for(auto x: y)
//            cout<<x.first<<' '<<x.second<<'\n';
//    }
    priority_queue<pair<int,int> , vector<pair<int , int>> , greater<>> q;

    q.push({0,1}); //cost, nod

    while(!q.empty()){
        pair<int,int> current = q.top();
        //cout<<current.first<<' '<<current.second<<'\n';
        q.pop();

        cout<<current.first<<' '<<d[current.second]<<'\n';
        if(visited[current.second]|| current.first != d[current.second]) continue; //|| current.first != d[current.second] -- e outdated perechea

        visited[current.second] = true;
        for(auto x: adj_w[current.second]){
            if(d[x.first] > current.first + x.second){
                d[x.first] = current.first + x.second;
                q.push({d[x.first], x.first});
            }
        }

    }

    for(int i = 2; i <= n; ++i){
        if(d[i] == inf) d[i] = 0;
        fout<<d[i]<<' ';
    }


}
int main() {
    Graph g;
    g.solve_dijkstra();
    return 0;
}
