
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "ui.h"

// Clear extra characters from input buffer
void clear_input_buffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

// Read an integer safely
int read_integer(void)
{
    int number;

    while (scanf("%d", &number) != 1)
    {
        printf("Invalid input. Enter a number: ");

        clear_input_buffer();
    }

    clear_input_buffer();

    return number;
}

// Read a string safely
void read_string(char *str, int size)
{
    if (fgets(str, size, stdin) == NULL)
    {
        str[0] = '\0';
        return;
    }

    int i = 0;

    while (str[i] != '\0' && str[i] != '\n')
    {
        i++;
    }

    if (str[i] == '\n')
    {
        str[i] = '\0';
    }
    else
    {
        clear_input_buffer();
    }
}
// Main Front Desk Menu
void display_main_menu(void)
{
    printf("\n========== HOTEL FRONT DESK ==========\n");
    printf("1. List All Rooms\n");
    printf("2. Add a New Room to Inventory\n");
    printf("3. Select / Search Room or Guest Name\n");
    printf("4. Generate End-of-Day Report\n");
    printf("5. Save and Exit\n");
    printf("Enter your choice: ");
}

// Room Filter Menu
void display_room_filter_menu(void)
{
    printf("\n========== ROOM FILTER ==========\n");
    printf("1. All Rooms\n");
    printf("2. Available Rooms\n");
    printf("3. Occupied Rooms\n");
    printf("4. Maintenance Rooms\n");
    printf("Enter your choice: ");
}



// Get room status as text
const char *get_room_status(RoomStatus status)
{
    switch (status)
    {
        case ROOM_AVAILABLE:
            return "Available";

        case ROOM_OCCUPIED:
            return "Occupied";

        case ROOM_MAINTENANCE:
            return "Maintenance";

        default:
            return "Unknown";
    }
}

// Get room type as text
const char *get_room_type(RoomType type)
{
    switch (type)
    {
        case ROOM_SINGLE:
            return "Single";

        case ROOM_DOUBLE:
            return "Double";

        case ROOM_SUITE:
            return "Suite";

        default:
            return "Unknown";
    }
}

// Display rooms in formatted table
void display_room_table(RoomList *list, int filter)
{
    Node *current;
    int found = 0;

    if (list == NULL || list->head == NULL)
    {
        printf("\nNo rooms available.\n");
        return;
    }

    printf("\n");
    printf("---------------------------------------------------------------\n");
    printf("%-10s %-15s %-12s %-12s %-15s\n",
           "Room No.", "Guest Name", "Type", "Price/Night", "Status");
    printf("---------------------------------------------------------------\n");

    current = list->head;

    while (current != NULL)
    {
        Room room = current->data;

        if (filter == 1 ||
            (filter == 2 && room.status == ROOM_AVAILABLE) ||
            (filter == 3 && room.status == ROOM_OCCUPIED) ||
            (filter == 4 && room.status == ROOM_MAINTENANCE))
        {
            printf("%-10d %-15s %-12s %-12.2f %-15s\n",
                   room.room_number,
                   room.guest_name,
                   get_room_type(room.type),
                   room.price_per_night,
                   get_room_status(room.status));

            found = 1;
        }

        current = current->next;
    }

    printf("---------------------------------------------------------------\n");

    if (found == 0)
    {
        printf("No rooms found for this filter.\n");
    }
}
