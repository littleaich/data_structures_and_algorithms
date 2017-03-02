/*
 * Solution Hints:
 *  The correct criterion for testing that there exist arbitrarily short
 *  paths from node S to node u (or, equivalently, that the shortest path
 *  from S to u is −∞; or that infinite arbitrage is possible for
 *  exchanging US dollars into Russian rubles) is the following:
 *
 * (1) Run Bellman-Ford's algorithm to find shortest paths from
 * node S for exactly |V| iterations, where |V| is the number of nodes
 * in the graph.
 *
 * (2) Save all the nodes for which the distance estimate was decreased
 * on the V-th iteration - denote the set of these nodes by A.
 *
 * (3) Find all nodes reachable from any node in A, use breadth-first
 * search to do that (put all the nodes from A in the queue initially,
 * then run the regular breadth-first search with that queue). Denote
 * the set of these nodes by B.
 *
 * (4) There exist arbitrarily short paths from S to u if and only
 * if u is in the set B.
 */

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <cstdlib>

using std::vector;
using std::queue;
using std::pair;


void bellman_ford_shortest_path(vector<vector<int> > &adj,
		vector<vector<int> > &cost, int s,
		vector<long long> &dist, vector<int> &nodes_changing, long long max_val)
{
	int n = adj.size()-1;
	dist[s] = 0;
	for(int i=0; i<n; ++i) {
		// update weights for all edges
		bool change_val = false;
		for(int v=1; v<=n; ++v) {
			int numEdge = adj[v].size();
			for(int e=0; e<numEdge; ++e) {
				int w = adj[v][e];
				// update weight
				long long tmpCost = dist[v]+cost[v][e];
				// short-circuit condition to avoid overflow and
				// faulty large number comparison
				if(dist[v] != max_val && dist[w] > tmpCost) {
					dist[w] = tmpCost;
					change_val = true;
					if(i==n-1) { // |V|-th iteration
						nodes_changing.push_back(w);
					}
				}
			}
		}

		if(!change_val) {
			break;
		}
	}

}

void bfs(vector<vector<int> > &adj,
		vector<int> &nodes_changing, vector<bool> &shortest)
{
	queue<int> queue_node;
	int n = adj.size()-1;
	int sent_val = -1;
	vector<int> dist_(n+1, sent_val); // max_limit = n
	vector<int> prev_(n+1, 0); // previous node
	for(size_t i=0; i<nodes_changing.size(); ++i) {
		dist_[nodes_changing[i]] = 0;
		shortest[nodes_changing[i]] = false;
		queue_node.push(nodes_changing[i]);
		while(!queue_node.empty()) {
			int u = queue_node.front();
			queue_node.pop();
			int numEdge = adj[u].size();
			for(int i=0; i<numEdge; ++i) {
				int v = adj[u][i];
				if(dist_[v] == sent_val) {
					queue_node.push(v);
					// incorrect dist value update for this initial
					// queue-based listing. But it serves the purpose correctly.
					dist_[v] = dist_[u]+1; /* INCORRECT */
					prev_[v] = u;
					shortest[v] = false;
				}
			}
		}
	}


}

void isReachable_dfs(vector<vector<int> > &adj, int s, vector<bool> &reachable)
{
	reachable[s] = true;
	int numEdge = adj[s].size();
	for(int e=0; e<numEdge; ++e) {
		if(!reachable[adj[s][e]]) {
			isReachable_dfs(adj, adj[s][e], reachable);
		}
	}
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost,
		int s, vector<long long> &distance, vector<bool> &shortest,
		vector<bool> &reachable, long long max_val)
{
	//write your code here
	vector<int> nodes_changing;
	bellman_ford_shortest_path(adj, cost, s, distance, nodes_changing, max_val);
	if(!nodes_changing.empty()) {
		bfs(adj, nodes_changing, shortest);
	}
	isReachable_dfs(adj, s, reachable);
}

int main()
{
	int n, m, s;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	vector<vector<int> > cost(n+1, vector<int>());
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x].push_back(y);
		cost[x].push_back(w);
	}
	std::cin >> s;

	long long max_val = std::numeric_limits<long long>::max();
	vector<long long> distance(n+1, max_val);
	vector<bool> reachable(n+1, false);
	vector<bool> shortest(n+1, true);

	shortest_paths(adj, cost, s, distance, shortest, reachable, max_val);

	for (int i = 1; i <= n; ++i) {
		if (!reachable[i]) {
			std::cout << "*\n";
		} else if (!shortest[i]) {
			std::cout << "-\n";
		} else {
			std::cout << distance[i] << "\n";
		}
	}

	return EXIT_SUCCESS;
}
