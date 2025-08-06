#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count;
size_t capacity;
char ** type_keys;
char ** str_names;
char ** bonus_funcs;
char ** bonus_impls;

// can be replaced by strndup when compilers update to c23
char * allocstr(char const * const buf, size_t len)
{
	char * out = malloc(len + 1);
	if (!out) return NULL;
	memcpy(out, buf, len);
	out[len] = '\0';
	return out;
}

void process_file_contents(FILE * file)
{
	// this method of getting the file size only works properly on
	// unixy/posixy files
	fseek(file, 0, SEEK_END);
	// i know that this can only handle files of up to 2 GiB but if the
	// file is that big then something is very wrong
	int filesize = ftell(file);
	rewind(file);

	char * buf = malloc(filesize + 1);
	if (!buf) return;
	fread(buf, sizeof(*buf), filesize, file);
	buf[filesize] = '\0';

	// i know that this can only handle files of up to 2 GiB but if the
	// file is that big then something is very wrong
	int start = 0;
	int multistart = 0;

	static char const key[] = "// AUTOGEN CharacterType ";
	static char const name[] = "// AUTOGEN character2str ";
	static char const bonus[] = "// AUTOGEN character2bonus ";
	static char const end[] = "// AUTOGEN end"; // no space here

	for (int cur = 0; cur < filesize; cur++) {
		if (buf[cur] != '\n')
			continue;

		// at this point, the chars from start to cur (inclusive) are
		// part of the line, and cur is the \n at the end of the line

		// is it a special line that we are responsible for?
		if (strncmp(key, buf + start, strlen(key)) == 0) {
			start += strlen(key);
			type_keys[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(name, buf + start, strlen(name)) == 0) {
			start += strlen(key);
			str_names[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(bonus, buf + start, strlen(bonus)) == 0) {
			start += strlen(bonus);
			bonus_funcs[count] = allocstr(buf + start, cur - start);
			multistart = cur + 1;

		} else if (strncmp(end, buf + start, strlen(end)) == 0) {
			// copy everything from i = multistart; i < start
			bonus_impls[count] = allocstr(buf + multistart, start - multistart);
		}

		start = cur + 1;
	}

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

	count = 0;
	capacity = 1;
	type_keys = calloc(capacity, sizeof(*type_keys));
	str_names = calloc(capacity, sizeof(*str_names));
	bonus_funcs = calloc(capacity, sizeof(*bonus_funcs));
	bonus_impls = calloc(capacity, sizeof(*bonus_impls));

	while (entry = readdir(directory)) {
		if (count >= capacity) {
			capacity *= 2;
			type_keys = realloc(type_keys, capacity * sizeof(*type_keys));
			str_names = realloc(str_names, capacity * sizeof(*str_names));
			bonus_funcs = realloc(bonus_funcs, capacity * sizeof(*bonus_funcs));
			bonus_impls = realloc(bonus_impls, capacity * sizeof(*bonus_impls));
		}

		type_keys[count] = NULL;
		str_names[count] = NULL;
		bonus_funcs[count] = NULL;
		bonus_impls[count] = NULL;

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

		count += 1;
	}

	closedir(directory);

	/*
	printf("type_keys:\n");
	for (int i = 0; i < count; i++)
		if (type_keys[i] != NULL)
			printf("start--%s--end\n", type_keys[i]);
	printf("str_names:\n");
	for (int i = 0; i < count; i++)
		if (str_names[i] != NULL)
			printf("start--%s--end\n", str_names[i]);
	printf("bonus_funcs:\n");
	for (int i = 0; i < count; i++)
		if (bonus_funcs[i] != NULL)
			printf("start--%s--end\n", bonus_funcs[i]);
	printf("bonus_impls:\n");
	for (int i = 0; i < count; i++)
		if (bonus_impls[i] != NULL)
			printf("start--%s--end\n", bonus_impls[i]);
			*/

	FILE * type_keys_file = fopen("build/include/characters_enum.h", "w");
	if (!type_keys_file) {
		printf("failed to create characters_enum.h");
		exit(1);
	}

	fprintf(type_keys_file, "#ifdef CHARACTERS_ENUM_H\n"
			"#define CHARACTERS_ENUM_H\n"
			"typedef enum character_type {\n"
			"\tCHARACTER_NOTHING,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL)
			fprintf(type_keys_file, "\t%s,\n", type_keys[i]);
		else
			fprintf(type_keys_file, "\tNIL%d,\n", i);
	}
	fprintf(type_keys_file, "} CharacterType;\n"
			"#endif");

	return 0;
}
