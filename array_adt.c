#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	int *pointer;
	int lenght;
	int last_position;
}ARRAY;

void get_int(int *integer)
{
	char user_input[10];

	fgets(user_input, sizeof(user_input), stdin);
	sscanf(user_input, "%d", integer);
}

void display_pointer(ARRAY array)
{
	int i;

	printf("\n");

	for (i = 0; i <= array.last_position; ++i)
	{
		printf("  %d  ", array.pointer[i]);
		printf("|");
	}
}

bool isEmpty(ARRAY array)
{
	if(array.last_position == (-1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isFull(ARRAY array)
{
	if(array.last_position >= (array.lenght - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSorted(ARRAY *array)
{
	int i;

	for (i = 0; i <= array->last_position; ++i)
	{
		if(array->pointer[i] > array->pointer[i])
		{
			return false;
		}

		return true;
	}
}

void insert_sort(ARRAY *array, int key)
{
	int i;

	i = (array->last_position);

	while(array->pointer[i] > key)
	{
		array->pointer[i + 1] = array->pointer[i];

		--i;
	}

	array->pointer[i + 1] = key;
	++array->last_position;
}

void set(ARRAY *array, int key, int position)
{
	array->pointer[position] = key;
}

int get(ARRAY *array, int position)
{
	return array->pointer[position];
}

void append(ARRAY *array, int key)
{
	array->pointer[array->last_position + 1] = key;
	++array->last_position;
}

void delete_by_position(ARRAY *array, int position)
{
	int i;

	for (i = position; i < array->last_position; ++i)
	{
		array->pointer[i] = array->pointer[i + 1];
	}

	--array->last_position;
}

void insert_on_position(ARRAY *array, int key, int position)
{
	int i;

	for (i = array->last_position; i >= position; --i)
	{
		array->pointer[i + 1] = array->pointer[i];
	}

	array->pointer[position] = key;
	++array->last_position;
}

void initialize_array(ARRAY *array, char **elements)
{
	int qtd_of_elements;
	int i;

	qtd_of_elements = atoi(elements[2]);

	for (i = 0; i < qtd_of_elements; ++i)
	{
		array->pointer[i] = atoi(elements[i + 3]);
	}

	array->last_position = (qtd_of_elements - 1);
}

void create_array(ARRAY *array, int lenght)
{
	array->pointer = (int *)malloc(lenght * sizeof(int));
	
	array->last_position = -1;
	array->lenght = lenght;
}

void swap(ARRAY **array, int source, int destination)
{
	int aux;

	aux = (*array)->pointer[destination];

	(*array)->pointer[destination] = (*array)->pointer[source];
	(*array)->pointer[source] = aux;
}

void transposition(ARRAY *array, int position)
{
	swap(&array, position, (position - 1));
}

void move_to_head(ARRAY *array, int position)
{
	swap(&array, position, 0);
}

int linear_search(ARRAY *array, int key)
{
	int i;

	for (i = 0; i <= array->last_position; ++i)
	{
		if(key == array->pointer[i])
		{
			return i;
		}
	}
}

int binary_search(ARRAY *array, int key)
{
	int first;
	int last;
	int middle;

	first = 0;
	last = array->last_position;

	while(first <= last)
	{
		middle = (first + last) / 2;

		if (key == array->pointer[middle])
		{
			return middle;
		}
		else if(key > array->pointer[middle])
		{
			first = (middle + 1);
		}
		else
		{
			last = (middle - 1);
		}
	}
}

void reverse_array(ARRAY *array)
{
	int i;
	int j;
	int tmp;

	for (i = 0, j = array->last_position; i <= (array->last_position / 2); ++i, --j)
	{
		tmp = array->pointer[i]; 
		array->pointer[i] = array->pointer[j];
		array->pointer[j] = tmp; 
	}
}

char menu()
{
	char user_input[10];

	printf("(P) - Print\n");
	printf("(A) - Add/Applast_position\n");
	printf("(I) - Insert into position\n");
	printf("(Q) - Insert sort\n");
	printf("(D) - Delete\n");
	printf("(S) - Search\n");
	printf("(M) - Max\n");
	printf("(N) - Min\n");
	printf("(O) - Set\n");
	printf("(T) - Get\n");
	printf("(R) - Reverse\n");
	printf("(E) - Exit\n");
	printf(": ");
	fgets(user_input, sizeof(user_input), stdin);	

	return user_input[0];
}

char search_menu()
{
	char user_input[10];

	printf("(L) - linear_Search\n");
	printf("(B) - Binary Search\n");
	fgets(user_input, sizeof(user_input), stdin);	

	return user_input[0];
}

char linear_search_menu()
{
	char user_input[10];

	printf("(T) Transposition\n" );
	printf("(H) Move to Head\n" );

	fgets(user_input, sizeof(user_input), stdin);

	return user_input[0];
}

int main(int argc, char **argv)
{
	ARRAY array;
	int op;

	if(argc < 3)
	{
		printf("Invalid numbers of arguments.\n");
		return 1;
	}
	else if(atoi(argv[2]) != (argc - 3))
	{
		printf("Number of numbers has to match inital array size.\n");
		return 1;
	}
	else if(atoi(argv[2]) > atoi(argv[1]))
	{
		printf("Too many characters for the aarray\n");
		return 1;
	}

	create_array(&array, atoi(argv[1]));
	initialize_array(&array, argv);

	do
	{
		system("clear");
		op = menu();

		switch(op)
		{
			case 'P':
			case 'p':
			{
				display_pointer(array);
			}break;

			case 'A':
			case 'a':
			{
				int key;
				
				if(isFull(array))
				{
					printf("There is no space left in the array!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);

					append(&array, key);
				}
			}break;

			case 'I':
			case 'i':
			{
				int key;
				int position;

				if(isFull(array))
				{
					printf("There is no space left in the array!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);
					printf("The postion to be inserted: \n");
					get_int(&position);
					insert_on_position(&array, key, position);
				}


			}break;

			case 'Q':
			case 'q':
			{
				int key;

				if(isFull(array))
				{
					printf("There is no space left in the array!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);
					insert_sort(&array, key);
				}
			}break;

			case 'D':
			case 'd':
			{
				int position;

				printf("Type the position of the element you want to remove: \n");
				get_int(&position);

				delete_by_position(&array, position);

			}break;

			case 'S':
			case 's':
			{
				int key;
				int position;

				printf("Key to be found: ");
				get_int(&key);

				op = search_menu();
				system("clear");
				switch(op)
				{
					case 'L':
					case 'l':
					{
						op = linear_search_menu();
						system("clear");
						if(op == 'T' || op == 't')
						{	
							int position;

							position = linear_search(&array, key);
							transposition(&array, position);
							printf("Key %d is set on position %d\n", key, position);
						}
						else if(op == 'H' || op == 'h')
						{
							int position;

							position = linear_search(&array, key);
							move_to_head(&array, position);							
							printf("Key %d is set on position %d\n", key, position);
						}

					}break;

					case 'B':
					case 'b':
					{
						position = binary_search(&array, key);

						printf("Key %d is set on position %d\n", key, position);
					}break;
					default:
					{
						printf("Invalid Choice!\n");
					}
				}
			}break;

			case 'O':
			case 'o':
			{

			}break;

			case 'M':
			case 'm':
			{

			}break;

			case 'R':
			case 'r':
			{
				reverse_array(&array);
			}break;

			case 'T':
			case 't':
			{

			}break;

			case 'E':
			case 'e':
			{
				printf("Bye!\n");
			}break;
			default:
			{
				printf("Invalid choice!\n");
			}
		}
		
		int c = getchar();

	}while(op != 'E' && op != 'e');
}
