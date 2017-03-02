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

/*
int getMax(vector<vector<int> > &vec, int ind) // computation time O(|V|+|E|)
{
	// ind is the 0 or 1 based index number
	// ind = 0 for 0-based indexing
	// ind = 1 for 1-based indexing
	int n = vec.size()-ind;
	int max_val = std::numeric_limits<int>::min();
	for(int i=ind; i<n+ind; ++i) {
		int m = vec[i].size();
		for(int j=0; j<m; ++j) {
			if(max_val < vec[i][j])
				max_val = vec[i][j];
		}
	}

	return max_val;
}
*/

void erase_priority_queue(multimap<int, int> &queue_map, const int key_, const int val_)
{
	// get the range of values with the same key
	pair<multimap<int,int>::iterator, multimap<int,int>::iterator> range_it;
	range_it = queue_map.equal_range(key_);
	for(multimap<int,int>::iterator it=range_it.first; it!=range_it.second; ++it) {
		if(it->second == val_) {
			queue_map.erase(it);
			break;
		}
	}
}

void dijkstra_shortest_path(vector<vector<int> > &adj, vector<int> &dist,
		vector<vector<int> > &cost, int s)
{
	int n = adj.size()-1;
	vector<int> prev(n+1, 0);
	// design priority queue with dist as key values
	multimap<int, int> queue_map;
	for(int v=1; v<=n; ++v) {
		queue_map.insert(std::pair<int, int>(dist[v], v));
	}

	while(!queue_map.empty()) {
		// extract node with minimum dist or key_value
		multimap<int, int>::iterator it = queue_map.begin();
		int key_ = it->first;
		int val_ = it->second;
		erase_priority_queue(queue_map, key_, val_);
		int numEdge = adj[val_].size();
		for(int i=0; i<numEdge; ++i) {
			int w = adj[val_][i];
			int tmp_cost = dist[val_]+cost[val_][i];
			if(dist[w] > tmp_cost) {
				erase_priority_queue(queue_map, dist[w], w);
				dist[w] = tmp_cost;
				prev[w] = val_;
				queue_map.insert(std::pair<int, int>(dist[w], w));
			}
		}
	}
}

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t)
{
	//write your code here
	/*
	int max_cost = getMax(cost, 1); // maximum cost used in dijkstra
	long max_val = std::numeric_limits<long>::max();
	int n = adj.size()-1;
	vector<long> dist(n+1, 0);
	long cost_init;
	// initialize distance values to the possible maximum
	// with the condition that no 2 values are the same
	// this is needed for map based priority queuing
	for(int v=1; v<=n; ++v) {
		if(v!=s) {
			dist[v] = max_val-max_cost-v; // +1
		}
	}
	*/

	int max_val = std::numeric_limits<int>::max()-MAX_COST;
	int n = adj.size()-1;
	int cost_init;
	vector<int> dist(n+1,max_val);
	dist[s] = 0;
	cost_init = dist[t];
	dijkstra_shortest_path(adj, dist, cost, s);

	if(dist[t] == cost_init)
		return -1;
	else
		return dist[t];
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n+1, vector<int>());
	vector<vector<int> > cost(n+1, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x].push_back(y);
		cost[x].push_back(w);
	}
	int s, t;
	std::cin >> s >> t;
	std::cout << distance(adj, cost, s, t);

	return EXIT_SUCCESS;
}
