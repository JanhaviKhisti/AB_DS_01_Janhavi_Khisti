
// Header
#ifndef _MV_QUICK_SORT_H
#define _MV_QUICK_SORT_H

#define FALSE 0
#define TRUE  1

typedef int ret_t;
typedef void* data_t;

typedef ret_t (*COMPARE)(data_t data1, data_t data2);

extern void QuickSort(data_t* array, long long first, long long last, COMPARE compare);

#endif /* _MV_MERGE_SORT_H */

