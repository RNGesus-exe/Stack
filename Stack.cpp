#include<iostream>

template <class T>
class Stack {
	class Node {
	public:
		T data;
		Node* next;
	}*head;

public:

	Stack():head(nullptr) {}
	Stack(T data) {
		this->push(data);
	}
	void push(T data) {
		if (head) {
			Node* temp = new Node;
			if (temp) {
				temp->data = data;
				temp->next = head;
				head = temp;
				temp = nullptr;
			}
			else {
				std::cerr << "The Stack is Full!!!\n";
			}
		}
		else {
			this->head = new Node;
			this->head->data = data;
			this->head->next = nullptr;
		}
	}
	T pop() {
		T holder = NULL;
		if (head) {
			holder = this->head->data;
			Node* temp = this->head;
			this->head = this->head->next;
			delete temp;
			temp = nullptr;
		}
		return holder;
	}
	T peekAtTop() const {
		if (head) {
			return this->head->data;
		}
		return NULL;
	}
	void display() const {
		Node* temp = this->head;
		while (temp) {
			std::cout << temp->data;
			temp = temp->next;
		}
	}
	bool isEmpty() const {
		return head == nullptr;
	}
	Node& getHead() {
		return this->head;
	}
	bool checkBraces(std::string equation) {
		Stack<char> braces;

		for (int i = 0; i < equation.length(); i++) {
			if (equation[i] == '(' || equation[i] == '{' || equation[i] == '[') {
				braces.push(equation[i]);
			}
			else if (equation[i] == ')' || equation[i] == '}' || equation[i] == ']') 
			{
				if ((equation[i] == ')' && braces.peekAtTop() == '(') || (equation[i] == '}'
					&& braces.peekAtTop() == '{') || (equation[i] == ']' && braces.peekAtTop() == '[')) {
					braces.pop();
				}
				else {
					return false;
				}
			}
		}
		return braces.isEmpty();
	}
	bool isOperator(char ch) {
		return (ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '%');
	}
	int getPre(char op) {
		switch (op) {
		case '/':
		case '%':
			return 3;
		case '*':
			return 2;
		case '-':
		case '+':
			return 1;
		default:
			std::cerr << "Such an operator does not exist!!!";
		}
	}

	std::string infixToPostfix(std::string infix) {
		Stack<char> temp_stk;
		std::string postfix;
		for (int i = 0; i < infix.length(); i++) {
			if (this->isOperator(infix[i])) {
				while ((!temp_stk.isEmpty()) && this->getPre(infix[i]) <= this->getPre(temp_stk.peekAtTop())) {
					postfix.push_back(temp_stk.pop());
				}
				temp_stk.push(infix[i]);
			}
			else {
				postfix.push_back(infix[i]);
			}
		}

		while (!temp_stk.isEmpty()) {
			postfix.push_back(temp_stk.pop());
		}
		return postfix;
	}
	~Stack() {
		while (this->head) {
			this->pop();
		}
	}
};

int main() {

	Stack<int> stk;
	std::string str = "a*b/c%e-f";
	std::cout << stk.infixToPostfix(str) << std::endl;

	return EXIT_SUCCESS;
}