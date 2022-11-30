/*
    Total Lines of code = 35 + 60 + 87 = 182
*/

#include    <stdio.h>
#include    <stdlib.h>
#include    <time.h>

#include    "mv_insertion_sort.h"

#define     NEW_LINE    fprintf(stdout, "\n\n")

long long* iarr = NULL;

ret_t compare_proc(data_t data1, data_t data2)
{
    // Code

    //  Sorting Condition
    if( (long long)data1 > (long long)data2 )   
        return(SUCCESS);

    return(FAILURE);
}

int main(void)
{

    srand(time(0));

    //long long  no_of_elements = 10 + rand() % 10;
    long long  no_of_elements = 999;

    iarr = (long long*) calloc(no_of_elements, sizeof(long long));

    for( long long le = 0; le < no_of_elements; ++le )
    {
        iarr[le] = 1 + rand() % 22;
    }

    NEW_LINE;

    fprintf(stdout, "Before Sort:\n");
    fprintf(stdout, "No Of Elements: %lld\n", no_of_elements);
    fprintf(stdout, "[START]-");
    for( long long le = 0; le < no_of_elements; ++le )
    {
        fprintf(stdout, "[%lld]-", iarr[le]);
    }
    fprintf(stdout, "[END]");

    //NEW_LINE;

    //  MOMENT OF TRUTH: Call The Insertion Sort 

    clock_t start = clock();
    mv_insertion_sort((data_t*)iarr, no_of_elements, compare_proc);
    clock_t end = clock();

    double time_for_sorting = ( (double)(end - start) ) / CLOCKS_PER_SEC;

    fprintf(stdout, "Time of Sorting: %lf\n", time_for_sorting);

    NEW_LINE;

    fprintf(stdout, "After Sort:\n");
    fprintf(stdout, "No Of Elements: %lld\n", no_of_elements);
    fprintf(stdout, "[START]\n");

    for( long long le = 0; le < no_of_elements; ++le )
    {
        fprintf(stdout, "[%lld]\n", iarr[le]);
    }

    fprintf(stdout, "[END]");

    NEW_LINE;

    if( iarr )
    {
        free(iarr);
        iarr = NULL;
    }

    exit(EXIT_SUCCESS);
}



