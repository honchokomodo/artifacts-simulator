#ifndef LINEAR_ALLOCATOR_C
#define LINEAR_ALLOCATOR_C

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct la_arena {
	uint8_t * buf;
	size_t bufsz;
	size_t offset;
} la_Arena;

// Allocate a region of memory bufsz bytes large.
// returns NULL if out of memory.
void * la_alloc(la_Arena * arena, size_t bufsz);

// Format a string like printf, then store it in arena, and return the
// null-terminated formatted string.
// returns NULL if out of memory.
char * la_strfmt(la_Arena * arena, char * fmt, ...);

// Free all memory stored in arena.
void la_reset(la_Arena * arena);

/* usage:
 *
 * // create a new arena.
 * size_t memorysize = 1024;
 * la_Arena arena = {
 * 	.buf = malloc(memorysize),
 * 	.bufsz = memorysize,
 * };
 *
 * // allocate some memory.
 * int * ptr = la_alloc(&arena, sizeof(*ptr));
 *
 * // create some strings.
 * char * name = "Amber";
 * char * s = la_strfmt(&arena, "Hello %s!\n", name);
 * char * numbers = la_strfmt(&arena, "numbers: %d, %d, %d", 1, 2, 3);
 *
 * // reset arena when data no longer in use.
 * la_reset(&arena);
 *
 * // free all memory when arena no longer in use.
 * free(arena.buf);
 */

void * la_alloc(la_Arena * arena, size_t bufsz)
{
	uintptr_t offset = arena->offset;
	uintptr_t align;

	// idk man
	if (bufsz == 1) align = 1;
	else if (bufsz <= 4) align = 4;
	else align = 8;

	offset += (align - 1) & (align - (offset & (align - 1)));

	if (offset + bufsz > arena->bufsz)
		return NULL;

	void * out = arena->buf + offset;
	arena->offset = offset + bufsz;

	memset(out, 0, bufsz);
	return out;
}

char * la_strfmt(la_Arena * arena, char * fmt, ...)
{
	int max_len = arena->bufsz - arena->offset;
	if (max_len <= 0) return NULL;

	char * out = (char *) (arena->buf + arena->offset);

	va_list args;
	va_start(args, fmt);
	arena->offset += 1 + vsnprintf(out, max_len, fmt, args);
	va_end(args);

	return out;
}

void la_reset(la_Arena * arena)
{
	arena->offset = 0;
}

#endif
