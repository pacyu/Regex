#pragma once

#include <unordered_map>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <memory>

enum class EState {
	INITISTATE, // Initial State
	INTERSTATE, // Intermediate State
	FINALSTATE  // Final State(or Accept State)
};

// Intermediate state
class State {
public:
	State() : e(EState::INTERSTATE) {}
	virtual bool isFinal() const {
		return e == EState::FINALSTATE;
	};
private:
	EState e;
};

class InitiState : public State {
public:
	InitiState() : e(EState::INITISTATE) {}
	bool isFinal() const override {
		return e == EState::FINALSTATE;
	};
private:
	EState e;
};

class FinalState : public State {
public:
	FinalState() : e(EState::FINALSTATE) {}
	bool isFinal() const override {
		return e == EState::FINALSTATE;
	};
private:
	EState e;
};

// 通过正则表达式生成状态转移表
// 示例：(a|b)*aab
// S : {q0, q1, q2, q3}
// S0: {q0}
// Σ : {a,b}
// F : {q3}
// 状态转移图:
//{
//	q0: { "a": [q0, q1] , "b": [q0] },
//	q1: { "a": [q2] },
//	q2: { "b": [q3] }
//}
class NFA {
public:
	NFA() : state_diagram(), init_state(), regex() {}
	NFA(std::string regex);

	bool isMatch(std::string seq) { return isMatch(init_state, seq); }
	bool isMatch(std::string regex, std::string seq);

private:
	bool isMatch(std::shared_ptr<State> state, std::string seq);
	void form(std::string regex);

private:
	// State-transfer diagram
	std::unordered_map<std::shared_ptr<State>,
		std::unordered_map<char, std::vector<std::shared_ptr<State>>>> state_diagram;

	// Initial state
	std::shared_ptr<State> init_state;

	// State sets
	std::vector<std::shared_ptr<State>> state_set;

	// Final state
	std::shared_ptr<State> final_state;

	// Regular expression
	std::string regex;
};