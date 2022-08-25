#include <iostream>
#include <fstream>
#include <vector>
#define inf 1<<30
using namespace std;

ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

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

    void solve_royfloyd();
};

void Graph::solve_royfloyd(){
    int n;
    fin>>n;
    int d[n+1][n+1];

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            fin>>d[i][j];
            if(d[i][j] == 0) d[i][j] = inf;
        }
    }

    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            if(d[i][k] == inf || k == i) continue;
            for(int j = 1; j <= n; ++j){
                if(d[k][j] == inf || i == j) continue;
                if(d[i][j] > d[i][k] + d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(d[i][j] == inf) d[i][j] = 0;
            fout<<d[i][j]<<' ';
        }
        fout<<'\n';
    }
}
int main() {
    Graph g;
    g.solve_royfloyd();
    return 0;
}
