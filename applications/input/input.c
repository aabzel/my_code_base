#include "input.h"

#include <stdio.h>
#include <conio.h>

int g_last_input = INPUT_NONE;

bool input_task(void* p) {
    bool loop=true;
		if (_kbhit()) {
			char ch = _getch( );
			switch (ch) {
			case '8':
				printf("\nUp");
				g_last_input = InputUp;
				break;
			case '3':
				printf("\nReset");
				g_last_input = InputBack;
				break;
			case '2':
				printf("\nDown");
				g_last_input = InputDown;
				break;
			case '4':
				printf("\nLeft");
				g_last_input = InputLeft;
				break;
			case '6':
				printf("\nRight");
				g_last_input = InputRight;
				break;
			case '5':
				printf("\nOK");
				g_last_input = InputOk;
				break;
			case '9':
				printf("\nExit");
				g_last_input = InputBack;
				loop = false;
				break;
			default:
				g_last_input = INPUT_UNDEF;
				printf("\n undef command key: %d %c", ch, ch);
				break;
			}
			printf("\n>");
		}else {
			g_last_input = INPUT_NONE;
		}
    
	return loop;
}

