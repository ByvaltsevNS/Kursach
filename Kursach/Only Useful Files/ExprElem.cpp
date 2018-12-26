//#include <string>
#include <iostream>
//#include <vector>
//#define _USE_MATH_DEFINES
//#include <math.h>
#include "ExprElem.h"
//#include "Stack.h"
//#include "Map.h"

extern my_map* bin_oper_map = create_bin_oper_map(); //�������� ���������� �������� ��������
extern my_map* uno_oper_map = create_uno_oper_map(); //�������� ���������� ������� ��������
extern my_map* const_map = create_const_map(); //�������� ���������� ������� ��������
extern my_map* bin_oper_iden = create_bin_oper_identity(); //�������� ���������� ���������� ��������������� �������� ��������
extern my_map* uno_oper_iden = create_uno_oper_identity(); //�������� ���������� ���������� ��������������� ������� ��������


using namespace std;

//���������� ������� � ����������
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//��������� ������� ��������
string expr_elem::get_status() {
	return status;
}
//��������� ���������� ��������
string expr_elem::get_content() {
	return content;
}
//��������� ��������� ���������
vector <expr_elem>* first_oper_expr(string* input) {
	vector <expr_elem>* expr = new vector <expr_elem>; //�������� ���������
	string flag = "operator"; //����
	for (size_t i = 0; i < input->size(); i++) { //���� �� �������� ������� ������
		if (isdigit(input->at(i)) || input->at(i) == '.') { //���� ������� ������ ����� ��� �����
			if (i == 0) { //���� ������� ������ ������
				expr->push_back(expr_elem(input->substr(i, 1), "operand")); //��������� ������� � ���������
				flag = "operand"; //������ �������� �����
			}
			else {
				if (flag != "operand") { //���� ���������� ������� - �� �������
					expr->push_back(expr_elem(input->substr(i, 1), "operand")); //��������� ������� � ���������
					flag = "operand"; //������ �������� �����
				}
				else {
					expr->back().content.push_back(input->at(i)); //��������� ������� ������ � �������� ��������
				}
			}
		}
		else {
			if (bin_oper_map->is_elem(input->substr(i, 1)) || uno_oper_map->is_elem(input->substr(i, 1))) { //������� ������� ��������
				expr->push_back(expr_elem(input->substr(i, 1), "operator")); //��������� ������� � ���������
				flag = "operator"; //������ �������� �����
			}
			else {
				if (isalpha(input->at(i))) { //���� ������� ������ - �����
					if (i == 0) { //���� ������� ������ ������
						expr->push_back(expr_elem(input->substr(i, 1), "word")); //��������� ������� � ���������
						flag = "word"; //������ �������� �����
					}
					else {
						if (/*dig */flag == "operand" || flag == "operator") { //���� ���������� ������� - ������� ��� ��������
							expr->push_back(expr_elem(input->substr(i, 1), "word")); //��������� ������� � ���������
							flag = "word"; //������ �������� �����
						}
						else {
							expr->back().content.push_back(input->at(i)); //��������� ������� ������ � �������� ��������
						}
					}
				}
				else {
					if (input->at(i) != ' ' && input->at(i) != '\t') {//���� �� ������ � �� ��������� 
						string error = "Entered is not a valid symbol: ";
						error.push_back(input->at(i));
						throw error; //������ ���������� � ������������ �������
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
//��������� ��������� ���������� ���������
void second_oper_expr(vector <expr_elem>* expr) {
	for (size_t i = 0; i < expr->size(); i++) { //���� �� ��������� ���������
		if (expr->at(i).get_status() != "operand") { //���� ������� ������� - �������
			if (bin_oper_map->is_elem(expr->at(i).get_content())) { //���� ������� ������� - �������� ��������
				expr->at(i).status = "binary operator"; //������������� � �������, ��� �������� ��������
			}
			else {
				if (uno_oper_map->is_elem(expr->at(i).get_content())) { //���� ������� ������� - ������� ��������
					expr->at(i).status = "unary operator"; //������������� � �������, ��� ������� ��������
				}
				else {
					if (const_map->is_elem(expr->at(i).get_content())) { //���� ������� ������� - ���������
						expr->at(i).status = "const operand"; //������������� � �������, ��� ���������
					}
					else {
						string error = "Introduced unknown element: ";
						error.compare(expr->at(i).get_content());
						throw error; //������ ���������� �� ������� ������������� ����������, ��� �������� �������
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
//�������������� �� ��������� � �����������
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix) {
	vector <expr_elem>* postfix = new vector <expr_elem>; //�������� ������������ ���������
	my_stack* stack = new my_stack; //�������� �����
	//vector <expr_elem>::iterator iter = infix->begin(); //�������� ��������� �� ���������
	for (size_t i = 0; i < infix->size(); i++) { //���� �� ��������� ���������
		if (infix->at(i).get_status() == "operand" || infix->at(i).get_status() == "const operand" || infix->at(i).get_status() == "unary operator" && uno_oper_map->get_elem(infix->at(i).get_content()) == POST) { //���� ������� ������� - ������� ��� ����������� ������� ��������
			postfix->push_back(infix->at(i)); //��������� ������� � ����������� ���������
		}
		else {
			if (infix->at(i).get_status() == "unary operator" && uno_oper_map->get_elem(infix->at(i).get_content()) == PREF) { //���� ������� �������� - ������� ���������� ��������
				stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //���������� �������� � ����
			}
			else {
				if (infix->at(i).get_content() == "(") { //���� ������� ������� - ����������� ������
					stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //���������� �������� � ����
				}
				else {
					if (infix->at(i).get_content() == ")") { //���� ������� ������� - ����������� ������
						while (stack->get_head()->get_content()->get_content() != "(" && !stack->empty()) { //���� ������� ������� ����� - �� ����������� ������ � ���� �� ��������
							postfix->push_back(*stack->get_head()->get_content()); //��������� ������� ������� ����� � ����������� ���������
							stack->pop(); //������� ������� �� �����
							if (stack->empty() || stack->get_head()->get_content()->get_content() == ")") { //���� ��������� ������� ����� - ���������� ��� ������� ������� - ����������� ������
								throw string("Incorrect expression! It can't be convert in postfix form correctly!");
							}
						}
						stack->pop(); //������� ������ �� �����
						//iter++;
					}
					else {
						if (infix->at(i).get_status() == "binary operator") { // ���� ������� - �������� ��������
							while (!stack->empty() && (stack->get_head()->get_content()->get_status() == "unary operator" && uno_oper_map->get_elem(stack->get_head()->get_content()->get_content()) == PREF || stack->get_head()->get_content()->get_status() == "binary operator" && bin_oper_map->get_elem(infix->at(i).get_content()) <= bin_oper_map->get_elem(stack->get_head()->get_content()->get_content()))) {
								/*���� ���� �� ���� � (���� ������� ������� ����� - ���������� ������� ��� �������� �� ������� ����� ������������ ���� �������� ��� �������� �� ������� ����� � ����� �� �����������, ��� � ����) ? ? */
								postfix->push_back(*stack->get_head()->get_content()); //��������� ������� ������� ����� � ����������� ���������
								stack->pop(); //������� ������� �� �����
							}
							stack->push(new stack_elem(new expr_elem(infix->at(i).get_content(), infix->at(i).get_status()))); //�������� �������� � ����
						}
					}
				}
			}
		}
	}
	while (!stack->empty()) { //��������� � ��������� ���������� � ����� ��������
		postfix->push_back(*stack->get_head()->get_content()); //��������� ������� ������� ����� � ����������� ���������
		stack->pop(); //������� ������� �� �����
	}
	for (size_t i = 0; i < postfix->size(); i++) {
		cout << postfix->at(i).get_content();
	}
	cout << endl;
	delete stack;
	delete infix;
	return postfix;
}
//���������� ������������ ��������� �� �����
double calc(vector <expr_elem>* expr) {
	my_stack* stack = new my_stack; //�������� �����
	//vector <expr_elem>::iterator iter = expr->begin(); //�������� ��������� �� ���������
	string temp;
	for (size_t i = 0; i < expr->size(); i++) { //���� �� ��������� ���������
		if (expr->at(i).get_status() == "operand" || expr->at(i).get_status() == "const operand") { //���� ������� ������� - �������
			stack->push(new stack_elem(new expr_elem(expr->at(i).get_content(), expr->at(i).get_status()))); //���������� �������� � ����
		}
		else {
			if (expr->at(i).get_content() == "-") { //���� ������� ������� - �����
				if (!stack->empty() && (stack->get_head()->get_content()->get_status() == "operand" || stack->get_head()->get_content()->get_status() == "const operand")) { //���� ���� �� ���� � �� ������� ��� �������
					if (stack->get_head()->get_next() != nullptr && (stack->get_head()->get_next()->get_content()->get_status() == "operand" || stack->get_head()->get_next()->get_content()->get_status() == "const operand")) { //���� ���� ����� ����� ������ �������� � ������ ���� �������� ���������
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
				if (expr->at(i).get_status() == "binary operator") { //���� ���� ����� ����� ������ �������� � ������ ���� �������� ���������
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
//���������� ����� �������� ��������
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
//���������� ����� ������� ��������
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