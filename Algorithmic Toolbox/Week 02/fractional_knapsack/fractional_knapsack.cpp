#include <iostream>
#include <vector>
#include <functional>   // std::divides
#include <algorithm>    // std::transform

#define MAX_VAL 2000000

using std::vector;

bool wayToSort(double i, double j) { return i > j; }

int maxVector(vector<double> v, vector<double> w) {
    double val = 0;
    int index = 0;
    for(int i=0; i<v.size(); ++i)
	if(val<v[i] && w[i]>0)
	{
	    val = v[i];
	    index = i;	
	}

    return index;
}

/*
double get_optimal_value(int capacity, vector<double> weights, vector<double> values) {
    double value = 0.0;
    double a = 0;	
    // write your code here
    int n = weights.size();
//    std::transform (values, values+n, weights, values, std::divides<double>());
    for(int i=0; i<n; ++i)
	values[i] /= weights[i];
    
    double c = MAX_VAL*maxVector(values)/maxVector(weights);

    for(int i=0; i<n; ++i)
	weights[i] *= values[i]*MAX_VAL;

    std::sort(values.begin(), values.end(), wayToSort);	
    std::sort(weights.begin(), weights.end(), wayToSort);

    for(int i=0; i<n; ++i)
	weights[i] /= (MAX_VAL*values[i]);
	
    for(int i=0; i<n; ++i) {
	if(capacity==0) 
	    return value;
	a = (weights[i] >= capacity)? capacity : weights[i];
	value += a * values[i];
	capacity -= a;
    }

  return value;
}
*/

double get_optimal_value(int capacity, vector<double> weights, vector<double> values) {
    double value = 0.0;
    double a = 0;	
    // write your code here
    int n = weights.size();
//    std::transform (values, values+n, weights, values, std::divides<double>());
    for(int i=0; i<n; ++i) //{
	values[i] /= weights[i];
//	std::cout << values[i] << std::endl; }
    int ind = 0;
    for(int i=0; i<n; ++i) {
	if(capacity==0) 
	    return value;
	ind = maxVector(values, weights);
//	std::cout << ind << std::endl;	
	a = (weights[ind] >= capacity)? capacity : weights[ind];
//	std::cout << a << std::endl;
	value += a * values[ind];
	weights[ind] -= a;
	capacity -= a;
//	std::cout << capacity << std::endl;
    }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<double> values(n);
  vector<double> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
