#undef _GNU_SOURCE
#define _GNU_SOURCE
#include <string.h>



#include <stdlib.h>

#include "defs.h"
#include "rc.h"
#include "input.h"




char *keybind[MAX_KEYS];




int rc_bindkey(char *keyname, char *cmd)
{
	int key;
	char *a;

	key = k_keycode(keyname);
	if (!key) return -1;

	a = strdup(cmd);
	if (!a) die("out of memory binding key\n");

	if (keybind[key]) free(keybind[key]);
	keybind[key] = a;

	//printf("Bound keybind[%d] = %s\n", key, a);
	
	return 0;
}



int rc_unbindkey(char *keyname)
{
	int key;

	key = k_keycode(keyname);
	if (!key) return -1;
	
	if (keybind[key]) free(keybind[key]);
	keybind[key] = NULL;
	return 0;
}


void rc_unbindall()
{
	int i;

	for (i = 0; i < MAX_KEYS; i++)
	{
		if (keybind[i])
		{
			free(keybind[i]);
			keybind[i] = NULL;
		}
	}
}



void rc_dokey(int key, int st)
{
	if (!keybind[key]) return;
	if (keybind[key][0] != '+' && !st) return; // this is to handle only the press evt for not gamepad buttons (shortcuts for menu, save, ...)
	
	if (st)
		rc_command(keybind[key]);
	else
	{
		keybind[key][0] = '-';
		rc_command(keybind[key]);
		keybind[key][0] = '+';
	}
}
