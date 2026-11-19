CC = gcc

hotel: main.c linked_list.c file_io.c booking.c search.c ui.c
	$(CC) -o hotel main.c linked_list.c file_io.c booking.c search.c ui.c

clean:
	rm -f hotel hotel.exe
