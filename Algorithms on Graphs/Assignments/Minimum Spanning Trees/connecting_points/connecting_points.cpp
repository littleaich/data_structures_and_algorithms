#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <set>

using std::vector;
using std::string;
using std::multimap;


double dist_euclid(double x1, double x2, double y1, double y2)
{
	return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

void calcEdgeWeights(vector<int> &x, vector<int> &y,
		multimap<double, string> &edge_list_ordered)
{
	int n = x.size()-1;
	for(int i=1; i<=n; ++i) {
		for(int j=i+1; j<=n; ++j) {
			double key_ = dist_euclid(x[i], x[j], y[i], y[j]);
			string val_ = std::to_string(i) + " " + std::to_string(j);
			edge_list_ordered.insert(std::pair<double, string>(key_, val_));
		}
	}
}

void getEdgeVertices_str2int(string &str, string &delim, int &v1, int &v2)
{
	size_t pos = str.find(delim); // delimiter starting position
	v1 = stoi(str.substr(0, pos));
	v2 = stoi(str.substr(++pos)); // delimiter is only 1 character
}

void makeSet(int n, vector<int> &parent_, vector<int> &rank_)
{
	for(int v=0; v<=n; ++v) {
		parent_[v] = v;
		rank_[v] = 0;
	}
}

int findParent(int v, vector<int> &parent_)
{
	if(v != parent_[v]) {
		parent_[v] = findParent(parent_[v], parent_);
	}

	return parent_[v];
}

void unionVertices(int par1, int par2, vector<int> &parent_, vector<int> &rank_)
{
	if(par1 == par2) return;
	if(rank_[par1] > rank_[par2]) {
		parent_[par2] = par1;
	}
	else {
		parent_[par1] = par2;
		if(rank_[par1] == rank_[par2]) {
			++rank_[par2];
		}
	}
}

void getMST_Kruskal(vector<int> &x, vector<int> &y,
		vector<string> &edge_set_mst, vector<double> &weights_mst)
{
	int n = x.size()-1;
	int numAddEdges = 0;
	multimap<double, string> edge_list_ordered;
	vector<string> edge_list_mst;
	// used in string based vertex indexing
	string delim = " ";
	int ver1, ver2, par1, par2;
	// procedure makeset()
	vector<int> parent_(n+1);
	vector<int> rank_(n+1);
	makeSet(n, parent_, rank_);

	// calculate and sort edge weights by non-decreasing order using multimap
	calcEdgeWeights(x, y, edge_list_ordered);
	// process edges in the order of non-decreasing edge weights
	multimap<double, string>::iterator it_mmap = edge_list_ordered.begin();
	while(it_mmap!=edge_list_ordered.end()) {
		double key_ = it_mmap->first; // minimum weight
		string val_ = it_mmap->second; // edge of minimum weight
		// DEBUG -- edge extraction hierarchy from multimap
		//std::cout << "Edge = " << val_ << " ... ";
		//std::cout << "Distance = " << key_ << std::endl;
		getEdgeVertices_str2int(val_, delim, ver1, ver2);
		par1 = findParent(ver1, parent_); // get parent 1
		par2 = findParent(ver2, parent_); // get parent 2
		if(par1 != par2) {
			edge_set_mst.push_back(val_); // adding edge to the mst list
			weights_mst.push_back(key_); // adding weights to the mst list
			unionVertices(par1, par2, parent_, rank_);
			++numAddEdges;
		}
		if(numAddEdges == n-1) break;
		++it_mmap;
	}
}

void calcMinDistance(vector<double> dist_, double &result)
{
	int n = dist_.size();
	result = 0;
	for(int i=0; i<n; ++i) {
		result += dist_[i];
	}
}

double minimum_distance_Kruskal(vector<int> &x, vector<int> &y)
{
	double result = 0.;
	//write your code here


	vector<string> edge_set_mst; // store edges for MST
	vector<double> weights_mst; // store weights for MST
	getMST_Kruskal(x, y, edge_set_mst, weights_mst);
	calcMinDistance(weights_mst, result);

	return result;
} 

int main()
{
	size_t n;
	std::cin >> n;
	vector<int> x(n+1), y(n+1);
	for (size_t i = 1; i <= n; ++i) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10)
		<< minimum_distance_Kruskal(x, y) << std::endl;

	return EXIT_SUCCESS;
}
