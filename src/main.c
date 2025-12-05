#include <stdio.h>
#include <password.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

// #define MAX_PASSWORD_LIMIT 100
// #define MIN_PASSWORD_LIMIT 7
//
// static struct termios oldt, newt;
//
// static void enable_raw_mode(void) {
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
// }
//
// static void disable_raw_mode(void) {
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
// }
//
// char* getPassword(void) {
//   char* password = malloc(MAX_PASSWORD_LIMIT);
//
//   if (!password) {
//     return NULL;
//   }
//
//   int len = 0;
//   int c;
//
//   while ((c = getchar()) != '\n' && len < MAX_PASSWORD_LIMIT - 1) {
//
//     if (c == 127 || c == '\b') {
//       if (len > 0) {
//         len--;
//         password[len] = '\0';
//
//         printf("\b \b");
//         fflush(stdout);
//       }
//       continue;
//     }
//
//     if (c == '\x1b') {
//       int c1 = getchar();
//       int c2 = getchar();
//
//       (void) c1; (void) c2;
//
//       continue;
//     }
//
//     if (c == '\x03' || c == '\x04') {
//       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//       free(password);
//       exit(1);
//     }
//
//     password[len++] = c;
//     putchar('*');
//     putchar(' ');
//     fflush(stdout);
//   }
//
//   if (len < MIN_PASSWORD_LIMIT) {
//     printf("\nPassword should be more than or equal to %d.\n", MIN_PASSWORD_LIMIT);
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//     free(password);
//     return getPassword();
//   }
//
//   password[len] = '\0';
//   putchar('\n'); 
//
//   return password;
// }
//
// bool verifyPassword(const char* password) {  
//
//   enable_raw_mode(); 
//
//   char* tempPassword = getPassword();
//
//   int len = 0;
//   char c;
//
//   fprintf(stdout, "Verify password: ");
//   while ((c = getchar()) != '\n' && password[len] != '\0') {
//     if (password[len] != c) {
//       return false;
//     } else {
//       putchar('*');
//       len++;
//     }
//   }
//
//   putchar('\n');
//
//   disable_raw_mode();
//
//   return true;
// }
//
int main(void) {
  // char* pass = getPassword();
  //
  // if (!verifyPassword(pass)) {
  //   fprintf(stderr, "Password did not match.");
  // }

  // free(pass);

  
  printf("Passwords are important.\n");

  return 0;
}
