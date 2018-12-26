#pragma once
//#include <string>
#include "ExprElem.h"
class my_map;
using namespace std;

//����� �������� ����������
class map_elem {
private:
	string key; //���� �������� ����������
	int content; //���������� ��������
	map_elem* next; //��������� �� ��������� ������� � ����������
public:
	friend my_map; //������ � �����������
	map_elem(string str, int var); //����������� �������� ����������
	~map_elem(); //���������� �������� ����������
	int get_content(); //��������� ���������� ��������
};
//����� ���������� Map
class my_map {
private:
	map_elem* head; //��������� �� ������ ����������
public:
	my_map() : head(nullptr) {}; //����������� ����������
	~my_map(); //���������� ����������
	bool is_elem(string str); //�������� ������� ��������
	int get_elem(string str); //��������� �������� �� �����
	void push(map_elem* node); //���������� �������� � ���������
	map_elem* get_head(); //��������� ������� �������� ����������
};
my_map* create_bin_oper_map(); //�������� ���������� �������� ��������
my_map* create_uno_oper_map(); //�������� ���������� ������� ��������
my_map* create_const_map(); //�������� ���������� ��������
my_map* create_bin_oper_identity(); //�������� ���������� ���������� ��������������� �������� ��������
my_map* create_uno_oper_identity();//�������� ���������� ���������� ��������������� ������� ��������