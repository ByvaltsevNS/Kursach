#include <string>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ExprElem.h"
#include "Stack.h"
#include "Map.h"

using namespace std;

//���������� ������� � ����������
void expr_elem::add(char ch) {
	content.push_back(ch);
}
//��������� ������� ��������
string expr_elem::get_status() {
	return status;
}
//��������� ���������� ��������
string expr_elem::get_content() {
	return content;
}