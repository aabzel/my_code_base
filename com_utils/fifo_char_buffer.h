#ifndef __FIFO_CHAR_BUFFER_H
#define __FIFO_CHAR_BUFFER_H

#include "fifo_index.h"
#include "device.h"
#ifdef ENABLE_MULTICORE
#include "ic_mutex.h"
#endif

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
    fifo_index_info_t r;
    char *data;
#ifdef ENABLE_MULTICORE
    ic_mutex_t mutex;
#endif
} fifo_char_t;


#ifdef ENABLE_MULTICORE
#define FIFO_CHAR_INIT(size, data) {FIFO_INDEX_INIT(size), data, IC_MUTEX_INVALID}
#define FIFO_CHAR_INIT_WITH_IC_MUTEX(size, data, mutex) {FIFO_INDEX_INIT(size), data, mutex}
#else
#define FIFO_CHAR_INIT(size, data) {FIFO_INDEX_INIT(size), data}
#endif

static INLINE bool fifo_char_add (fifo_char_t *f, char c);
static INLINE const char* fifo_char_get_contiguous_block (const fifo_char_t *f, fifo_index_t *size);
static INLINE void fifo_char_free (fifo_char_t *f, fifo_index_t size);
static INLINE fifo_index_t fifo_char_get_used (const fifo_char_t *f);
static INLINE fifo_index_t fifo_char_get_size (const fifo_char_t *f);

static INLINE bool fifo_char_add (fifo_char_t *f, char c) {
    bool ret = true;
    fifo_index_t index;
#ifdef ENABLE_MULTICORE
    ic_mutex_lock(f->mutex);
#endif
    enter_critical();
    index = fifo_index_add (&f->r);
    if (index == RING_INVALID_INDEX) {
        ret = false;
    } else {
        f->data [index] = c;
    }
    exit_critical();
#ifdef ENABLE_MULTICORE
    ic_mutex_unlock(f->mutex);
#endif
    return ret;
}

static INLINE const char* fifo_char_get_contiguous_block (const fifo_char_t *f, fifo_index_t *size) {
    const char* retval;
#ifdef ENABLE_MULTICORE
    ic_mutex_lock(f->mutex);
#endif
    enter_critical();
    *size = fifo_index_continuus_used_size (&f->r);
    if (*size) {
        retval = f->data + f->r.start;
    } else {
        retval = (char*) NULL;
    }
    exit_critical();
#ifdef ENABLE_MULTICORE
    ic_mutex_unlock(f->mutex);
#endif
    return retval;
}

static INLINE void fifo_char_free (fifo_char_t *f, fifo_index_t size) {
#ifdef ENABLE_MULTICORE
    ic_mutex_lock(f->mutex);
#endif
    enter_critical();
    fifo_index_free (&f->r, size);
    exit_critical();
#ifdef ENABLE_MULTICORE
    ic_mutex_unlock(f->mutex);
#endif
}

static INLINE fifo_index_t fifo_char_get_used (const fifo_char_t *f) {
    fifo_index_t retval;
    enter_critical();
    retval = f->r.count;
    exit_critical();
    return retval;
}

static INLINE fifo_index_t fifo_char_get_size (const fifo_char_t *f) {
    fifo_index_t retval;
    enter_critical();
    retval = f->r.size;
    exit_critical();
    return retval;
}

#ifdef	__cplusplus
}
#endif

#endif /* __FIFO_CHAR_BUFFER_H */
