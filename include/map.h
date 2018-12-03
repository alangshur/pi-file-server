#ifndef MAP_H
#define MAP_H

#include "strings.h"
#include <stdbool.h>

// define map structs
struct map_node_t;
typedef struct map_node_t map_node_t;

typedef struct {
    map_node_t** buckets;
    unsigned nbuckets, nnodes;
} map_base_t;

typedef struct {
    unsigned bucketidx;
    map_node_t *node;
} map_iter_t;

// use custom map container type
#define map_t(T) struct { map_base_t base; T *ref; T tmp; }

// init map object
#define map_init(m) memset(m, 0, sizeof(*(m)))

// deinit map object
#define map_deinit(m) map_deinit_(&(m)->base)

// get map value for key
#define map_get(m, key) ((m)->ref = map_get_(&(m)->base, key))

// set map value for key
#define map_set(m, key, value) ((m)->tmp = (value), map_set_(&(m)->base, key, &(m)->tmp, sizeof((m)->tmp)))

// remove map value for key
#define map_remove(m, key) map_remove_(&(m)->base, key)

// get map iterator
#define map_iter(m) map_iter_()

// iterate to next key
#define map_next(m, iter) map_next_(&(m)->base, iter)

// check if map contains key
#define map_contains(m, key) map_contains_(&(m)->base, key)

// define map function prototypes
void map_deinit_(map_base_t* m);
void* map_get_(map_base_t* m, const char* key);
int map_set_(map_base_t* m, const char* key, void* value, int vsize);
void map_remove_(map_base_t* m, const char* key);
map_iter_t map_iter_(void);
const char *map_next_(map_base_t *m, map_iter_t *iter);
bool map_contains_(map_base_t* m, const char* key);

// define map container types
typedef map_t(void*) map_void_t;
typedef map_t(char*) map_str_t;
typedef map_t(int) map_int_t;
typedef map_t(char) map_char_t;
typedef map_t(float) map_float_t;
typedef map_t(double) map_double_t;

#endif