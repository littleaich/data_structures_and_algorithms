#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

using std::vector;
using std::queue;

bool bfs_undirected_bipartite(vector<vector<int> > &adj, int s, vector<int> &label_,
		vector<int> &prev_)
{
	bool bi_part = true;
	queue<int> queue_node;
	label_[s] = 1;
	queue_node.push(s);
	while(!queue_node.empty()) {
		int u = queue_node.front();
		queue_node.pop();
		int numEdge = adj[u].size();
		for(int i=0; i<numEdge; ++i) {
			int v = adj[u][i];
			if(label_[v] == 0) {
				queue_node.push(v);
				label_[v] = (label_[u]==1)? 2:1;
				prev_[v] = u;
			}
			else if(label_[v] == label_[u]) {
				bi_part = false;
				break;
			}
		}
		if(!bi_part) { break; }
	}

	return bi_part;
}

int bipartite(vector<vector<int> > &adj)
{
	//write your code here
	int n = adj.size()-1; // 1-based indexing
	vector<int> label_(n+1, 0); // max_limit = n
	vector<int> prev_(n+1, 0); // previous node

	return bfs_undirected_bipartite(adj, 1, label_, prev_); // check from node 1
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	std::cout << bipartite(adj);

	return EXIT_SUCCESS;
}
