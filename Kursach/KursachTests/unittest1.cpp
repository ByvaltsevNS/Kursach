#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Kursach/Stack.h"
#include "../Kursach/Map.h"
#include "../Kursach/ExprElem.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KursachTests
{		
	//����� �����
	TEST_CLASS(Stack_Tests)
	{
	public:
		my_stack* stack;
		//�������� �����
		TEST_METHOD_INITIALIZE(create_stack) 
		{
			stack = new my_stack;
		}
		//�������� �����
		TEST_METHOD_CLEANUP(delete_stack) 
		{
			delete stack;
		}
		//���������� �������� � ������ ����
		TEST_METHOD(push_empty_stack)
		{
			stack_elem* added = new stack_elem(new expr_elem("content", "status"));
			stack->push(added);
			Assert::IsTrue(stack->get_head() != nullptr && stack->get_head()->get_content()->get_content() == "content");
			delete added;
		}
		//���������� �������� � �������� ����
		TEST_METHOD(push_not_empty_stack)
		{
			stack->push(new stack_elem(new expr_elem("content1", "status1")));
			stack_elem* temp = stack->get_head();
			stack->push(new stack_elem(new expr_elem("content2", "status2")));
			Assert::AreNotEqual(temp->get_content()->get_content(), stack->get_head()->get_content()->get_content());
			delete temp;
		}
		//�������� �������� �� ��������� �����
		TEST_METHOD(pop_not_empty_stack_test)
		{
			stack->push(new stack_elem(new expr_elem("content1", "status1")));
			stack_elem* temp = stack->get_head();
			stack->push(new stack_elem(new expr_elem("content2", "status2")));
			stack->pop();
			Assert::AreEqual(temp->get_content()->get_content(), stack->get_head()->get_content()->get_content());
			delete temp;
		}
		//�������� �������� �� ������� �����
		TEST_METHOD(pop_empty_stack_test) 
		{
			try
			{
				stack->pop();
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Is empty!", e.what());
			}
		}
		//�������� �� ������� ������� �����
		TEST_METHOD(empty_empty_stack_tets)
		{
			Assert::IsTrue(stack->empty());
		}
		//�������� �� ������� �� ������� �����
		TEST_METHOD(empty_not_empty_stack_tets)
		{
			stack->push(new stack_elem(new expr_elem("content", "status")));
			Assert::IsFalse(stack->empty());
		}
	};
	//����� ����������
	TEST_CLASS(Map_Tests)
	{
	public:
		my_map* map;
		//�������� ����������
		TEST_METHOD_INITIALIZE(create_map)
		{
			map = new my_map();
		}
		//�������� ����������
		TEST_METHOD_CLEANUP(delete_map)
		{
			delete map;
		}
		//�������� ���������� �������� � ������ ���������
		TEST_METHOD(push_empty_map)
		{
			map->push(new map_elem("key", 1));
			Assert::IsTrue(map->get_head() != nullptr && map->get_head()->get_content() == 1);
		}
		//�������� ���������� �������� � �������� ��������
		TEST_METHOD(push_not_empty_map)
		{
			map->push(new map_elem("key1", 1));
			map->push(new map_elem("key2", 2));
			Assert::IsTrue(map->get_head()->get_content() == 2);
		}
		//�������� ������� ���������� ��������
		TEST_METHOD(is_elem_is_test)
		{
			map->push(new map_elem("key", 1));
			Assert::IsTrue(map->is_elem("key"));
		}
		//�������� ������� �������������� ��������
		TEST_METHOD(is_not_elem_is_test) 
		{
			map->push(new map_elem("key", 1));
			Assert::IsFalse(map->is_elem("key1"));
		}
		//�������� ��������� ���������� ��������
		TEST_METHOD(is_elem_get_elem_test)
		{
			map->push(new map_elem("key", 1));
			Assert::IsTrue(map->get_elem("key") == 1);
		}
		//�������� ��������� �������������� ��������
		TEST_METHOD(is_not_elem_get_elem_test)
		{
			try
			{
				map->get_elem("key");
			}
			catch (std::out_of_range e)
			{
				Assert::AreEqual("Element is missing!", e.what());
			}
		}
	};
	//����� ������� ��������� ��������� ���������
	TEST_CLASS(Expr_Elem_Class)
	{
	public:
		string* input;
		vector <expr_elem>*	true_after;
		vector <expr_elem>*	real_after;
		//��������� ������ ��� ������ ��������� ���������
		TEST_METHOD_INITIALIZE(create_exprs)
		{
			input = new string;
			true_after = new vector <expr_elem>;
			real_after = new vector <expr_elem>;
		}
		//������������ ������ �� ��� ���������
		TEST_METHOD_CLEANUP(delete_exprs)
		{
			delete input;
			delete true_after;
			delete real_after;
		}
		//���� ��������� ������� �������
		TEST_METHOD(first_oper_expr_some_test_1)
		{
			*input = "cos(4.5*e)";
			true_after->push_back(expr_elem("cos", "word"));
			true_after->push_back(expr_elem("(", "operator"));
			true_after->push_back(expr_elem("4.5", "operand"));
			true_after->push_back(expr_elem("*", "operator"));
			true_after->push_back(expr_elem("e", "word"));
			true_after->push_back(expr_elem(")", "operator"));
			real_after = first_oper_expr(input);
			string var = "All right!";
			if (true_after->size() != real_after->size())
				var = "size mismatch";
			else {
				for (size_t i = 0; i < real_after->size(); i++)
				{
					if (true_after->at(i).get_content() != real_after->at(i).get_content()) {
						var = "Error in content of ";
						var.append(to_string(i));
						var.append(" elem: ");
						var.append(real_after->at(i).get_content());
						break;
					}
					if (true_after->at(i).get_status() != real_after->at(i).get_status()) {
						var = "Error in status of ";
						var.append(to_string(i));
						var.append(" elem: ");
						var.append(real_after->at(i).get_status());
						break;
					}
				}
			}
			Assert::AreEqual(var, string("All right!"));
		}
	};
}