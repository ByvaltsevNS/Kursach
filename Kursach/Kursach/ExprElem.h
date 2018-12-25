#pragma once
#include <string>
#include "Stack.h"

using namespace std;

//Элемент выражения
class expr_elem {
private:
	string status; //Если оператор - то какой, если операнд - то константа, число или мб переменная
	string content; //Содержание
public:
	//friend stack_elem; //Дружит с элементом стэка
	expr_elem(string var1, string var2) : content(var1), status(var2) {}; //Конструкор элемента выражения
	void add(char ch); //Добавление символа в содержание
	string get_status(); //Получение статуса элемента
	string get_content(); //Получение содержания элемента
};