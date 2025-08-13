#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count;
size_t capacity;
char ** type_keys;
char ** str_names;
char ** icons;
char ** portraits;
char ** talent_funcs;
char ** talent_impls;
char ** gen_funcs;
char ** gen_impls;
char ** ui_funcs;
char ** ui_impls;

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
	char ** dest = NULL;

	static char const key[] = "// AUTOGEN CharacterType ";
	static char const name[] = "// AUTOGEN character2str ";
	static char const icon[] = "// AUTOGEN character2icon ";
	static char const portrait[] = "// AUTOGEN character2portrait ";
	static char const talent[] = "// AUTOGEN character2talent ";
	static char const gen[] = "// AUTOGEN character2generator ";
	static char const ui[] = "// AUTOGEN character2ui ";
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
			start += strlen(name);
			str_names[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(icon, buf + start, strlen(icon)) == 0) {
			start += strlen(icon);
			icons[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(portrait, buf + start, strlen(portrait)) == 0) {
			start += strlen(portrait);
			portraits[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(talent, buf + start, strlen(talent)) == 0) {
			start += strlen(talent);
			talent_funcs[count] = allocstr(buf + start, cur - start);
			dest = talent_impls + count;
			multistart = cur + 1;

		} else if (strncmp(gen, buf + start, strlen(gen)) == 0) {
			start += strlen(gen);
			gen_funcs[count] = allocstr(buf + start, cur - start);
			dest = gen_impls + count;
			multistart = cur + 1;

		} else if (strncmp(ui, buf + start, strlen(ui)) == 0) {
			start += strlen(ui);
			ui_funcs[count] = allocstr(buf + start, cur - start);
			dest = ui_impls + count;
			multistart = cur + 1;

		} else if (strncmp(end, buf + start, strlen(end)) == 0) {
			// copy everything from i = multistart; i < start
			*dest = allocstr(buf + multistart, start - multistart);
		}

		start = cur + 1;
	}

	free(buf);
}

void generate_characters_enum_h(void)
{
	printf("generating characters_enum.h\n");
	FILE * type_keys_file = fopen("build/include/characters_enum.h", "w");
	if (!type_keys_file) {
		printf("failed to create characters_enum.h\n");
		exit(1);
	}

	fprintf(type_keys_file, "#ifndef CHARACTERS_ENUM_H\n"
			"#define CHARACTERS_ENUM_H\n\n");
	fprintf(type_keys_file, "typedef enum character_type {\n"
			"\tCHARACTER_NOTHING,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL)
			fprintf(type_keys_file, "\t%s,\n", type_keys[i]);
		else
			fprintf(type_keys_file, "\tNIL%d,\n", i);
	}
	fprintf(type_keys_file, "} CharacterType;\n");
	fprintf(type_keys_file, "\n#endif\n");
	fclose(type_keys_file);
}

void generate_characters_arrs_h(void)
{
	printf("generating characters_arrs.h\n");
	FILE * arrays_file = fopen("build/include/characters_arrs.h", "w");
	if (!arrays_file) {
		printf("failed to create characters_arrs.h\n");
		exit(1);
	}

	fprintf(arrays_file, "#ifndef CHARACTERS_ARRS_H\n"
			"#define CHARACTERS_ARRS_H\n\n");
	fprintf(arrays_file, "#include \"characters_impls.c\"\n\n");
	fprintf(arrays_file, "char const * const character2str[] = {\n"
			"\t[CHARACTER_NOTHING] = \"nil character\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && str_names[i] != NULL)
			fprintf(arrays_file, "\t[%s] = \"%s\",\n", type_keys[i], str_names[i]);
	}
	fprintf(arrays_file, "};\n\n");

	fprintf(arrays_file, "CharacterTalentFunc const character2talent[] = {\n"
			"\t[CHARACTER_NOTHING] = noop_talent_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && talent_funcs[i] != NULL)
			fprintf(arrays_file, "\t[%s] = %s,\n", type_keys[i], talent_funcs[i]);
	}
	fprintf(arrays_file, "};\n\n");

	fprintf(arrays_file, "CharacterGeneratorFunc const character2generator[] = {\n"
			"\t[CHARACTER_NOTHING] = noop_character_generator_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && gen_funcs[i] != NULL)
			fprintf(arrays_file, "\t[%s] = %s,\n", type_keys[i], gen_funcs[i]);
	}
	fprintf(arrays_file, "};\n\n");

	fprintf(arrays_file, "char const * const character2icon[] = {\n"
			"\t[CHARACTER_NOTHING] = \"resources/images/characters/character_nothing_icon.png\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && icons[i] != NULL)
			fprintf(arrays_file, "\t[%s] = %s,\n", type_keys[i], icons[i]);
	}
	fprintf(arrays_file, "};\n\n");

	fprintf(arrays_file, "char const * const character2portrait[] = {\n"
			"\t[CHARACTER_NOTHING] = \"resources/images/characters/character_nothing_portrait.png\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && icons[i] != NULL)
			fprintf(arrays_file, "\t[%s] = %s,\n", type_keys[i], icons[i]);
	}
	fprintf(arrays_file, "};\n\n");

	fprintf(arrays_file, "#endif\n");
	fclose(arrays_file);
}

void generate_characters_impls_c(void)
{
	printf("generating characters_impls.c\n");
	FILE * impls_file = fopen("build/include/characters_impls.c", "w");
	if (!impls_file) {
		printf("failed to create characters_impls.c\n");
		exit(1);
	}

	fprintf(impls_file, "#ifndef CHARACTERS_IMPLS_H\n"
			"#define CHARACTERS_IMPLS_H\n\n");
	fprintf(impls_file, "#include \"../../src/character_defs.h\"\n\n");
	for (int i = 0; i < count; i++)
		if (talent_impls[i] != NULL)
			fprintf(impls_file, "%s", talent_impls[i]);
	for (int i = 0; i < count; i++)
		if (gen_impls[i] != NULL)
			fprintf(impls_file, "%s", gen_impls[i]);
	fprintf(impls_file, "\n#endif\n");

	fclose(impls_file);
}

void generate_characters_ui_c(void)
{
	printf("generating characters_ui.c\n");
	FILE * ui_file = fopen("build/include/characters_ui.c", "w");
	if (!ui_file) {
		printf("failed to create characters_ui.c\n");
		exit(1);
	}

	fprintf(ui_file, "#ifndef CHARACTERS_UI_H\n"
			"#define CHARACTERS_UI_H\n\n");
	fprintf(ui_file, "#include \"../../src/character.c\"\n"
			"#include \"../../src/components.c\"\n\n");
	fprintf(ui_file, "typedef void (*CharacterUIFunc)(CharacterStats *);\n\n");
	fprintf(ui_file, "void noop_character_ui_func(CharacterStats * in) {\n"
			"\t// this function does nothing\n"
			"}\n\n");
	for (int i = 0; i < count; i++)
		if (ui_impls[i] != NULL)
			fprintf(ui_file, "%s", ui_impls[i]);
	fprintf(ui_file, "\n");
	fprintf(ui_file, "CharacterUIFunc const character2ui[] = {\n"
			"\t[CHARACTER_NOTHING] = noop_character_ui_func,\n");
	for (int i = 0; i < count; i++)
		if (type_keys[i] != NULL && ui_funcs[i] != NULL)
			fprintf(ui_file, "\t[%s] = %s,\n", type_keys[i], ui_funcs[i]);
	fprintf(ui_file, "};\n");
	fprintf(ui_file, "\n#endif\n");

	fclose(ui_file);
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
	icons = calloc(capacity, sizeof(*icons));
	portraits = calloc(capacity, sizeof(*portraits));
	talent_funcs = calloc(capacity, sizeof(*talent_funcs));
	talent_impls = calloc(capacity, sizeof(*talent_impls));
	gen_funcs = calloc(capacity, sizeof(*gen_funcs));
	gen_impls = calloc(capacity, sizeof(*gen_impls));
	ui_funcs = calloc(capacity, sizeof(*ui_funcs));
	ui_impls = calloc(capacity, sizeof(*ui_impls));

	while ((entry = readdir(directory)) != NULL) {
		if (count >= capacity) {
			capacity *= 2;
			type_keys = realloc(type_keys, capacity * sizeof(*type_keys));
			str_names = realloc(str_names, capacity * sizeof(*str_names));
			talent_funcs = realloc(talent_funcs, capacity * sizeof(*talent_funcs));
			talent_impls = realloc(talent_impls, capacity * sizeof(*talent_impls));
			gen_funcs = realloc(gen_funcs, capacity * sizeof(*gen_funcs));
			gen_impls = realloc(gen_impls, capacity * sizeof(*gen_impls));
			ui_funcs = realloc(ui_funcs, capacity * sizeof(*ui_funcs));
			ui_impls = realloc(ui_impls, capacity * sizeof(*ui_impls));
			icons = realloc(icons, capacity * sizeof(*icons));
			portraits = realloc(portraits, capacity * sizeof(*portraits));
		}

		type_keys[count] = NULL;
		str_names[count] = NULL;
		icons[count] = NULL;
		portraits[count] = NULL;
		talent_funcs[count] = NULL;
		talent_impls[count] = NULL;
		gen_funcs[count] = NULL;
		gen_impls[count] = NULL;
		ui_funcs[count] = NULL;
		ui_impls[count] = NULL;

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

	generate_characters_enum_h();
	generate_characters_arrs_h();
	generate_characters_impls_c();
	generate_characters_ui_c();

	return 0;
}
