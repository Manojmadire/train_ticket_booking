#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define USER_FILE "usr_logins.txt"
#define TRAIN_FILE "trains_info.txt"
#define PASS_FILE "passengers_info.txt"
#define MAX 128

typedef enum { MALE=1, FEMALE=2, OTHER=3 } Gender;
typedef struct Train { int number; char name[64], source[48], destination[48]; int total_seats; struct Train *next; } Train;
typedef struct Passenger { int train_number, seat_number, age; char date[11], username[48], name[64]; Gender gender; struct Passenger *next; } Passenger;
void read_line(const char *prompt, char *buf, size_t size);
int read_int(const char *prompt, int min, int max);
int valid_password(const char *p);
int signup_user(void);
int signin_user(char *username);
Train *load_trains(void); void save_trains(Train *head); void free_trains(Train *head); void show_trains(Train *head); int add_train(Train **head); int delete_train(Train **head);
Passenger *load_passengers(void); void save_passengers(Passenger *head); void free_passengers(Passenger *head);
void booking_menu(const char *username, Train *trains);
int valid_journey_date(const char *date);
#endif
