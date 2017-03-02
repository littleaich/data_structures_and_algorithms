#include <iostream>
#include <vector>

long long get_fibonaccihuge(long long n, long long m) {
  //write your code here
    std::vector<int> fib_rem;
    if (n <= 1)
        return n;
    else {
	int lenPeriod = 0, lenFib = 0;
	fib_rem.push_back(0);
	fib_rem.push_back(1);
	for(int i=2; i<=n; ++i) {
//	    std::cout << i << std::endl;
	    fib_rem.push_back((fib_rem[i-1]+fib_rem[i-2]) % m);
	    if(fib_rem[i]==1 && fib_rem[i-1]==0) { // period started
		lenPeriod = fib_rem.size() - 2;
		lenFib = n % lenPeriod;
//		std::cout << lenPeriod << " " << lenFib << " " << i << std::endl;
		return fib_rem[lenFib];	
	    }
	}
    } 
    return fib_rem.back();
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonaccihuge(n, m) << '\n';
}
