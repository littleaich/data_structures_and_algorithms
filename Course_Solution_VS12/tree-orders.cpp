#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using std::endl;
using std::stack;

class TreeOrders {
  int n;
  int root_node;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
	TreeOrders(): root_node(0) {}
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

void processNode(const int& index_node, vector<int>& result)
{
	result.push_back(key[index_node]);
}

void in_order_traversal(int index_node, vector<int>& result)
{
	if(index_node == -1) { return; }
	in_order_traversal(left[index_node], result);
	processNode(index_node, result);
	in_order_traversal(right[index_node], result);
}


vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	int root_node = 0;
	in_order_traversal(root_node, result);
    return result;
}	

/*
void processNode(int node) 
{
	cout << key[node] << endl;
}

void in_order_iterative()
{
	stack<int> inorder;
	int visit = 1;
	bool passingRoot = false;
	int node = root_node;
	int prev_node = root_node;
	inorder.push(node);
	while(visit <= n) {
		while(left[node]!=-1) {
			++visit;
			prev_node = node;
			node = left[node];
			left[prev_node] = -1; // already visited
			inorder.push(node);
		}
		if(inorder.top() == root_node) // passing root
		{ passingRoot = true; }
		processNode(inorder.top());
		inorder.pop();

		if(inorder.empty() && !passingRoot) {
			if(visit >= n) { break; } // tree visit completed
			else {
				//node.left is NULL
				// node = node
			}
		}
		else if(inorder.empty() && passingRoot) { // root.left completed
			node = root_node; // only assign the position of root
			passingRoot = false;
		}
		else
		{ node = inorder.top(); }
		

		if(right[node]!=-1) {
			++visit;
			prev_node = node;
			node = right[node];
			right[prev_node] = -1; // already visited
			if(!inorder.empty()) {
				processNode(inorder.top());
				inorder.pop();
			}
			inorder.push(node);
		}
		else {
			processNode(node);
			inorder.pop();
			if(inorder.empty()) break;
			node = inorder.top(); 
		}
	}
}
*/

void pre_order_traversal(int index_node, vector<int>& result)
{
	if(index_node == -1) { return; }
	processNode(index_node, result);
	pre_order_traversal(left[index_node], result);
	pre_order_traversal(right[index_node], result);
}

vector <int> pre_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	int root_node = 0;
	pre_order_traversal(root_node, result);
    return result;
}	

void post_order_traversal(int index_node, vector<int>& result)
{
	if(index_node == -1) { return; }
	post_order_traversal(left[index_node], result);
	post_order_traversal(right[index_node], result);
	processNode(index_node, result);
}

vector<int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
	int root_node = 0;
	post_order_traversal(root_node, result);
    return result;
}

};

void print_traversal(const vector<int>& ans) {
  for (size_t i = 0; i < ans.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << ans[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print_traversal(t.in_order());
  print_traversal(t.pre_order());
  print_traversal(t.post_order());
  
  return 0;
}
