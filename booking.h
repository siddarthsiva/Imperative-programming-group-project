#ifndef BOOKING_H
#define BOOKING_H

#include "room.h"

int check_in(RoomList *list, int room_number, const char *guest_name, int nights);
double check_out(RoomList *list, int room_number);
int cancel_reservation(RoomList *list, int room_number);
int change_status(RoomList *list, int room_number, RoomStatus new_status);

#endif