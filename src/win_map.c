#include "control.h"

// A hash function for whatever type is used as KEYS
static unsigned pointer_hash(const uiControl *control) {
	return (unsigned int)(unsigned long)control;
}

int pointer_cmp(const uiControl *key0, const uiControl *key1) {
	if (key0 < key1) {
		return -1;
	} else if (key0 > key1) {
		return 1;
	} else {
		return 0;
	}
}

// In ONE c file:
_IMPLEMENT_MAP(struct control_handle *, uiControl *, struct ctrl_map, ctrl_map, pointer_cmp,
			   pointer_hash)
