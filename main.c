#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "room.h"
#include "linked_list.h"
#include "file_io.h"
#include "booking.h"
#include "search.h"
#include "ui.h"

void add_room(RoomList *list){
    printf("enter room number: ");
    int room_number = read_integer();
    if (room_exists(list, room_number)){
        printf("room %d already exists\n", room_number);
        return;
    }

    printf("0. Single  1. Double  2. Suite\nenter type: ");
    int type = read_integer();

    printf("enter price per night: ");
    double price;
    if (scanf("%lf", &price) != 1){
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    Room r;
    r.room_number = room_number;
    strcpy(r.guest_name, "N/A");
    r.type = (RoomType)type;
    r.price_per_night = price;
    r.nights_booked = 0;
    r.status = ROOM_AVAILABLE;

    insert_room(list, r);
    printf("room %d added\n", room_number);
}

void room_operations(RoomList *list, int room_number){
    Node *node = find_room(list, room_number);
    if (node == NULL){
        printf("room %d not found\n", room_number);
        return;
    }

    while (1){
        display_room_operations_menu();
        int choice = read_integer();

        if (choice == 1){
            printf("room: %d\nguest: %s\ntype: %s\nprice: %.2f\nnights: %d\nstatus: %s\n",
                   node->data.room_number, node->data.guest_name,
                   get_room_type(node->data.type), node->data.price_per_night,
                   node->data.nights_booked, get_room_status(node->data.status));
        } else if (choice == 2){
            char name[50];
            printf("enter guest name: ");
            read_string(name, sizeof(name));
            printf("enter nights: ");
            int nights = read_integer();
            if (check_in(list, room_number, name, nights)){
                printf("check in successful\n");
            } else {
                printf("room not available\n");
            }
        } else if (choice == 3){
            double bill = check_out(list, room_number);
            if (bill >= 0.0){
                printf("total bill: %.2f\n", bill);
            } else {
                printf("room not occupied\n");
            }
        } else if (choice == 4){
            printf("1. Available  2. Maintenance: ");
            int s = read_integer();
            RoomStatus st = (s == 1) ? ROOM_AVAILABLE : ROOM_MAINTENANCE;
            change_status(list, room_number, st);
            printf("status updated\n");
        } else if (choice == 5){
            if (cancel_reservation(list, room_number)){
                printf("reservation cancelled\n");
            } else {
                printf("no booking to cancel\n");
            }
        } else if (choice == 6){
            break;
        }
    }
}

void search_or_select(RoomList *list){
    printf("\n1. Select Room by Number\n2. Search Guest by Name\nenter choice: ");
    int choice = read_integer();
    if (choice == 1){
        printf("enter room number: ");
        int num = read_integer();
        room_operations(list, num);
    } else if (choice == 2){
        search_guest(list);
    }
}

int main(void){
    RoomList list;
    init_list(&list);
    load_rooms_from_file(&list);

    int running = 1;
    while (running){
        display_main_menu();
        int choice = read_integer();

        if (choice == 1){
            display_room_filter_menu();
            int filter = read_integer();
            display_room_table(&list, filter);
        } else if (choice == 2){
            add_room(&list);
        } else if (choice == 3){
            search_or_select(&list);
        } else if (choice == 4){
            generate_report(&list);
        } else if (choice == 5){
            save_rooms_to_file(&list);
            free_list(&list);
            printf("saved and exited\n");
            running = 0;
        }
    }
    return 0;
}
