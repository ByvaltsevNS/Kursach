#pragma once
//#include <string>
#include "ExprElem.h"
class my_map;
using namespace std;

//Класс элемента контейнера
class map_elem {
private:
	string key; //Ключ элемента контейнера
	int content; //Содержание элемента
	map_elem* next; //Указатель на следующий элемент в контейнере
public:
	friend my_map; //Дружит с контейнером
	map_elem(string str, int var); //Конструктор элемента контейнера
	~map_elem(); //Деструктор элемента контейнера
	int get_content(); //Получение содержания элемента
};
//Класс контейнера Map
class my_map {
private:
	map_elem* head; //Указатель на начало контейнера
public:
	my_map() : head(nullptr) {}; //Конструктор контейнера
	~my_map(); //Деструктор контейнера
	bool is_elem(string str); //Проверка наличия элемента
	int get_elem(string str); //Получение элемента по ключу
	void push(map_elem* node); //Добавление элемента в контейнер
	map_elem* get_head(); //Получение первого элемента контейнера
};
my_map* create_bin_oper_map(); //Создание контейнера бинарных операций
my_map* create_uno_oper_map(); //Создание контейнера унарных операций
my_map* create_const_map(); //Создание контейнера констант
my_map* create_bin_oper_identity(); //Создание контейнера уникальных идентификаторов бинарных операций
my_map* create_uno_oper_identity();//Создание контейнера уникальных идентификаторов унарных операций