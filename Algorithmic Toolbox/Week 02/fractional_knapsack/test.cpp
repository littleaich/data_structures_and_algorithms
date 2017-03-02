#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<double> values(10);
  for (int i = 0; i < 10; i++) {
    std::cin >> values[i];
  }
  
cout << *std::max_element(values,values+10) << endl;



    return 0;
}
