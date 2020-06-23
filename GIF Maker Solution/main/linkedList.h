#ifndef LINKEDLISTH
#define LINKEDLISTH

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR_LEN 100

enum choices { EXIT, ADD, REMOVE, LOCATION, DURATION, ALL_DURATION, PRINT, PLAY, SAVE };

// Frame struct
typedef struct Frame
{
	char*		name;
	unsigned int	duration;
	char*		path;
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

FrameNode* initFrame(FrameNode* head);
FrameNode* createFrame(char* name, unsigned int duration, char* path);
void insertAtEnd(FrameNode** head, FrameNode* newNode);

void printList(FrameNode* head);

void removeFrame(FrameNode** head);

void changeFrameDuration(FrameNode** node, unsigned int duration);
void frameDuration(FrameNode** head);
void allFrameDuration(FrameNode** head);

void changeLocation(FrameNode** head);
bool checkLocationData(FrameNode* head, int index, char* name);

int listLength(FrameNode* head);
bool nameInList(FrameNode* head, char* name);
void myFgets(char str[], int n);

void freeList(FrameNode** head);
void freeNode(FrameNode* node);

#endif
