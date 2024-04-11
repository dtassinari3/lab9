#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct Node* head;
};

// Compute the hash function
int hash(int x)
{
	return x % 10;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		printf("Index %d: ", i);
		struct Node* current = hashArray[i].head;
		while (current != NULL)
		{
			printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
			current = current->next;
		}
		printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
	//initialize hash table
	struct HashType hashTable[10];
	for (int i = 0; i < 10; i++)
	{
		hashTable[i].head = NULL;
	}
	//insert records into hash table
	for (int i = 0; i < recordSz; i++)
	{
		int index = hash(key);
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->data = record;
		newNode->next = hashArray[index].head;
		hashArray[index].head = newNode;
	}

	//display records in hash table
	displayRecordsInHash(hashTable, 10);

	//free allocated memory
	for (int i = 0; i < 10; i++)
	{
		struct Node* current = hashTable[i].head;
		while (current != NULL)
		{
			struct Node* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(pRecords);

	return 0;
}