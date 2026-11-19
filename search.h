
#ifndef SEARCH_H
#define SEARCH_H

#include "room.h"

// Display rooms based on status
void display_filtered_rooms(RoomList *list, int filter);

// Search guest by name
void search_guest(RoomList *list);

// Search rooms by type
void search_room_type(RoomList *list);

// Generate occupancy and revenue report
void generate_report(RoomList *list);

#endif
