# include <iostream>
# include <stack>

using namespace std;

template <class T> class StackExt {
	stack<T> s;
	stack<T> s_min;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return this->s.empty();
}

template <class T>
T& StackExt<T>::top() {
	return s.top();
}

template <class T>
void StackExt<T>::pop() {
	// Se removermos o minimo, removemos tambem da stack com os minimos
	if(!s_min.empty() && s.top() == s_min.top()) {
		s.pop();
		s_min.pop();
	}
	else if (!s.empty()) {
		s.pop();
	}
}

template <class T>
void StackExt<T>::push(const T& val) {

	if (s_min.empty()) {
		s_min.push(val);
		s.push(val);
		return;
	}

	// Se adicionarmos um novo minimo, temos que adicionar as duas stacks
	if (!s_min.empty() && val <= s_min.top()) {
		s_min.push(val);
	}

	s.push(val);
}

template <class T>
T& StackExt<T>::findMin() {
	return s_min.top();
}
