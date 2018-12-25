#include "Stack.h"
#include "Stack_Elem.h"

//���������� �������� �����
stack_elem::~stack_elem() {
	content = nullptr;
	next = nullptr;
}
//��������� ���������� �������� �����
expr_elem* stack_elem::get_content() {
	return content;
}
//��������� ������� �����
stack_elem* my_stack::get_head() {
	return head;
}
//��������� ������� � ����
void my_stack::push(stack_elem* node) {
	node->next = head;
	head = node;
}
//������� ������� ������� �� �����
void my_stack::pop() {
	if (empty())
		throw out_of_range("Is empty!");
	else {
		stack_elem* temp = head;
		head = head->next;
		temp = nullptr;
	}
}
//���������� ���� �� ����
bool my_stack::empty() {
	return head == nullptr;
}
