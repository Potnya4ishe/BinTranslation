//{===========================================================
//! @file Commands.h
//============================================================}
#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED
#define MAX_LABELS 200
#define MAX_SIZE_OF_CODE 2000
#define MAX_CHAR_SIZE 200


enum
{
	CMD_nop = 90,

    CMD_IN = 1000,
    CMD_OUT = 1001,
    CMD_OUTLN = 1002,

    CMD_push = 1,
    CMD_pop = 2,
    CMD_add = 3,
    CMD_mul = 4,
    CMD_div = 5,
    CMD_sub = 6,
    CMD_sin = 7,
    CMD_cos = 8,
    CMD_tan = 9,
    CMD_pow = 10,
    CMD_sqrt = 11,
    CMD_dubl = 12,

    CMD_push_ax = 101,
    CMD_push_bx = 102,
    CMD_push_cx = 103,
    CMD_push_dx = 104,

    CMD_pop_ax = 201,
    CMD_pop_bx = 202,
    CMD_pop_cx = 203,
    CMD_pop_dx = 204,

    CMD_label = 499,
    CMD_jmp = 500,
    CMD_je = 501,
    CMD_jne = 502,
    CMD_jbg = 503,
    CMD_jsml = 504,
    CMD_jnbg = 505,
    CMD_jnsml = 506,

    CMD_call = 777,
    CMD_ret = 778,

    CMD_End = 666,			// DONE!!!

    CMD_EF = -666			// DONE!!!
};

#endif // COMMANDS_H_INCLUDED
