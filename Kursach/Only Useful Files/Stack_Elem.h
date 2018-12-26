#pragma once
#include "Stack.h"
class my_stack;
class expr_elem;

//Класс элемента стэка
class stack_elem {
private:
	expr_elem* content; //Содержание элемента
	stack_elem* next; //Указатель на следующий элемент в стэке
public:
	friend my_stack; //Дружит со стэком
	stack_elem(expr_elem* var) : content(var), next(nullptr) {}; //Конструктор элемента стэка
	~stack_elem(); //Деструктор элемента стэка
	expr_elem* get_content(); //Получение содержания элемента стэка
	stack_elem* get_next(); //Получение указателя на следующий элемент
};