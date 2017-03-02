#include <iostream>

int get_change(int n) {
    int count = 0, tmp;
    while(n!=0) {
	if(n>=10) {
	    tmp = n/10;
	    n = n-tmp*10; 	
	}
	else if(n>=5) {
	    tmp = n/5;
	    n = n-tmp*5; 	
	}
	else {
	    tmp = n/1;
	    n = n-tmp*1; 	
	}
	
	count += tmp;
    }

  return count;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << get_change(n) << '\n';
}
