#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <stack>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ExprElems.h"

const int PREF = 1; //����������
const int POST = 2; //�����������
const int BRACK = 0; //���������� ������

using namespace std;
//��������� �������� ��������
map <string, int> bin_oper = { {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"(", 0}, {")", 0}, {"^", 3} };
//��������� ������� ��������
map <string, int> unar_oper = { {"-", PREF}, {"[", BRACK}, {"]", BRACK}, {"sin", PREF}, {"cos", PREF}, {"tg", PREF}, {"ctg", PREF}, {"!", POST}, {"ln", PREF}, {"log", PREF}, {"sqrt", PREF} };
//��������� ��������
map <string, double> num_const = { {"e", M_E}, {"pi", M_PI} };
//��������� ������
map <string, int> brackets = { {"[", BRACK}, {"]", BRACK}, {"(", BRACK}, {")", BRACK} };
//��������� ��������� 
size_t proc_expr(string* input, vector <expr_elem>* expr) {
	//map < string, int>::iterator it;
	//vector <string>::iterator iter;
	//map <string, bool> post_expr;
	size_t sym_iter = 0, elem_iter = 0; //��������� ��������� � ��������� ������������ ���������
	//expr->push_back("");
	bool dig = false; //����� ��� ���
	for (size_t i = 0; i < input->size(); i++) { //���� �� �������� �������� ���������
		if (isdigit(input->at(i)) || input->at(i) == '.') { //���� ��� �����
			//iter->push_back(input->at(sym_iter++));
			if (!dig) { //���� ���������� ������ �� �����
				dig = true; //�����
				expr->push_back(expr_elem("", dig)); //���������� �������� � ����������
				if (i != 0) //���� �� ������ ������
					elem_iter++;
				//post_expr.insert({ "", dig });
			}
			(*expr)[elem_iter].add(input->at(i)); //���������� ������� � ����������� ��������
		}
		else {
			//it = bin_oper.find(input->substr(sym_iter, 1));
			//if (/*it*/bin_oper.find(input->substr(i, 1)) != bin_oper.end()) { //���� ��� �������� ��������
				//expr->push_back(input->substr(i, 1));
			if (dig) //���� ���������� ������ �����
			{
				dig = false;
				expr->push_back(expr_elem(input->substr(i, 1), dig)); //���������� ��������� � ���������
				if (i != 0) //���� �� ������ ������
					elem_iter++;
			}
			else {
				dig = false; //�� �����
				if (i == 0) //���� ������ ������
					expr->push_back(expr_elem(input->substr(i, 1), dig)); //���������� ��������� � ���������
				else {
					if (isalpha(input->at(i)) && isalpha(input->at(i - 1))) //���� ������� � ���������� ������� -�����
						(*expr)[elem_iter].add(input->at(i)); //���������� ������� � ���������� ��������
					else {
						expr->push_back(expr_elem(input->substr(i, 1), dig)); //���������� ��������� � ���������
						elem_iter++;
					}
				}
			}
			 /*}*/
		}
	}
	for (size_t i = 0; i < expr->size(); i++) //����� ���������
		if (expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //����� ����������
		if (!expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //����� ��������� � ��������� �����
		cout << expr->at(i).get_content() << " ";
	cout << endl;
	return 0;
}
//���������� "���������" �� ���������, �������� � ������� ���������
void fix_infix(vector <expr_elem>* expr) {
	for (size_t i = 0; i < expr->size(); i++) {
		if (!(*expr)[i].get_operand()) { //���� "��������"
			if (num_const.find(expr->at(i).get_content()) != num_const.end()) //���� "���������"
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
	for (size_t i = 0; i < expr->size(); i++) //����� ���������
		if (expr->at(i).get_operand())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //����� �������� ����������
		if (!expr->at(i).get_operand() && expr->at(i).get_binar())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
	for (size_t i = 0; i < expr->size(); i++) //����� ������� ����������
		if (!expr->at(i).get_operand() && !expr->at(i).get_binar())
			cout << expr->at(i).get_content() << " ";
	cout << endl;
}
//�������������� �� ��������� � ����������� �����
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix) {
	vector <expr_elem>* postfix = new vector <expr_elem>;
	stack <expr_elem> * mystack = new stack <expr_elem>;
	for (size_t i = 0; i < infix->size(); i++) {
		expr_elem temp((*infix)[i].get_content(), (*infix)[i].get_operand()); //������� �������
		if (temp.get_operand() || !temp.get_binar()) //���� ������ ��� ����������� ��������
			postfix->push_back(temp); //���������� �������� � ����������� ���������
		else {
			if (temp.get_content() == "(") //���� ������� ����������� ������� ������
				mystack->push(temp); //���������� � ����
			else {
				if (temp.get_content() == ")") { //���� ������� ����������� ������� ������
					while (mystack->top().get_content() != "(") { //���� �� ����������� ������� ������
						bool close_brack = false;
						if (mystack->empty() || mystack->top().get_content() == "[" && !close_brack) { //���� ���� ������ ��� ������� ������� ���������� ������
							try {
								throw (infix->at(i).get_content());
							}
							catch (string str) {
								cout << "Entered the expression incorrect! Possible error: " << str << endl;
								return;
							}
						}
						if (mystack->top().get_content() == "]") //���� ���� ����������� ������
							close_brack = true;
						postfix->push_back(mystack->top()); //���������� �������� �� ����� � ����������� ���������
						mystack->pop(); //�������� �������� �� �����
					}
					mystack->pop(); //�������� ����������� ������� ������ �� �����
				}
				else {
					while (!mystack->empty() && bin_oper[temp.get_content()] <= bin_oper[mystack->top().get_content()]) { //���� ��������� �������� ������, ��� ������� � ���� �� ����
						postfix->push_back(mystack->top()); //���������� �������� � ����������� ���������
						mystack->pop(); //�������� �������� �� �����
					}
					if (mystack->empty() || bin_oper[temp.get_content()] > bin_oper[mystack->top().get_content()]) //���� ���� ����-
						mystack->push(temp); //���������� �������� � ����
				}
			}
		}
	}
	while (!mystack->empty()) { //���� ���� �� ����
		if (bin_oper[mystack->top().get_content()] == BRACK) {//���� �������� ������� ������
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
		postfix->push_back(mystack->top()); //���������� �������� � ����������� ���������
		mystack->pop(); //�������� �������� �� �����
	}
	for (size_t i = 0; i < postfix->size(); i++) //����� ������������ ���������
		cout << postfix->at(i).get_content();
	cout << endl;
	return postfix;
}
//���������� ����������
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
//���������� ������� � ���������� ��������
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//���������� ��������
string expr_elem::get_content() {
	return content;
}
//������� ��� ��������
bool expr_elem::get_operand() {
	return operand;
}
//��������� ���������� �������� ��� �������
void expr_elem::set_binar(bool flag) {
	binar = flag;
}
//��������� ��������� �������� ��� �������
void expr_elem::set_operand(bool flag) {
	operand = flag;
}
//�������� ��� �������
bool expr_elem::get_binar() {
	return binar;
}