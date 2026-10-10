#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

#define pii pair<int, int>
#define ff first
#define ss second

int n;
vector<vector<int>> adj;
vector<vector<int>> uadj;
vector<int> indeg;
vector<int> outdeg;
vector<int> deg;

vector<int> indeg_dup;
vector<int> outdeg_dup;
vector<int> deg_dup;

vector<int> vis;

vector<int> tin;
vector<int> low;
vector<int> onst;
vector<int> st;
int timer = 0;
int scc = 0;

set<pii> edges;
set<pii> uedges;

void dfs(int u) {
    vis[u] = true;

    for(auto v : uadj[u]) {
        if(!vis[v]) dfs(v);
    }
}

void tarjan(int u) {
    tin[u] = low[u] = timer++;
    st.push_back(u);
    onst[u] = true;

    for(auto v : adj[u]) {
        if(tin[v] == -1) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(onst[v]) low[u] = min(low[u], tin[v]);
    }

    if(low[u] == tin[u]) {
        ++scc;

        while(true) {
            int v = st.back();
            st.pop_back();
            onst[v] = false;

            if(v == u) break;
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream fin("data/" + string(argv[1]) + ".txt");
    ofstream fout("output/" + string(argv[1]) + ".out");
    fin >> n;

    adj = vector<vector<int>>(n);
    uadj = vector<vector<int>>(n);

    deg = vector<int>(n, 0);
    indeg = vector<int>(n, 0);
    outdeg = vector<int>(n, 0);

    deg_dup = vector<int>(n, 0);
    indeg_dup = vector<int>(n, 0);
    outdeg_dup = vector<int>(n, 0);

    vis = vector<int>(n, false);

    tin = vector<int>(n, -1);
    low = vector<int>(n, 0);
    onst = vector<int>(n, false);

    int u, v;
    while(fin >> u >> v) {
        edges.insert({u, v});
        uedges.insert({min(u, v), max(u, v)});

        ++indeg_dup[v]; ++outdeg_dup[u];
        ++deg_dup[u]; ++deg_dup[v];
    }

    for(auto [u, v] : edges) {
        adj[u].push_back(v);

        ++indeg[v]; ++outdeg[u];
    }

    for(auto [u, v] : uedges) {
        uadj[u].push_back(v);
        uadj[v].push_back(u);

        ++deg[u]; ++deg[v];
    }

    int cc = 0;
    for(int i = 0; i < n; ++i) {
        if(!vis[i]) {
            ++cc;
            dfs(i);
        }
        if(tin[i] == -1) tarjan(i);
    }

    fout << cc << endl;
    fout << scc << endl;

    for(int i = 0; i < n; ++i) fout << deg[i] << " ";
    fout << endl;
    for(int i = 0; i < n; ++i) fout << indeg[i] << " ";
    fout << endl;
    for(int i = 0; i < n; ++i) fout << outdeg[i] << " ";
    fout << endl;

    for(int i = 0; i < n; ++i) fout << deg_dup[i] << " ";
    fout << endl;
    for(int i = 0; i < n; ++i) fout << indeg_dup[i] << " ";
    fout << endl;
    for(int i = 0; i < n; ++i) fout << outdeg_dup[i] << " ";
    fout << endl;
}
