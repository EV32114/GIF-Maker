#include "view.h"
#include "linkedList.h"
#include "files.h"

void printOptions();

int main()
{
	int choice = 1;
	int loadFileChoice = 0;
	FrameNode* head = NULL;
	FrameNode* newFrame = NULL;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	
	printf(" [0] Create a new project\n");
	printf(" [1] Load existing project\n");
	scanf("%d", &loadFileChoice);
	getchar();

	if (loadFileChoice)
	{
		head = loadFile();
	}
	while (choice != 0)
	{
		printf("What would you like to do?\n");
		printOptions();
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
			case EXIT:
				printf("Bye!\n");
				break;
			case ADD:
				newFrame = initFrame(head);
				if (exists(newFrame->frame->path))
				{
					insertAtEnd(&head, newFrame);
				}
				else
				{
					printf("Error: File doesn't exist\n");
					freeNode(newFrame);
				}
				break;
			case REMOVE:
				removeFrame(&head);
				break;
			case LOCATION:
				changeLocation(&head);
				break;
			case DURATION:
				frameDuration(&head);
				break;
			case ALL_DURATION:
				allFrameDuration(&head);
				break;
			case PRINT:
				printList(head);
				break;
			case PLAY:
				play(head);
				break;
			case SAVE:
				saveFile(head);
				break;
			default:
				printf("Invalid Input, please enter a number between 0-8\n");
				break;
		}
	}

	freeList(&head);
	getchar();
	return 0;
}

/*
print the option for the user.
Input: none.
Output: none.
*/
void printOptions()
{
	printf(" [0] Exit\n");
	printf(" [1] Add new Frame\n");
	printf(" [2] Remove a Frame\n");
	printf(" [3] Change frame index\n");
	printf(" [4] Change frame duration\n");
	printf(" [5] Change duration of all frames\n");
	printf(" [6] List frames\n");
	printf(" [7] Play movie!\n");
	printf(" [8] Save project\n");
}