#include "common.h"

static void admin_menu(Train **trains){
    char choice[16];
    for(;;){
        puts("\n========== ADMIN MENU ==========\nA: Add train\nD: Delete train\nL: List trains\nB: Open booking menu\nQ: Sign out");
        read_line("Admin choice: ",choice,sizeof choice);
        if(choice[0]=='a'||choice[0]=='A') add_train(trains);
        else if(choice[0]=='d'||choice[0]=='D') delete_train(trains);
        else if(choice[0]=='l'||choice[0]=='L') show_trains(*trains);
        else if(choice[0]=='b'||choice[0]=='B') booking_menu("admin",*trains);
        else if(choice[0]=='q'||choice[0]=='Q') break;
        else puts("Invalid option.");
    }
}

int main(void){
    char choice[16],user[48];
    Train *trains=load_trains();
    if(!trains) puts("Warning: train list is empty; check write permissions.");
    for(;;){
        puts("\n========== TRAIN TICKET BOOKING APP ==========");
        puts("1: Admin Sign-in");
        puts("2: User Sign-in");
        puts("3: User Sign-up");
        puts("Q: Quit");
        read_line("Choose: ",choice,sizeof choice);
        if(choice[0]=='1'){
            if(signin_user(user)){
                if(!strcmp(user,"admin")) admin_menu(&trains);
                else puts("Access denied: this account is not the admin account.");
            }
        }
        else if(choice[0]=='2'){
            if(signin_user(user)){
                if(!strcmp(user,"admin"))
                    puts("Please use Admin Sign-in for the admin account.");
                else booking_menu(user,trains);
            }
        }
        else if(choice[0]=='3') signup_user();
        else if(choice[0]=='q'||choice[0]=='Q') break;
        else puts("Invalid option. Please choose 1, 2, 3, or Q.");
    }
    save_trains(trains);
    free_trains(trains);
    puts("Thank you for using Train Ticket Booking App.");
    return 0;
}
