#pragma once
#include <string>
#include "ExprElem.h"
#include "Stack_Elem.h"
class stack_elem;

using namespace std;

//Класс стэка
class my_stack {
private:
	stack_elem* head; //Указатель на верхний элемент стэка
	size_t size; //Количество элементов
public:
	//friend stack_elem; //Дружит с классом элемент стэка
	my_stack() : head(nullptr) {}; //Конструктор стэка
	string top(); //Показывает верхний элемент в стэке
	void pop(); //Удаляет верхний элемент из стэка
	bool empty(); //Показывает пуст ли стэк
	void push(stack_elem* node); //Добавляет элемент в стэк
	stack_elem* get_head(); //Получение вершины стэка
	size_t get_size(); //Получение размера стэка
};