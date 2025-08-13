#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count;
size_t capacity;
char ** type_keys;
char ** str_names;
char ** icon_paths;
char ** asc2_paths;
char ** passive_funcs;
char ** passive_impls;
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

void generate_weapons_enum_h(void)
{
	printf("generating weapons_enum.h\n");
	FILE * file = fopen("build/include/weapons_enum.h", "w");
	if (!file) {
		printf("failed to create weapons_enum.h\n");
		exit(1);
	}

	fprintf(file, "#ifndef WEAPONS_ENUM_H\n"
			"#define WEAPONS_ENUM_H\n\n");

	fprintf(file, "typedef enum weapon_type {\n"
			"\tWEAPON_NOTHING,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL) {
			fprintf(file, "\t%s,\n", type_keys[i]);
		} else {
			fprintf(file, "\tNIL%d,\n", i);
		}
	}
	fprintf(file, "} WeaponType;\n");

	fprintf(file, "\n#endif\n");

	fclose(file);
}

void generate_weapons_arrs_h(void)
{
	printf("generating weapons_arrs.h\n");
	FILE * file = fopen("build/include/weapons_arrs.h", "w");
	if (!file) {
		printf("failed to create weapons_arrs.h\n");
		exit(1);
	}

	fprintf(file, "#ifndef WEAPONS_ARRS_H\n"
			"#define WEAPONS_ARRS_H\n\n");
	fprintf(file, "#include \"weapons_impls.c\"\n\n");

	fprintf(file, "char const * const weapon2str[] = {\n"
			"\t[WEAPON_NOTHING] = \"nil weapon\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && str_names[i] != NULL)
			fprintf(file, "\t[%s] = \"%s\",\n", type_keys[i], str_names[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const weapon2icon[] = {\n"
			"\t[WEAPON_NOTHING] = \"resources/images/weapons/weapon_nothing_icon.png\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && icon_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], icon_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const weapon2icon_asc[] = {\n"
			"\t[WEAPON_NOTHING] = \"resources/images/weapons/weapon_nothing_asc_icon.png\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && asc2_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], asc2_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "WeaponPassiveFunc const weapon2passive[] = {\n"
			"\t[WEAPON_NOTHING] = noop_passive_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && passive_funcs[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], passive_funcs[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "WeaponGeneratorFunc const weapon2generator[] = {\n"
			"\t[WEAPON_NOTHING] = noop_weapon_generator_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && gen_funcs[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], gen_funcs[i]);
	}
	fprintf(file, "};\n");

	fprintf(file, "\n#endif\n");

	fclose(file);
}

void generate_weapons_impls_c(void)
{
	printf("generating weapons_impls.c\n");
	FILE * file = fopen("build/include/weapons_impls.c", "w");
	if (!file) {
		printf("failed to create weapons_impls.c\n");
		exit(1);
	}

	fprintf(file, "#ifndef WEAPONS_IMPLS_C\n"
			"#define WEAPONS_IMPLS_C\n\n");
	fprintf(file, "#include \"../../src/weapon_defs.h\"\n\n");

	for (int i = 0; i < count; i++) {
		if (passive_impls[i] != NULL)
			fprintf(file, "%s", passive_impls[i]);
	}
	for (int i = 0; i < count; i++) {
		if (gen_impls[i] != NULL)
			fprintf(file, "%s", gen_impls[i]);
	}

	fprintf(file, "\n#endif\n");

	fclose(file);
}

void generate_weapons_ui_c(void)
{
	printf("generating weapons_ui.c\n");
	FILE * file = fopen("build/include/weapons_ui.c", "w");
	if (!file) {
		printf("failed to create weapons_ui.c\n");
		exit(1);
	}

	fprintf(file, "#ifndef WEAPONS_UI_C\n"
			"#define WEAPONS_UI_C\n\n");
	fprintf(file, "#include \"../../src/weapon.c\"\n"
			"#include \"../../src/components.c\"\n\n");
	fprintf(file, "typedef void (*WeaponUIFunc)(Weapon * in);\n");
	fprintf(file, "void noop_weapon_ui_func(Weapon *) {\n"
			"\t// this function does nothing\n"
			"}\n\n");

	for (int i = 0; i < count; i++) {
		if (ui_impls[i] != NULL)
			fprintf(file, "%s", ui_impls[i]);
	}

	fprintf(file, "\nWeaponUIFunc const weapon2ui[] = {\n"
			"\t[WEAPON_NOTHING] = noop_weapon_ui_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && ui_funcs[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], ui_funcs[i]);
	}
	fprintf(file, "};\n");

	fprintf(file, "\n#endif\n");

	fclose(file);
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

	static char const key[] = "// AUTOGEN WeaponType ";
	static char const name[] = "// AUTOGEN weapon2str ";
	static char const icon[] = "// AUTOGEN weapon2icon ";
	static char const asc2[] = "// AUTOGEN weapon2icon_asc ";
	static char const passive[] = "// AUTOGEN weapon2passive ";
	static char const gen[] = "// AUTOGEN weapon2generator ";
	static char const ui[] = "// AUTOGEN weapon2ui ";
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
			icon_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(asc2, buf + start, strlen(asc2)) == 0) {
			start += strlen(asc2);
			asc2_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(passive, buf + start, strlen(passive)) == 0) {
			start += strlen(passive);
			passive_funcs[count] = allocstr(buf + start, cur - start);
			dest = passive_impls + count;
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
			if (multistart != 0)
				*dest = allocstr(buf + multistart, start - multistart);
			multistart = 0;
		}

		start = cur + 1;
	}

	free(buf);
}

int main(void)
{
	DIR * directory;
	struct dirent * entry;

	char * dirname = "src/weapons/";
	directory = opendir(dirname);
	if (directory == NULL) {
		perror("Couldn't open the directory");
		exit(1);
	}

	count = 0;
	capacity = 1;
	type_keys = calloc(capacity, sizeof(*type_keys));
	str_names = calloc(capacity, sizeof(*str_names));
	icon_paths = calloc(capacity, sizeof(*icon_paths));
	asc2_paths = calloc(capacity, sizeof(*asc2_paths));
	passive_funcs = calloc(capacity, sizeof(*passive_funcs));
	passive_impls = calloc(capacity, sizeof(*passive_impls));
	gen_funcs = calloc(capacity, sizeof(*gen_funcs));
	gen_impls = calloc(capacity, sizeof(*gen_impls));
	ui_funcs = calloc(capacity, sizeof(*ui_funcs));
	ui_impls = calloc(capacity, sizeof(*ui_impls));

	while ((entry = readdir(directory)) != NULL) {
		if (count >= capacity) {
			capacity *= 2;
			type_keys = realloc(type_keys, capacity * sizeof(*type_keys));
			str_names = realloc(str_names, capacity * sizeof(*str_names));
			icon_paths = realloc(icon_paths, capacity * sizeof(*icon_paths));
			asc2_paths = realloc(asc2_paths, capacity * sizeof(*asc2_paths));
			passive_funcs = realloc(passive_funcs, capacity * sizeof(*passive_funcs));
			passive_impls = realloc(passive_impls, capacity * sizeof(*passive_impls));
			gen_funcs = realloc(gen_funcs, capacity * sizeof(*gen_funcs));
			gen_impls = realloc(gen_impls, capacity * sizeof(*gen_impls));
			ui_funcs = realloc(ui_funcs, capacity * sizeof(*ui_funcs));
			ui_impls = realloc(ui_impls, capacity * sizeof(*ui_impls));
		}

		type_keys[count] = NULL;
		str_names[count] = NULL;
		icon_paths[count] = NULL;
		asc2_paths[count] = NULL;
		passive_funcs[count] = NULL;
		passive_impls[count] = NULL;
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

	generate_weapons_enum_h();
	generate_weapons_arrs_h();
	generate_weapons_impls_c();
	generate_weapons_ui_c();

	return 0;
}
