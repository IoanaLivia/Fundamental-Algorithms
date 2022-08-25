#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#define inf 1<<30
using namespace std;

ifstream fin("biconex.in");
ofstream fout("biconex.out");

class Graph{
private:
    int n_nodes;
    vector<vector<int>> adj;
    vector<pair<int,pair<int,int>>> adj_w;
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

    void solve_comp_biconexe();
    void dfs_biconexe(int node, int parent, vector<vector<int>>& ans, stack<int>& s);
};

void Graph::dfs_biconexe(int node, int parent, vector<vector<int>> &ans, stack<int> &s) {
    lvl[node] = lvl_min[node] = lvl[parent] + 1;
    s.push(node);
    for(auto x: adj[node]){
        if(lvl[x] != 0){
            if(x != parent)  //l am vizitat pana acum si nu e parintele
                lvl_min[node] = min(lvl[x], lvl_min[node]);
        }
        else
        {
            //nu l am mai vizitat, deci
            dfs_biconexe(x, node, ans, s);
            if(lvl_min[x] < lvl_min[node]){
                lvl_min[node] = lvl_min[x];
            }
            if(lvl_min[x] >= lvl[node]){
                //nod critic cout<<node<<' ';
                vector<int> comp;
                while(s.top() != x){
                    comp.push_back(s.top());
                    s.pop();
                }
                comp.push_back(x);
                s.pop();
                comp.push_back(node);
                ans.push_back(comp);
            }
        }
    }
}

void Graph::solve_comp_biconexe(){
    int n, m, x, y;
    fin>>n>>m;

    adj.resize(n+1);
    lvl.resize(n+1,0);
    lvl_min.resize(n+1,0);

    stack<int> s;

    for(int i = 1; i <= m; ++i){
        fin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<vector<int>> answer;
    for(int i = 1; i <= n; ++i){
        if(!lvl[i]){
            dfs_biconexe(i, 0, answer, s);
            while(!s.empty()) s.pop();
        }
    }

    fout<<answer.size()<<'\n';
    for(auto x: answer){
        for(int j = x.size() - 1; j >= 0; j--){
            fout<<x[j]<<' ';
        }
        fout<<'\n';
    }

//    cout<<"\nLevels:\n";
//    for(auto x: lvl) cout<<x<<' ';
//    cout<<"\nLevels_MIN:\n";
//    for(auto x: lvl_min) cout<<x<<' ';
    
}


int main() {
    Graph g;
    g.solve_comp_biconexe();
    return 0;
}
