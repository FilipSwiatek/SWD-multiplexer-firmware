#ifndef CLI_H_
#define CLI_H_

#define FORWARD_INPUT_TO_OUTPUT 1

#include <stdbool.h>
#include <stdint.h>


/// type definition for the user callback function
typedef void (*CLICallbackFunc)(const char *args);

/// CLI command descriptor
typedef struct CLI_CommandItem {
	/// pointer to a callback function
	CLICallbackFunc callback;
	/// pointer to comand name (string)
	char *commandName;
	/// pointer to command description (string)
	char *description;
	/// pointer to next command descriptor on the command list (uni-directional list)
	struct CLI_CommandItem* next;
} CLI_CommandItem;



void CLI_Proc(void);


bool CLI_AddCommand(CLI_CommandItem *item);


void CLI_PrintAllCommands(void);

#endif // CLI_H_
