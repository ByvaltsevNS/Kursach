//#include <string>
#include <iostream>
//#include <vector>
//#define _USE_MATH_DEFINES
//#include <math.h>
#include "ExprElem.h"
//#include "Stack.h"
//#include "Map.h"

extern my_map* bin_oper_map = create_bin_oper_map(); //Создание контейнера бинарных операций
extern my_map* uno_oper_map = create_uno_oper_map(); //Создание контейнера унарных операций
extern my_map* const_map = create_const_map(); //Создание контейнера унарных операций
extern my_map* bin_oper_iden = create_bin_oper_identity(); //Создание контейнера уникальных идентификаторов бинарных операций
extern my_map* uno_oper_iden = create_uno_oper_identity(); //Создание контейнера уникальных идентификаторов унарных операций


using namespace std;

//Добавление символа к содержанию
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//Получение статуса элемента
string expr_elem::get_status() {
	return status;
}
//Получение содержания элемента
string expr_elem::get_content() {
	return content;
}
//Первичная обработка выражения
vector <expr_elem>* first_oper_expr(string* input) {
	vector <expr_elem>* expr = new vector <expr_elem>; //Создание выражения
	string flag = "operator"; //Флаг
	for (size_t i = 0; i < input->size(); i++) { //Цикл по символам входной строки
		if (isdigit(input->at(i)) || input->at(i) == '.') { //Если текущий символ цифра или точка
			if (i == 0) { //Если текущий символ первый
				expr->push_back(expr_elem(input->substr(i, 1), "operand")); //Добавляем элемент в выражение
				flag = "operand"; //Меняем значение флага
			}
			else {
				if (flag != "operand") { //Если предыдущий элемент - не операнд
					expr->push_back(expr_elem(input->substr(i, 1), "operand")); //Добавляем элемент в выражение
					flag = "operand"; //Меняем значение флага
				}
				else {
					expr->back().content.push_back(input->at(i)); //Добавляем текущий символ к текущему элементу
				}
			}
		}
		else {
			if (bin_oper_map->is_elem(input->substr(i, 1)) || uno_oper_map->is_elem(input->substr(i, 1))) { //Текущий элемент операция
				expr->push_back(expr_elem(input->substr(i, 1), "operator")); //Добавляем элемент в выражение
				flag = "operator"; //Меняем значение флага
			}
			else {
				if (isalpha(input->at(i))) { //Если текущий символ - буква
					if (i == 0) { //Если текущий символ первый
						expr->push_back(expr_elem(input->substr(i, 1), "word")); //Добавляем элемент в выражение
						flag = "word"; //Меняем значение флага
					}
					else {
						if (/*dig */flag == "operand" || flag == "operator") { //Если предыдущий элемент - операнд или оператор
							expr->push_back(expr_elem(input->substr(i, 1), "word")); //Добавляем элемент в выражение
							flag = "word"; //Меняем значение флага
						}
						else {
							expr->back().content.push_back(input->at(i)); //Добавляем текущий символ к текущему элементу
						}
					}
				}
				else {
					if (input->at(i) != ' ' && input->at(i) != '\t') {//Если не пробел и не табуляция 
						string error = "Entered is not a valid symbol: ";
						error.push_back(input->at(i));
						throw error; //Кидаем исключение о недопустимом символе
					}
				}
			}
		}
	}
	for (size_t i = 0; i < expr->size(); i++) {
		cout << expr->at(i).get_status() << " ";
		cout << expr->at(i).get_content() << " " << endl;
	}
	cout << endl;
	cout << endl;
	delete input;
	return expr;
}
//Вторичная обработка инфиксного выражения
void second_oper_expr(vector <expr_elem>* expr) {
	for (size_t i = 0; i < expr->size(); i++) { //Цикл по элементам выражения
		if (expr->at(i).get_status() != "operand") { //Если текущий элемент - операнд
			if (bin_oper_map->is_elem(expr->at(i).get_content())) { //Если текущий элемент - бинарная операция
				expr->at(i).status = "binary operator"; //Устанавливаем в статусе, что бинарный оператор
			}
			else {
				if (uno_oper_map->is_elem(expr->at(i).get_content())) { //Если текущий элемент - унарный оператор
					expr->at(i).status = "unary operator"; //Устанавливаем в статусе, что унарный оператор
				}
				else {
					if (const_map->is_elem(expr->at(i).get_content())) { //Если текущий элемент - константа
						expr->at(i).status = "const operand"; //Устанавливаем в статусе, что константа
					}
					else {
						string error = "Introduced unknown element: ";
						error.compare(expr->at(i).get_content());
						throw error; //Кидаем исключение по причине невозможности определить, чем является элемент
					}
				}
			}
		}
	}
	for (size_t i = 0; i < expr->size(); i++) {
		cout << expr->at(i).get_status() << " ";
		cout << expr->at(i).get_content() << " " << endl;
	}
	cout << endl;
}
//Преобразование из инфиксной в потсфиксную
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix) {
	vector <expr_elem>* postfix = new vector <expr_elem>; //Создание постфиксного выражения
	my_stack* stack = new my_stack; //Создание стэка
	//vector <expr_elem>::iterator iter = infix->begin(); //Создание итератора по выражению
	for (size_t i = 0; i < infix->size(); i++) { //Цикл по элементам выражения
		if (infix->at(i).get_status() == "operand" || infix->at(i).get_status() == "const operand" || infix->at(i).get_status() == "unary operator" && uno_oper_map->get_elem(infix->at(i).get_content()) == POST) { //Если текущий элемент - операнд или постфиксный унарный оператор
			postfix->push_back(infix->at(i)); //Добавляем элемент в постфиксное выражение
		}
		else {
			if (infix->at(i).get_status() == "unary operator" && uno_oper_map->get_elem(infix->at(i).get_content()) == PREF) { //Если текущий ээлемент - унарный префиксный оператор
				stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //Добавление элемента в стэк
			}
			else {
				if (infix->at(i).get_content() == "(") { //Если текущий элемент - открывающая скобка
					stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //Добавление элемента в стэк
				}
				else {
					if (infix->at(i).get_content() == ")") { //Если текущий элемент - закрывающая скобка
						while (stack->get_head()->get_content()->get_content() != "(" && !stack->empty()) { //Пока верхний элемент стэка - не открывающая скобка И стэк не кончился
							postfix->push_back(*stack->get_head()->get_content()); //Добавляем верхний элемент стэка в постфиксное выражение
							stack->pop(); //Удаляем элемент из стэка
							if (stack->empty() || stack->get_head()->get_content()->get_content() == ")") { //Если следующий элемент стэка - отсутсвует ИЛИ верхний элемент - закрывающая скобка
								throw string("Incorrect expression! It can't be convert in postfix form correctly!");
							}
						}
						stack->pop(); //Удаляем скобку из стэка
						//iter++;
					}
					else {
						if (infix->at(i).get_status() == "binary operator") { // Если элемент - бинарная операция
							while (!stack->empty() && (stack->get_head()->get_content()->get_status() == "unary operator" && uno_oper_map->get_elem(stack->get_head()->get_content()->get_content()) == PREF || stack->get_head()->get_content()->get_status() == "binary operator" && bin_oper_map->get_elem(infix->at(i).get_content()) <= bin_oper_map->get_elem(stack->get_head()->get_content()->get_content()))) {
								/*Пока стэк не пуст И (пока верхний элемент стэка - префиксная функция ИЛИ операция на вершине стэка приоритетнее этой операции ИЛИ операция на вершине стэка с таким же приоритетом, как у этой) ? ? */
								postfix->push_back(*stack->get_head()->get_content()); //Добавляем верхний элемент стэка в постфиксное выражение
								stack->pop(); //Удаляем элемент из стэка
							}
							stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //Помещаем операцию в стэк
						}
					}
				}
			}
		}
	}
	while (!stack->empty()) { //Добавляем в выражение оставшиеся в стэке элементы
		postfix->push_back(*stack->get_head()->get_content()); //Добавляем верхний элемент стэка в постфиксное выражение
		stack->pop(); //Удаляем элемент из стэка
	}
	for (size_t i = 0; i < postfix->size(); i++) {
		cout << postfix->at(i).get_content();
	}
	cout << endl;
	delete stack;
	delete infix;
	return postfix;
}
//Вычисление постфискного выражения на стэке
double calc(vector <expr_elem>* expr) {
	my_stack* stack = new my_stack; //Создание стэка
	//vector <expr_elem>::iterator iter = expr->begin(); //Создание итератора по выражению
	string temp;
	for (size_t i = 0; i < expr->size(); i++) { //Цикл по элементам выражения
		if (expr->at(i).get_status() == "operand" || expr->at(i).get_status() == "const operand") { //Если текущий элемент - операнд
			stack->push(new stack_elem(new expr_elem(expr->at(i).get_content(), expr->at(i).get_status()))); //Добавление элемента в стэк
		}
		else {
			if (expr->at(i).get_content() == "-") { //Если текущий элемент - минус
				if (!stack->empty() && (stack->get_head()->get_content()->get_status() == "operand" || stack->get_head()->get_content()->get_status() == "const operand")) { //Если стэк не пуст и на вершине его операнд
					if (stack->get_head()->get_next() != nullptr && (stack->get_head()->get_next()->get_content()->get_status() == "operand" || stack->get_head()->get_next()->get_content()->get_status() == "const operand")) { //Если стэк имеет более одного элемента и второй тоже является операндом
						temp = one_oper_bin(stack->get_head()->get_content()->get_content(), stack->get_head()->get_next()->get_content()->get_content(), expr->at(i).get_content());
						stack->pop();
						stack->pop();
						stack->push(new stack_elem(new expr_elem(temp, "operand")));
					}
					else {
						temp = one_oper_uno(stack->get_head()->get_content()->get_content(), expr->at(i).get_content());
						stack->pop();
						stack->push(new stack_elem(new expr_elem(temp, "operand")));
					}
				}
			}
			else {
				if (expr->at(i).get_status() == "binary operator") { //Если стэк имеет более одного элемента и второй тоже является операндом
					temp = one_oper_bin(stack->get_head()->get_content()->get_content(), stack->get_head()->get_next()->get_content()->get_content(), expr->at(i).get_content());
					stack->pop();
					stack->pop();
					stack->push(new stack_elem(new expr_elem(temp, "operand")));
				}
				else {
					temp = one_oper_uno(stack->get_head()->get_content()->get_content(), expr->at(i).get_content());
					stack->pop();
					stack->push(new stack_elem(new expr_elem(temp, "operand")));
				}
			}
		}
	}
	cout << stack->get_head()->get_content()->get_content() << endl;
	return stod(stack->get_head()->get_content()->get_content());
}
//Вычисление одной бинарной операции
string one_oper_bin(string operand1, string operand2, string operation) {
	switch (bin_oper_iden->get_elem(operation)) {
	case 0:
		return to_string(stod(operand1) + stod(operand1));
	case 1:
		return to_string(stod(operand1) - stod(operand1));
	case 2:
		return to_string(stod(operand1) * stod(operand1));
	case 3:
		return to_string(stod(operand1) / stod(operand1));
	case 4:
		return  to_string(pow(stod(operand1),stod(operand1)));
	}
}
//Вычисление одной унарной операции
string one_oper_uno(string operand, string operation) {
	switch (uno_oper_iden->get_elem(operation)) {
	case 0:
		return to_string(sin(stod(operand)));
	case 1:
		return to_string(cos(stod(operand)));
	case 2:
		return to_string(tan(stod(operand)));
	case 3:
		return to_string(1/tan(stod(operand)));
	case 4:
		return  to_string(log(stod(operand)));
	case 5:
		return  to_string(log10(stod(operand)));
	case 6:
		return  to_string(sqrt(stod(operand)));
	case 7:
		return  to_string(-stod(operand));
	}
}