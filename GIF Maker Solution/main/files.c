#include "files.h"

/*
check if a file exists.
Input: file path.
Output: True - if the file exists, False otherwise.
*/
bool exists(char *fileName)
{
	bool exist = false;
	FILE *file;
	file = fopen(fileName, "r");
	if (file)
	{
		fclose(file);
		exist = true;
	}
	return exist;
}

void saveFile(FrameNode* head)
{
	FILE * log;
	char file_path[STR_LEN] = { 0 };
	FrameNode* curr = head;
	printf("Enter file path (including name):\n");
	myFgets(file_path, STR_LEN);

	log = fopen(file_path, "w");
	while (curr)
	{
		fprintf(log, "%s#%u#%s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	printf("File saved\n");
	fclose(log);
}

FrameNode* loadFile()
{
	FrameNode* head = NULL;
	char data[STR_LEN] = { 0 };
	char path[STR_LEN] = { 0 };
	char delim[2] = "#";
	char* token = 0;
	FILE * dataFile;

	printf("Enter file path:\n");
	myFgets(path, STR_LEN);

	dataFile = fopen(path, "r");
	while (fgets(data, STR_LEN, dataFile))
	{
		data[strcspn(data, "\n")] = 0;
		token = strtok(data, delim);
		while (token)
		{
			printf(" %s\n", token);

			token = strtok(NULL, delim);
		}
	}
	fclose(dataFile);
}
