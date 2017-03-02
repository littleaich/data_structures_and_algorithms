#include <iostream>

int gcd(int a, int b) {
  //write your code here
    if(b==0) {
    	return a;
    }
    else {
	a = a % b;
	return gcd(b,a);
    }
}

long long lcm(long long a, long long b) {
  //write your code here
  int g = gcd(a,b);
  return a*b/g;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}
