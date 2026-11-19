
#include "search.h"
#include "menu.h"

// 1. Display rooms based on status filter
void display_filtered_rooms(RoomList *list, int filter)
{
    Node *temp = list->head;
    int found = 0;

    printf("\n========== ROOM LIST ==========\n");

    while (temp != NULL) {

        int match = 0;

        if (filter == 1)
            match = 1;

        else if (filter == 2 &&
                 temp->data.status == ROOM_AVAILABLE)
            match = 1;

        else if (filter == 3 &&
                 temp->data.status == ROOM_OCCUPIED)
            match = 1;

        else if (filter == 4 &&
                 temp->data.status == ROOM_MAINTENANCE)
            match = 1;

        if (match) {

            printf("\nRoom Number: %d\n",
                   temp->data.room_number);

            printf("Guest Name: %s\n",
                   temp->data.guest_name);

            printf("Price Per Night: %.2f\n",
                   temp->data.price_per_night);

            printf("Status: ");

            if (temp->data.status == ROOM_AVAILABLE)
                printf("Available\n");

            else if (temp->data.status == ROOM_OCCUPIED)
                printf("Occupied\n");

            else
                printf("Maintenance\n");

            found = 1;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("No matching rooms found.\n");
    }
}


// 2. Search guest using name
void search_guest(RoomList *list)
{
    char name[50];
    Node *temp = list->head;
    int found = 0;

    printf("Enter guest name: ");

    read_string(name, sizeof(name));

    while (temp != NULL) {

        if (temp->data.status == ROOM_OCCUPIED &&
            strcmp(temp->data.guest_name, name) == 0) {

            printf("\nGuest found!\n");

            printf("Guest Name: %s\n",
                   temp->data.guest_name);

            printf("Room Number: %d\n",
                   temp->data.room_number);

            printf("Room Price: %.2f\n",
                   temp->data.price_per_night);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("Guest not found!\n");
    }
}


// 3. Search rooms using room type
void search_room_type(RoomList *list)
{
    Node *temp = list->head;
    int type;
    int found = 0;

    printf("\n0. Single Room\n");
    printf("1. Double Room\n");
    printf("2. Suite\n");

    printf("Enter room type: ");

    type = read_integer();

    if (type < ROOM_SINGLE || type > ROOM_SUITE) {
        printf("Invalid room type!\n");
        return;
    }

    while (temp != NULL) {

        if (temp->data.type == (RoomType)type) {

            printf("\nRoom Number: %d\n",
                   temp->data.room_number);

            printf("Guest Name: %s\n",
                   temp->data.guest_name);

            printf("Price Per Night: %.2f\n",
                   temp->data.price_per_night);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("No rooms of this type found.\n");
    }
}


// 4. Generate occupancy and revenue report
void generate_report(RoomList *list)
{
    Node *temp = list->head;

    int available = 0;
    int occupied = 0;
    int maintenance = 0;

    double revenue = 0;

    while (temp != NULL) {

        if (temp->data.status == ROOM_AVAILABLE) {
            available++;
        }

        else if (temp->data.status == ROOM_OCCUPIED) {

            occupied++;

            revenue += temp->data.price_per_night *
                       temp->data.nights_booked;
        }

        else if (temp->data.status == ROOM_MAINTENANCE) {
            maintenance++;
        }

        temp = temp->next;
    }

    printf("\n========== HOTEL REPORT ==========\n");

    printf("Total Rooms: %d\n", list->total_rooms);

    printf("Available Rooms: %d\n", available);

    printf("Occupied Rooms: %d\n", occupied);

    printf("Maintenance Rooms: %d\n", maintenance);

    if (list->total_rooms > 0) {

        printf("Occupancy Percentage: %.2f%%\n",
               occupied * 100.0 / list->total_rooms);
    }
    else {
        printf("Occupancy Percentage: 0.00%%\n");
    }

    printf("Expected Booking Revenue: %.2f\n", revenue);

    printf("==================================\n");
}
