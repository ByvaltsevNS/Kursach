#include <string>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ExprElem.h"
#include "Stack.h"
#include "Map.h"

using namespace std;

//Добавление символа к содержанию
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//Получение статуса элемента
string expr_elem::get_status() {
	return status;
}
//Получение содержания элемента
string expr_elem::get_content() {
	return content;
}