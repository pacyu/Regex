#include "pch.h"
#include <iostream>
#include "regex.h"

int main()
{
	NFA nfa;

	std::cout << (nfa.isMatch("(a|b)*abb", "ababb") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch("a*a", "a") ? "true" : "false") << std::endl;				// true
	std::cout << (nfa.isMatch("a+a", "aa") ? "true" : "false") << std::endl;			// true
	return 0;
}
