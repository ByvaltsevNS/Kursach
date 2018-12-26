#pragma once
//#include <string>
#include <vector>
#include "Stack.h"
#include "Map.h"

const int PREF = 1; //����������
const int POST = 2; //�����������

enum ufdyj { dig = 0, hui = 1 };

using namespace std;

//������� ���������
class expr_elem {
private:
	string status; //���� �������� - �� �����, ���� ������� - �� ���������, ����� ��� �� ����������
	string content; //����������
public:
	//friend stack_elem; //������ � ��������� �����
	expr_elem(string var1, string var2) : content(var1), status(var2) {}; //���������� �������� ���������
	void add(char ch); //���������� ������� � ����������
	string get_status(); //��������� ������� ��������
	string get_content(); //��������� ���������� ��������
	friend vector <expr_elem>* first_oper_expr(string* input); //��������� ��������� ���������
	friend void second_oper_expr(vector <expr_elem>* input);//��������� ��������� ���������� ���������
};
vector <expr_elem>* first_oper_expr(string* input); //��������� ��������� ���������
void second_oper_expr(vector <expr_elem>* input);//��������� ��������� ���������� ���������
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix);//�������������� �� ��������� � �����������
double calc(vector <expr_elem>* expr); //���������� ������������ ��������� �� �����
string one_oper_bin(string operand1, string operand2, string operation); //���������� ����� �������� ��������
string one_oper_uno(string operand, string operation); //���������� ����� ������� ��������