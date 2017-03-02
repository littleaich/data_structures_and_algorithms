#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void postVisit(int v, vector<int> &vertices_postNum)
{
	vertices_postNum.push_back(v);
}

void reverse_explore_dfs(int v, vector<vector<int> > &adj,
	vector<bool>& visited, vector<int> &vertices_postNum)
{
	visited[v] = true;
	int numEdge = adj[v].size();
	for(int i=0; i<numEdge; ++i) {
		int w = adj[v][i];
		if(!visited[w]) {
			reverse_explore_dfs(w, adj, visited, vertices_postNum);
		}
	}

	postVisit(v, vertices_postNum);
}

void explore_dfs(int v, vector<vector<int> > &adj,
	vector<bool>& visited)
{
	visited[v] = true;
	int numEdge = adj[v].size();
	for(int i=0; i<numEdge; ++i) {
		int w = adj[v][i];
		if(!visited[w]) {
			explore_dfs(w, adj, visited);
		}
	}

}

void reverse_graph_dfs(vector<vector<int> > &adj, vector<int> &vertices_postNum)
{
	int n = adj.size()-1;
	vector<bool> visited(n+1, false);
	for(int v=1; v<=n; ++v) {
		if(!visited[v]) {
			reverse_explore_dfs(v, adj, visited, vertices_postNum);
		}
	}

}

int graph_dfs(vector<vector<int> > &adj, vector<int> &vertices_postNum)
{
	int n = adj.size()-1;
	vector<bool> visited(n+1, false);
	int num_scc = 1;
	for(int p=n-1; p>=0; --p) { // p = postorder number
		if(!visited[vertices_postNum[p]]) {
			explore_dfs(vertices_postNum[p], adj, visited);
			++num_scc;
		}
	}
	return --num_scc;
}

void reverse_graph(vector<vector<int> > &adj, vector<vector<int> > &adj_reverse)
{
	int n = adj.size()-1;
	for(int v=1; v<=n; ++v) {
		int numEdge = adj[v].size(); // degree of node v
		for(int e=0; e<numEdge; ++e) {
			adj_reverse[adj[v][e]].push_back(v);
		}
	}
}

int acyclic(vector<vector<int> > &adj)
{
	int n = adj.size()-1; // size (n+1) , 1-based indexing
	int num_scc;
	// generate reverse graph
	vector<vector<int> > adj_reverse(n+1, vector<int>());
	vector<int> vertices_postNum; // don't fix size to facilitate counting
	reverse_graph(adj,adj_reverse);
	// get post ordering by running dfs on reverse graph
	reverse_graph_dfs(adj_reverse, vertices_postNum);
	// run modified dfs on graph to find number of SCC
	num_scc = graph_dfs(adj, vertices_postNum);

	if(num_scc == n) { return 0; }
	else { return 1; }
}



int main()
{
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x].push_back(y);
	}
	std::cout << acyclic(adj);
}
