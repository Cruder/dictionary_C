#include "input.h"

bool get_int(int *number) {
  char line[256];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%d", number)) {
      return true;
    }
  }
  return false;
}

bool get_double(double *number) {
  char line[256];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%lf", number)) {
      return true;
    }
  }
  return false;
}

bool get_char(char *letter) {
  char line[2];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%c", letter)) {
      return true;
    }
  }
  return false;
}

bool get_string(size_t size, char *str) {
  char line[size + 1];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%s", str)) {
      return true;
    }
  }
  return false;
}

bool get_char_range(char *letter, char min, char max) {
  char line[2];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%c", letter)) {
      if (*letter < min || *letter > max) {
        return false;
      }
      return true;
    }
  }
  return false;
}

bool get_int_range(int *number, int min, int max) {
  char line[256];
  fseek(stdin, 0, SEEK_END);
  if (fgets(line, sizeof(line), stdin)) {
    if (1 == sscanf(line, "%d", number)) {
      if (*number < min || *number > max) {
        return false;
      }
      return true;
    }
  }
  return false;
}

bool is_char_range(char letter, char min, char max) {
  if (letter < min || letter > max) {
    return false;
  }
  return true;
}

bool is_int_range(int number, int min, int max) {
  if (number < min || number > max) {
    return false;
  }
  return true;
}
