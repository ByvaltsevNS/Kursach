#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "ExprElem.h"
using namespace std;

int main() {
	string* input_expr = new string; //�������� �������� ���������
	vector <expr_elem>* expr; //�������� ���������
	//bool to_continue; //���������� �� ������ ���������
	string answer; //����� ������������
	cout << "You are in the program \"Postfix calculator\"!" << endl;
	/*do {*/
		cout << "Enter your expression in the record's infix form: ";
		getline(cin, *input_expr); //���������� �������� ���������
		try {
			expr = first_oper_expr(input_expr); //��������� ��������� ���������
			second_oper_expr(expr); //��������� ��������� ���������
			vector <expr_elem>* post_expr = infix_postfix(expr); //�������������� ��������� � ����������� �����
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