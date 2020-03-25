// hw4.c

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <termio.h>
#include <fcntl.h>
#include <stdlib.h>

void set_icanon(int op) {  // 0: off, 1: on
    struct termios ttystate;

    tcgetattr(0, &ttystate);
    if (!op) {
        ttystate.c_lflag &= ~ICANON;
    } else {
        ttystate.c_lflag |= ICANON;
    }
    tcsetattr(0, TCSANOW, &ttystate);
}

void set_echo(int op) {  // 0: off, 1: on
    struct termios ttystate;

    tcgetattr(0, &ttystate);
    if (!op) {
        ttystate.c_lflag &= ~ECHO;
    } else {
        ttystate.c_lflag |= ECHO;
    }
    tcsetattr(0, TCSANOW, &ttystate);
}

void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    static int stored = 0;

    if (how == 0) {  // save original mode, flags
        tcgetattr(0, &original_mode);
        original_flags = fcntl(0, F_GETFL);
        stored = 1;
    } else {  // restore
        tcsetattr(0, TCSANOW, &original_mode);
        original_flags = fcntl(0, F_GETFL, original_flags);
    }
}

int main() {
    char c;
    int currmode = 0;  // 0: command, 1: insert

    tty_mode(0);
    set_echo(0);  // echo off
    set_icanon(0);  // icanon off

    while (1) {
        c = getchar();

        if (!currmode) {
            // command mode
            switch (c) {
                case 'i':
                    currmode = 1;
                    printf("\ninsert mode!\n");
                    break;
                case '1':
                    set_echo(1);
                    printf("\necho on!\n");
                    break;
                case '2':
                    set_echo(0);
                    printf("\necho off!\n");
                    break;
                case 'q':
                    tty_mode(1);
                    return 0;
                default:
                    continue;
            }
        } else {
            // insert mode
            switch (c) {
                case 27:
                    currmode = 0;
                    printf("\ncommand mode!\n");
                    break;
                default:
                    if (c == 'z') c = 'a';
                    else if (islower(c)) c++;
                    putchar(c);
                    break;
            }
        }
    }

    return 0;
}
