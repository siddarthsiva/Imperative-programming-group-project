#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "room.h"

/*Setting up an empty list*/
void init_list(RoomList *list);

// Creating a new node and if the malloc fails, returns NULL
Node *create_node(Room room);

// Adding a room to the end of the list. Returns 1 if added otherwise returns 0.
int insert_room(RoomList *list, Room room);

// Looking for a room by its number. Returns its node, otherwise returns NULL if not found.
Node *find_room(RoomList *list, int room_number);

// Returns 1 if the room number is already in the list otherwise returns 0.
int room_exists(RoomList *list, int room_number);

// Removes a room by number. Returns 1 if removed, otherwise returns 0 if not found.
int delete_room(RoomList *list, int room_number);

// Free the nodes
void free_list(RoomList *list);

#endif