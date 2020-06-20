#ifndef LINKEDLISTH
#define LINKEDLISTH

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR_LEN 100

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
void myFgets(char str[], int n);
bool nameTaken(char* name, FrameNode* head);
FrameNode* createFrame(char* name, unsigned int duration, char* path);

#endif
