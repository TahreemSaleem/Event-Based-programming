#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>


#define eventid_onProgramStart 0
#define eventid_onKeyPress 1

typedef void(*EventHandler) (void *data);

void addEventListener(int eventId, EventHandler eh);
void removeEventListener(int eventid, EventHandler eh);
void onEventOccured(int eventId);
void init();

//on program start 
int onKeypressed_Size = 4;
int onKeypressed_Idx = 0; 
EventHandler* onKeypressed_array ;


//on key pressed
int onProgramStart_Size = 4;
int onProgramStart_Idx = 0;
EventHandler* onProgramStart_array ;

//

void onEventOccured(int eventId,char c) {
	if (eventId == 0) 
	{
		for (int i = 0; i < onProgramStart_Idx; i++) 
		{	
			if(onProgramStart_array[i])
			onProgramStart_array[i](eventId);
		}
	}
	if (eventId == 1)
	{
		for (int i = 0; i < onKeypressed_Idx; i++)
		{	
			if (onKeypressed_array[i])
			onKeypressed_array[i](c);
		}

	}
}

void addEventListener(int eventId, EventHandler eh)
{
	if (eventId == 0)
	{
		if (onProgramStart_Idx >= onProgramStart_Size)
		{
			onProgramStart_Size *= 2;
			onProgramStart_array = realloc(onProgramStart_array, onProgramStart_Size);
		}
		onProgramStart_array[onProgramStart_Idx++] = eh;
		
	}

	if (eventId == 1)
	{
		if (onKeypressed_Idx >= onProgramStart_Size)
		{
			onKeypressed_Size *= 2;
			onKeypressed_array = realloc(onKeypressed_array, onKeypressed_Size);
		}
		onKeypressed_array[onKeypressed_Idx++] = eh;
		
	}
}
void removeEventListener(int eventid, EventHandler eh)
{
	if (eventid == 0)
	{
		

		for (int i = 0; i < onProgramStart_Idx; i++)
		{
			if (onProgramStart_array[i] == eh) 
			{
				onProgramStart_array[i] = NULL; 

			}
		}

	}

	if (eventid == 1)
	{
		for (int i = 0; i < onKeypressed_Idx;  i++)
		{
			if (onKeypressed_array[i] == eh)
			{
				onKeypressed_array[i] = NULL;

			}
		}

	}

}
//user defined functions
void myfunc1P();
void myfunc2P();
void myfunc3P();

void myfunc1P()
{
	printf("function1 in ProgramStart\n");
}

void myfunc2P()
{
	printf("function2 in ProgramStart\n");
}

void myfunc3P()
{
	printf("function3 in ProgramStart\n");
}
void myfunc1K(void *data);
void myfunc2K(void *data);
void myfunc3K(void *data);

void myfunc1K(void *data)
{
	if (data == NULL)
		printf("function1 in KeyPressed\n");
	else
		printf("function1 in KeyPressed:\n%c\n ", data);
}
void myfunc2K(void *data)
{
	if (data==NULL)
		printf("function2 in KeyPressed\n");
	else
		printf("function2 in KeyPressed:\n%c\n ", data);
}

void myfunc3K(void *data)
{
	if (data == NULL)
		printf("function3 in KeyPressed\n");
	else
		printf("function3 in KeyPressed:\n%c\n ", data);
}
//init function to call the functions
void init()
{
	char c ='c';

	addEventListener(0, myfunc1P);
	addEventListener(0, myfunc2P);
	addEventListener(0, myfunc3P);
	addEventListener(1, myfunc1K);
	addEventListener(1, myfunc2K);
	addEventListener(1, myfunc3K);
	printf("Events added successfully\nProgram Started\n");
	onEventOccured(0,c);
	printf("Event removed \nProgram Started\n");
	removeEventListener(0, myfunc2P);
	onEventOccured(0,c);

	for (;;) 
	{
		if (_kbhit()) 
		{
			c = _getch();
			onEventOccured(1,c);
		}
	}

}

int main() 
{
	
	onKeypressed_array = malloc(sizeof(EventHandler)*onKeypressed_Size);
	onProgramStart_array = malloc(sizeof(EventHandler)*onProgramStart_Size);
	init();
}
