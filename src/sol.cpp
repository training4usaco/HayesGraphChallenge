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
vector<vector<int>> radj;
vector<int> indeg;
vector<int> outdeg;
vector<int> deg;

vector<int> indeg_dup;
vector<int> outdeg_dup;
vector<int> deg_dup;

vector<int> vis;
vector<int> ord;

vector<int> par;
vector<int> sz;

set<pii> edges;
set<pii> uedges;

int find(int u) {
    if(u == par[u]) return u;
    return par[u] = find(par[u]);
}

bool merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return false;

    if(sz[u] > sz[v]) swap(u , v);

    par[u] = v;
    sz[v] += sz[u];

    return true;
}

void dfs(int u) {
    vis[u] = true;

    for(auto v : adj[u]) {
        if(!vis[v]) dfs(v);
    }

    ord.push_back(u);
}

void dfs2(int u) {
    vis[u] = false;
    for(auto v : radj[u]) {
        if(vis[v]) dfs2(v);
    }
}

int main(int argc, char* argv[]) {
    ifstream fin("data/" + string(argv[1]) + ".txt");
    ofstream fout("output/" + string(argv[1]) + ".out");
    fin >> n;

    adj = vector<vector<int>>(n);
    radj = vector<vector<int>>(n);

    deg = vector<int>(n, 0);
    indeg = vector<int>(n, 0);
    outdeg = vector<int>(n, 0);

    deg_dup = vector<int>(n, 0);
    indeg_dup = vector<int>(n, 0);
    outdeg_dup = vector<int>(n, 0);

    vis = vector<int>(n, false);

    par = vector<int>(n);
    sz = vector<int>(n);

    for(int i = 0; i < n; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    int u, v;
    while(fin >> u >> v) {
        edges.insert({u, v});
        uedges.insert({min(u, v), max(u, v)});

        ++indeg_dup[v]; ++outdeg_dup[u];
        ++deg_dup[u]; ++deg_dup[v];
    }

    for(auto [u, v] : edges) {
        merge(u, v);

        adj[u].push_back(v);
        radj[v].push_back(u);

        ++indeg[v]; ++outdeg[u];
    }

    for(auto [u, v] : uedges) {
        ++deg[u]; ++deg[v];
    }

    int cc = 0;
    for(int i = 0; i < n; ++i) {
        if(par[i] == i) ++cc;
        if(!vis[i]) dfs(i);
    }

    reverse(ord.begin(), ord.end());

    int scc = 0;
    for(auto u : ord) {
        if(vis[u]) {
            ++scc;
            dfs2(u);
        }
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