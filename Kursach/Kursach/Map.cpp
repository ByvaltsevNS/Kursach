#include "Map.h"

const int PREF = 1; //����������
const int POST = 2; //�����������

//����������� �������� ����������
map_elem::map_elem(string str, int var) {
	key = str;
	content = var;
	next = nullptr;
}
//���������� �������� ����������
map_elem::~map_elem() {
	next = nullptr;
}
//���������� ����������
my_map::~my_map() {
	map_elem* temp = head;
	while (temp != nullptr) {
		map_elem* deleted = temp;
		temp = temp->next;
		delete deleted;
	}
}
//��������� ���������� ����������
int map_elem::get_content() {
	return content;
}
//��������� ������� �������� �����������
map_elem* my_map::get_head() {
	return head;
}
//���������� �������� � ���������
void my_map::push(map_elem* node) {
	node->next = head;
	head = node;
}
//��������� �������� �� �����
int my_map::get_elem(string str) {
	if (is_elem(str)) {
		map_elem* temp = head;
		while (temp != nullptr) {
			if (temp->key == str)
				return temp->content;
			temp = temp->next;
		}
	}
	else
		throw out_of_range("Element is missing!");
}
//�������� ������� ��������
bool my_map::is_elem(string str) {
	map_elem* temp = head;
	while (temp != nullptr) {
		if (temp->key == str)
			return true;
		temp = temp->next;
	}
	return false;
}
//�������� ���������� �������� ��������
my_map* create_bin_oper_map() {
	my_map* map = new my_map();
	map->push(new map_elem("(", 0));
	map->push(new map_elem(")", 0));
	map->push(new map_elem("+", 1));
	map->push(new map_elem("-", 1));
	map->push(new map_elem("*", 2));
	map->push(new map_elem("/", 2));
	map->push(new map_elem("^", 3));
	return map;
}
//�������� ���������� ������� ��������
my_map* create_uno_oper_map() {
	my_map* map = new my_map();
	map->push(new map_elem("sin", PREF));
	map->push(new map_elem("cos", PREF));
	map->push(new map_elem("tg", PREF));
	map->push(new map_elem("ctg", PREF));
	map->push(new map_elem("!", POST));
	map->push(new map_elem("ln", PREF));
	map->push(new map_elem("log", PREF));
	map->push(new map_elem("sqrt", PREF));
	return map;
}
//�������� ���������� ��������
my_map* create_const_map() {
	my_map* map = new my_map();
	map->push(new map_elem("pi", 0));
	map->push(new map_elem("e", 0));
	return map;
}