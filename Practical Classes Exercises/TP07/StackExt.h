# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
	stack<T> main_stack;
	stack<T> mins;

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
	return (main_stack.empty());
}

template <class T>
T& StackExt<T>::top() {
	return (main_stack.top());
}

template <class T>
void StackExt<T>::pop() {
	// Check if it should be removed from the mins stack. If so, do it
	if (mins.top() == main_stack.top())
		mins.pop();

	// Pop it from the main stack
	main_stack.pop();
}

template <class T>
void StackExt<T>::push(const T& val) {
	// Add it to the main stack
	main_stack.push(val);

	// Add it to the min. values stack, if needed
	if (mins.size() == 0){
		mins.push(val);			// First element! Add it, it is the minimum
	}
	else if (val <= mins.top()){	// New minimum value
		mins.push(val);
	}
}

template <class T>
T& StackExt<T>::findMin() {
	return (mins.top());
}
