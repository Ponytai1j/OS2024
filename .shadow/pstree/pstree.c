#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
void traverse_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char fullpath[1024];

    dir = opendir(path);
    if (dir == NULL) {
        printf("无法打开目录: %s\n", path);
        return;
    }

    printf("目录: %s\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        struct stat st;
        if (stat(fullpath, &st) == -1) {
            printf("无法获取文件信息: %s\n", fullpath);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            traverse_directory(fullpath);  // 递归遍历子目录
        } else {
            printf("文件: %s\n", fullpath);
        }
    }

    closedir(dir);
}
int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]);
  traverse_directory(argv[0]);
  return 0;
}
