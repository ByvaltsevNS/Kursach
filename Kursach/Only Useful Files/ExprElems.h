#pragma once
#include <string>

using namespace std;

class expr_elem {
private:
	bool operand; //Операнд или оператор
	string content; //Содержание
	bool binar; //Бинарный - унарный

public:
	//Конструктор класса
	expr_elem(string str, bool dig) : content(str), operand(dig) {};
	friend size_t proc_expr(string* input, vector <expr_elem>* expr);
	void add(char ch); //Добавление символа в содержание
	string get_content();
	bool get_operand();
	bool get_binar();
	void set_binar(bool flag);
	void set_operand(bool flag);
	friend void fix_infix(vector <expr_elem>* expr);
};
