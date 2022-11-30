

#ifndef	_MV_INSERTION_SORT_H
#define	_MV_INSERTION_SORT_H

#ifndef	SUCCESS
#define	SUCCESS	0
#endif

#ifndef	FAILURE
#define	FAILURE	1
#endif

//	Typedef	

typedef		void* 	data_t;
typedef		int 	ret_t;

typedef		ret_t(*COMPAREDATAPROC)(data_t, data_t);

//	Interface Function Declarations

/*
 * @function	mv_insertion_sort is a function that sorts the given elements in an array
 * @params	1) 	Array of elements
 * 			2)	Size of array
 * 
 * @return	Status of sorting
 */

extern ret_t mv_insertion_sort(	data_t* array, 
								long long array_size, 
								size_t element_size,
								COMPAREDATAPROC pcompareproc);

#endif /* _MV_INSERTION_SORT_H */


