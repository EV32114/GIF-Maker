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
	while (nameTaken(name, head))
	{
		printf("The name is already taken, please enter another name:\n");
		myFgets(name, STR_LEN);
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

}

FrameNode* createFrame(char* name, unsigned int duration, char* path)
{
	Frame* newFrame = (Frame*)malloc(sizeof(Frame));
	FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));

	strncpy(newFrame->name, name, STR_LEN);
	newFrame->duration = duration;
	strncpy(newFrame->path, path, STR_LEN);

	newNode->frame = newFrame;
	newNode->next = NULL;
	return newNode;
}