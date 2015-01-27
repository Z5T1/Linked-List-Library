#pragma once

#include <stdlib.h>
#include <string.h>

/** @file */

/** This is the struct that stores the linked list.
 * @note The typedef LinkedList should be used for managing linked lists.
 */
struct LinkedList_s {
	/** The number of items the list can hold */
	int size;
	
	/** The index of the first free slot in list */		
	int first_free;
	
	/** The pointer to the list */	
	void** list;
	
	/** Whether the list should automatically grow in size 
	 * If true (nonzero) the list will automatically by auto_size if it
	 *   is overfilled
	 * If false (0) the list will not automatically grow. If it is
	 *   overfilled, it will retrun an error
	 */
	int auto_size;
};

typedef struct LinkedList_s* LinkedList;

/** Convienience macro for looping over a list.
 * Iterates over each value of the list, with i pointing to the current
 * index.
 * @param list list to iterate over
 * @param i the variable to store the current index
 */
#define ll_foreach(list,i) for((i) = 0; i < ll_getMaximumSize(list); (i)++)

/** Creates a new linked list with a constant (static) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param size the number of slots for this list
 * @return a new linked list
 */
LinkedList ll_create(int size);

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @return a new linked list
 */
LinkedList ll_createDynamic();

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param growth_rate	The ammount by which to grow the list
 * @return a new linked list
 */
LinkedList ll_createDynamicCustom(int growth_rate);

/** Destroys a linked list
 * @param list the list to be destroyed
 */
void ll_destroy(LinkedList list);

/** Gets the maximum size of a list
 * @param list the list to get the size of
 * @return the maximum number of items list can hold
 */
inline int ll_getMaximumSize(LinkedList list);

/** Gets the first free index of a list
 * @param list the list to get the index of
 * @return the first free index of list, or -1 if list is full
 */
inline int ll_getFirstFreeIndex(LinkedList list);

/** Fetches a pointer at an index
 * @param list the list to fetch from
 * @param index the index to fetch
 * @return the pointer at index, or NULL if index is unused
 */
inline void* ll_get(LinkedList list, int index);

/** Adds a pointer to a list
 * @param list the list to add to
 * @param ptr the pointer to add
 * @return index of pointer on success, -1 if list is full
 */
int ll_put(LinkedList list, void* ptr);

/** Grows a linked list by a given ammount
 * @param list		The list to grow
 * @param ammount	The ammount by which to grow the list
 */
void ll_grow(LinkedList list, int ammount);
