#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using std::vector;
using std::queue;

int numEdges_shortestPath(int s, int t, vector<int> &prev_)
{
	int numEdge = 0;
	int n = prev_.size()-1;
	for(int i=0; i<n; ++i) {
		if(t!=s) {
			++numEdge;
			t = prev_[t];
		}
		else { return numEdge; }
	}

	return -1;
}

void bfs_undirected(vector<vector<int> > &adj, int s, vector<int> &dist_,
		vector<int> &prev_)
{
	queue<int> queue_node;
	int n = adj.size()-1;
	dist_[s] = 0;
	queue_node.push(s);
	while(!queue_node.empty()) {
		int u = queue_node.front();
		queue_node.pop();
		int numEdge = adj[u].size();
		for(int i=0; i<numEdge; ++i) {
			int v = adj[u][i];
			if(dist_[v] == n) {
				queue_node.push(v);
				dist_[v] = dist_[u]+1;
				prev_[v] = u;
			}
		}
	}
}

int node_distance(vector<vector<int> > &adj, int s, int t)
{
	//write your code here
	int numEdge_sp = -1;
	int n = adj.size()-1; // 1-based indexing
	vector<int> dist_(n+1, n); // max_limit = n
	vector<int> prev_(n+1, 0); // previous node
	bfs_undirected(adj, s, dist_, prev_);
	numEdge_sp = numEdges_shortestPath(s,t,prev_);

	return numEdge_sp;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int s, t;
	std::cin >> s >> t;
	std::cout << node_distance(adj, s, t);

	return EXIT_SUCCESS;
}
