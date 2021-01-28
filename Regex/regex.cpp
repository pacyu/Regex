#include "stdafx.h"
#include "regex.h"

NFA::NFA(std::string regex)
	: state_diagram(), init_state(), regex(regex)
{
	form(regex);
}

bool NFA::isMatch(std::shared_ptr<State>& state, std::string seq) {
	if (state->isFinal()) return true;

	std::unordered_map<char, std::vector<std::shared_ptr<State>>>
		&accept = state_diagram[state];

	for (auto c : seq) {
		bool is_finded = (accept.find(c) != accept.end());
		if (is_finded || accept.find('.') != accept.end()) {
			std::vector<std::shared_ptr<State>> stateSet = accept[is_finded ? c : '.'];
			for (auto& s : stateSet)
				if (isMatch(s, { seq.begin() + 1, seq.end() }))
					return true;
		}
	}

	return false;
}

bool NFA::isMatch(std::string regex, std::string seq) {
	this->regex = regex;
	form(regex);
	return isMatch(seq);
}

void NFA::form(std::string regex) {
	std::stack<char> parens;
	std::stack<std::shared_ptr<State>> sta;
	std::shared_ptr<State> previous_state;
	char prevc;

	state_diagram.clear();
	init_state = std::make_shared<InitiState>();
	sta.push(init_state);
	for (size_t i = 0; i < regex.length(); i++) {
		char c = regex[i];
		switch (c) {
		case '(':
		{
			bool operor = false;
			size_t j = i + 1;
			prevc = regex[j];
			parens.push(c);
			while (!parens.empty() && j < regex.length()) {
				c = regex[j];
				switch (c) {
				case ')':
					parens.pop();
					if (!std::isalpha(prevc)
						&& prevc != '*'
						&& prevc != '+'
						&& prevc != '.')
						throw std::exception("Syntax error");
					break;
				case '|':
					if (!std::isalpha(prevc)
						&& prevc != '*'
						&& prevc != '+'
						&& prevc != '.')
						throw std::exception("Syntax error");
					operor = true;
					break;
				case '*':
					if (!std::isalpha(prevc)
						&& prevc != '.')
						throw std::exception("Syntax error");
					state_diagram.erase(sta.top());
					sta.pop();
					for (auto& accept : state_diagram[sta.top()])
						state_diagram[sta.top()][accept.first].push_back(sta.top());
					break;
				case '+':
					if (!std::isalpha(prevc)
						&& prevc != '.')
						throw std::exception("Syntax error");
					state_diagram[sta.top()][prevc].push_back(sta.top());
					break;
				default:
					if (!operor)
					{
						previous_state = sta.top();
						sta.push(std::make_shared<State>());
					}
					state_diagram[previous_state][c].push_back(sta.top());
					break;
				}
				prevc = c;
				j++;
			}
			i = j - 1;
		}
		break;
		case '*':
			state_diagram.erase(sta.top());
			sta.pop();
			for (auto& accept: state_diagram[sta.top()])
				state_diagram[sta.top()][accept.first].push_back(sta.top());
			break;
		case '+':
			state_diagram[sta.top()][prevc].push_back(sta.top());
			break;
		default:
			previous_state = sta.top();
			sta.push(std::make_shared<State>());
			state_diagram[previous_state][c].push_back(sta.top());
			break;
		}
		prevc = c;
	}
	if (!parens.empty()) throw std::exception("Syntax error");
	final_state = std::make_shared<FinalState>();
	std::unordered_map<char, std::vector<std::shared_ptr<State>>>
		&accepts = state_diagram[previous_state];
	if (previous_state == sta.top())
	{
		for (auto& ac : accepts) {
			state_diagram[final_state][ac.first].push_back(final_state);
		}
		state_diagram.erase(previous_state);
	}
	else {
		for (auto& ac : accepts) {
			state_diagram[previous_state][ac.first].pop_back();
			state_diagram[previous_state][ac.first].push_back(final_state);
		}
	}
	if (sta.top() == init_state) {
		init_state = final_state;
		sta.pop();
	}
	state_set.push_back(init_state);
	while (!sta.empty()) {
		if (std::find(state_set.begin(), state_set.end(), sta.top()) != state_set.end())
			state_set.push_back(sta.top());
		sta.pop();
	}
}