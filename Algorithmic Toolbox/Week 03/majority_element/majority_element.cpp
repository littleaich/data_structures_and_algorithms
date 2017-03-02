#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

bool sortfunction (int i,int j) { return (i<j); }

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  std::sort(a.begin(), a.end(), sortfunction);
  int majority = floor(right/2) + 1, count = 1, tmp = 0;
  --right;
  while(left <= right) {
	tmp = left + 1;
	if(a[left] == a[tmp]) {
	    ++count; 
	    ++tmp;
	    if(tmp <= right)	        
		while(a[left] == a[tmp]) {       
		    ++count;
		    ++tmp;
		    if(tmp > right)
			break;	 
	        }
	}

	if(count >= majority)
	    return 1;

	left = tmp;
	count = 1;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
