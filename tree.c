#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static int isDirectory(const char *fullPath) {
  struct stat st;

  if (stat(fullPath, &st) == 0) {
    return S_ISDIR(st.st_mode);
  }

  return 1;
}

static void getFiles(char path[4096], char prefix[1024]) {
  DIR *d;
  struct dirent *dir;
  char fullPath[4096];
  char newPrefix[1024];

  d = opendir(path);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)) {
        continue;
      }

      snprintf(fullPath, sizeof(fullPath), "%s/%s", path, dir->d_name);
      if (isDirectory(fullPath)) {
        printf("%s├── %s\n", prefix, dir->d_name);
        snprintf(newPrefix, sizeof(newPrefix), "%s│  ", prefix);
        getFiles(fullPath, newPrefix);
      } else {
        printf("%s├── %s\n", prefix, dir->d_name);
      }
    }
    closedir(d);
  }
}

int main(int argc, char **argv) {
  char dumb[1024] = "";
  if (argc < 2) {
    return 1;
  }

  getFiles(argv[1], dumb);

  return 0;
}