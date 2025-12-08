#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#include "password.h"

int main(void) {
  char* pass = read_password();
  password_secure_erase(pass, strlen(pass));

  unsigned char salt[PASSWORD_SALT_LEN];
  generate_salt(salt); 

  free(pass);

  return 0;
}
