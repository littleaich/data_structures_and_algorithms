#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
  int got = 0;
  int tmp_inf = 2*n, tmp_num = 0, tmp_val = 0;
  std::vector<int> sequence;
  std::vector<int> num(n+1, tmp_inf);
  num[0] = 0;
  num[1] = 0;
  for(int i=2; i<num.size(); ++i) {
	num[i] = tmp_inf;
	if(i % 3 == 0) {
	    tmp_val = num[i/3] + 1;
	    if(tmp_val < num[i]) {
		num[i] = tmp_val;
		tmp_num = 3;
	    }
	}
	if(i % 2 == 0) {
	    tmp_val = num[i/2] + 1;
	    if(tmp_val < num[i]) {
		num[i] = tmp_val;
		tmp_num = 2;
	    }
	}
    
	tmp_val = num[i-1] + 1;
	if(tmp_val < num[i]) {
	    num[i] = tmp_val;
	    tmp_num = 1;
	}	

//	std::cout<< i << " ";
  }	

  tmp_num = num[n];
  tmp_val = 0;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
	if(num[n/3]+1 == tmp_num - tmp_val)
	    n = n/3;
	    got = 1;
    } 
    else if (got == 0 && n % 2 == 0 && (num[n/2]+1 == tmp_num - tmp_val)) {
		n = n/2;
		got = 1;

    } 
    else {
      n = n - 1;
    }

    ++tmp_val;
    got = 0;
  }

  reverse(sequence.begin(), sequence.end());
  return sequence;
}


int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
