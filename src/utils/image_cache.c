#ifndef IMAGE_CACHE_C
#define IMAGE_CACHE_C

void image_cache_init(int num_entries);
void image_cache_destroy(void);

Texture2D ic_get_tex(char * path);
void ic_unload_tex(char * path);
void ic_unload_all(void);

struct ic_tbl_entry {
	char * fpath;
	uint32_t hash;
	int nextidx;
	Texture2D tex;
};

size_t image_cache_table_size;
struct ic_tbl_entry * image_cache_table;

size_t image_cache_overflow_cap;
size_t image_cache_overflow_len;
int image_cache_overflow_next_free;
struct ic_tbl_entry * image_cache_overflow;

void image_cache_init(int num_entries)
{
	image_cache_table_size = num_entries;
	image_cache_table = calloc(num_entries, sizeof(*image_cache_table));

	image_cache_overflow_cap = 2;
	image_cache_overflow_len = 1;
	image_cache_overflow_next_free = image_cache_overflow_len;
	image_cache_overflow = calloc(1, sizeof(*image_cache_overflow));
}

void image_cache_destroy(void)
{
	// TODO: loop over all entries and free them
	free(image_cache_table);

	// TODO: loop over all entries and free them
	free(image_cache_overflow);

	image_cache_table_size = 0;
	image_cache_overflow_cap = 0;
	image_cache_overflow_len = 0;
	image_cache_overflow_next_free = 1;
}

uint32_t _image_cache_hash_filepath(char * s)
{
	// these two could be anything really
	uint32_t big = 2654435761;
	uint32_t prime = 7331;

	uint32_t hash = 1;
	for (; *s; s++) {
		hash *= prime;
		hash += *s * big;
	}

	return hash;
}

char * _ic_strdup(char * s)
{
	int len = strlen(s);
	char * out = malloc(len + 1);
	if (!out) return NULL;
	memcpy(out, buf, len);
	out[len] = '\0';
	return out;
}

Texture2D ic_get_tex(char * path)
{
	uint32_t hash = _image_cache_hash_filepath(path);
	int index = hash % image_cache_table_size;

	struct ic_tbl_entry * arr = image_cache_table;
	struct ic_tbl_entry entry = arr[index];

	if (entry.fpath == NULL) {
		struct ic_tbl_entry new = {
			.fpath = _ic_strdup(path);
			.hash = hash,
			.nextidx = 0, //TODO: handle this properly
			.tex = //
		};
	}

	if (entry.hash == hash && strcmp(entry.fpath, path) == 0) {
		return entry.tex;
	}

	/*
	arr = image_cache_overflow;
	index = entry.nextidx;
	entry = arr[index];
	while (entry.fpath != NULL) {
		if (entry.hash == hash && strcmp(entry.fpath, path) == 0) {
			return entry.tex;
		}
		index = entry.nextidx;
		entry = arr[index];
	}
	*/
}

void ic_unload_tex(char * path)
{
	// TODO
}

void ic_unload_all(void)
{
	// TODO
}

#endif
