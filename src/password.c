#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "password.h"

char* read_password(void) {

  struct termios newt, oldt;

  tcgetattr(STDIN_FILENO, &oldt); 
  newt = oldt;

  newt.c_lflag &= ~(ICANON | ECHO); 
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  char* password = malloc(PASSWORD_MAX_LEN);

  if (!password) {
    return NULL;
  }

  int len = 0;
  int c;

  while ((c = getchar()) != '\n' && len < PASSWORD_MAX_LEN - 1) {

    if (c == 127 || c == '\b') {
      if (len > 0) {
        len--;
        password[len] = '\0';

        printf("\b \b");
        fflush(stdout);
      }
      continue;
    }

    if (c == '\x1b') {
      int c1 = getchar();
      int c2 = getchar();

      (void) c1; (void) c2;

      continue;
    }

    if (c == '\x03' || c == '\x04') {
      // tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      free(password);
      exit(1);
    }

    password[len++] = c;
    putchar('*');
    putchar(' ');
    fflush(stdout);
  }

  if (len < 7) {
    // printf("\nPassword should be more than or equal to %d.\n", MIN_PASSWORD_LIMIT);
    // tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    free(password);
    return read_password();
  }

  password[len] = '\0';
  putchar('\n'); 

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return password;
}
