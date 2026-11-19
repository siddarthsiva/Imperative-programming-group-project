#ifndef FILE_IO_H
#define FILE_IO_H

#include "room.h"

int load_rooms_from_file(RoomList *list);
int save_rooms_to_file(RoomList *list);

#endif