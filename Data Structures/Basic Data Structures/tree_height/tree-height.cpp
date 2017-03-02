#include <iostream>
#include <vector>
#include <algorithm>

class TreeHeight {
	int n;				// number of nodes
	std::vector<int> parent; // parent vector
	std::vector<int> height; // height vector
	static const int HEIGHT_UNDEFINED = -2; // undefined height sentinel value
  
	void getVertexHeight(int vertex) {
		// parent height undefined
		if(height.at(vertex) == HEIGHT_UNDEFINED) {
			if(parent.at(vertex) == -1) {
				setVertexHeight(vertex, 1);
				return;
			}
			if(height.at(parent.at(vertex)) == HEIGHT_UNDEFINED)
				getVertexHeight(parent.at(vertex));
			setVertexHeight(vertex, 1+height.at(parent.at(vertex)));
		}
	}

	void setVertexHeight(int vertex, int ht) {
		height.at(vertex) = ht;
	}

public:
	void read() {
		std::cin >> n;
		parent.resize(n);
		height.assign(n, HEIGHT_UNDEFINED);

		for (int i = 0; i < n; i++)
		  std::cin >> parent[i];
	}

	int compute_height() {
		// Replace this code with a faster implementation
		for(int vertex = 0; vertex <n; ++vertex) {
			getVertexHeight(vertex);
		}
		
		return *std::max_element(height.begin(), height.end());

/*
		int maxHeight = 0;
		for (int vertex = 0; vertex < n; vertex++) {
		  int height = 0;
		  for (int i = vertex; i != -1; i = parent[i])
			height++;
		  maxHeight = std::max(maxHeight, height);
		}
		return maxHeight;
*/
	}
};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
