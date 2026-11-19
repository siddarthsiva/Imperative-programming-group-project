#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void init_list(RoomList *list)
{
    // This is an empty list that has no first node and has zero rooms initially.
    list->head = NULL;
    list->total_rooms = 0;
}

Node *create_node(Room room)
{
    Node *new_node = (struct Node *)malloc(sizeof(Node));

    // The if statement is to check if malloc returns NULL when memory runs out.
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->data = room; // Copies the whole Room struct into the node.
    new_node->next = NULL; // New node is not linked to anything yet.
    return new_node;
}

int insert_room(RoomList *list, Room room)
{
    Node *new_node = create_node(room);
    if (new_node == NULL)
    {
        return 0;
    }
    if (list->head == NULL)
    {
        list->head = new_node; // This node becomes the first node.
    }
    else
    {
        // Moving until we reach last node
        Node *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    list->total_rooms++;
    return 1;
}

Node *find_room(RoomList *list, int room_number)
{
    Node *current = list->head;

    // Go through the list until we find a match or run out of nodes.
    while (current != NULL)
    {
        if (current->data.room_number == room_number)
        {

            return current;
        }
        current = current->next;
    }
    return NULL;
}

int room_exists(RoomList *list, int room_number)
{
    // If the room is missing it gives null when we find a room.
    return find_room(list, room_number) != NULL;
}
int delete_room(RoomList *list, int room_number)
{
    Node *previous = NULL; // This is the node just before current.
    Node *current = list->head;

    while (current != NULL)
    {
        if (current->data.room_number == room_number)
        {
            if (previous == NULL)
            {
                // Deleting the first node so that the head moves ahead
                list->head = current->next;
            }
            else
            {
                // Skip over the node being removed
                previous->next = current->next;
            }
            free(current);
            list->total_rooms--;
            return 1;
        }

        previous = current;
        current = current->next;
    }
    return 0; // List was empty
}

void free_list(RoomList *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        // Need to save the next node first so that we dont lose access once we free this one
        Node *next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->total_rooms = 0;
}
