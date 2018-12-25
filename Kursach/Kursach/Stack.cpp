#include "Stack.h"
#include "Stack_Elem.h"

//Деструктор элемента стэка
stack_elem::~stack_elem() {
	content = nullptr;
	next = nullptr;
}
//Получение содержания элемента стэка
expr_elem* stack_elem::get_content() {
	return content;
}
//Получение вершины стэка
stack_elem* my_stack::get_head() {
	return head;
}
//Добавляет элемент в стэк
void my_stack::push(stack_elem* node) {
	node->next = head;
	head = node;
}
//Удаляет верхний элемент из стэка
void my_stack::pop() {
	if (empty())
		throw out_of_range("Is empty!");
	else {
		stack_elem* temp = head;
		head = head->next;
		temp = nullptr;
	}
}
//Показывает пуст ли стэк
bool my_stack::empty() {
	return head == nullptr;
}
