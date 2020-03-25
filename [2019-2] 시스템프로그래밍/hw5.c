// hello5_revised.c

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <termio.h>
#include <fcntl.h>
#define LEFTEDGE 10
#define RIGHTEDGE 30
#define ROW 10

char message[] = "Hello";
char blank[] = "     ";
int dir = 1;
int pos = LEFTEDGE;

// terminal
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
// terminal end

void trigger() {
    move(ROW, pos);
    addstr(message);
    move(LINES - 1, COLS - 1);
    
    refresh();
    
    move(ROW, pos);
    addstr(blank);
    pos += dir;
    if (pos >= RIGHTEDGE) dir = -1;
    if (pos <= LEFTEDGE) dir = 1;
}

int set_ticker(int n_msecs) {
    struct itimerval new_timeset;
    long n_sec, n_usecs;
    n_sec = n_msecs / 1000;
    n_usecs = (n_msecs % 1000) * 1000L;

    new_timeset.it_interval.tv_sec = n_sec;
    new_timeset.it_interval.tv_usec = n_usecs;
    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec = n_usecs;
    
    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

int main(int ac, char* av[]) {
    int msec = atoi(av[1]);
    char c;

    tty_mode(0);
    set_echo(0);  // echo off
    set_icanon(0);  // icanon off

    initscr();
    clear();
    
    signal(SIGALRM, trigger);
    
    while (1) { 
        if (set_ticker(msec) == -1) perror("set_ticker");
        
        c = getchar();
        
        if (c == 'p') {
            msec += 50;
        } else if (c == 'm') {
            msec -= 50;
        } else if (c == 'q') {
            endwin();
            tty_mode(1);
            return 0;
        }
    }

    return 0;
}
