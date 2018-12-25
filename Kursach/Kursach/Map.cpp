#include "Map.h"

const int PREF = 1; //Префиксный
const int POST = 2; //Постфиксный

//Конструктор элемента контейнера
map_elem::map_elem(string str, int var) {
	key = str;
	content = var;
	next = nullptr;
}
//Деструктор элемента контейнера
map_elem::~map_elem() {
	next = nullptr;
}
//Деструктор контейнера
my_map::~my_map() {
	map_elem* temp = head;
	while (temp != nullptr) {
		map_elem* deleted = temp;
		temp = temp->next;
		delete deleted;
	}
}
//Получение содержания контейнера
int map_elem::get_content() {
	return content;
}
//Получение первого элемента контейнерпа
map_elem* my_map::get_head() {
	return head;
}
//Добавление элемента в контейнер
void my_map::push(map_elem* node) {
	node->next = head;
	head = node;
}
//Получение элемента по ключу
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
//Проверка наличия элемента
bool my_map::is_elem(string str) {
	map_elem* temp = head;
	while (temp != nullptr) {
		if (temp->key == str)
			return true;
		temp = temp->next;
	}
	return false;
}
//Создание контейнера бинарных операций
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
//Создание контейнера унарных операций
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
//Создание контейнера констант
my_map* create_const_map() {
	my_map* map = new my_map();
	map->push(new map_elem("pi", 0));
	map->push(new map_elem("e", 0));
	return map;
}