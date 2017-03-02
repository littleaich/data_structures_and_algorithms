#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using std::string;
using std::vector;
typedef unsigned long long ull;

static size_t multiplier = 263;
static const ull prime = 1000000007;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

// ============================================== //
ull polyHash(const string& s, const ull prime, const size_t multiplier) {
    	static size_t bucket_count = s.size()+1;
    	ull hash = 0;
    	for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        	hash = (hash * multiplier + s[i]); //% prime; ///////////
    	return hash; //% bucket_count;
}

void preComputeHashes(vector<ull>& hashVector, 
	const string& text, const size_t& lenPattern)
{
	//const ull prime = pow(10, ceil(log10(text.size()*lenPattern)) + 2) + 7;
	//const ull prime = pow(10, text.size()) + 7;
	//if(prime <= multiplier) { multiplier = 1; }	
	string subText = text.substr(text.size()-lenPattern, lenPattern);
	hashVector[text.size()-lenPattern] = polyHash(subText, prime, multiplier);
	ull y = 1;	
	for(size_t i=1; i<=lenPattern; ++i)
	{ y = (y*multiplier); } //% prime; } /////////////
	for(int i = text.size()-lenPattern-1; i>=0; --i) {
		hashVector[i] = (multiplier*hashVector[i+1]+text[i]-y*text[i+lenPattern]); //% prime; ///////////////	
		//hashVector[i] = hashVector[i] % (lenPattern+1);
	}
}

void RabinKarp_faster(vector<int>& result, const string& text, const string& pattern)
{
	//const ull prime = pow(10, ceil(log10(text.size()*pattern.size())) + 2) + 7;
	//const ull prime = pow(10, text.size()) + 7;
	//if(prime <= multiplier) { multiplier = 1; }
	size_t patternHash = polyHash(pattern, prime, multiplier);
	vector<ull> hashVector(text.size()-pattern.size()+1);
	preComputeHashes(hashVector, text, pattern.size());
	for(size_t i=0; i<=text.size()-pattern.size(); ++i) {
		if(patternHash != hashVector[i]) { continue; }
		if(text.substr(i,pattern.size()) == pattern)
		{ result.push_back(i); }
	}
}
// ============================================== //

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}


std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    vector<int> ans;
	RabinKarp_faster(ans,t,s);
/*    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
*/
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
