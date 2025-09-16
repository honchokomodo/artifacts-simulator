#ifndef HASH_SET
#define HASH_SET

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct hs_set {
	size_t tbl_size;
	int len;
	size_t bufsz;
	int * buf;
} hs_Set;

uint32_t hs_hash(void * buf, size_t bufsz);
uint32_t hs_hashs(char const * s);

void hs_put(hs_Set * set, uint32_t hash);
bool hs_has(hs_Set * set, uint32_t hash);
void hs_del(hs_Set * set, uint32_t hash);

void hs_clear(hs_Set * set);

/* usage:
 * 
 * // create a new set.
 * size_t memorysize = 1024;
 * hs_Set set = {
 * 	.buf = malloc(memorysize),
 * 	.bufsz = memorysize,
 * 	.tbl_size = 29,
 * 	// a tbl_size of 29 occupies 29 * 4 = 116 bytes
 * 	// this leaves 1024 - 116 - 8 = 900 bytes left
 * 	// for a max item count of 900 / 8 = 112
 * };
 *
 * // add items in the set.
 * hs_put(&set, hs_hashs("deepwood memories 4p"));
 *
 * int num = 10;
 * hs_put(&set, hs_hash(&num, sizeof(num)));
 *
 * // check if an item is in the set.
 * assert(hs_has(&set, hs_hashs("deepwood memories 4p")));
 *
 * // remove an item from the set.
 * hs_del(&set, hs_hashs("deepwood memories 4p"));
 * assert(!hs_has(&set, hs_hashs("deepwood memories 4p")));
 *
 * // clear the set.
 * hs_clear(&set);
 * assert(!hs_has(&set, hs_hash(&num, sizeof(num))));
 *
 * // free memory when no longer in use.
 * free(set.buf);
 */

struct _hs_tbl_entry {
	uint32_t hash;
	int next;
};

uint32_t hs_hash(void * buf, size_t bufsz)
{
	uint8_t * b = buf;

	// these two could be anything really
	uint32_t big = 2654435761;
	uint32_t prime = 7331;

	uint32_t hash = 1;
	for (int i = 0; i < bufsz; i++) {
		hash *= prime;
		hash += b[i] * big;
	}

	return hash;
}

uint32_t hs_hashs(char const * s)
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

void hs_put(hs_Set * set, uint32_t hash)
{
	struct _hs_tbl_entry * arr = (typeof(arr)) (set->buf + set->tbl_size);
	size_t bufsz = set->bufsz - set->tbl_size * sizeof(*set->buf);
	size_t max_entries = bufsz / sizeof(*arr);

	if (set->len == 0) set->len = 1; // the first item is a stub
	if (set->len >= max_entries) return; // bailout if full

	int index = hash % set->tbl_size;

	int pos = set->len++;
	struct _hs_tbl_entry new = {
		.hash = hash,
		.next = set->buf[index], // point to the first item in the LL
	};
	arr[pos] = new; // put item into place
	set->buf[index] = pos; // insert in front of LL
}

bool hs_has(hs_Set * set, uint32_t hash)
{
	struct _hs_tbl_entry * arr = (typeof(arr)) (set->buf + set->tbl_size);

	int index = hash % set->tbl_size;
	int * ptr = set->buf + index;

	while (*ptr != 0) {
		if (arr[*ptr].hash == hash) return true;
		ptr = &arr[*ptr].next;
	}

	return false;
}

void hs_del(hs_Set * set, uint32_t hash)
{
	struct _hs_tbl_entry * arr = (typeof(arr)) (set->buf + set->tbl_size);

	int index = hash % set->tbl_size;
	int * ptr = set->buf + index;

	int pos;
	while (1) {
		if (*ptr == 0) {
			return; // the item was not found. bail out now
		}

		if (arr[*ptr].hash != hash) {
			ptr = &arr[*ptr].next;
			continue; // the hash does not match. next item
		}

		// the item has been found.
		pos = *ptr; // save the position of the found item
		*ptr = arr[pos].next; // remove the item from the linked list
		// overwrite the item with the last item
		arr[pos] = arr[--set->len];

		break;
	}

	// the last item was moved somewhere.
	// whatever was pointing to the last item now needs to point to that
	// somewhere.

	// search for the item that points to the former last item
	uint32_t lasthash = arr[set->len - 1].hash;
	index = lasthash % set->tbl_size;
	ptr = set->buf + index;

	while (*ptr != 0) {
		if (arr[*ptr].hash != hash) {
			ptr = &arr[*ptr].next;
			continue; // the hash does not match. next item
		}

		// the item has been found. point to the new position
		*ptr = pos;
		break;
	}
}

void hs_clear(hs_Set * set)
{
	// clear the table
	for (int i = 0; i < set->tbl_size; i++) {
		set->buf[i] = 0;
	}

	// no extra work needed to clear the list
	set->len = 1;
}

#endif
