#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "ExprElem.h"
using namespace std;

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
		cin.get();
	cout << "Goodbye!" << endl;
	return 0;
}