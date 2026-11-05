#ifndef ROOM_H
#define ROOM_H

typedef enum {
ROOM_AVAILABLE,
ROOM_OCCUPIED,
ROOM_MAINTENANCE
} RoomStatus;

typedef enum {
ROOM_SINGLE,
ROOM_DOUBLE,
ROOM_SUITE
} RoomType;

typedef struct Room {
int room_number; // Unique identifier (e.g., 101)
char guest_name[50]; // Guest name ("N/A" if available)
RoomType type; // ROOM_SINGLE, ROOM_DOUBLE, ROOM_SUITE
double price_per_night; // Daily rate
int nights_booked; // Duration of stay
RoomStatus status; // AVAILABLE, OCCUPIED, or MAINTENANCE
} Room;

typedef struct Node {
Room data;
struct Node *next;
} Node;

typedef struct {
Node *head;
int total_rooms;
} RoomList;

#endif 