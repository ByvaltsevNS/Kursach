#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <stack>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ExprElems.h"

const int PREF = 1; //Префиксный
const int POST = 2; //Постфиксный
const int BRACK = 0; //Квадратные скобки

using namespace std;
//Контейнер бинарных операций
map <string, int> bin_oper = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0}, {"^", 3} };
//Контейнер унарных операций
map <string, int> unar_oper = { {"-", PREF}, {"[", BRACK}, {"]", BRACK}, {"sin", PREF}, {"cos", PREF}, {"tg", PREF}, {"ctg", PREF}, {"!", POST}, {"ln", PREF}, {"log", PREF}, {"sqrt", PREF} };
//Контейнер констант
map <string, double> num_const = { {"e", M_E}, {"pi", M_PI} };
//Контейнер скобок
map <string, int> brackets = { {"[", BRACK}, {"]", BRACK}, {"(", BRACK}, {")", BRACK} };
//Обработка выражения 
size_t proc_expr(string* input, vector <expr_elem>* expr) {
	//map < string, int>::iterator it;
	//vector <string>::iterator iter;
	//map <string, bool> post_expr;
	size_t sym_iter = 0, elem_iter = 0; //Итераторы симвлолов и элементов постфиксного выражения
	//expr->push_back("");
	bool dig = false; //Цифра или нет
	for (size_t i = 0; i < input->size(); i++) { //Цикл по символам входного выражения
		if (isdigit(input->at(i)) || input->at(i) == '.') { //Если это число
			//iter->push_back(input->at(sym_iter++));
			if (!dig) { //Если предыдущий символ не цифра
				dig = true; //Цифра
				expr->push_back(expr_elem("", dig)); //Добавление операнда в выражениие
				if (i != 0) //Если не первый символ
					elem_iter++;
				//post_expr.insert({ "", dig });
			}
			(*expr)[elem_iter].add(input->at(i)); //Добавление символа в осодержание элемента
		}
		else {
			//it = bin_oper.find(input->substr(sym_iter, 1));
			//if (/*it*/bin_oper.find(input->substr(i, 1)) != bin_oper.end()) { //Если это бинарный оператор
				//expr->push_back(input->substr(i, 1));
			if (dig) //Если предыдущий символ цифра
			{
				dig = false;
				expr->push_back(expr_elem(input->substr(i, 1), dig)); //Добавление оператора в выражение
				if (i != 0) //Если не первый символ
					elem_iter++;
			}
			else {
				dig = false; //Не цифра
				if (i == 0) //Если первый символ
					expr->push_back(expr_elem(input->substr(i, 1), dig)); //Добавление оператора в выражение
				else {
					if (isalpha(input->at(i)) && isalpha(input->at(i - 1))) //Если текущий и предыдущий символы -буквы
						(*expr)[elem_iter].add(input->at(i)); //Добавление символа в содержание элемента
					else {
						expr->push_back(expr_elem(input->substr(i, 1), dig)); //Добавление оператора в выражение
						elem_iter++;
					}
				}
			}
			 /*}*/
		}
	}
	for (size_t i = 0; i < expr->size(); i++) //Вывод операндов
		if (expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //Вывод операторов
		if (!expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //Вывод выражения в инфиксной форме
		cout << expr->at(i).get_content() << " ";
	cout << endl;
	return 0;
}
//Разделение "операндов" на константы, бинарные и унарные операторы
void fix_infix(vector <expr_elem>* expr) {
	for (size_t i = 0; i < expr->size(); i++) {
		if (!(*expr)[i].get_operand()) { //Если "оператор"
			if (num_const.find(expr->at(i).get_content()) != num_const.end()) //Если "константа"
				(*expr)[i].operand = true;
			else {
				if (bin_oper.find(expr->at(i).get_content()) != bin_oper.end())
					(*expr)[i].binar = true;
				else {
					if (unar_oper.find(expr->at(i).get_content()) != unar_oper.end())
						(*expr)[i].binar = false;
					else {
						try
						{
							throw (expr->at(i).get_content());
						}
						catch (string str)
						{
							cout << "Entered the expression incorrect! Possible error: " << str << endl;
							return;
						}
					}
				}
			}
		}
	}
	for (size_t i = 0; i < expr->size(); i++) //Вывод операндов
		if (expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //Вывод бинарных операторов
		if (!expr->at(i).get_operand() && expr->at(i).get_binar())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //Вывод унарных операторов
		if (!expr->at(i).get_operand() && !expr->at(i).get_binar())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
}
//Преобразование из инфиксной в постфиксную форму
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix) {
	vector <expr_elem>* postfix = new vector <expr_elem>;
	stack <expr_elem> * mystack = new stack <expr_elem>;
	for (size_t i = 0; i < infix->size(); i++) {
		expr_elem temp((*infix)[i].get_content(), (*infix)[i].get_operand()); //Текущий элемент
		if (temp.get_operand() || !temp.get_binar()) //Если символ или постфиксный оператор
			postfix->push_back(temp); //Добавление элемента в постфиксное выражение
		else {
			if (temp.get_content() == "(") //Если элемент открывающая круглая скобка
				mystack->push(temp); //Добавление в стэк
			else {
				if (temp.get_content() == ")") { //Если элемент закрывающая круглая скобка
					while (mystack->top().get_content() != "(") { //Пока не открывающая круглая скобка
						bool close_brack = false;
						if (mystack->empty() || mystack->top().get_content() == "[" && !close_brack) { //Если стэк пустой или текущий элемент квадратная скобка
							try {
								throw (infix->at(i).get_content());
							}
							catch (string str) {
								cout << "Entered the expression incorrect! Possible error: " << str << endl;
								return;
							}
						}
						if (mystack->top().get_content() == "]") //Если была закрывающая скобка
							close_brack = true;
						postfix->push_back(mystack->top()); //Добавление элемента из стэка в постфиксное выражение
						mystack->pop(); //Удаление элемента из стэка
					}
					mystack->pop(); //Удаление открывающей круглой скобки из стэка
				}
				else {
					while (!mystack->empty() && bin_oper[temp.get_content()] <= bin_oper[mystack->top().get_content()]) { //Пока приоритет операции меньше, чем текущей и стэк не пуст
						postfix->push_back(mystack->top()); //Добавление элемента в постфиксное выражение
						mystack->pop(); //Удаление элемента из стэка
					}
					if (mystack->empty() || bin_oper[temp.get_content()] > bin_oper[mystack->top().get_content()]) //Если стэк пуст-
						mystack->push(temp); //Добавление элемента в стэк
				}
			}
		}
	}
	while (!mystack->empty()) { //Пока стэк не пуст
		if (bin_oper[mystack->top().get_content()] == BRACK) {//Если осталась круглая скобка
			try
			{
				throw(mystack->top().get_content());
			}
			catch (string str)
			{
				cout << "Entered the expression incorrect! Possible error: " << str << endl;
				return postfix;
			}
		}
		postfix->push_back(mystack->top()); //Добавление элемента в постфиксное выражение
		mystack->pop(); //Удаление элемента из стэка
	}
	for (size_t i = 0; i < postfix->size(); i++) //Вывод постфиксного выражения
		cout << postfix->at(i).get_content();
	cout << endl;
	return postfix;
}
//Вычисление результата
//double cacl(vector <expr_elem>* expr) {
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
//Добавление символа в содержание элемента
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//Содержание элемента
string expr_elem::get_content() {
	return content;
}
//Операнд или оператор
bool expr_elem::get_operand() {
	return operand;
}
//Установка параматера бинарный или унарный
void expr_elem::set_binar(bool flag) {
	binar = flag;
}
//Установка параметра оператор или операнд
void expr_elem::set_operand(bool flag) {
	operand = flag;
}
//Бинарный или унарный
bool expr_elem::get_binar() {
	return binar;
}