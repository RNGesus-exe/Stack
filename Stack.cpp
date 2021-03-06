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
        T holder;
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
    int evaluatePostFix(std::string postfix) {
        Stack<int> stk_temp;
        for (int i = 0; i < postfix.length(); i++) {
            if (isOperator(postfix[i])) {
                switch (postfix[i]) {
                    case '+':
                        stk_temp.push(stk_temp.pop() + stk_temp.pop());
                        break;
                    case '-':
                        stk_temp.push(stk_temp.pop() - stk_temp.pop());
                        break;
                    case '*':
                        stk_temp.push(stk_temp.pop() * stk_temp.pop());
                        break;
                    case '/':
                        stk_temp.push(stk_temp.pop() / stk_temp.pop());
                        break;
                    case '%':
                        stk_temp.push(stk_temp.pop() % stk_temp.pop());
                        break;
                }
            }
            else {
                stk_temp.push(postfix[i]-'0');
            }
        }
        return stk_temp.pop();
    }

   /* void undoRedo(){
        std::string line,temp;
        std::cout<<"Enter the sentence = ";
        std::getline(std::cin,line);

        Stack<std::string> undo_stk,redo_stk;

        char choice = '\0';



        while(true){
            std::cout<<"What do you want to do = "
                     <<"\n 1) Undo "
                     <<"\n 2) Redo "
                     <<"\n 3) Write"
                     <<"\n 4) Append"
                     <<"\n 5) Exit"<<std::endl;
            std::cin>>choice;
            switch(choice){
                case '1':
                    if(!line.empty()){
                        int i=(int)(line.length()-1);
                        for(;i>=0&&line[i]!=' ';i--){}
                        i++;
                        for(;i<line.length();i++){
                            temp.push_back(line[i]);
                        }
                        std::cout<<temp<<std::endl;
                        undo_stk.push(temp);
                        line.erase(line.begin()+(line.length()-(temp.length()+1)),line.end());
                        temp.clear();
                    }
                    else {
                        std::cerr<<"There is nothing to undo!!!"<<std::endl;
                    }
                    break;
                case '2':
                    if(!undo_stk.isEmpty()){
                        line+=" "+undo_stk.pop();
                    }
                    else{
                        std::cerr<<"You need to undo first!!!"<<std::endl;
                    }
                    break;
                case '3':
                    if(!line.empty()){
                        std::cout<<line<<std::endl;
                    }
                    else {
                        std::cerr<<"There is nothing to write"<<std::endl;
                    }
                    break;
                case '4':
                    break;
                case '5':
                    exit(1);
                default:
                    std::cerr<<"Invalid Option!!!"<<std::endl;
            }
        }
    }
    */
    ~Stack() {
        while (this->head) {
            this->pop();
        }
    }
};

int main() {

    Stack<int> stk;
    //stk.undoRedo();
    return EXIT_SUCCESS;
}