#include <cstdio>
#include <string>
#include <iostream>

using std::string;

class Rope {
	std::string s;
public:
	Rope(std::string &s) : s(s) { 
	}

	void process( int i, int j, int k ) {
                // Replace this code with a faster implementation
                //std::string t = s.substr(0, i) + s.substr(j + 1);
                //s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
		if(k>=i) { k = j-i+1+k; }
		string t = s.substr(i, j-i+1);
		for(int x=i, y=k; x<j+1, y<j-i+1+k; ++x, ++y)
			s[x] = s[y];
		for(int x=k, y=1; x<j-i+1+k, y<j+1; ++x, ++y)
			s[x] = t[y];
/*
		if(k > j) {
			string t = s.substr(i, j-i+1);
			k = k-1+j-i+1;
			for(int x=i, y=k; x<j+1, y<j-i+1+k; ++x, ++y)
				s[x] = s[y];
			for(int x=k, y=1; x<j-i+1+k, y<j-i+2; ++x, ++y)
				s[x] = s[y];
			//s.substr(i, j-i+1).assign(s.substr(k, j-i+1));
//			for(int x=i, y=j+1; x<k-j+1+i, y<k-j+1+j+1; ++x, ++y)
//				s[x] = s[y];
//			for(int x=k+1, y=1; x<j-i+1+k+1, y<j-i+1+1; ++x, ++y)
//				s[x] = s[y];
			//s.substr(i, k-j+1).assign(s.substr(j+1, k-j+1));
			//s.substr(k+1, j-i+1).assign(t);
		}
		else if (k+1 < i) {
			string t = s.substr(i, j-i+1);
			for(int x=j-i+k+2, y=k+1; x<j+1, y<i; ++x, ++y)
				s[x] = s[y];
			for(int x=k+1, y=1; x<j-i+k+2, y<j-i+2; ++x, ++y)
				s[x] = s[y];
			//s.substr(j-i+k+2, i-k-1).assign(s.substr(k+1, i-k-1));
			//s.substr(k+1, j-i+1).assign(t);
		}
		else if(k+1 > i) { // k+1 exactly in between
			string t = s.substr(i, j-i+1);
			for(int x=i, y=k+1; x<j+1, y<j-i+k+2; ++x, ++y)
				s[x] = s[y];
			for(int x=k+1, y=1; x<j-i+k+2, y<j-i+2; ++x, ++y)
				s[x] = s[y];
			//s.substr(i, j-i+1).assign(s.substr(k+1, j-i+1));
			//s.substr(k+1, j-i+1).assign(t);
		}
*/
	}

	std::string result() {
		return s;
	}
};

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
        for (int action_index = 0; action_index < actions; ++action_index) {
                int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	std::cout << rope.result() << std::endl;
}
