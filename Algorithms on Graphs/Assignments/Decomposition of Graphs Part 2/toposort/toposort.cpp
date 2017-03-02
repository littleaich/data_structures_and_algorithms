#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void postVisit(int v, vector<int> &vertices_postNum)
{
	vertices_postNum.push_back(v);
}

void explore_dfs(int v, vector<vector<int> > &adj,
	vector<bool>& visited, vector<int> &vertices_postNum)
{
	visited[v] = true;
	int numEdge = adj[v].size();
	for(int i=0; i<numEdge; ++i) {
		int w = adj[v][i];
		if(!visited[w]) {
			explore_dfs(w, adj, visited, vertices_postNum);
		}
	}

	postVisit(v, vertices_postNum);
}

void toposort_by_dfs(vector<vector<int> > &adj, vector<int> &vertices_postNum)
{
  //write your code here
	int n = adj.size()-1;
	vector<bool> visited(n+1, false);
	for(int v=1; v<=n; ++v) {
		if(!visited[v]) {
			explore_dfs(v, adj, visited, vertices_postNum);
		}
	}
}     

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n+1, vector<int>());
  vector<int> vertices_postNum;
  for (size_t i = 0; i < m; i++) {
	  int x, y;
	  std::cin >> x >> y;
	  adj[x].push_back(y);
  }
  toposort_by_dfs(adj, vertices_postNum);
  for (int i = vertices_postNum.size()-1; i >=0; --i) {
    std::cout << vertices_postNum[i] << " ";
  }
}
