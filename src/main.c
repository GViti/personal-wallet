#include <errno.h>   // Provides errno and EINTR for interrupted reads.
#include <stdio.h>
#include <string.h>
#include <termios.h> // Provides POSIX terminal settings and their flags.
#include <unistd.h>  // Provides read() and STDIN_FILENO.
#include "credentials.h"

void draw_main_menu(int selected); // Declare the function that draws three option rows.
int select_main_menu(void); // Declare the function that reads keys and returns a choice.
int login(void);
void register_user(void);

// ======================================
// 1) TO DO
// The code is becoming too big
// Split it into different file and folders
// ======================================

int main(void) {
    int user_menu_choice;
    int running = 1;
    int current_menu = 0;

    puts("===================================");
    puts("         Personal Wallet");
    puts("===================================\n");

    while (running){

        if(current_menu == 0){
            user_menu_choice = select_main_menu(); // Wait for Enter or a request to quit.
            if (user_menu_choice < 0) { // A negative result reports a terminal error.
                return 1; // End the program with a failure status.
            }
            if (user_menu_choice == 0) { // Zero means Ctrl+C or Ctrl+D requested exit.
                puts("Goodbye!"); 
                break; 
            }

            if (user_menu_choice == 1) {
                // Redirect to Login
                current_menu = 1;
            } else if (user_menu_choice == 2) {
                // Redirect to registration
                current_menu = 2;
            } else if (user_menu_choice == 3) {
                // Exit the program
                puts("See you next time!");
                running = 0;
            }
        } else if (current_menu == 1){
            // Here we are at the login page
            // If the username and password are right the function return 1, either 0
            int login_result = login();

            if(login_result == 1){
                // Actually if the login goes right the program end, but that not what I actually need
                // ======================================
                // 4) TO DO
                // Improve a better menu navigation to go at the right page
                // ======================================
                puts("Your credentials are right\n");
                running = 0;
            } else {
                // If the credential are wrong the login function start again
                puts("\nYour credentials are wrong! Please try again!\n");
            }

        } else if (current_menu == 2){
            register_user();
            running = 0;
        }
        
        
        
    }

    return 0;
}

// ======================================
// 4.1) TO DO
// Check for unnecessary code and understand everything of new logic implemented with AI for arrow keys menu control
// ======================================
// Print only the options; leave the cursor on the line immediately below them.
void draw_main_menu(int selected) { // selected is the highlighted index, from 0 to 2.
    const char *options[] = {"Login", "Register", "Exit"}; // An array of three string pointers.
    for (int i = 0; i < 3; i++) { // Visit each option in order.
        // Carriage return goes to column one; ESC[2K erases this row before replacing it.
        printf("\r\033[2K%s %s\n", i == selected ? ">" : " ", options[i]);
    }
    fflush(stdout); // Send pending output to the terminal before waiting for a key.
}

// Returns 1..3 for a choice, 0 to quit, or -1 on an error.
int select_main_menu(void) {
    struct termios original; // Stores the terminal settings so we can restore them.
    if (tcgetattr(STDIN_FILENO, &original) == -1) { // Read settings into original through its address.
        perror("The arrow menu requires an interactive terminal"); // Describe the operating-system error.
        return -1; // Tell main that setup failed.
    }

    struct termios menu_settings = original; // Copy the settings before changing any flags.
    // Turn off line buffering, typed-character echo, and automatic keyboard signals.
    menu_settings.c_lflag &= ~(ICANON | ECHO | ISIG);
    menu_settings.c_cc[VMIN] = 0; // A read may return without receiving a character.
    menu_settings.c_cc[VTIME] = 1; // The read timeout is one tenth of a second.
    if (tcsetattr(STDIN_FILENO, TCSANOW, &menu_settings) == -1) { // Apply these settings immediately.
        perror("Unable to configure terminal"); // Describe why applying the settings failed.
        return -1; // Stop because keyboard setup did not succeed.
    }

    int selected = 0; // Initially highlight Login, whose array index is zero.
    int escape_state = 0; // 0: no prefix; 1: received ESC; 2: received ESC[ or ESCO.
    int result = 0; // Keep zero unless Enter selects an option or an error occurs.
    puts("Use Up/Down arrows and Enter. Ctrl+C or Ctrl+D exits.\n"); // Print instructions only once.
    draw_main_menu(selected); // Draw the initial three rows below the instructions.

    for (;;) { // Read keys repeatedly until a break leaves this loop.
        unsigned char key; // Holds one byte of keyboard input.
        ssize_t count = read(STDIN_FILENO, &key, 1); // Ask the operating system for one byte.
        if (count < 0) { // A negative byte count indicates a read error.
            if (errno == EINTR) { // An unrelated signal interrupted the read.
                continue; // Retry reading rather than treating interruption as failure.
            }
            perror("Unable to read menu key"); // Report other read errors.
            result = -1; // Remember failure while still allowing terminal cleanup below.
            break; // Stop reading and proceed to cleanup.
        }
        if (count == 0) { // No byte arrived before the timeout.
            escape_state = 0; // Discard any unfinished arrow-key prefix.
            continue; // Wait for another key without drawing anything.
        }
        if (key == 3 || key == 4) { // These byte values represent Ctrl+C and Ctrl+D.
            break; // Leave with result zero, then restore the terminal.
        }
        if (key == '\n' || key == '\r') { // Accept either common Enter representation.
            result = selected + 1; // Convert indexes 0..2 to main's choices 1..3.
            break; // Selection is complete; proceed to terminal cleanup.
        }

        int previous = selected; // Remember the old highlight to detect a real change.
        if (key == '\033') { // An ESC byte can start an arrow-key sequence.
            escape_state = 1; // Expect the next byte to be '[' or 'O'.
        } else if (escape_state == 1 && (key == '[' || key == 'O')) { // Recognize either common prefix.
            escape_state = 2; // The next byte should describe the arrow direction.
        } else if (escape_state == 2) { // Interpret the last byte of the sequence.
            if (key == 'A' && selected > 0) { // Up moves only if we are below the first option.
                selected--; // Move the highlight one row upward.
            } else if (key == 'B' && selected < 2) { // Down moves only above the last option.
                selected++; // Move the highlight one row downward.
            }
            escape_state = 0; // The sequence is finished, even if its final byte was unsupported.
        } else { // An ordinary or unsupported key has no menu action.
            escape_state = 0; // Reset sequence parsing and leave the selection unchanged.
        }
        if (selected != previous) { // Redraw only when an arrow actually changed the selection.
            fputs("\033[3A", stdout); // Move up three rows to the first existing option.
            draw_main_menu(selected); // Replace those same rows; do not append another menu.
        }
    }

    if (tcsetattr(STDIN_FILENO, TCSANOW, &original) == -1) { // Restore normal input on every handled exit.
        perror("Unable to restore terminal"); // Report a failure to restore the saved settings.
        return -1; // Tell main that cleanup failed.
    }
    putchar('\n'); // Separate the menu from the next page or exit message.
    return result; // Return the selected choice, quit request, or error to main.
}

int login(void){

    // Maximum size of username and password 49 char (the last one is reserved for \0 char)
    char username[50]; 
    char password[50];

    puts("\n========== LOGIN ==========");

    fputs("Username: ", stdout);
    scanf("%49s", username);

    // ======================================
    // 5) TO DO
    // Improve a bettter password input. Hide the password while writing it in the terminal (use *****)
    // ======================================
    fputs("Password: ", stdout);
    scanf("%49s", password);

    // If the user put the right credential in the terminal (if they are the same of the constant)
    // ======================================
    // 6) TO DO
    // Implement a better and safer solution for storing username and password value
    // ======================================
    if(strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0){
        return 1;
    }

    return 0;

}

void register_user(void){

    puts("\n======== REGISTER =========");
    // ======================================
    // 7) TO DO 
    // Implement register new user function
    // ======================================

}
