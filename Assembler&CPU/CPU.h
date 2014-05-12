//{===========================================================
//! @file CPU.h
//============================================================}
#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_SIZE 1000
//#include "Stacklib.h"
#include "Stacklib.h"
#include "Commands.h"

const int Poison = (int) 0xDEAD;

struct CPU
{
    Stackt cpu_stack;
    Stackt label_stack;
    int file_code[MAX_SIZE_OF_CODE];
    int code_length;
    double ax, bx, cx, dx;
};

typedef struct CPU CPU_t;

int CPU_write( CPU_t *my_cpu, FILE* out_file);

int CPU_construct( CPU_t* my_cpu);

int CPU_destruct ( CPU_t* my_cpu);

int CPU_OK ( CPU_t* my_cpu);

int CPU_dump ( CPU_t* my_cpu);

int CPU_calculate ( CPU_t* my_cpu);

int CPU_read( CPU_t* my_cpu, FILE* read_file);

#endif // CPU_H_INCLUDED
