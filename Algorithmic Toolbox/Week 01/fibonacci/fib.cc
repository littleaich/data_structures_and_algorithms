#include <iostream>
#include <vector>

int calc_fib(int n) {
    if (n <= 1)
        return n;
    else {
	std::vector<unsigned long long> fib;
	fib.push_back(0);
	fib.push_back(1);
	for(int i=2; i<=n; ++i) {
	    fib.push_back(fib[i-1]+fib[i-2]);
	}
	return fib[n];
    }

}

int main() {
    int n = 0;
    std::cin >> n;

    std::cout << calc_fib(n) << '\n';
    return 0;
}
