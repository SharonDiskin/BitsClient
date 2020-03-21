#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/*The main we got to implement*/
void main()

{
	int n;
	Short_client * arr;
	char id[9];
	char* phone;

	printf("Please enter the number of clients: ");
	scanf("%d", &n);

	arr = createShortClientArr(n);
	fseek(stdin, 0, 1);
	scanf("%s", id);
	phone = searchClientByID(arr, n, id);

	if (phone == NULL)
		printf("Can not find client with i.d. %s\n", id);
	else

	{
		printf("The phone number of client i.d. %s is %s\n", id, phone);
		free(phone);
	}

	free(arr);
}
