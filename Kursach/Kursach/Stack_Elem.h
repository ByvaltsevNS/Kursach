#pragma once
#include "Stack.h"
class my_stack;
class expr_elem;

//����� �������� �����
class stack_elem {
private:
	expr_elem* content; //���������� ��������
	stack_elem* next; //��������� �� ��������� ������� � �����
public:
	friend my_stack; //������ �� ������
	stack_elem(expr_elem* var) : content(var), next(nullptr) {}; //����������� �������� �����
	~stack_elem(); //���������� �������� �����
	expr_elem* get_content(); //��������� ���������� �������� �����
	stack_elem* get_next(); //��������� ��������� �� ��������� �������
};