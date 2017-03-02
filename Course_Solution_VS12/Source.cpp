#include <iostream>
#include <limits>
#include <unordered_set>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main(void) {
	/*
	cout << numeric_limits<int>::max() << endl;
	cout << numeric_limits<float>::max() << endl;
	cout << numeric_limits<unsigned long long>::max() << endl;
	cout << numeric_limits<char>::digits << endl;
	cout << numeric_limits<int>::digits << endl;
	unordered_set<string> set;
	//set.insert("aaa");
	set.erase("aaa");
	*/
/*
	vector<vector<vector<int> > > mat3d, mat3d_copy;
	mat3d.resize(3);
	for(int i=0; i<3; ++i) {
		mat3d[i].resize(4);
	}

	for(int i=0; i<3; ++i) {
		for(int j=0; j<4; ++j) {
			vector<int> tmp(5, i+j);
			mat3d[i][j] = tmp;
		}
	}

	mat3d_copy = mat3d;
	for(int i=0; i<3; ++i) {
		for(int j=0; j<4; ++j) {
			cout << "printing i,j = " << i << "," << j << endl;
			for(int k=0; k<5; ++k) {
				cout << mat3d_copy[i][j][k] << " " ;
			}
			cout << endl;
		}
	}

	cout << "Size = " << mat3d.size() << endl;
	cout << "Size = " << mat3d[0].size() << endl;
	cout << "Size = " << mat3d[0][0].size() << endl;
*/
/*
	vector<vector<vector<int> > > mat3d;
	mat3d.resize(3);
	for(int i=0; i<3; ++i) {
		mat3d[i].resize(4);
		for(int j=0; j<4; ++j)
			mat3d[i][j].resize(5, 0);
	}

	for(int i=0; i<3; ++i) {
		for(int j=0; j<4; ++j) {
			cout << "printing i,j = " << i << "," << j << endl;
			for(int k=0; k<5; ++k) {
				cout << mat3d[i][j][k] << " " ;
			}
			cout << endl;
		}
	}
*/

/*
	char * const n[] = {"l2", "l2_sqrt", "l1", "l1_sqrt"};
	cout << strlen(n[1]) << endl;
*/

	/*
	std::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	std::map<char,int>::iterator it=mymap.begin();
	std::cout << it->first << " => " << it->second << '\n';
	mymap['a'] = 500;
	//it=mymap.begin();
	std::cout << it->first << " => " << it->second << '\n';
	mymap.erase('a');
	//it=mymap.begin();
	std::cout << it->first << " => " << it->second << '\n';
	// show content:

	//for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	//	std::cout << it->first << " => " << it->second << '\n';
	*/

	int x = -42, y=10;
	std::string s = std::to_string(x) + " " + std::to_string(y);
	string d = " ";
	cout << s << endl;
	cout<< stoi(s) << endl;
	size_t pos = s.find(d);
	string s1 = s.substr(0, pos);
	string s2 = s.substr(++pos);
	cout<< s1 << endl;
	cout << s2 << endl;
	cout << s1+s2 << endl;
	return 0;
}