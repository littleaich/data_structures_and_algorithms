#include <iostream>
#include <stack>
#include <string>

using namespace std;

/*

bool match_bracket_pair(char bracket_open, char bracket_close) 
{
	if (bracket_open == '[' && bracket_close == ']')
		return true;
	if (bracket_open == '{' && bracket_close == '}')
        return true;
	if (bracket_open == '(' && bracket_close == ')')
        return true;
    return false;
}

int main() {
    std::string text;
    getline(cin, text);
	bool success = true;
	int position;
    stack<char> stack_open_brackets;
    for (position = 0; position < text.length(); ++position) {
        char next = text[position];

		switch(next) {
		case '(':
		case '{':
		case '[':
			stack_open_brackets.push(next);
			break;
		case ')':
		case '}':
		case ']':
			if(!match_bracket_pair(stack_open_brackets.top(), next))
				success = false;
			break;
		default:
			;
		}

		if(!success)
			break;
    }

	if(!success)
		

    // Printing answer, write your code here

    return 0;
}
*/



struct Bracket {
    Bracket(int type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};


int main() {
    std::string text;
    getline(std::cin, text);
	int position;
	bool success = true;
    std::stack <Bracket> opening_brackets_stack;
    for (position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
			opening_brackets_stack.push(Bracket(next,position));
        }

        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
			if(opening_brackets_stack.empty() || 
				!opening_brackets_stack.top().Matchc(next)) {
				success = false;
				break;
			}
			else
				opening_brackets_stack.pop();
        }
    }

    // Printing answer, write your code here
	if(!success)
		std::cout << ++position << std::endl;
	else if(!opening_brackets_stack.empty())
		std::cout << ++opening_brackets_stack.top().position << std::endl;
	else
		std::cout << "Success" << std::endl;

    return 0;
}