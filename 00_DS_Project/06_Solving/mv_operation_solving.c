

#include <stdio.h>
#include <stdlib.h>

#include "mv_expression_stack.h"

extern char* Addition(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, 1024);

	mv_strcpy(str, "Add( ");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, " , ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, " ) ");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %p\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	printf("Str_len : %d\n",mv_strlen(str));

	printf("Str : %s\n", str);

	return(str);

} 

extern data_t Subtraction(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, sizeof(str));

	mv_strconcate(str, "Sub( ");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, " , ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, " ) ");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return((data_t)str);

} 


extern data_t Multiplication(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, sizeof(str));

	mv_strconcate(str, "Mul( ");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, " , ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, " ) ");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return((data_t)str);

} 


extern data_t Division(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, sizeof(str));

	mv_strconcate(str, "Div( ");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, " , ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, " ) ");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return((data_t)str);

} 


extern data_t Modulous(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	char* str = (char*)malloc(1024);

	memset(str, 0, sizeof(str));

	mv_strconcate(str, "Mod( ");
	mv_strconcate(str, str_obj1);
	mv_strconcate(str, " , ");
	mv_strconcate(str, str_obj2);
	mv_strconcate(str, " ) ");

	str = (char*)realloc(str, mv_strlen(str));

	printf("Str = %s\n", str);
	
	free(object1->object_value);
	object1->object_value = NULL;

	free(object1);
	object1 = NULL;

	free(object2->object_value);
	object2->object_value = NULL;

	free(object2);
	object2 = NULL;

	return((data_t)str);

} 


extern void Assignment(p_mv_object_t object1, p_mv_object_t object2)
{
	char* str_obj1 = object1->object_value;
	char* str_obj2 = object2->object_value;

	printf("Assignment(%s, %s)\n", str_obj1, str_obj2);

	return(0);

}



