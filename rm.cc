#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int usage(int status) {
  if (status == 0) {
    puts("Usage: rm [-h | --help] [-c] [-r]");
  } else {
    fputs("Usage: rm [-h | --help] [-c] [-r]\n", stderr);
  }
  exit (status);
}

int main(int argc, char **argv) {
  const option long_options[] = {
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 }
  };

  int c;
  bool create = false;
  bool remove = false;
  while ((c = getopt_long (argc, argv, "hcr", long_options, nullptr)) != -1) {
    switch (c) {
    case 'c':
      create = true;
      break;
    case 'r':
      remove = true;
      break;
    case 'h':
      usage(0);
      break;
    default:
      usage (1);
      return 1;
    }
  }

  if (create && remove) {
    fputs("-r conflicts with -c\n", stderr);
    exit(1);
  }

  if (!(create || remove)) {
    fputs("Need to specify at least -c or -r\n", stderr);
    exit(1);
  }

  const char *filename = "/tmp/test_rm_file";

  if (create) {
    int fd;
    if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
      perror("open");
      return 1;
    }
  } else if (remove) {
    unlink(filename);
  }

  return 0;
}
