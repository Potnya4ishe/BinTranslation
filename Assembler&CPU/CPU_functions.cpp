#define _CRT_SECURE_NO_WARNINGS


#ifndef CPU_FUNCTIONS_CPP_
#define CPU_FUNCTIONS_CPP_
//{===========================================================
//! @file CPU_functions.c
//============================================================}

#include "CPU.h"

//char SIGN[3] = { 'A', 'R', '\0' };

int CPU_construct( CPU_t* my_cpu)
    {
        assert( my_cpu!=NULL);
        Stack_construct(&my_cpu->cpu_stack, MAX_SIZE);
        Stack_construct(&my_cpu->label_stack, MAX_SIZE);
        my_cpu->ax = 0;
        my_cpu->bx = 0;
        my_cpu->cx = 0;
        my_cpu->dx = 0;
        my_cpu->code_length = 0;
        assert( CPU_OK(my_cpu));
		return 0;
    }

int CPU_destruct ( CPU_t* my_cpu)
    {
        assert( CPU_OK(my_cpu));
        assert( my_cpu!=NULL);
        Stack_destruct( &my_cpu->cpu_stack);
        Stack_destruct( &my_cpu->label_stack);
        my_cpu->ax = Poison;
        my_cpu->bx = Poison;
        my_cpu->cx = Poison;
        my_cpu->dx = Poison;
        //free( &my_cpu->file_code);
        my_cpu->code_length = Poison;
		return 0;
    }

int CPU_OK ( CPU_t* my_cpu)
    {
        assert( my_cpu!=NULL);
        if (!Stack_ok(&my_cpu->cpu_stack))               return 0;
        if (!Stack_ok(&my_cpu->label_stack))             return 0;
        else if (my_cpu->code_length > MAX_SIZE_OF_CODE) return 0;
        else return 1;

    }

int CPU_dump ( CPU_t* my_cpu)
    {
        assert( CPU_OK(my_cpu));
        assert( my_cpu!=NULL);
        Stack_dump(&my_cpu->cpu_stack);
        printf( "ax = %lf\n", my_cpu->ax);
        printf( "bx = %lf\n", my_cpu->bx);
        printf( "cx = %lf\n", my_cpu->cx);
		return 0;
    }

int CPU_read( CPU_t* my_cpu, FILE* read_file)
    {
        assert( CPU_OK(my_cpu));
        assert( my_cpu!=NULL);
        //char ok_sign[2];
        //fscanf(read_file, "%s", ok_sign);
        //if (strcmp( SIGN, ok_sign))
        //{
        //    printf("It seems the file has wrong signature!\nYours one is '%s', but it should be '%s'\nSorry, program is aborting...\n ", ok_sign, SIGN);
        //    assert( 0 );
        //}
        printf("The signature is correct! Thanks!\n");
        int neof = 1, length = 0, now_cmnd = 0;
        while (neof)
        {
            fscanf( read_file, "%d", &now_cmnd);
            my_cpu->file_code[length] = now_cmnd;
            if ( now_cmnd == CMD_EF)
                neof = 0;
            length++;
        }
        my_cpu->code_length = length;
        assert( CPU_OK(my_cpu));
		return 0;
    }

int CPU_calculate ( CPU_t* my_cpu)
{
        assert( CPU_OK(my_cpu));
        printf( "Hello! Let`s start!\n");
        assert( my_cpu!=NULL);
        int position = 0;
        double a1, a2 = 0;

        #define CMD_SWITCH_(name,code) \
        case CMD_##name :  \
        code;\
        break;

		while (my_cpu->file_code[position] != CMD_End && my_cpu->file_code[position] != CMD_EF )
        {
            assert( 0 <= position && position <= MAX_SIZE_OF_CODE);
            int cmd = my_cpu->file_code[position];
            //printf( "Now command is %d\nPosition is %d\n", cmd, position);
            switch (cmd)
            {
                CMD_SWITCH_(push, Stack_push( &my_cpu->cpu_stack, my_cpu->file_code[++position]))
                CMD_SWITCH_(pop, Stack_pop( &my_cpu->cpu_stack))
                CMD_SWITCH_(add, a1 = Stack_pop( &my_cpu->cpu_stack); a2 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, a1+a2))
                CMD_SWITCH_(mul, a1 = Stack_pop( &my_cpu->cpu_stack); a2 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, a1*a2))
                CMD_SWITCH_(div, a1 = Stack_pop( &my_cpu->cpu_stack); a2 = Stack_pop( &my_cpu->cpu_stack); if (!a2){printf("You can`t divide by zero!");assert(0);} Stack_push( &my_cpu->cpu_stack, a1/a2))
                CMD_SWITCH_(sub, a1 = Stack_pop( &my_cpu->cpu_stack); a2 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, a1-a2))
                CMD_SWITCH_(sin, a1 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, sin(a1)))
                CMD_SWITCH_(cos, a1 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, cos(a1)))
                CMD_SWITCH_(tan, a1 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, tan(a1)))
                CMD_SWITCH_(sqrt,a1 = Stack_pop( &my_cpu->cpu_stack);if (a1<0){printf("You can`t take sqrt from numbers less them zero!!! Equations has no roots!");} Stack_push( &my_cpu->cpu_stack, sqrt(a1)))
                CMD_SWITCH_(pow, a1 = Stack_pop( &my_cpu->cpu_stack); a2 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, pow(a1 ,a2)))
                CMD_SWITCH_(dubl,a1 = Stack_pop( &my_cpu->cpu_stack); Stack_push( &my_cpu->cpu_stack, a1); Stack_push( &my_cpu->cpu_stack, a1))

                CMD_SWITCH_(push_ax, Stack_push( &my_cpu->cpu_stack, my_cpu->ax))
                CMD_SWITCH_(push_bx, Stack_push( &my_cpu->cpu_stack, my_cpu->bx))
                CMD_SWITCH_(push_cx, Stack_push( &my_cpu->cpu_stack, my_cpu->cx))
                CMD_SWITCH_(push_dx, Stack_push( &my_cpu->cpu_stack, my_cpu->dx))

                CMD_SWITCH_(pop_ax,  my_cpu->ax = Stack_pop( &my_cpu->cpu_stack))
                CMD_SWITCH_(pop_bx,  my_cpu->bx = Stack_pop( &my_cpu->cpu_stack))
                CMD_SWITCH_(pop_cx,  my_cpu->cx = Stack_pop( &my_cpu->cpu_stack))
                CMD_SWITCH_(pop_dx,  my_cpu->dx = Stack_pop( &my_cpu->cpu_stack))

                CMD_SWITCH_(jmp, position = my_cpu->file_code[position+1]-1)
                CMD_SWITCH_(je, if (Stack_pop( &my_cpu->cpu_stack) == Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)
                CMD_SWITCH_(jne, if (Stack_pop( &my_cpu->cpu_stack) != Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)
                CMD_SWITCH_(jbg, if (Stack_pop( &my_cpu->cpu_stack) > Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)
                CMD_SWITCH_(jnbg, if (Stack_pop( &my_cpu->cpu_stack) <= Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)
                CMD_SWITCH_(jsml, if (Stack_pop( &my_cpu->cpu_stack) < Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)
                CMD_SWITCH_(jnsml, if (Stack_pop( &my_cpu->cpu_stack) >= Stack_pop( &my_cpu->cpu_stack))
                             position = my_cpu->file_code[position+1]-1;
                             else position++)

                CMD_SWITCH_(call, Stack_push( &my_cpu->label_stack, position); /*printf("we need to call to position %d\n", position);*/ position = my_cpu->file_code[position+1]-1 )
                CMD_SWITCH_(ret, if ( !Stack_empty( &my_cpu->label_stack) ) { position = (int) Stack_pop( &my_cpu->label_stack ) + 1;} )

                CMD_SWITCH_(IN, scanf("%lf", &a1); Stack_push( &my_cpu->cpu_stack, a1))
                CMD_SWITCH_(OUT, a1 = Stack_pop( &my_cpu->cpu_stack); printf("%.2f\n", a1))
                CMD_SWITCH_(OUTLN, printf("\n"))
            }
            assert( 0 <= position <= MAX_SIZE_OF_CODE);
            assert( CPU_OK(my_cpu));
            assert( my_cpu!=NULL);
            position++;
            //CPU_dump(my_cpu);
        }
        return 0;
        #undef CMD_SWITCH_
}

/*int CPU_write( CPU_t *my_cpu, FILE* out_file)
{
    assert( CPU_OK(my_cpu));
    assert( out_file);
    int i = 0;
    for ( i = 0; i < my_cpu->code_length; i++)
        fprintf(out_file, "%d\n", my_cpu->file_code[i]);
}*/
#endif







