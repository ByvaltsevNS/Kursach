#pragma once
#include <string>
#include "Stack.h"

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
};