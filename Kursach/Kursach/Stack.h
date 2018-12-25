#pragma once
#include <string>
#include "ExprElem.h"
#include "Stack_Elem.h"
class stack_elem;

using namespace std;

//����� �����
class my_stack {
private:
	stack_elem* head;//��������� �� ������� ������� �����
public:
	//friend stack_elem; //������ � ������� ������� �����
	my_stack() : head(nullptr) {}; //����������� �����
	string top(); //���������� ������� ������� � �����
	void pop(); //������� ������� ������� �� �����
	bool empty(); //���������� ���� �� ����
	void push(stack_elem* node); //��������� ������� � ����
	stack_elem* get_head(); //��������� ������� �����
};