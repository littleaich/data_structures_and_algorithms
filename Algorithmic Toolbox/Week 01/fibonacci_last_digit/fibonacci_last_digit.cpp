#include <iostream>
#include <vector>

int get_fibonacci_last_digit(int n) {
    //write your code here
    if (n <= 1)
        return n;
    else {
	std::vector<int> fib;
	fib.push_back(0);
	fib.push_back(1);
	for(int i=2; i<=n; ++i) {
	    fib.push_back((fib[i-1]+fib[i-2]) % 10);
	}
	return fib[n];
    } 
}

int main() {
  int n;
  std::cin >> n;
  int c = get_fibonacci_last_digit(n);
  std::cout << c << '\n';
}
