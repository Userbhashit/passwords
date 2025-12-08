#include <stdio.h>
#include <fcntl.h>
#include <sys/_types/_ssize_t.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "password.h"

static struct termios oldt;

static void restore_terminal(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
} 

static void handle_signal(int sig) {
  restore_terminal();

  signal(sig, SIG_DFL);
  kill(getpid(), sig);
}

char* read_password(void) {

  struct termios newt;

  // Save old terminal settings to oldt
  tcgetattr(STDIN_FILENO, &oldt); 
  newt = oldt;

  // Turn off raw and echo mode
  newt.c_lflag &= ~(ICANON | ECHO); 
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  char* password = malloc(PASSWORD_MAX_LEN);

  if (!password) {
    return NULL;
  }

  // Handle control c and segmentation fault
  atexit(restore_terminal);
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);
  signal(SIGSEGV, handle_signal);

  int len = 0;
  int c;

  while ((c = getchar()) != '\n' && len < PASSWORD_MAX_LEN - 1) {

    // Backspace key
    if (c == 127 || c == '\b') {
      if (len > 0) {
        len--;
        password[len] = '\0';

        printf("\b \b");
        fflush(stdout);
      }
      continue;
    }

    // Ignore arrow keys
    if (c == '\x1b') {
      getchar(); getchar();

      continue;
    }

    password[len++] = c;
    putchar('*');
    fflush(stdout);
  }
  
  password[len] = '\0';
  putchar('\n'); 

  restore_terminal();

  return password;
}

void password_secure_erase(void* buffer, size_t len) {

  volatile unsigned char* p = buffer;

  while (len--) {
    *p++ = 0;
  }    
}

int generate_salt(unsigned char* salt) {
  int fd = open("/dev/urandom", O_RDONLY);
  
  if (fd < 0) {
    perror("Can't genrate salt.");
  }

  ssize_t bytes = read(fd, salt, PASSWORD_SALT_LEN);
  close(fd);

  if (bytes == -1) {
    perror("Error reading from /dev/random.");
    return -1;
  }

  if ((size_t)bytes != PASSWORD_SALT_LEN) {
    fprintf(stderr, "Warning: Only %zd bytes read from /dev/urandom, expected %zu\n", bytes, PASSWORD_SALT_LEN);
    return -1;
  }

  return 0;
}
