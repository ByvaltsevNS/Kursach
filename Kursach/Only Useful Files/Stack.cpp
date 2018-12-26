#include "Stack.h"
//#include "Stack_Elem.h"

//���������� �������� �����
stack_elem::~stack_elem() {
	content = nullptr;
	next = nullptr;
}
//��������� ���������� �������� �����
expr_elem* stack_elem::get_content() {
	return content;
}
//��������� ��������� �� ��������� �������
stack_elem* stack_elem::get_next() {
	return next;
}
//��������� ������� �����
stack_elem* my_stack::get_head() {
	return head;
}
//��������� ������� �����
size_t my_stack::get_size() {
	return size;
}
//��������� ������� � ����
void my_stack::push(stack_elem* node) {
	node->next = head;
	head = node;
	size++;
}
//������� ������� ������� �� �����
void my_stack::pop() {
	if (empty())
		throw out_of_range("Is empty!");
	else {
		stack_elem* temp = head;
		head = head->next;
		size--;
		delete temp;
	}
}
//���������� ���� �� ����
bool my_stack::empty() {
	return head == nullptr;
}

