#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>


using namespace std;

int applyOperation(int a, int b, char op){  //apply operators ON DEMAND MONKEY
    switch (op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        default: return 0;
    }
}
int arithmetic(const string& expression){
    stack<int> values; //operands
    //as values are added to this stack, when operators are encountered we pop them to perform the operation then replace it with the new value
    stack<char> operators; //operators
    int i = 0;
    while(i < expression.length()){ //traverse through the expression string
        if(isdigit(expression[i])){ //traverse forward when a number is found
            int val = 0;
            while(i < expression.length() && isdigit(expression[i])){ //while expression index is not concluded and expression index is a number
                val = val * 10 + (expression[i] - '0'); //convert string to base 10
                i++;
            }
            values.push(val);
        } else if (expression[i] == '('){
            operators.push(expression[i]);
            i++;
        } else if (expression[i] == ')'){
            while (!operators.empty() && operators.top() != '(') {
                int val2 = values.top(); 
                values.pop();

                int val1 = values.top(); 
                values.pop();

                char op = operators.top(); 
                operators.pop();

                values.push(applyOperation(val1, val2, op)); //when ) is reached, a pair of an expression is complete and can be assessed
            }
        operators.pop(); //this will pop the opening parenthesis
        i++;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/' ) {
            //if we encounter an operator, we need to add it to the operator stack to track operation order
            while (
            !operators.empty() //operator stack is not empty
            && (
                operators.top() == '*' || operators.top() == '/' || (operators.top() == '+' || operators.top() == '-') //if the last recorded operator is higher prio
                && (expression[i] == '+' || expression[i] == '-') //current index is +/-
                )
            ){
                int val2 = values.top(); 
                values.pop();

                int val1 = values.top(); 
                values.pop();

                char op = operators.top(); 
                operators.pop();

                values.push(applyOperation(val1, val2, op));
            }
            operators.push(expression[i]);
            i++;
        } else {
            i++; //char not number or operator (white space) SKIP
        }
    }
    while (!operators.empty()) { //apply final pass of remaining operators
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(val1, val2, op));
    }
    return values.top();
}
int main(){
    char exitres;
    cout << "Welcome to my F A W K I N four function calculator! Enter an expression or type \"Q\" to exit." << endl;
    do{
        exitres = 'n';
        string expression;
        cout << "Expression: ";
        getline(cin, expression);   //record input
        if (isalpha(expression[0]) && expression.length() == 1){
            exitres = expression[0];
            exitres = tolower(exitres);
            if(exitres != 'q'){
                exitres = 'n';
                cout << "Invalid entry" << endl;
                continue;
            }//only accept q if alphabetic, otherwise restart loop
        }//check if input is an alphabetic char and length 1
        int result = arithmetic(expression);
        cout << "Result: " << result << endl;        
        
    }
    while(exitres !='q');

    return 0;
}