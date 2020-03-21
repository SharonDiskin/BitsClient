#pragma once

/*Structs*/
typedef struct _client
{
	char id[9];
	char phone[12];
} Client;


typedef struct _short_client
{
	unsigned char short_id[4];
	unsigned char short_phone[5];
} Short_client;

/*Define*/
#define ERROR -1
#define ID_LEN 9
#define PHONE_LEN 12
#define SHORT_ID_LEN 4
#define SHORT_PHONE_LEN 5
#define DIG_IN_BITS 4

/*Prototypes*/
Client* getClients(int n);
void CompressId(unsigned char* short_id, char* id);
void compressPhone(unsigned char* short_phone, char* phone);
Short_client* createCompressedArr(int n, Client* clients);
Short_client* createShortClientArr(int n);
char* unCompressId(unsigned char* short_id);
char* unCompressPhone(unsigned char* short_phone);
char* searchClientByID(Short_client* arr, int n, char* id);
void checkMalloc(void* p);
