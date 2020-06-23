#include "linkedList.h"

/*
Function will initialize a new frame.
Input: head of linked list
Output: new Frame Node.
*/
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
		while (nameInList(head, name))
		{
			printf("The name is already taken, please enter another name:\n");
			myFgets(name, STR_LEN);
		}
	}

	return createFrame(name, duration, path);
}

/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
Input: the buffer to read into, the number of chars to read.
Output: none.
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

/*
Allocate memory to new node and return it.
Input: Frame data.
Output: New frame node.
*/
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

/*
Insert a new frame at the end of the list.
Input: head of linked list and new frame node.
Output: none.
*/
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

/*
free a linked list.
Input: head of linked list.
Output: none.
*/
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

/*
print all the frames.
Input: head of linked list.
Output: none.
*/
void printList(FrameNode* head)
{
	FrameNode* curr = head;
	printf("    Name    Duration    Path\n");
	while (curr)
	{
		printf("    %s    %d ms    %s\n", curr->frame->name, curr->frame->duration, curr->frame->path);
		curr = curr->next;
	}
	printf("\n");
}

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
Remove a frame from the list.
Input: head of linked list.
Output: none.
*/
void removeFrame(FrameNode** head)
{
	bool deleted = false;
	char name[STR_LEN] = { 0 };
	FrameNode* temp = *head;
	FrameNode* prev = NULL;

	printf("Enter the name of the frame you wish to erase:\n");
	myFgets(name, STR_LEN);

	if (temp && !strcmp(temp->frame->name, name)) // if the frame to remove is the head.
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

/*
Free a Frame Node.
Input: a frame node.
Output: none.
*/
void freeNode(FrameNode* node)
{
	free(node->frame->name);
	free(node->frame->path);
	free(node->frame);
	free(node);
}

/*
Change a frame's duration.
Input: The frame node and duration.
Output: none.
*/
void changeFrameDuration(FrameNode** node, unsigned int time)
{
	FrameNode* realNode = *node;
	realNode->frame->duration = time;
}

/*
Get the frame name and new duration from the user and change the frame's duration.
Input: head of linked list.
Output: none.
*/
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

/*
Change the duration for all the frames.
Input: head of linked list.
Output: none.
*/
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

/*
change the location of a frame.
Input: head of linked list.
Output: none.
*/
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
		else // remove the node from the list and keep it in temp.
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

		if (index == 1) // insert in start of list
		{
			temp->next = *head;
			*head = temp;
		}
		else // insert in middle of list
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

/*
check if the data for changeLocation is valid - index is between the list length and name is in list.
Input: head of linked list, index and frame name.
Output: True - if the data is valid, false otherwise.
*/
bool checkLocationData(FrameNode* head, int index, char* name)
{
	if (index >= 1 && index <= listLength(head) && nameInList(head, name))
	{
		return true;
	}
	return false;
}

/*
return the list's length.
Input: head of linked list.
Output: it's length.
*/
int listLength(FrameNode* head)
{
	int size = 0;
	if (head)
	{
		size = 1 + listLength(head->next);
	}
	return size;
}

/*
Function will check if a given name is already inside the linked list.
Input: head of linked list and name to find.
Output: True - if the name is in the list, False otherwise.
*/
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
