#include <stdio.h>          
#include "file_io.h"        
#include "linked_list.h"    
int load_rooms_from_file(RoomList *list)  
{
    FILE *file = fopen("rooms.dat", "rb"); // open rooms.dat for reading in binary mode

    if (file == NULL)                      // file could not be opened (e.g. first run, no file yet)
    {
        return 1;                          // not an error: just start with an empty list
    }

    Room room;                             // temporary variable to hold one room read from the file

    while (fread(&room, sizeof(Room), 1, file) == 1)  // read one Room record; loop continues while a full record was read
    {
        if (insert_room(list, Room) == 0)  // add that room to the end of the list; 0 means malloc failed
        {
            fclose(file);                  // close the file before leaving
            return 0;                      
        }
    }

    if (ferror(file))                      // after the loop: did it stop because of a read error (not just end of file)?
    {
        fclose(file);                     
        return 0;                          
    }

    fclose(file);                          
    return 1;                              
}

int save_rooms_to_file(RoomList *list){     
    FILE *file = fopen("rooms.tmp", "wb"); // open a TEMPORARY file for writing, so rooms.dat stays safe if saving fails

    if (file == NULL)                      
    {
        return 0;                          
    }

    Node *current = list->head;            // start at the first node of the list

    while (current != NULL)                // walk through every node until the end of the list
    {
        if (fwrite(&current->data, sizeof(Room), 1, file) != 1)  // write this node's Room struct (not the next pointer) to the file
        {
            fclose(file);                  // writing failed, close the temp file
            remove("rooms.tmp");           // delete the incomplete temp file
            return 0;                      
        }

        current = current->next;           // move on to the next node
    }

    if (fclose(file) != 0)                 // close the temp file; a failure here means the data may not be fully saved
    {
        remove("rooms.tmp");               // delete the temp file
        return 0;                          
    }

    if (rename("rooms.tmp", "rooms.dat") != 0)  // everything was written, so replace the old rooms.dat with the new file
    {
        remove("rooms.tmp");               // rename failed, clean up the temp file
        return 0;                          
    }

    return 1;                              
}