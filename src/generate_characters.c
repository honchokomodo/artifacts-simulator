#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** CharacterType_keys;
char ** character2str_names;

void process_file_contents(FILE * file)
{
	fseek(file, 0, SEEK_END);
	size_t filesize = ftell(file);
	rewind(file);

	char * buf = malloc(filesize + 1);
	fread(buf, sizeof(*buf), filesize, file);
	buf[filesize] = '\0';

	/*
	typedef enum readmode {
		NOTHING,
		LINE,
		MULTI,
	} ReadMode;
	*/

	printf("file: %zu bytes\n", filesize);
	printf("%s", buf);
	printf("end file\n");
	free(buf);
}

int main(void)
{
	DIR * directory;
	struct dirent * entry;

	char * dirname = "src/characters/";
	directory = opendir(dirname);
	if (directory == NULL) {
		perror("Couldn't open the directory");
		exit(1);
	}

	while (entry = readdir(directory)) {
		if (entry->d_name[0] == '.') {
			continue;
		}

		char fname[300]; // hope that this is enough
		if (strlen(dirname) + strlen(entry->d_name) >= sizeof(fname)) {
			printf("the file name is too long. skipping\n");
			continue;
		}

		snprintf(fname, sizeof(fname), "%s%s", dirname, entry->d_name);
		FILE * file = fopen(fname, "r");
		if (!file) {
			printf("failed to open file %s. bruh\n", fname);
			continue;
		}

		process_file_contents(file);
		fclose(file);
	}

	closedir(directory);

	return 0;
}
