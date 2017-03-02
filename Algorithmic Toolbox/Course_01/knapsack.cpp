#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &weights) {
  //write your code here
	int n = weights.size();
	vector<vector<int>> V(n+1, vector<int>(W+1));
	vector<int> values = weights;
	int val = 0;

	for(int i=1; i<=n; ++i) {
		for(int w=1; w<=W; ++w) {
//			std::cout << V[i][w] << " ";
			V[i][w] = V[i-1][w];
			if(weights[i-1] <= w) {
				val = V[i-1][w-weights[i-1]] + values[i-1];
				if(V[i][w] < val) {
					V[i][w] = val;
				}
			}
		}
//		std::cout << std::endl;
	}
  
/*	
	int current_weight = 0;
	for (size_t i = 0; i < w.size(); ++i) {
		if (current_weight + w[i] <= W) {
			current_weight += w[i];
		}
	}
	
	return current_weight;
*/
	return V[n][W];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
