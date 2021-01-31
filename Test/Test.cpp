#include "pch.h"
#include <iostream>
#include "../Regex/regex.h"

int main()
{
	NFA nfa;

	std::cout << (nfa.isMatch("a*a", "a") ? "true" : "false") << std::endl;				// true
	std::cout << (nfa.isMatch("a+a", "aa") ? "true" : "false") << std::endl;			// true
	std::cout << (nfa.isMatch("(a|b)+", "aa") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)+", "ba") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)+", "bb") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)+", "ab") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)+", "ba") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)*", "aa") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)*", "bb") ? "true" : "false") << std::endl;		// true
	std::cout << (nfa.isMatch("(a|b)+a", "ba") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch("(a|b)+b", "bb") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch("(a|b)*a", "ba") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch("(a|b)*b", "bb") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch("github", "github.com") ? "true" : "false") << std::endl;	// true, because its not a fullmatch, instead to a submatch.
	std::cout << (nfa.isMatch("github.com", "github.com") ? "true" : "false") << std::endl;	// true
	std::cout << (nfa.isMatch(".*.com", "github.com") ? "true" : "false") << std::endl;	// true
	
	return 0;
}
