#include <iostream>
#include <stack>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <map>
#include "ExprElems.h"
using namespace std;

//map <string, int> bin_oper = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0}, {"^", 3} }; 
//
////Обработка выражения 
//size_t proc_expr(string* input, vector <expr_elem>* expr) {
//	//map < string, int>::iterator it;
//	//vector <string>::iterator iter;
//	map <string, bool> post_expr;
//	size_t sym_iter = 0, elem_iter = 0;
//	//expr->push_back("");
//	bool dig = false;
//	for (size_t i = 0; i < input->size(); i++) {
//		if (isdigit(input->at(i)) || input->at(i) == '.') {
//			//iter->push_back(input->at(sym_iter++));
//			if (!dig) {
//				dig = true;
//				expr->push_back(expr_elem("", dig));
//				//post_expr.insert({ "", dig });
//			}
//			(*expr)[elem_iter].add(input->at(i))/*->push_back(input->at(sym_iter++))*/;
//		}
//		else {
//			//it = bin_oper.find(input->substr(sym_iter, 1));
//			if (/*it*/bin_oper.find(input->substr(i, 1)) != bin_oper.end()) {
//				//expr->push_back(input->substr(i, 1));
//				if (dig)
//					elem_iter += 2;
//				else
//					elem_iter++;
//				dig = false;
//				expr->push_back(expr_elem(input->substr(i, 1), dig));
//			}
//		}
//	}
//	for (size_t i = 0; i < expr->size();i++)
//		if((*expr)[i].get_operand())
//			cout << (*expr)[i].get_content();
//	cout << endl;
//	for (size_t i = 0; i < expr->size(); i++)
//		if (!(*expr)[i].get_operand())
//			cout << (*expr)[i].get_content();
//	cout << endl;
//	return 0;
//}



//Преобразование из инфиксной в постфиксную форму
//vector <expr_elem>* infix_postfix(vector <expr_elem>* input) {
//	vector <expr_elem>* output = new vector <expr_elem>;
//	stack <expr_elem> * mystack = new stack <expr_elem>;
//	for (size_t i = 0; i < input->size(); i++) {
//		expr_elem temp((*input)[i].get_content(), (*input)[i].get_operand());
//		if (temp.get_operand())
//			output->push_back(temp);
//		else {
//			if (temp.get_content() == "(")
//				mystack->push(temp);
//			else {
//				if (temp.get_content() == ")") {
//					while (mystack->top().get_content() != "(") {
//						output->push_back(mystack->top());
//						mystack->pop();
//					}
//					mystack->pop();
//				}
//				else {
//					while (!mystack->empty() && bin_oper[temp.get_content()] <= bin_oper[mystack->top().get_content()]) {
//						output->push_back(mystack->top());
//						mystack->pop();
//					}
//					if (mystack->empty() || bin_oper[temp.get_content()] > bin_oper[mystack->top().get_content()])
//						mystack->push(temp);
//				}
//			}
//		}
//	}
//	while (!mystack->empty()) {
//		output->push_back(mystack->top());
//		mystack->pop();
//	}
//	for (size_t i = 0; i < output->size(); i++)
//		cout << output->at(i).get_content();
//	cout << endl;
//	return output;
//}
//Бинарные операции
double bin_act(double var1, double var2, char act) {
	switch (act) {
	case '+':
		return var1 + var2;
	case '-':
		return var1 - var2;
	case '*':
		return var1 * var2;
	case '/':
		return var1 / var2;
	}
}
//Вычисление результата
double calc(vector <expr_elem>* expr) {
	stack <double>* mystack = new stack <double>;
	double var1, var2;
	for (size_t i = 0; i < expr->size(); i++) {
		if (expr->at(i).get_operand())
			mystack->push(atof(expr->at(i).get_content().c_str()));
		else {
			var1 = mystack->top();
			mystack->pop();
			var2 = mystack->top();
			mystack->pop();
			mystack->push(bin_act(var2, var1, expr->at(i).get_content().at(0)));
		}
	}
	return mystack->top();
}


int main() {
	//stack <string> MyStack; //Создание стэка
	stack <string> * Mystack = new stack <string>; //Также создание стэка, только через указатель
	//stack <operand> * Mystack = new stack <operand>;
	//Или таки написать свой стэк ?? - Хотя строчка выше дает понять, что не обязательно
	//vector <string>* operations = new vector <string>; //Создание вектора операций
	//*operations = { "cos", "sin", "tg", "ctg", "ln", "log", "sqrt", "-", "+", "*", "/", "^" };
	//vector <string>* digits = new vector <string>; //Создание вектора цифр
	//*operations = { "cos", "sin", "tg", "ctg", "ln", "log", "sqrt", "-", "+", "*", "/", "^" };
	string* input_expr = new string;
	vector <expr_elem>* expr = new vector <expr_elem>;
	cout << "You are in the program \"Postfix calculator\"!" << endl;
	cout << "Enter your expression in the record's infix form: ";
	getline(cin, *input_expr);
	proc_expr(input_expr, expr);
	fix_infix(expr);
	/*vector <expr_elem>* pref = */
	//cout << calc(infix_postfix(expr)) << endl;

	/*double var = atof(pref->at(2).get_content().c_str());
	cout << var;*/
	/*vector <string>::iterator it = expr->begin();
	while (it != expr->end())
		cout << *(it++) << endl;*/
	//cout << expr->size();
	//expr->push_back(*input_expr);
	//cout << expr->at(0);

	cin.get();
	return 0;
}