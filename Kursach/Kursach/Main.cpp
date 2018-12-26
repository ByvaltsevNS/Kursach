#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "ExprElem.h"
using namespace std;

////Бинарные операции
//double bin_act(double var1, double var2, char act) {
//	switch (act) {
//	case '+':
//		return var1 + var2;
//	case '-':
//		return var1 - var2;
//	case '*':
//		return var1 * var2;
//	case '/':
//		return var1 / var2;
//	}
//}
////Вычисление результата
//double calc(vector <expr_elem>* expr) {
//	stack <double>* mystack = new stack <double>;
//	double var1, var2;
//	for (size_t i = 0; i < expr->size(); i++) {
//		if (expr->at(i).get_operand())
//			mystack->push(atof(expr->at(i).get_content().c_str()));
//		else {
//			var1 = mystack->top();
//			mystack->pop();
//			var2 = mystack->top();
//			mystack->pop();
//			mystack->push(bin_act(var2, var1, expr->at(i).get_content().at(0)));
//		}
//	}
//	return mystack->top();
//}


int main() {
	string* input_expr = new string; //Создание входного выражения
	vector <expr_elem>* expr; //Создание выражения
	//bool to_continue; //Продолжать ли работу программе
	string answer; //Ответ пользователя
	cout << "You are in the program \"Postfix calculator\"!" << endl;
	/*do {*/
		cout << "Enter your expression in the record's infix form: ";
		getline(cin, *input_expr); //Считывание входного выражения
		try {
			expr = first_oper_expr(input_expr); //Первичная обработка выражения
			second_oper_expr(expr); //Вторичная обработка выражения
			vector <expr_elem>* post_expr = infix_postfix(expr); //Преобразование выражения в постфиксную форму
			double result = calc(post_expr);
		}
		catch (string str) {
			cout << str << endl;
		}
		/*do {
			cout << "Try again or exit? (Answer \"yes\" or \"no\"): ";
			cin >> answer;
			cin.ignore(32767, '\n');
		} while (answer != "yes" && answer != "no");
	} while (answer == "yes");*/
	cout << "Goodbye!" << endl;
	return 0;
}