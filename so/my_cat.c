#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 4096

bool number_all = false;
bool number_nonempty = false;
int line_count = 1;

void process_file(int fd) {
  char buffer[BUF_SIZE];
  ssize_t bytes_read;
  bool start_of_line = true;

  while ((bytes_read = read(fd, buffer, BUF_SIZE)) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      char c = buffer[i];

      if (start_of_line) {
        if (number_all || (number_nonempty && c != '\n')) {
          printf("%6d  ", line_count++);
        }
        start_of_line = false;
      }

      putchar(c);

      if (c == '\n') {
        start_of_line = true;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int opt;

  while ((opt = getopt(argc, argv, "nb")) != -1) {
    switch (opt) {
    case 'n':
      number_all = true;
      break;
    case 'b':
      number_nonempty = true;
      break;
    default:
      fprintf(stderr, "Usage: %s [-n | -b] [file ...]\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (number_nonempty)
    number_all = false;

  if (optind == argc) {
    process_file(STDIN_FILENO);
  } else {
    for (int i = optind; i < argc; i++) {
      int fd = open(argv[i], O_RDONLY);
      if (fd == -1) {
        perror(argv[i]);
        continue;
      }
      process_file(fd);
      close(fd);
    }
  }

  return 0;
}
