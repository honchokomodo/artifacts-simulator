#ifndef IMAGE_CACHE_C
#define IMAGE_CACHE_C

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <stdio.h>

// initialize the cache, num_entries being the size of the hash table.
void ic_initcache(int num_entries, int max_images);

// deinitialize the cache and free all memory.
void ic_destroycache(void);

Texture2D * ic_get_tex(char const * const path); // get a texture from a filepath.
void ic_unload_tex(char const * const path); // unload a texture from the cache.
void ic_unload_all(void); // unload all textures in the cache.

/* usage:
 *
 * // initialize the cache. 599 is chosen here for the tablesize because it is a
 * // prime number. expecting to load roughly 300 images, so this is much more
 * // than enough. the size does not have to be larger than the expected amount
 * // of images though
 * // 1024 is chosen for max images because we definitely won't get that far.
 * ic_initcache(599);
 *
 * // load some textures.
 * Texture2D * tex = ic_get_tex("cute-yoimiya.png");
 * Texture2D * tex2 = ic_get_tex("thundering_pulse_icon.png");
 *
 * // load it again. This time, it fetched the texture from the cache.
 * Texture2D * tex3 = ic_get_tex("cute-yoimiya.png");
 *
 * // unload a texture.
 * ic_unload_tex("cute-yoimiya.png");
 *
 * // unload all textures.
 * // The cache is now fresh and ready to accept new images.
 * ic_unload_all();
 * ic_get_tex("cute-yoimiya.png");
 *
 * // free all memory when no longer in use.
 * ic_destroycache();
 */

struct _ic_tbl_entry {
	char * fpath;
	uint32_t hash;
	int next;
	Texture2D tex;
};

size_t _ic_table_size;
int * _ic_table;

// the item at 0 is a stub.
size_t _ic_arr_cap;
size_t _ic_arr_len;
int _ic_arr_next_free;
struct _ic_tbl_entry * _ic_arr;

void ic_initcache(int num_entries, int max_images)
{
	_ic_table_size = num_entries;
	_ic_table = calloc(num_entries, sizeof(*_ic_table));

	_ic_arr_cap = max_images;
	_ic_arr_len = 1;
	_ic_arr_next_free = 0;
	_ic_arr = calloc(_ic_arr_cap, sizeof(*_ic_arr));
}

void ic_destroycache(void)
{
	free(_ic_table);

	for (int i = 0; i < _ic_arr_len; i++) {
		if (_ic_arr[i].fpath != NULL)
			free(_ic_arr[i].fpath);

		if (_ic_arr[i].tex.format != 0)
			UnloadTexture(_ic_arr[i].tex);
	}
	free(_ic_arr);

	_ic_table = NULL;
	_ic_arr = NULL;

	_ic_table_size = 0;
	_ic_arr_cap = 0;
	_ic_arr_len = 0;
	_ic_arr_next_free = 0;
}

uint32_t _ic_strhash(char const * s)
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

// can be removed after compilers update to c23
char * _ic_strdup(char const * s)
{
	int len = strlen(s);
	char * out = malloc(len + 1);
	if (!out) return NULL;
	memcpy(out, s, len);
	out[len] = '\0';
	return out;
}

int _ic_load_tex(char const * const path) {
	char * fpath = _ic_strdup(path);
	if (fpath == NULL)
		return 0;

	uint32_t hash = _ic_strhash(path);

	Texture2D tex = LoadTexture(path);
	if (tex.format == 0) {
		free(fpath);
		return 0;
	}
	GenTextureMipmaps(&tex);
	SetTextureFilter(tex, TEXTURE_FILTER_TRILINEAR);

	if (_ic_arr_next_free == 0) {
		if (_ic_arr_len >= _ic_arr_cap) {
			free(fpath);
			UnloadTexture(tex);
			return 0;
		}

		_ic_arr_next_free = _ic_arr_len;
		_ic_arr[_ic_arr_next_free].next = 0;
		_ic_arr_len += 1;
	}

	struct _ic_tbl_entry new = {
		.fpath = fpath,
		.hash = hash,
		.tex = tex,
	};

	int next_free = _ic_arr_next_free;
	_ic_arr_next_free = _ic_arr[next_free].next;
	_ic_arr[next_free] = new;

	return next_free;
}

Texture2D * ic_get_tex(char const * const path)
{
	uint32_t hash = _ic_strhash(path);
	int index = hash % _ic_table_size;

	int prev = 0;
	int pos = _ic_table[index];
	while (pos != 0) {
		struct _ic_tbl_entry entry = _ic_arr[pos];

		if (entry.hash == hash && strcmp(path, entry.fpath) == 0) {
			return &_ic_arr[pos].tex;
		}

		prev = pos;
		pos = _ic_arr[pos].next;
	}
	
	pos = _ic_load_tex(path);

	if (prev == 0) _ic_table[index] = pos;
	else _ic_arr[prev].next = pos;

	return &_ic_arr[pos].tex;
}

void ic_unload_tex(char const * const path)
{
	uint32_t hash = _ic_strhash(path);
	int index = hash % _ic_table_size;

	int * ptr = _ic_table + index;
	while (*ptr != 0) {
		struct _ic_tbl_entry entry = _ic_arr[*ptr];

		if (entry.hash == hash && strcmp(path, entry.fpath) == 0) {
			free(entry.fpath);
			UnloadTexture(entry.tex);

			_ic_arr[*ptr].fpath = NULL;
			_ic_arr[*ptr].hash = 0;
			_ic_arr[*ptr].tex = (Texture2D) {0};

			int found = *ptr;
			*ptr = _ic_arr[found].next;
			_ic_arr[found].next = _ic_arr_next_free;
			_ic_arr_next_free = found;
			return;
		}

		ptr = &_ic_arr[*ptr].next;
	}
}

void ic_unload_all(void)
{
	for (int i = 0; i < _ic_table_size; i++)
		_ic_table[i] = 0;

	for (int i = 0; i < _ic_arr_len; i++) {
		if (_ic_arr[i].fpath != NULL)
			free(_ic_arr[i].fpath);

		if (_ic_arr[i].tex.format != 0)
			UnloadTexture(_ic_arr[i].tex);
	}

	_ic_arr_len = 1;
	_ic_arr_next_free = 0;
}

#endif
