#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void list_directory(char *dirpath) {
  DIR *dir;
  struct dirent *entry;
  struct stat st;

  if (!(dir = opendir(dirpath))) {
    perror("Error opening directory");
    return;
  }

  while ((entry = readdir(dir))) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char fullpath[256];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);

    if (stat(fullpath, &st) == -1) {
      perror("Error getting file status");
      continue;
    }

    if (S_ISDIR(st.st_mode)) {
      printf("%s/\n", entry->d_name);
    } else {
      printf("%s\n", entry->d_name);
    }
  }

  closedir(dir);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: ls <directory>\n");
    return 1;
  }

  char *dirpath = argv[1];
  list_directory(dirpath);

  return 0;
}
