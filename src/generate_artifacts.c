#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count;
size_t capacity;
char ** type_keys;
char ** str_names;
char ** flower_paths;
char ** feather_paths;
char ** sands_paths;
char ** goblet_paths;
char ** circlet_paths;
char ** bonus_funcs;
char ** bonus_impls;
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

	static char const key[] = "// AUTOGEN ArtifactSet ";
	static char const name[] = "// AUTOGEN set2str ";
	static char const flower[] = "// AUTOGEN flowerpath ";
	static char const feather[] = "// AUTOGEN featherpath ";
	static char const sands[] = "// AUTOGEN sandspath ";
	static char const goblet[] = "// AUTOGEN gobletpath ";
	static char const circlet[] = "// AUTOGEN circletpath ";
	static char const bonus[] = "// AUTOGEN set2bonus ";
	static char const ui[] = "// AUTOGEN set2ui ";
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

		} else if (strncmp(flower, buf + start, strlen(flower)) == 0) {
			start += strlen(flower);
			flower_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(feather, buf + start, strlen(feather)) == 0) {
			start += strlen(feather);
			feather_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(sands, buf + start, strlen(sands)) == 0) {
			start += strlen(sands);
			sands_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(goblet, buf + start, strlen(goblet)) == 0) {
			start += strlen(goblet);
			goblet_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(circlet, buf + start, strlen(circlet)) == 0) {
			start += strlen(circlet);
			circlet_paths[count] = allocstr(buf + start, cur - start);

		} else if (strncmp(bonus, buf + start, strlen(bonus)) == 0) {
			start += strlen(bonus);
			bonus_funcs[count] = allocstr(buf + start, cur - start);
			dest = bonus_impls + count;
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

void generate_artifacts_enum_h(void)
{
	printf("generating artifacts_enum.h\n");
	FILE * file = fopen("build/include/artifacts_enum.h", "w");
	if (!file) {
		printf("failed to create artifacts_enum.h\n");
		exit(1);
	}

	fprintf(file, "#ifndef ARTIFACTS_ENUM_H\n"
			"#define ARTIFACTS_ENUM_H\n\n");

	fprintf(file, "typedef enum artifact_set {\n"
			"\tSET_NOTHING,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL) {
			fprintf(file, "\t%s,\n", type_keys[i]);
		} else {
			fprintf(file, "\tNIL%d,\n", i);
		}
	}
	fprintf(file, "} ArtifactSet;\n");

	fprintf(file, "\n#endif\n");

	fclose(file);
}

void generate_artifacts_arrs_h(void)
{
	printf("generating artifacts_arrs.h\n");
	FILE * file = fopen("build/include/artifacts_arrs.h", "w");
	if (!file) {
		printf("failed to create artifacts_arrs.h\n");
		exit(1);
	}

	fprintf(file, "#ifndef ARTIFACTS_ARRS_H\n"
			"#define ARTIFACTS_ARRS_H\n\n");

	fprintf(file, "#include \"artifacts_impls.c\"\n\n");

	fprintf(file, "char const * const set2str[] = {\n"
			"\t[SET_NOTHING] = \"nil set\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && str_names[i] != NULL)
			fprintf(file, "\t[%s] = \"%s\",\n", type_keys[i], str_names[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const flowerpath[] = {\n"
			"\t[SET_NOTHING] = \"flower/path\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && flower_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], flower_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const featherpath[] = {\n"
			"\t[SET_NOTHING] = \"feather/path\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && feather_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], feather_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const sandspath[] = {\n"
			"\t[SET_NOTHING] = \"sands/path\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && sands_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], sands_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const gobletpath[] = {\n"
			"\t[SET_NOTHING] = \"goblet/path\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && goblet_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], goblet_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "char const * const circletpath[] = {\n"
			"\t[SET_NOTHING] = \"circlet/path\",\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && circlet_paths[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], circlet_paths[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "SetBonusFunc const set2bonus[] = {\n"
			"\t[SET_NOTHING] = noop_set_bonus_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && bonus_funcs[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], bonus_funcs[i]);
	}
	fprintf(file, "};\n\n");

	fprintf(file, "#endif\n");

	fclose(file);
}

void generate_artifacts_impls_c(void)
{
	printf("generating artifacts_impls.c\n");
	FILE * file = fopen("build/include/artifacts_impls.c", "w");
	if (!file) {
		printf("failed to create artifacts_impls.c\n");
		exit(1);
	}

	fprintf(file, "#ifndef ARTIFACTS_IMPLS_H\n"
			"#define ARTIFACTS_IMPLS_H\n\n");

	fprintf(file, "#include \"../../src/artifact_defs.h\"\n\n");

	for (int i = 0; i < count; i++) {
		if (bonus_impls[i] != NULL)
			fprintf(file, "%s", bonus_impls[i]);
	}

	fprintf(file, "\n#endif\n");

	fclose(file);
}

void generate_artifacts_ui_c(void)
{
	printf("generating artifacts_ui.c\n");
	FILE * file = fopen("build/include/artifacts_ui.c", "w");
	if (!file) {
		printf("failed to create artifacts_ui.c\n");
		exit(1);
	}

	fprintf(file, "#ifndef ARTIFACTS_UI_C\n"
			"#define ARTIFACTS_UI_C\n\n");

	fprintf(file, "#include \"../../src/artifact.c\"\n"
			"#include \"../../src/components.c\"\n\n");

	fprintf(file, "typedef void (*ArtifactUIFunc)(ArtifactLoadout *);\n");
	fprintf(file, "void noop_artifact_ui_func(ArtifactLoadout * in) {\n"
			"\t// this function does nothing\n"
			"}\n\n");

	for (int i = 0; i < count; i++) {
		if (ui_impls[i] != NULL)
			fprintf(file, "%s", ui_impls[i]);
	}

	fprintf(file, "\nArtifactUIFunc const set2ui[] = {\n"
			"\t[SET_NOTHING] = noop_artifact_ui_func,\n");
	for (int i = 0; i < count; i++) {
		if (type_keys[i] != NULL && ui_funcs[i] != NULL)
			fprintf(file, "\t[%s] = %s,\n", type_keys[i], ui_funcs[i]);
	}
	fprintf(file, "};\n");

	fprintf(file, "\n#endif\n");

	fclose(file);
}

int main(void)
{
	DIR * directory;
	struct dirent * entry;

	char * dirname = "src/artifacts/";
	directory = opendir(dirname);
	if (directory == NULL) {
		perror("Couldn't open the directory");
		exit(1);
	}

	count = 0;
	capacity = 1;
	type_keys = calloc(capacity, sizeof(*type_keys));
	str_names = calloc(capacity, sizeof(*str_names));
	flower_paths = calloc(capacity, sizeof(*flower_paths));
	feather_paths = calloc(capacity, sizeof(*feather_paths));
	sands_paths = calloc(capacity, sizeof(*sands_paths));
	goblet_paths = calloc(capacity, sizeof(*goblet_paths));
	circlet_paths = calloc(capacity, sizeof(*circlet_paths));
	bonus_funcs = calloc(capacity, sizeof(*bonus_funcs));
	bonus_impls = calloc(capacity, sizeof(*bonus_impls));
	ui_funcs = calloc(capacity, sizeof(*ui_funcs));
	ui_impls = calloc(capacity, sizeof(*ui_impls));

	while ((entry = readdir(directory)) != NULL) {
		if (count >= capacity) {
			capacity *= 2;
			type_keys = realloc(type_keys, capacity * sizeof(*type_keys));
			str_names = realloc(str_names, capacity * sizeof(*str_names));
			flower_paths = realloc(flower_paths, capacity * sizeof(*flower_paths));
			feather_paths = realloc(feather_paths, capacity * sizeof(*feather_paths));
			sands_paths = realloc(sands_paths, capacity * sizeof(*sands_paths));
			goblet_paths = realloc(goblet_paths, capacity * sizeof(*goblet_paths));
			circlet_paths = realloc(circlet_paths, capacity * sizeof(*circlet_paths));
			bonus_funcs = realloc(bonus_funcs, capacity * sizeof(*bonus_funcs));
			bonus_impls = realloc(bonus_impls, capacity * sizeof(*bonus_impls));
			ui_funcs = realloc(ui_funcs, capacity * sizeof(*ui_funcs));
			ui_impls = realloc(ui_impls, capacity * sizeof(*ui_impls));
		}

		type_keys[count] = NULL;
		str_names[count] = NULL;
		flower_paths[count] = NULL;
		feather_paths[count] = NULL;
		sands_paths[count] = NULL;
		goblet_paths[count] = NULL;
		circlet_paths[count] = NULL;
		bonus_funcs[count] = NULL;
		bonus_impls[count] = NULL;
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

	generate_artifacts_enum_h();
	generate_artifacts_arrs_h();
	generate_artifacts_impls_c();
	generate_artifacts_ui_c();

	return 0;
}
