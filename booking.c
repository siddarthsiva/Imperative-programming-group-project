#include<stdio.h>
#include<string.h>
#include "booking.h"
#include "linked_list.h"

int check_in(RoomList *list, int room_number, const char *guest_name, int nights){
    Node *node = find_room(list, room_number);
    if (node == NULL || node->data.status != ROOM_AVAILABLE){
        return 0;
    }
    strcpy(node->data.guest_name, guest_name);
    node->data.nights_booked = nights;
    node->data.status = ROOM_OCCUPIED;
    return 1;
}

double check_out(RoomList *list, int room_number){
    Node *node = find_room(list, room_number);
    if (node == NULL || node->data.status != ROOM_OCCUPIED){
        return -1.0;
    }
    double total = node->data.price_per_night * node->data.nights_booked;
    strcpy(node->data.guest_name, "N/A");
    node->data.nights_booked = 0;
    node->data.status = ROOM_AVAILABLE;
    return total;
}

int cancel_reservation(RoomList *list, int room_number){
    Node *node = find_room(list, room_number);
    if (node == NULL || node->data.status != ROOM_OCCUPIED){
        return 0;
    }
    strcpy(node->data.guest_name, "N/A");
    node->data.nights_booked = 0;
    node->data.status = ROOM_AVAILABLE;
    return 1;
}

int change_status(RoomList *list, int room_number, RoomStatus new_status){
    Node *node = find_room(list, room_number);
    if (node == NULL){
        return 0;
    }
    if (new_status == ROOM_AVAILABLE && node->data.status == ROOM_OCCUPIED){
        strcpy(node->data.guest_name, "N/A");
        node->data.nights_booked = 0;
    }
    node->data.status = new_status;
    return 1;
}