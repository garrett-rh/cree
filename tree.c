#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static int isDirectory(const char *fullPath) {
  struct stat st;

  if (stat(fullPath, &st) == 0) {
    return S_ISDIR(st.st_mode);
  }

  return 1;
}

static void getFiles(char path[4096], char prefix[1024], int depth, int files) {
  DIR *d;
  struct dirent *dir;
  char fullPath[4096];
  char newPrefix[1024];

  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (depth == 0) {
        break;
      }

      if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)) {
        continue;
      }

      snprintf(fullPath, sizeof(fullPath), "%s/%s", path, dir->d_name);
      if (isDirectory(fullPath)) {
        printf("%s├── %s\n", prefix, dir->d_name);
        snprintf(newPrefix, sizeof(newPrefix), "%s│  ", prefix);
        depth--;
        getFiles(fullPath, newPrefix, depth, files);
        depth++;
      } else if (files) {
        printf("%s├── %s\n", prefix, dir->d_name);
      }
    }
    closedir(d);
  }
}

int main(int argc, char **argv) {
  char dumb[1024] = "";
  char path[4096] = ".";
  int files = 0;
  int depth = -100;
  int option;

  while ((option = getopt(argc, argv, ":p:fd:h")) != -1) {
    switch (option) {
      case 'p':
        strncpy(path, optarg, sizeof(path));
        break;
      case 'f':
        files = 1;
        break;
      case 'd':
        depth = atoi(optarg);
        break;
      case 'h':
        printf("tree\n");
        printf("-p <path>\ttakes the path to run tree on\n");
        printf("-d <depth>\ttakes an int as the upper depth\n");
        printf(
            "-f\t set this variable if you want to see the directories & "
            "files\n");
        printf("-h\t print this page\n");
        exit(0);
      case ':':
        printf("one of the specified options needs a value\n");
        break;
      case '?':
        printf("unknown option: %c\n", option);
        break;
      default:
        exit(1);
    }
  }

  getFiles(path, dumb, depth, files);

  return 0;
}
