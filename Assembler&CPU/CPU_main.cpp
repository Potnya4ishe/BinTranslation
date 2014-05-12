#define _CRT_SECURE_NO_WARNINGS

//{===========================================================
//! @file      CPU_main.cpp
//! @date      2013-11-10
//! @author    Andrey Ryazanov <andrrez95@mail.ru>, 377
//!    @version   1.1
//!
//! CPU.
//!
//! @par       Commands avaible:
//!            : {value}       - sets label {value}
//!             push    - pushes value to stack
//!             pop     - pops valuse from stack
//!             push_ax (bx, cx, dx)    - pushes reg to stack
//!             pop_ax (bx, cx, dx)     - pops the value from stack to reg
//!             add     - pushes the sum of two popped values from stack
//!             mul     - pushes the product of two popped values from stack
//!             div     - pushes the division of last value to another popped value from stack
//!             sub     - pushes the residual of two popped values from stack
//!             sin     - pushes sin of popped value from stack
//!             pow     - pushes power function of two popped values from stack
//!             cos     - pushes cos of popped value from stack
//!             tan     - pushes tan of popped value from stack
//!             sin     - pushes sin of popped value from stack
//!             sqrt    - pushes sqrt of popped value from stack
//!             dubl    - pushes a dublication of popped value from stack
//!
//!             jmp :   - jumps on to the label
//!             je :    - jumps on to the label, if two popped values are equal
//!             jne :   - jumps on to the label, if two popped values are not equal
//!             jbg :   - jumps on to the label, if first popped value is bigger then second popped value
//!             jnbg :  - jumps on to the label, if first popped value is not bigger then second popped value
//!             jsml :  - jumps on to the label, if first popped value is smaller then second popped value
//!             jnsml :   - jumps on to the label, if first popped value is not smaller then second popped value
//!
//!             IN      - gets the value from intput stream and pushes it
//!             OUT     - prints into output stream popped value
//!
//!             End     - ends a program.
//============================================================}

#include "CPU.h"
//#include "CPU_functions.cpp"

int main()
{
    printf( "It`s the program that will read your code from the file \n\
             and will give you a result\n");
    CPU_t my_cpu = { 0 };
    FILE *read_file = fopen( "Out_code.txt", "r");
    int file_code[MAX_SIZE_OF_CODE] = {0};
    assert( &my_cpu);
    CPU_construct( &my_cpu);
    assert( &my_cpu);
    CPU_read( &my_cpu, read_file);
    assert( &my_cpu);
    CPU_calculate( &my_cpu);
    assert( &my_cpu);
    fclose( read_file);
    CPU_destruct( &my_cpu);
	system("pause");
    return 0;
}
