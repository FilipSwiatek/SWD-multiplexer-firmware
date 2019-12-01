#include "cli.h"
#include "uart.h"
#include "usbd_cdc_if.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>



// head of CLI command list
static CLI_CommandItem* head = NULL;

// char buffer where command will be stored
static char commandBuffer[100];

static CLI_CommandItem* CLI_GetMenuItemByCommandName(char* command);

static bool CLI_StoreCommand(void);

static void CLI_StringToLower(char* dst, const char* src);
	
	
	
void CLI_Proc(void){
		if(CLI_StoreCommand() ==  true){
			// zamieniamy na male
			CLI_StringToLower(commandBuffer, (const char*) commandBuffer);
			// sprawdzamy czy podana komenda znajduje sie w ogole w zbiorze komend
			CLI_CommandItem* ptr = (CLI_GetMenuItemByCommandName(commandBuffer));
			if(ptr != NULL){
			ptr->callback(commandBuffer+strlen(commandBuffer)+1); // argument is string shifted by strlen (because space was converted to '\0' <3
			}else{
			}
			printf("String commandbuffera to: %s\n\r",commandBuffer);
			//czyscimy bufor (nadpisujemy nullami)
			memset(commandBuffer, '\0', sizeof(commandBuffer));
		}
	}
		

bool CLI_AddCommand(CLI_CommandItem* item){
	//jesli ktorekolwiek pole poza "next" jest puste, wtedy element nie zostanie dodany do kolejki, bo jest nieprawidlowy
	if(item == NULL || item->callback == NULL || item->commandName == NULL ){
		return false;
	}
	CLI_CommandItem* nextPtr = head;
	if(nextPtr == NULL){
		// lista jest pusta
		head = item;
	}else{
		// lista nie jest pusta
		// jesli wskaznik na kolejny element nie jest NULLem, (element nie jest ostatnim elementem) to skaczemy do kolejnego az do osiagniecia ostatniego elementu:
		while(nextPtr->next != NULL){
			nextPtr = nextPtr->next;
		}
	nextPtr->next = item;
	}
	item->next = NULL;
	return true;
}

void CLI_PrintAllCommands(void){
	CLI_CommandItem* nextPtr = head;
	USART_WriteString("List of Available commands and their descriptions:\n\r");
	while(nextPtr != NULL){
		USART_WriteString(nextPtr->commandName);
		USART_WriteString("\n\r");
		USART_WriteString(nextPtr->description);
		USART_WriteString("\n\r");
		nextPtr = nextPtr->next;
	}
}

CLI_CommandItem* CLI_GetMenuItemByCommandName(char* command){
	CLI_CommandItem* ptr = head;
	while(ptr != NULL) {
		if(!strcmp(ptr->commandName, command)){
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

void CLI_StringToLower(char* dst, const char* src){
	for (int i=0; i < strlen(src); i++){
	dst[i] = tolower(src[i]);
	}
}

bool CLI_StoreCommand(){
	static uint8_t index = 0;
	volatile char c;
	if(USART_GetChar((char*) &c) || USB_VCOM_GetChar((char*) &c)){
#if defined(FORWARD_INPUT_TO_OUTPUT) && FORWARD_INPUT_TO_OUTPUT == 1
		USART_PutChar(c);
        USB_VCOM_PutChar(c);
		if(c == '\r'){ // to make new line
			USART_PutChar('\n');
            USB_VCOM_PutChar('\n');
		}
#endif
		
		switch(c){
			case '\b': 
			case 127 : // delete
			if(index > 0){
				index--;
				commandBuffer[index] = '\0';
			}
				break;
			
			case ' ':
				commandBuffer[index] = '\0';
				index++;
				break;
			
			case '\r':
			case '\n':
				commandBuffer[index] = '\0';
				index = 0;
				return true;	
				//break;
			
			default:
				commandBuffer[index] = c;
				index++;
				break;
		}
		//zabezpieczonko przed pisaniem byle gdzie i czytaniem zbyt wiele potem
		if(index >= sizeof(commandBuffer) - 1){
			index = 0;
		}
	}
	return false;
}
