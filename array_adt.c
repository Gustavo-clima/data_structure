#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
	int *array;
	int lenght;
	int last_position;
}ARRAY;

void get_int(int *integer)
{
	char user_input[10];

	fgets(user_input, sizeof(user_input), stdin);
	sscanf(user_input, "%d", integer);				
}

void display_array(ARRAY adt)
{
	int i;

	printf("\n");

	for (i = 0; i <= adt.last_position; ++i)
	{
		printf("  %d  ", adt.array[i]);
		printf("|");
	}
}

bool isEmpty(ARRAY adt)
{
	if(adt.last_position == (-1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isFull(ARRAY adt)
{
	if(adt.last_position >= (adt.lenght - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSorted(ARRAY *adt)
{
	int i;

	for (i = 0; i <= adt->last_position; ++i)
	{
		if(adt->array[i] > adt->array[i])
		{
			return false;
		}

		return true;
	}
}

void insert_sort(ARRAY *adt, int key)
{
	int i;

	i = (adt->last_position);

	while(adt->array[i] > key)
	{
		adt->array[i + 1] = adt->array[i];

		--i;
	}

	adt->array[i + 1] = key;
	++adt->last_position;
}

void set(ARRAY *adt, int key, int position)
{
	adt->array[position] = key;
}

int get(ARRAY *adt, int position)
{
	return adt->array[position];
}

void applast_position(ARRAY *adt, int key)
{
	adt->array[adt->last_position + 1] = key;
	++adt->last_position;
}

void delete_by_position(ARRAY *adt, int position)
{
	int i;

	for (i = position; i < adt->last_position; ++i)
	{
		adt->array[i] = adt->array[i + 1];
	}

	--adt->last_position;
}

void insert_on_position(ARRAY *adt, int key, int position)
{
	int i;

	for (i = adt->last_position; i >= position; --i)
	{
		adt->array[i + 1] = adt->array[i];
	}

	adt->array[position] = key;
	++adt->last_position;
}

void initialize_adt(ARRAY *adt, char **elements)
{
	int qtd_of_elements;
	int i;

	qtd_of_elements = atoi(elements[2]);

	for (i = 0; i < qtd_of_elements; ++i)
	{
		adt->array[i] = atoi(elements[i + 3]);
	}

	adt->last_position = (qtd_of_elements - 1);
}

void create_adt(ARRAY *adt, int lenght)
{
	adt->array = (int *)malloc(lenght * sizeof(int));
	
	adt->last_position = -1;
	adt->lenght = lenght;
}

void swap(ARRAY **adt, int source, int destination)
{
	int aux;

	aux = (*adt)->array[destination];

	(*adt)->array[destination] = (*adt)->array[source];
	(*adt)->array[source] = aux;
}

void transposition(ARRAY *adt, int position)
{
	swap(&adt, position, (position - 1));
}

void move_to_head(ARRAY *adt, int position)
{
	swap(&adt, position, 0);
}

int linear_search(ARRAY *adt, int key)
{
	int i;

	for (i = 0; i <= adt->last_position; ++i)
	{
		if(key == adt->array[i])
		{
			return i;
		}
	}
}

int binary_search(ARRAY *adt, int key)
{
	int first;
	int last;
	int middle;

	first = 0;
	last = adt->last_position;

	while(first <= last)
	{
		middle = (first + last) / 2;

		if (key == adt->array[middle])
		{
			return middle;
		}
		else if(key > adt->array[middle])
		{
			first = (middle + 1);
		}
		else
		{
			last = (middle - 1);
		}
	}
}

void reverse_adt(ARRAY *adt)
{
	int i;
	int j;
	int tmp;

	for (i = 0, j = adt->last_position; i <= (adt->last_position / 2); ++i, --j)
	{
		tmp = adt->array[i]; 
		adt->array[i] = adt->array[j];
		adt->array[j] = tmp; 
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
	ARRAY adt;
	int op;

	if(argc < 3)
	{
		printf("Invalid numbers of arguments.\n");
		return 1;
	}
	else if(atoi(argv[2]) != (argc - 3))
	{
		printf("Number of numbers has to match inital adt size.\n");
		return 1;
	}
	else if(atoi(argv[2]) > atoi(argv[1]))
	{
		printf("Too many characters for the aadt\n");
		return 1;
	}

	create_adt(&adt, atoi(argv[1]));
	initialize_adt(&adt, argv);

	do
	{
		system("clear");
		op = menu();

		switch(op)
		{
			case 'P':
			case 'p':
			{
				display_array(adt);
			}break;

			case 'A':
			case 'a':
			{
				int key;
				
				if(isFull(adt))
				{
					printf("There is no space left in the adt!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);

					applast_position(&adt, key);
				}
			}break;

			case 'I':
			case 'i':
			{
				int key;
				int position;

				if(isFull(adt))
				{
					printf("There is no space left in the adt!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);
					printf("The postion to be inserted: \n");
					get_int(&position);
					insert_on_position(&adt, key, position);
				}


			}break;

			case 'Q':
			case 'q':
			{
				int key;

				if(isFull(adt))
				{
					printf("There is no space left in the adt!\n");
				}
				else
				{
					printf("Type the key you want to include: \n");
					get_int(&key);
					insert_sort(&adt, key);
				}
			}break;

			case 'D':
			case 'd':
			{
				int position;

				printf("Type the position of the element you want to remove: \n");
				get_int(&position);

				delete_by_position(&adt, position);

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

							position = linear_search(&adt, key);
							transposition(&adt, position);
							printf("Key %d is set on position %d\n", key, position);
						}
						else if(op == 'H' || op == 'h')
						{
							int position;

							position = linear_search(&adt, key);
							move_to_head(&adt, position);							
							printf("Key %d is set on position %d\n", key, position);
						}

					}break;

					case 'B':
					case 'b':
					{
						position = binary_search(&adt, key);

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
				reverse_adt(&adt);
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
