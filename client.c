*This function creates an array os clients size n, create each client
and gets the information of each client. Then it returns the array of clients*/

Client* getClients(int n)
{
	int i;
	Client* clients = (Client*)malloc(sizeof(Client)*n);
	checkMalloc(clients);
	for (i = 0; i < n; i++)
	{
		printf("Please enter client's id:\n");
		scanf("%s", clients[i].id);
		clients[i].id[8] = '\0';
		printf("Please enter client's phone:\n");
		scanf("%s", clients[i].phone);
	}
	return clients;
}

/*This function compresses the Id from regular to short*/
void CompressId(unsigned char* short_id, char* id)
{
	int i, j = 0; //Declaration of index
	unsigned char temp;
	for (int i = 0; i<SHORT_ID_LEN; i++) //While the size if smaller and the length of a short ID
	{
		short_id[i] = 0; //We initialize the short ID to 0
						 
		temp = id[j] - '0' << DIG_IN_BITS; //We convert the digit in  right place from the regular id to be between 0-9 in ascii
		//and we shift it 4 places (size of digit in bits) to the left
		short_id[i] |= temp; //We "turn on" the bits of the short id digit
		temp = id[j + 1] - '0'; //we convert another digit in the right to be between 0 to 9 in ascii
		short_id[i] |= temp; //We turn on the the bits of the short id digit
		j += 2; //We jump promote the index of the regular id by 2 and after we convered two digits to 1 unsigned char
	}
}


/*This function compresses the phone from regular to short*/
void compressPhone(unsigned char* short_phone, char* phone)
{
	int i, j = 0; //Declaration of index
	unsigned char temp;
	for (int i = 0; i<SHORT_PHONE_LEN; i++)
	{
		short_phone[i] = 0; //We initialize the short phone to 0
		temp = phone[j] - '0' << DIG_IN_BITS; //We convert the digit in  right place from the regular id to be between 0-9 in ascii
		//and we shift it 4 places (size of digit in bits) to the left
		short_phone[i] |= temp; //We "turn on" the bits of the short phone digit

		if (phone[j + 1] == '-') //If the charcater is '-' we skip this charcter
			j++;

		temp = phone[j + 1] - '0'; //we convert another digit in the right to be between 0 to 9 in ascii
		short_phone[i] |= temp; //We turn on the the bits of the short id digit
		j += 2; //We jump promote the index of the regular phone by 2 and after we convered two digits to 1 unsigned char
	}
}

/*This function take each client and compress him to a short client*/
Short_client* createCompressedArr(int n, Client* clients)
{
	int i, j = 0, k = 0; //Declaration of index
	
	//Creating short client array
	Short_client* shortClients;
	shortClients = (Short_client*)malloc(sizeof(Short_client)*n);
	checkMalloc(shortClients);

	//For each client we compress his phone and id
	for (int i = 0; i < n; i++)
	{
		CompressId(shortClients[i].short_id, clients[i].id);
		compressPhone(shortClients[i].short_phone, clients[i].phone);
	}
	return shortClients;
}

/*This function gets the client (in a regular way) and returns an array of short clients (the client compressed) */
Short_client* createShortClientArr(int n)
{
	int i, j = 0;
	Client* clients;
	clients = getClients(n); //We get the clients

	Short_client* shortClients;
	shortClients = createCompressedArr(n, clients); //We send the clients array to compress

	free(clients); //We free the old array
	return shortClients; //We return the compressed array
}

/*This function take a short id and converts it to a regular id*/
char* unCompressId(unsigned char* short_id)
{
	int i, j = 0; //Declaration of index
	short int mask = 0xF; //We create a mask

	char* id = (char*)malloc(sizeof(char) * ID_LEN); //We create a string for the regual id
	checkMalloc(id);

	//We copy the short id to the regual id
	for (i = 0; i < SHORT_ID_LEN; i++)
	{
		id[j++] = ((short_id[i] >> DIG_IN_BITS) & mask) + '0'; //First we copy the left side (converting it to a digit) of the short id using a mask
		id[j++] = (short_id[i] & mask) + '0'; //Then we copy the left side of the id (converting it to a digit)
	}
	id[j] = '\0'; //We add '\0' on to last digit
	return id;
}

/*This function take a short phone and converts it to a regular id*/
char* unCompressPhone(unsigned char* short_phone)
{
	int i, j = 0; //Declaration of index
	short int mask = 0xF; //We create a mask

	char* phone = (char*)malloc(sizeof(char) * PHONE_LEN); //We create a string for the regual id
	checkMalloc(phone);

	//We copy the short phone to the regual phone
	for (i = 0; i < SHORT_PHONE_LEN; i++)
	{
		phone[j++] = ((short_phone[i] >> DIG_IN_BITS) & mask) + '0'; //First we copy the left side (converting it to a digit) of the short phone using a mask
		if (j == 3) //If the index is '3' we should insert '-' charcter 
			phone[j++] = '-';
		phone[j++] = (short_phone[i] & mask) + '0'; //Then we copy the left side of the phone (converting it to a digit)
	}
	phone[j] = '\0';
	return phone;
}

/*This function recieve a regular id and search for the client who has this id in the short client array/
it returns the phone of the ID of this client*/
char* searchClientByID(Short_client* arr, int n, char* id)
{
	int i;

	for (i = 0; i < n; i++)
	{
		char* currId = unCompressId(arr[i].short_id); //We convert the the short id to a regular id so we can compare it with the id we got
		if (strcmp(currId, id) == 0)
		{
			free(currId); //We free the regual id we created for comparsion
			return unCompressPhone(arr[i].short_phone); //We return the phone of the client we found 
		}
		free(currId);
	}

	return NULL; //If we didn't find the client we return NULL
}

/*This function checks if the memmory allocation we did was succsesful.
If not it prints a message and exit*/
void checkMalloc(void* p)
{
	if (!p)
	{
		printf("Memmory allocation error!\n");
		exit(ERROR);
	}
}

