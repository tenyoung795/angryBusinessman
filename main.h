#ifndef MAIN_H
#define MAIN_H

#define HIGH_INTERVAL 17
#define LOW_INTERVAL 16

unsigned int which_frame, level;
enum {MENU, GAMEPLAY, ENDING, EXIT} mode;

int main();

void initialize(); /* Initialize the program.*/
void cleanup(); /* Clean up before exiting. */
void sighandler(int signum);
void run();
void menu();
void gameplay();
void process_all();
void ending();

#endif
