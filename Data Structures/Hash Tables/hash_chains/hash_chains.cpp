#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>

using std::string;
using std::stack;
using std::vector;
using std::cin;
using std::unordered_set;

typedef std::unordered_set<std::string>::const_iterator C_Iterator;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    // store all strings in one vector
//    vector<string> elems;
	const float MAX_LOAD_FACTOR = 10.0;
/*
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }
*/
	struct Hash_ {
		size_t operator() (const string& str) const 
	   {
	   //                                    ^^^^^
	   //                             Don't forget this!
	   		const size_t p = 1000000007;
			const size_t x = 263;
			unsigned long long hash = 0; 
			size_t len = str.size()-1;
			for(int i = len; i>=0; --i) {
				hash = (hash * x + str[i]) % p;

			}
			return hash % bucket_count;
	   }
	};

	unordered_set<string, Hash_> stringSet;

public:
	static int bucket_count;
    //explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}
	QueryProcessor(int b_c) 
	{
		bucket_count = b_c;
	}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

/*
	void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }
*/
	void processQuery(const Query& query) 
	{
		if(stringSet.bucket_count() != bucket_count) {
//			std::cout << "max 1 = " << stringSet.max_load_factor() << std::endl;			
			stringSet.max_load_factor(MAX_LOAD_FACTOR);
//			std::cout << "max 2 = " << stringSet.max_load_factor() << std::endl;
			stringSet.rehash(bucket_count);
//			std::cout << "max 3 = " << stringSet.max_load_factor() << std::endl;
			
		}
		if(query.type == "add") { stringSet.insert(query.s); }
		else if(query.type == "del") { stringSet.erase(query.s); }
		else if(query.type == "find") {
			C_Iterator got = stringSet.find(query.s);
			writeSearchResult(got != stringSet.end());
		}
		else {
			stack<string> reverseBucket;
			for(auto local_it = stringSet.cbegin(query.ind); 
				local_it!= stringSet.cend(query.ind); ++local_it )
			{ std::cout << *local_it << " "; }
/*			{ reverseBucket.push(*local_it);}
			while (!reverseBucket.empty()) {
				std::cout << reverseBucket.top() << " "; 
				reverseBucket.pop();
			}
*/
			std::cout << std::endl;
		}
	}

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int QueryProcessor::bucket_count = 0;

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
