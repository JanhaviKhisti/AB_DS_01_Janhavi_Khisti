

#ifndef     _ND_ARRAY_H
#define     _ND_ARRAY_H

// Constant Literals
#ifndef         SUCCESS 
#define     SUCCESS     0
#endif

#ifndef     FAILURE
#define     FAILURE     1
#endif

// Type definitions
struct array;

typedef     struct array    array_t;
typedef     struct array*   p_array_t;
typedef     struct array**  pp_array_t;

typedef     void*           data_t;
typedef     data_t*         p_data_t;
typedef     long*           p_dimension_t;
typedef     int             ret_t;

// Structure Type Definition
struct array
{
    p_data_t        ptr;                    // actual array
    size_t          no_of_dimensions;       // total no of dimensions
    p_dimension_t   pdimension;             // array for storing size of each dimension
    size_t*         to_jump_dimension; 
};

#define     SIZE_ARRAY      sizeof(array_t)

// ND Array Interface Functions     ( given to client to use NDArray )

/*
    identifier  :   create_array
    input       :   1) size of elements
                    2) no of dimension (size_t)
                    3) ... (ellipses)
    output      :   pointer to struct 
*/
extern  p_array_t   create_array(size_t no_of_dimensions, ...);


/*
    identifer   :   array_set_data
    input       :   1) array 
                    2) data
                    3) ... (index)
    output      :   status
*/
extern  ret_t       array_set_data(p_array_t parray, data_t data, ...);


/*
    identifier  :   array_get_data 
    input       :   1) array
                    2) ...
    output      :   data
*/
extern  data_t      array_get_data(p_array_t parray, ...);


/*
    inentifier  :   array_get_size_of_dimension
    input       :   1) array
                    2) index
    output      :   returns size of dimension
*/
extern  long        array_get_size_of_dimension(p_array_t parray, long index);


/*
    identifier  :   array_destroy
    input       :   double pointer to array
    output      :   status(success or failure)
*/
extern  ret_t       array_destroy(pp_array_t pparray);

#endif      /* _ND_ARRAY_H */

