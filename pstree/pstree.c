#include <stdio.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#define MAX_PROCESS_NUM 10000
//const int MAX_PROCESS_NUM = 10000;
int processCnt = 0;
int childId[MAX_PROCESS_NUM];
int parentId[MAX_PROCESS_NUM];
bool is_num(char c){
	if( c >= '1' && c <= '9'){ return true;}
	else {return false;}
}
bool is_string_num(char s[]){
	for (int i = 0;i < strlen(s); i++){
		if(!is_num(s[i])){return false;}
	}
	return true;
}
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

        else {
	    if(S_ISDIR(st.st_mode)){
		if(is_string_num(entry->d_name)){		
		printf("目录: %s\n", fullpath);
        FILE *file = fopen(fullpath, "r");
        if(file == NULL){
            printf("can not open file %s\n", fullpath);
        }
        int MAX_LINE_LENGTH = 100;

        char line[MAX_LINE_LENGTH];
        
        
        int pid, ppid;

        while(fgets(line, MAX_LINE_LENGTH, file) != NULL){
            if (strncmp(line, "Pid:", 4) == 0){
                sscanf(line + 4,"%d", &pid);
                childId[processCnt] = pid;
            }else if (strncmp(line, "PPid:", 5) == 0){
                sscanf(line + 5, "%d", &ppid);
                parentId[processCnt] = ppid;
                processCnt += 1;
            }
        }
        fclose(file);

        // open each process directory's file 'status' , read pid and ppid

		// dir_target = opendir(fullpath);
		// char *file_target = "status";
		// while((entry = readdir(dir)) != NULL){
		// 	if(strcmp(entry->d_name, fileName) == 0){
		// 		char filePath[256];
		// 		snprintf(filepath, sizeof(filePath), "%s%s", dirPath, fileName);
		// //
		// FILE *file = fopen(filePath, "r");
		// if (file != NULL){

		// 	}
		// 		}
		// 	}	
		}
	    }
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
  traverse_directory(argv[1]);
  for(int i = 0;i < processCnt;i++){
    printf("%d-%d\n", childId[i],parentId[i]);
  }
  printf("%d\n",processCnt);
  printf("hello\n");
  return 0;
}
