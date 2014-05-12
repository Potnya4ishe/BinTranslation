//{===========================================================
//! @file Stackfunctions.c
//============================================================}

#include "Stacklib.h"

int Stack_construct ( Stackt* my_stack, int my_size )
{
    int i = 0;
    my_stack->my_max_size = my_size;
    my_stack->data = (double*) calloc ( my_stack->my_max_size , sizeof(double));
    for ( i = 0; i < my_stack->my_max_size; i ++)
        my_stack->data[i] = 0;
    my_stack->numb = 0;
    my_stack->my_max_size = my_size;
    if ( my_stack->my_max_size > MAX_SIZE )
        assert( !printf( "You want to have bigger size then it`s allowed, error at line %d", __LINE__));
    #ifdef COOL_PRINT
    printf( "The stack of size %d was successfully constructed\n", my_stack->my_max_size);
    #endif
	return 0;
}

int Stack_ok ( Stackt* my_stack )
{
    if( 0 <= my_stack->numb && my_stack->numb <= my_stack->my_max_size && my_stack )
    {
        #ifdef VERY_COOL_PRINT
        printf ( "The stack is still ok\n");
        #endif
        return 1;
    }
    else
    {
        #ifdef VERY_COOL_PRINT
        printf ( "The stack is not ok\n" );
        assert (0);
        #endif // VERY_COOL_PRINT
        return 0;
    }
}

#define BAD_ASSERT(cond) if( Stack_ok ( cond ) == 0) { printf ( "The stack is not ok, error at line %d\n", __LINE__ ); assert ( 0 ); }


int Stack_push ( Stackt* my_stack, double new_data )
{
    BAD_ASSERT( my_stack);
    #ifdef COOL_PRINT
    printf("New data is %f\n", new_data);
    #endif // COOL_PRINT
    my_stack->data[my_stack->numb] = new_data;
    #ifdef COOL_PRINT
    printf("In stack new data is %f\n", my_stack->data[my_stack->numb]);
    #endif // COOL_PRINT
    (my_stack->numb) ++;
    BAD_ASSERT( my_stack);
	return 0;
}

double Stack_pop ( Stackt* my_stack )
{
    BAD_ASSERT( my_stack);
    (my_stack->numb) --;
    #ifdef COOL_PRINT
    printf  ( "We poped the value %f from stack\n", my_stack->data[my_stack->numb] );
    #endif // COOL_PRINT
    BAD_ASSERT( my_stack);
    return my_stack->data[my_stack->numb];
}

int Stack_full ( Stackt* my_stack )
{
    BAD_ASSERT( my_stack);
    if (my_stack->numb == my_stack->my_max_size)
    {
        #ifdef COOL_PRINT
        printf ( "The stack is full\n" );
        #endif // COOL_PRINT
        return 1;
    }
    else
    {

        #ifdef COOL_PRINT
        printf ( "The stack is not full\n" );
        #endif // COOL_PRINT
        return 0;
    }
}

int Stack_empty ( Stackt* my_stack )
{
    if ( my_stack->numb == 0)
    {
        #ifdef COOL_PRINT
        printf ( "The stack is empty\n" );
        #endif // COOL_PRINT
        return 1;
    }
    else
    {
        #ifdef COOL_PRINT
        printf ( "The stack is not empty\n" );
        #endif // COOL_PRINT
        return 0;
    }
}

int Stack_dump ( Stackt* my_stack )
{
    BAD_ASSERT( my_stack);
    Stack_full( my_stack);
    //printf( "Size of stack is %d \n", my_stack->my_max_size);
    printf( "Now we have %d elements \n", my_stack->numb);
    if ( Stack_empty ( my_stack) )
    {
        printf("He is empty\n");
        return 1;
    }
    int i = 0;
    for ( i = 0; i < my_stack->numb; i ++)
        printf( " the %d element is equals %.2f \n", i+1, my_stack->data[i]);
    BAD_ASSERT( my_stack);
    return 1;
}

int Stack_destruct ( Stackt* my_stack )
{
    BAD_ASSERT( my_stack);
    //printf("we will destroy your shit now, nigger\n");
    int i = 0;
    for ( i = 0; i < my_stack->my_max_size - 2 ; i++)
    {
        assert( 0 <= i && i < my_stack->my_max_size);
        my_stack->data[i] = -666;
    }
    my_stack->numb = 0;
    free( my_stack->data);
    #ifdef COOL_PRINT
    printf( "The stack was successfully destructed");
    #endif // COOL_PRINT
    return 0;
}
