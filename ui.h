#ifndef UI_H
#define UI_H

#include "room.h"

// Input functions
int read_integer(void);
void read_string(char *str, int size);
void clear_input_buffer(void);

// Menu functions
void display_main_menu(void);
void display_room_filter_menu(void);
void display_room_operations_menu(void);

// Display rooms in table format
void display_room_table(RoomList *list, int filter);

// Helper display text functions
const char *get_room_status(RoomStatus status);
const char *get_room_type(RoomType type);

#endif
