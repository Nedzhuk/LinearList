#include <stdio.h>
#include <malloc.h>

struct ListStruct
{
	int data;
	struct ListStruct* next;
};
typedef struct ListStruct Element;
typedef Element* List;


int razm = 10;

List deleteOne(List list, int position, int razm)
{
	List listElements = list, tmp = NULL;
	int count = 0;
	if (position == 1)
	{
		List listElements2 = list->next;
		tmp = listElements2;
		list = tmp;
	}
	else if (razm == position)
	{
		while (count < position - 1)
		{
			tmp = listElements;
			listElements = listElements->next;
			count++;
		}
		tmp->next = listElements->next;
	}
	else {
		while (count < position - 1)
		{
			tmp = listElements;
			listElements = listElements->next;
			count++;
		}
		listElements->next = listElements->next;

		tmp->next = listElements->next;
	}

	free(listElements);

	return list;
}

List deleteAll(List list)
{
	while (list)
	{
		List lastlist = list;
		list = list->next;
		free(lastlist);
	}
	return list;
}
List addOne(List list, int position, int element)
{
	List listok = list, tmp = NULL;
	List dd = calloc(2, sizeof(int));
	int count = 0;

	if (position == 0)
	{
		dd->data = element;
		dd->next = listok;
		tmp = dd;
		list = tmp;
	}
	else
	{
		while (listok)
		{
			if (count == position)
			{
				List p = calloc(1, sizeof(int));
				p->data = element;
				p->next = listok;
				tmp->next = p;
				break;
			}
			tmp = listok;
			listok = listok->next;
			count++;
		}
	}

	return list;
}

List replacing(List list, int position1, int position2)
{
	List prev1 = NULL, prev2 = NULL, next1 = NULL, next2 = NULL, elem1 = NULL, elem2 = NULL;
	List tmp = list;
	prev1 = list;
	prev2 = list;

	int count = 1;
	if (position1<1 || position2<1 || position1>razm || position2>razm)
	{
		printf("\nВведены неверные позиции");
		return 0;
	}
	else 
	{
		if (position1 == position2)
			return list;
		else
		{
			if (position1 + 1 == position2 || position2 + 1 == position1) //проверка на соседние элементы
			{
				if (position1 == 1 || position2 == 1)
				{
					elem1 = prev1;
					elem2 = prev1->next;
					next2 = elem2->next;

					prev1 = elem2;
					prev1->next = elem1;
					prev1->next->next = next2;
					return prev1;
				}
				if (position1 == razm)
				{
					while (count != position2 - 1)
					{
						prev2 = prev2->next;
						count++;
					}
					elem2 = prev2->next;
					elem1 = elem2->next;
					next2 = elem1->next;
					prev2->next = elem1;
					prev2 = prev2->next;
					prev2->next = elem2;
					prev2->next->next = next2;
					return list;
				}
				else
				{
					if (position1 < position2)
					{
						while (count != position1 - 1) //поиск элементов, предшествующих обмениваемым
						{
							prev1 = prev1->next;
							count++;
						}
						count = 1;
						elem1 = prev1->next;
						elem2 = elem1->next;
						next2 = elem2->next;
						prev1->next = elem2;
						prev1 = prev1->next;
						prev1->next = elem1;
						prev1 = prev1->next;
						prev1->next = next2;
					}
					else
					{
						while (count != position2 - 1) //поиск элементов, предшествующих обмениваемым
						{
							prev1 = prev1->next;
							count++;
						}
						count = 1;
						elem2 = prev1->next;
						elem1 = elem2->next;
						next1 = elem1->next;
						prev1->next = elem1;
						prev1 = prev1->next;
						prev1->next = elem2;
						prev1 = prev1->next;
						prev1->next = next1;

					}
					return list;
				}
			}
			else
			{
				if (position1 == 1)
				{
					elem1 = prev1;
					next1 = elem1->next;
				}
				else if (position1 == razm)
				{
					while (count != razm - 1)
					{
						prev1 = prev1->next;
						count++;
					}
					count = 1;
					elem1 = prev1->next;
					next1 = NULL;
				}
				else
				{
					while (count != position1 - 1) //поиск элемента, предшествующего обмениваемому первому
					{
						prev1 = prev1->next;
						count++;
					}
					count = 1;
					elem1 = prev1->next; //определение обмениваемого 1 элемента
					next1 = elem1->next; //элемент после 1 элемента
				}

				if (position2 == 1)
				{
					elem2 = prev2;
					next2 = elem2->next;
				}
				else if (position2 == razm)
				{
					while (count != razm - 1)
					{
						prev2 = prev2->next;
						count++;
					}
					count = 1;
					elem2 = prev2->next;
					next2 = NULL;
				}
				else
				{
					while (count != position2 - 1)
					{
						prev2 = prev2->next;
						count++;
					}
					count = 1;
					elem2 = prev2->next;
					next2 = elem2->next;
				}

				if (prev1 != list)
					prev1->next = elem2; //обмен указателей (после предшевтвующего 1 элемента идет обмениваемый 2 элемент, а после него последующий от 1 элемента, и наоборот)
				else prev1 = elem2;
				if (prev2 != NULL)
					prev2->next = elem1;
				else prev2 = elem1;
				elem1->next = next2;
				elem2->next = next1;

				if (position1 == 1)
					return elem2;
				else if (position2 == 1)
					return elem1;
				else
					return list;
			}
		}
	}
}

List input(int count)
{
	List head = calloc(1, sizeof(Element));
	head->data = 1;
	head->next = NULL;
	List list = head, next;
	for (size_t i = 1; i < count; i++)
	{
		next = calloc(1, sizeof(Element));
		list->next = next;
		next->data = i + 1;
		list = next;
	}
	list->next = NULL;

	return head;
}
void output(List list)
{
	List listElementssss = list;
	while (listElementssss)
	{
		printf("%d ", listElementssss->data);
		listElementssss = listElementssss->next;
	}
	printf(".\n");
}

int main()
{
	system("chcp 1251 > null");
	List list = input(razm);
	printf("Лист из %d элементов: ", razm);
	output(list);//вывод работает
	list = input(razm);
	printf("---------------------------------");

	printf("\nУдаление 1 элемента: ");
	output(deleteOne(list, 1, razm));
	list = input(razm);

	printf("\nУдаление последнего элемента: ");
	output(deleteOne(list, razm, razm));
	list = input(razm);

	printf("\nУдаление 4 элемента: ");
	output(deleteOne(list, 4, razm));
	list = input(razm);
	printf("---------------------------------");

	printf("\nУдаление всего листа: ");
	output(deleteAll(list));
	list = input(razm);
	printf("---------------------------------");

	printf("\nДобавление 1 элемента: ");
	output(addOne(list, 0, 50));// 1 число позиция, т.е. от 0 до 9
	list = input(razm);

	printf("\nДобавление 10 элемента: ");
	output(addOne(list, 9, 50));// 1 число позиция, т.е. от 0 до 9
	list = input(razm);


	printf("\nДобавление 3 элемента: ");
	output(addOne(list, 2, 50));// 1 число позиция, т.е. от 0 до 9
	list = input(razm);
	printf("---------------------------------");

	printf("\nОбмен 4 и 7 элемента: ");
	output(replacing(list, 4, 7));
	list = input(razm);

	printf("\nОбмен 7 и 4 элемента: ");
	output(replacing(list, 7, 4));
	list = input(razm);

	printf("\nОбмен 1 и 5 элемента: ");
	output(replacing(list, 1, 5));
	list = input(razm);

	printf("\nОбмен 5 и 1 элемента: ");
	output(replacing(list, 5, 1));
	list = input(razm);

	printf("\nОбмен 6 и 10 элемента: ");
	output(replacing(list, 6, 10));
	list = input(razm);

	 printf("\nОбмен 10 и 6 элемента: ");
	output(replacing(list, 10, 6));
	list = input(razm);

	 printf("\nОбмен 1 и 10 элемента: ");
	output(replacing(list, 1, 10));
	list = input(razm);

	 printf("\nОбмен 10 и 1 элемента: ");
	output(replacing(list, 10, 1));
	list = input(razm);

	 printf("\nОбмен 3 и 4 элемента: ");
	output(replacing(list, 3, 4));
	list = input(razm);

	 printf("\nОбмен 4 и 3 элемента: ");
	output(replacing(list, 4, 3));
	list = input(razm);

	 printf("\nОбмен 1 и 2 элемента: ");
	output(replacing(list, 1, 2));
	list = input(razm);

	printf("\nОбмен 2 и 1 элемента: ");
	output(replacing(list, 2, 1));
	list = input(razm);

	 printf("\nОбмен 10 и 9 элемента: ");
	output(replacing(list, 10, 9));
	list = input(razm);

	 printf("\nОбмен 9 и 10 элемента: ");
	output(replacing(list, 9, 10));
	list = input(razm);

	printf("\nОбмен 1 и 1 элемента: ");
	output(replacing(list, 1, 1));
	list = input(razm);

	printf("\nОбмен 0 и 11 элемента: ");
	output(replacing(list, 0, 11));
	list = input(razm);

	return 0;
}