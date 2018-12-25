#pragma once
#include <string>

using namespace std;

class expr_elem {
private:
	bool operand; //������� ��� ��������
	string content; //����������
	bool binar; //�������� - �������

public:
	//����������� ������
	expr_elem(string str, bool dig) : content(str), operand(dig) {};
	friend size_t proc_expr(string* input, vector <expr_elem>* expr);
	void add(char ch); //���������� ������� � ����������
	string get_content();
	bool get_operand();
	bool get_binar();
	void set_binar(bool flag);
	void set_operand(bool flag);
	friend void fix_infix(vector <expr_elem>* expr);
};
