#include <iostream>
#include <vector>
//#include <queue>
#include <cstdlib>
#include <limits>
#include <map>
//#include <tr1/unordered_map>

#define MAX_COST 1000

using std::vector;
using std::multimap;
//using std::queue;
using std::pair;
//using std::map;
//using std::tr1::unordered_map;
//using std::priority_queue;

bool bellman_ford_shortest_path(vector<vector<int> > &adj,
		vector<vector<int> > &cost, int s)
{
	bool find_cycle = true;
	int max_val = std::numeric_limits<int>::max()-MAX_COST;
	int n = adj.size()-1;
	vector<int> dist(n+1,max_val);
	vector<int> prev(n+1, 0);

	dist[s] = 0;
	for(int i=0; i<n; ++i) {
		// update weights for all edges
		bool change_val = false;
		for(int v=1; v<=n; ++v) {
			int numEdge = adj[v].size();
			for(int e=0; e<numEdge; ++e) {
				int w = adj[v][e];
				// update weight
				int tmpCost = dist[v]+cost[v][e];
				if(dist[w] > tmpCost) {
					dist[w] = tmpCost;
					change_val = true;
				}
			}
		}

		if(!change_val) {
			find_cycle = false;
			break;
		}
	}

	return find_cycle;

}

bool negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost)
{
	//write your code here
	int s = 1;
	bool find_cycle = bellman_ford_shortest_path(adj, cost, s);

	return find_cycle;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	vector<vector<int> > cost(n+1, vector<int>());
	for (int i=0; i<m; ++i) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x].push_back(y);
		cost[x].push_back(w);
	}

	std::cout << negative_cycle(adj, cost);
}
