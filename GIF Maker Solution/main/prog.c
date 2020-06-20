#include "view.h"
#include "linkedList.h"

void printOptions();

int main()
{
	int choice = 1;
	printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
	// part 2
	while (choice != 0)
	{
		printf("What would you like to do?\n");
		printOptions();
		scanf("%d", &choice);
		getchar();
	}

	getchar();
	return 0;
}

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