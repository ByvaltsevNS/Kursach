#pragma once
#include <string>
#include "ExprElem.h"
#include "Stack_Elem.h"
class stack_elem;

using namespace std;

//����� �����
class my_stack {
private:
	stack_elem* head; //��������� �� ������� ������� �����
	size_t size; //���������� ���������
public:
	//friend stack_elem; //������ � ������� ������� �����
	my_stack() : head(nullptr) {}; //����������� �����
	string top(); //���������� ������� ������� � �����
	void pop(); //������� ������� ������� �� �����
	bool empty(); //���������� ���� �� ����
	void push(stack_elem* node); //��������� ������� � ����
	stack_elem* get_head(); //��������� ������� �����
	size_t get_size(); //��������� ������� �����
};