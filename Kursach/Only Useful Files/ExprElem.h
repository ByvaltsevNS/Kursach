#pragma once
//#include <string>
#include <vector>
#include "Stack.h"
#include "Map.h"

const int PREF = 1; //Префиксный
const int POST = 2; //Постфиксный

enum ufdyj { dig = 0, hui = 1 };

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
	friend vector <expr_elem>* first_oper_expr(string* input); //Первичная обработка выражения
	friend void second_oper_expr(vector <expr_elem>* input);//Вторичная обработка инфиксного выражения
};
vector <expr_elem>* first_oper_expr(string* input); //Первичная обработка выражения
void second_oper_expr(vector <expr_elem>* input);//Вторичная обработка инфиксного выражения
vector <expr_elem>* infix_postfix(vector <expr_elem>* infix);//Преобразование из инфиксной в потсфиксную
double calc(vector <expr_elem>* expr); //Вычисление постфискного выражения на стэке
string one_oper_bin(string operand1, string operand2, string operation); //Вычисление одной бинарной операции
string one_oper_uno(string operand, string operation); //Вычисление одной унарной операции