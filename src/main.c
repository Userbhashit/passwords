#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "password.h"
int main(void) {
  char* pass = read_password();
  //
  // if (!verifyPassword(pass)) {
  //   fprintf(stderr, "Password did not match.");
  // }

  printf("Passwords are important: %s.\n", pass);
  free(pass);

  
  printf("Passwords are important.\n");

  return 0;
}
