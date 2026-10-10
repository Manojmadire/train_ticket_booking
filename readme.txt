TRAIN TICKET BOOKING APP (C / SLL / FILE HANDLING)
=================================================

FILES
- main.c       Main menus and program flow
- common.h     Shared structures, enums, declarations
- utils.c      Input helpers, password policy, journey-date validation
- auth.c       Sign-up and sign-in
- trains.c     Train linked list, loading/saving, train administration
- booking.c    Passenger linked list, reservation, cancellation, details
- Makefile     Build rules
- usr_logins.txt, trains_info.txt, passengers_info.txt are created/updated at runtime.

BUILD (Linux / WSL / macOS with GCC and make)
    make

RUN
    ./myirctc

CLEAN BUILD FILES (keeps saved data)
    make clean

FIRST USE
1. Main menu: 1 = Admin Sign-in, 2 = User Sign-in, 3 = User Sign-up.
2. Create an account named admin with a strong password to use the admin menu.
3. Password must be at least 8 characters and contain uppercase, lowercase, digit, and special character.
4. Sign-in allows three attempts per run.
5. In the user booking menu, use R to reserve, C to cancel, B to view booking details, Q to return to the main menu.
6. Journey date must be YYYY-MM-DD, from today through three days ahead.
7. The admin menu supports adding, deleting (only when no active bookings exist), and listing trains, plus opening booking operations.
8. Sample trains are created automatically the first time the app runs.

ADMIN PAGE
Create an account with username "admin" and a strong password, then sign in.
The admin menu supports A=add train, D=delete train, L=list trains,
B=open the booking menu, and Q=sign out. A train cannot be deleted while
active passenger bookings refer to it; cancel those bookings first. This demo
identifies the admin by username; production software should use secure roles.

DATA FILE FORMAT
- usr_logins.txt: username|password
- trains_info.txt: number|name|source|destination|total_seats
- passengers_info.txt: train_number|date|seat_number|age|name|gender_code|username
Data files remain in the working directory, so existing records persist after
relaunch. Do not manually add the pipe character '|' to fields.

IMPLEMENTATION NOTES / LIMITATIONS
- Uses singly linked lists (SLL) for trains and passengers, structures, pointers,
  dynamic allocation, and file persistence via load/save functions.
- If fewer seats are available than requested, available seats are booked in
  order and the remaining passengers are not booked.
- Cancellations and booking-detail lookup are limited to the signed-in user's
  own bookings. Cancelled passenger records are removed from the saved file,
  so their seat numbers become available for new bookings on the same train/date.
- Admin can add and delete trains. Deletion is blocked while active bookings exist.
- This is an educational local-file demo, not a real railway booking system.
  Passwords are stored in plain text for simplicity; do not reuse real passwords.
- The 5-attempt password rule in the assignment is applied while entering a
  password during sign-up; the 3-attempt rule is applied to sign-in per run.
- Waiting-list handling and timed 5-minute lockout are displayed/outlined in
  the assignment but are not implemented as a real cross-process timer.
