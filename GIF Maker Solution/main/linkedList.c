#include "linkedList.h"

FrameNode* initFrame(FrameNode* head)
{
	char name[STR_LEN] = { 0 };
	unsigned int duration = 0;
	char path[STR_LEN] = { 0 };

	printf("*** Creating new frame ***\n");
	printf("Please insert frame path:\n");
	myFgets(path, STR_LEN);
	printf("Please insert frame duration(in milliseconds):\n");
	scanf("%d", &duration);
	getchar();
	printf("Please choose a name for that frame:\n");
	myFgets(name, STR_LEN);
	if (head)
	{
		while (nameTaken(name, head))
		{
			printf("The name is already taken, please enter another name:\n");
			myFgets(name, STR_LEN);
		}
	}

	return createFrame(name, duration, path);
}

void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

bool nameTaken(char* name, FrameNode* head)
{
	FrameNode* curr = head;
	do
	{
		if (!strcmp(curr->frame->name, name))
		{
			return true;
		}
		else
		{
			if (curr->next)
			{
				curr = curr->next;
			}
			else
			{
				return false;
			}
		}
	} while (curr);
	return false;
}

FrameNode* createFrame(char* name, unsigned int duration, char* path)
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));

	newFrame->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
	newFrame->path = (char*)malloc(sizeof(char) * strlen(path) + 1);


	strcpy(newFrame->name, name);
	newFrame->duration = duration;
	strcpy(newFrame->path, path);

	newNode->frame = newFrame;
	newNode->next = NULL;
	return newNode;
}

void insertAtEnd(FrameNode** head, FrameNode* newNode)
{
	FrameNode* curr = *head;
	if (!*head) // empty list!
	{
		*head = newNode;
	}
	else
	{
		while (curr->next) // while the next is NOT NULL (when next is NULL - that is the last node)
		{
			curr = curr->next;
		}

		curr->next = newNode;
		newNode->next = NULL;
	}
}

void freeList(FrameNode** head)
{
	FrameNode* temp = NULL;
	FrameNode* curr = *head;
	while (curr)
	{
		temp = curr;
		curr = (curr)->next;
		freeNode(temp);
	}

	*head = NULL;
}

void printList(FrameNode* head)
{
	FrameNode* curr = head;
	printf("    Name    Duration    Path\n");
	while (curr) // when curr == NULL, that is the end of the list, and loop will end (NULL is false)
	{
		printf("    %s    %d ms    %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	printf("\n");
}

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

void removeFrame(FrameNode** head)
{
	bool deleted = false;
	char name[STR_LEN] = { 0 };
	FrameNode* temp = *head;
	FrameNode* prev = NULL;

	printf("Enter the name of the frame you wish to erase:\n");
	myFgets(name, STR_LEN);

	if (temp && !strcmp(temp->frame->name, name))
	{
		*head = temp->next;
		freeNode(temp);
		deleted = true;
	}
	else
	{
		while (temp && strcmp(temp->frame->name, name))
		{
			prev = temp;
			temp = temp->next;
		}

		if (temp)
		{
			prev->next = temp->next;
			freeNode(temp);
			deleted = true;
		}
	}
	if (deleted)
	{
		printf("Frame deleted.\n");
	}
	else
	{
		printf("Frame Not Found.\n");
	}
}

void freeNode(FrameNode* node)
{
	free(node->frame->name);
	free(node->frame->path);
	free(node->frame);
	free(node);
}

void changeFrameDuration(FrameNode** node, unsigned int time)
{
	FrameNode* realNode = *node;
	realNode->frame->duration = time;
}

void frameDuration(FrameNode** head)
{
	unsigned int time = 0;
	char name[STR_LEN] = { 0 };
	FrameNode* curr = *head;
	bool durationChanged = false;

	printf("Enter the name of the frame:\n");
	myFgets(name, STR_LEN);

	printf("Enter the new duration:\n");
	scanf("%d", &time);
	getchar();
	if (curr && !strcmp(curr->frame->name, name))
	{
		changeFrameDuration(&curr, time);
		durationChanged = true;
	}
	else
	{
		while (curr && strcmp(curr->frame->name, name))
		{
			curr = curr->next;
		}

		if (curr)
		{
			changeFrameDuration(&curr, time);
			durationChanged = true;
		}
	}
	if (!durationChanged)
	{
		printf("Frame Not Found\n");
	}
}

void allFrameDuration(FrameNode** head)
{
	FrameNode* curr = *head;
	unsigned int time = 0;

	printf("Enter the duration for all frames:\n");
	scanf("%d", &time);
	getchar();

	while (curr)
	{
		changeFrameDuration(&curr, time);
		curr = curr->next;
	}
}

void changeLocation(FrameNode** head)
{
	char name[STR_LEN] = { 0 };
	int index = 0, i = 0;
	FrameNode* temp = *head;
	FrameNode* curr = *head;
	FrameNode* prev = NULL;

	printf("Enter the name of the frame:\n");
	myFgets(name, STR_LEN);

	printf("Enter the new index in the movie you wish to place the frame:\n");
	scanf("%d", &index);
	getchar();

	if (checkLocationData(*head, index, name))
	{
		if (temp && !strcmp(temp->frame->name, name))
		{
			*head = temp->next;
		}
		else
		{
			while (temp && strcmp(temp->frame->name, name))
			{
				prev = temp;
				temp = temp->next;
			}

			if (temp)
			{
				prev->next = temp->next;
				temp->next = NULL;
			}
		}
		if (index == 1)
		{
			temp->next = *head;
			*head = temp;
		}
		else
		{
			curr = *head;
			for (i = 0; i < index - 2; i++)
			{
				curr = curr->next;
			}
			temp->next = curr->next;
			curr->next = temp;
		}
	}
	else
	{
		printf("Error: Invalid index or name\n");
	}

}

bool checkLocationData(FrameNode* head, int index, char* name)
{
	if (index >= 1 && index <= listLength(head) && nameInList(head, name))
	{
		return true;
	}
	return false;
}

int listLength(FrameNode* head)
{
	int size = 0;
	if (head)
	{
		size = 1 + listLength(head->next);
	}
	return size;
}

bool nameInList(FrameNode* head, char* name)
{
	FrameNode* curr = head;
	if (curr && !strcmp(curr->frame->name, name))
	{
		return true;
	}
	else
	{
		while (curr && strcmp(curr->frame->name, name))
		{
			curr = curr->next;
		}

		if (curr)
		{
			return true;
		}
	}
	return false;
}
