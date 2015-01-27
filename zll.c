#include "zll.h"

/* The incrament by which to increase the number of list slots */
#define SLOT_INC_AMMOUNT 16

/** Gets the first free index of a list
 * @param list		List to get index of
 * @return Index, or -1 if list is full
 */
static int recalculateFirstFreeIndex(LinkedList list) {
	int i;
	
	for (i = ll_getFirstFreeIndex(list); i < ll_getMaximumSize(list); i++) {
		if (ll_get(list, i) == NULL)	// Check if index i is unused
			return i;
	}
	
	return -1;	// List full
}

/** Creates a new linked list with a constant (static) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param size		The number of slots for this list
 * @return A new linked list
 */
LinkedList ll_create(int size) {
	LinkedList list = malloc(sizeof(struct LinkedList_s));
	list->auto_size = 0;
	list->size = size;
	list->first_free = 0;
	list->list = malloc(sizeof(void*) * size);
	
	memset(list->list, 0, sizeof(void*) * size);
	
	return list;
}

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @return A new linked list
 */
LinkedList ll_createDynamic() {
	LinkedList list = malloc(sizeof(struct LinkedList_s));
	list->auto_size = SLOT_INC_AMMOUNT;
	list->size = SLOT_INC_AMMOUNT;
	list->first_free = 0;
	list->list = malloc(sizeof(void*) * SLOT_INC_AMMOUNT);
	
	memset(list->list, 0, sizeof(void*) * SLOT_INC_AMMOUNT);
	
	return list;
}

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param growth_rate	The ammount by which to grow the list
 * @return A new linked list
 */
LinkedList ll_createDynamicCustom(int growth_rate) {
	LinkedList list = malloc(sizeof(struct LinkedList_s));
	list->auto_size = growth_rate;
	list->size = growth_rate;
	list->first_free = 0;
	list->list = malloc(sizeof(void*) * growth_rate);
	
	memset(list->list, 0, sizeof(void*) * growth_rate);
	
	return list;
}

/** Destroys (deallocates) a linked list
 * @param list		The list to be destroyed
 */
void ll_destroy(LinkedList list) {
	free(list->list);
	free(list);
	
	return;
}

/** Sets the item at an index to a specified value
 * @param list		The list to set the item in
 * @param index		The index to set
 * @param ptr		The pointer to set the index to
 * @return 0 on success, or -1 if the index is out of bounds
 */
int ll_set(LinkedList list, int index, void* ptr) {
	if (index < list->size) {
		list->list[index] = ptr;
		return 0;
	}
	else {
		return -1;
	}
}

/** Adds a pointer to a list
 * @param list		The list to add to
 * @param ptr		The pointer to add
 * @return Index of pointer on success, -1 if list is full
 */
int ll_put(LinkedList list, void* ptr) {
	int i = ll_getFirstFreeIndex(list);
	
	if (i == -1) {
		// Static List
		if (list->auto_size == 0) {
			return -1;	// List full
		}
		// Dynamic List
		else {
			ll_grow(list, list->auto_size);
			return ll_put(list, ptr);
		}
	}
	list->list[i] = ptr;
	list->first_free = recalculateFirstFreeIndex(list);
	
	return i;
}

/** Grows a linked list by a given ammount
 * @param list		The list to grow
 * @param ammount	The ammount by which to grow the list
 */
void ll_grow(LinkedList list, int ammount) {
	void** new_list = malloc(sizeof(void*) * (list->size + ammount));
	memcpy(new_list, list->list, sizeof(void*) * list->size);
	memset(&new_list[list->size], 0, sizeof(void*) * ammount);
	list->size += ammount;
	free(list->list);
	list->list = new_list;
	
	list->first_free = recalculateFirstFreeIndex(list);
}
