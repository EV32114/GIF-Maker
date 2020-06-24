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

/*
save a gif to a file.
Input: head of linked list.
Output: none.
*/
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

/*
load an existing project.
Input: none.
Output: linked list with all loaded frames.
*/
FrameNode* loadFile()
{
	int counter = 0;
	FrameNode* head = NULL;
	FrameNode* curr = NULL;
	char data[STR_LEN] = { 0 };
	char path[STR_LEN] = { 0 };
	char name[STR_LEN] = { 0 };
	char framePath[STR_LEN] = { 0 };
	char duration[STR_LEN] = { 0 };
	char delim[2] = "#";
	char* token = 0;
	FILE * dataFile;

	printf("Enter file path:\n");
	myFgets(path, STR_LEN);
	if (!exists(path))
	{
		printf("Error: File not found\n");
		return head;
	}
	dataFile = fopen(path, "r");
	while (fgets(data, STR_LEN, dataFile))
	{
		data[strcspn(data, "\n")] = 0;
		token = strtok(data, delim);
		while (token)
		{
			counter++;
			switch (counter)
			{
				case 1:
					strcpy(name, token);
					break;
				case 2:
					strcpy(duration, token);
					break;
				case 3:
					strcpy(framePath, token);
					break;
			}

			token = strtok(NULL, delim);
		}
		counter = 0;
		if (!head)
		{
			head = createFrame(name, atoi(duration), framePath);
			head->next = NULL;
		}
		else
		{
			curr = createFrame(name, atoi(duration), framePath);
			insertAtEnd(&head, curr);
		}
	}
	fclose(dataFile);
	return head;
}
