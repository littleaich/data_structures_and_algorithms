#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore_dfs(int v, vector<vector<int> > &adj,
	vector<int>& compNum, vector<bool>& visited, int conComp) 
{
	visited[v] = true;
	compNum[v] = conComp;
	int numEdge = adj[v].size();
	for(int i=0; i<numEdge; ++i) {
		int w = adj[v][i];
		if(!visited[w]) {
			explore_dfs(w, adj, compNum, visited, conComp);
		}
	}
}

int number_of_components_dfs(vector<vector<int> > &adj, 
							 int x, int y) {
	int n = adj.size();
	vector<int> compNum(n);
	vector<bool> visited(n, false);
	int conComp = 1;
	for(int v=0; v<n; ++v) {
		if(!visited[v]) {
			explore_dfs(v, adj, compNum, visited, conComp);
			++conComp;
		}
	}

	if(compNum[x-1] == compNum[y-1]) { return 1; }
	else { return 0; }

}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  int x, y;

  for (size_t i = 0; i < m; i++) {
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }

  std::cin >> x >> y;
  std::cout << number_of_components_dfs(adj, x, y);
}
