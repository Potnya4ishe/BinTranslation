#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Commands.h"

#define SizeOfData 20000
#define SizeOfFile 20000

void put_4_bytes(unsigned int number, int* position, unsigned char* New, int roll);

void x86_printf(int* position, unsigned char* New);

void trans_End(unsigned char* New, int* pointer);

void add_ebp_4(unsigned char* New, int* pointer);

void add_esp_4(unsigned char* New, int* pointer);

void trans_Push(unsigned char* New, int* pointer, int number);

void trans_Pop(unsigned char* New, int* pointer);

void adress_fill(unsigned char* New, int* adress_in_86, int* label_on_line, int max_position);

void trans_Add(unsigned char* New, int* pointer);

void trans_Dubl(unsigned char* New, int* pointer);

void trans_Mull(unsigned char* New, int* pointer);

void trans_Div(unsigned char* New, int* pointer);

void trans_Sub(unsigned char* New, int* pointer);

void trans_OUT(unsigned char* New, int* pointer);

void trans_In(unsigned char* New, int* pointer);

void change_maket_exe(unsigned char* New, int* array_code, int length);

void trans_CMP(unsigned char* New, int* pointer);

int main()
{
	FILE* read_EXE = fopen("Tempelate.exe", "r+b");
	unsigned char Data[SizeOfData] = { '0' };
	unsigned char NewData[SizeOfData] = { '0' };

	FILE* text_from_EXE = fopen("Template.txt", "wt");
	fread_s(Data, SizeOfData, 1, SizeOfFile, read_EXE);

	for (int i = 0; i < SizeOfData; i++) NewData[i] = Data[i];

	FILE* code_to_translate = fopen("Assembler&CPU\\Out_code.txt", "r");
	int code_array[SizeOfData] = { 0 };
	int i = 0;
	while (!feof(code_to_translate))
		fscanf(code_to_translate, "%d", &code_array[i++]);
	int length = i - 1;
	change_maket_exe( NewData, code_array, length);
	for (i = 0x400; i < SizeOfData; i++)
	{
		fprintf(text_from_EXE, "%X:\t%X\t||\t%X\t", i, Data[i], NewData[i]);
		if (Data[i] != NewData[i])
			fprintf(text_from_EXE, "|!!!|");
		fprintf(text_from_EXE, "\n");
	}
	FILE* new_EXE = fopen("Program.exe", "wb");
	fwrite(NewData, 1, SizeOfData, new_EXE);

	fclose(new_EXE);
	fclose(read_EXE);
	fclose(text_from_EXE);
	//system("PAUSE");
	return 0;
}


void put_4_bytes(unsigned int number, int* position, unsigned char* New, int roll)
{
	New[*position + roll] = number % 256;
	number /= 256;
	New[*position + 1 + roll] = number % 256;
	number = (number) / 256;
	New[*position + 2 + roll] = number % 256;
	number = (number) / 256;
	New[*position + 3 + roll] = number % 256;
	*position += 4;
	return;
}

void x86_printf(int* position, unsigned char* New)
{
	New[*position] = 0xE8;
	int adress = 0x12F4 - (*position + 5);
	put_4_bytes(adress, position, New, 1);
	*position += 1;
	return;
}

void trans_End(unsigned char* New, int* pointer)
{
	New[*pointer] = 0x68;
	put_4_bytes(0x2328, pointer, New, 1);
	*pointer += 1;
	New[*pointer] = 0xE8;
	put_4_bytes(0x12EE - (*pointer + 5), pointer, New, 1);
	*pointer += 1;
	int length_jump = 0x12DC + -(*pointer + 7);
	New[*pointer] = 0x6A;
	New[*pointer + 1] = 0;
	New[*pointer + 2] = 0xE8;
	put_4_bytes(length_jump, pointer, New, 3);
	*pointer += 3;
	return;
}

void add_esp_4(unsigned char* New, int* pointer)
{
	New[*pointer] = 0x83;
	New[*pointer + 1] = 0xC4;
	New[*pointer + 2] = 0x4;
	*pointer += 3;
	return;
}

void add_ebp_4(unsigned char* New, int* pointer)
{
	New[*pointer] = 0x83;
	New[*pointer + 1] = 0xC5;
	New[*pointer + 2] = 0x4;
	*pointer += 3;
	return;
}

void trans_Push(unsigned char* New, int* pointer, int number)
{
	New[*pointer] = 0xC7;
	New[*pointer + 1] = 0x45;
	New[*pointer + 2] = 0;
	*pointer += 3;
	put_4_bytes(number, pointer, New, 0);
	add_ebp_4(New, pointer);
	return;
}

void trans_Pop(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x83;
	New[(*pointer)++] = 0xED;
	New[(*pointer)++] = 0x4;
	return;
}

void adress_fill(unsigned char* New, int* adress_of_line_in_86, int* label_on_line, int max_position)
{
	assert(adress_of_line_in_86);
	assert(label_on_line);
	int i = 0;
	int adress = 0;
	int addr_to_pl = 0;
	for (i = 0; i < max_position - 0x400; i++)
	{
		if (label_on_line[i] != 0)
		{
			adress = adress_of_line_in_86[label_on_line[i]];
			addr_to_pl = i + 0x400;
			put_4_bytes(adress - (i + 0x400 + 4), &addr_to_pl , New, 0);
		}
	}
	return;
}

void trans_Add(unsigned char* New, int* pointer)
{
	trans_Pop(New, pointer);
	put_4_bytes(0x03007D8B, pointer, New, 0);
	put_4_bytes(0x7D89FC7D, pointer, New, 0);
	New[(*pointer)++] = 0xFC;
	return;
}

void trans_Mull(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x50;
	trans_Pop(New, pointer);
	New[(*pointer)++] = 0x8B;
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0x0;
	put_4_bytes(0x89FC65F7, pointer, New, 0);

	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0xFC;
	New[(*pointer)++] = 0x58;

	return;
}

void trans_Dubl(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x50;
	New[(*pointer)++] = 0x8B;
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0xFC;
	New[(*pointer)++] = 0x89;
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0x0;
	add_ebp_4(New, pointer);
	New[(*pointer)++] = 0x58;
	return;
}

void trans_Div(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x50;
	New[(*pointer)++] = 0x52;
	trans_Pop(New, pointer);
	put_4_bytes(0xF700458B, pointer, New, 0);
	put_4_bytes(0x4589FC65, pointer, New, 0);
	New[(*pointer)++] = 0xFC;
	New[(*pointer)++] = 0x5A;
	New[(*pointer)++] = 0x58;
	return;
}

void trans_Sub(unsigned char* New, int* pointer)
{
	trans_Pop(New, pointer);
	put_4_bytes(0x2B007D8B, pointer, New, 0);
	put_4_bytes(0x7D89FC7D, pointer, New, 0);
	New[(*pointer)++] = 0xFC;
	return;
}

void trans_In(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x53;				//push ebx

	New[(*pointer)++] = 0xBB;				// mov ebx, 10d
	put_4_bytes(0x0A, pointer, New, 0);

	New[(*pointer)++] = 0x52;				// push edx
	New[(*pointer)++] = 0x52;				// push ecx
	New[(*pointer)++] = 0x50;				// push eax
	New[(*pointer)++] = 0x55;				// push ebp

	New[(*pointer)++] = 0x6A;				// push 0
	New[(*pointer)++] = 0x0;

	New[(*pointer)++] = 0x68;				// push string for read
	put_4_bytes(0x0040311C, pointer, New, 0);

	New[(*pointer)++] = 0x6A;				// push 10h
	New[(*pointer)++] = 0x10;

	New[(*pointer)++] = 0x68;				// puh string where to write
	put_4_bytes(0x0040310C, pointer, New, 0);

	New[(*pointer)++] = 0xFF;				// push dword ptr hand_In
	New[(*pointer)++] = 0x35;
	put_4_bytes(0x00403104, pointer, New, 0);

	New[(*pointer)++] = 0xE8;				// call ReadConsole
	put_4_bytes(0x12E8 - (*pointer+4) , pointer, New, 0);

	New[(*pointer)++] = 0xBD;				// mov ebp, offset read_char
	put_4_bytes(0x0040310C, pointer, New, 0);

	New[(*pointer)++] = 0x33;				// xor eax, eax
	New[(*pointer)++] = 0xC0;

	New[(*pointer)++] = 0x83;				// sub ebp, 1
	New[(*pointer)++] = 0xED;
	New[(*pointer)++] = 0x1;
	// Loop_dec:
	New[(*pointer)++] = 0x83;				// add ebp, 1
	New[(*pointer)++] = 0xC5;
	New[(*pointer)++] = 0x1;

	New[(*pointer)++] = 0x33;				// xor ecx, ecx
	New[(*pointer)++] = 0xC9;

	New[(*pointer)++] = 0x8A;				// mov cl, byte ptr [ebp]			
	New[(*pointer)++] = 0x4D;
	New[(*pointer)++] = 0x0;

	New[(*pointer)++] = 0x80;				// cmp cl, 0Dh
	New[(*pointer)++] = 0xF9;
	New[(*pointer)++] = 0xD;

	New[(*pointer)++] = 0x74;				// je Loop_exit
	New[(*pointer)++] = 0x9;

	New[(*pointer)++] = 0xF7;				// mul ebx		
	New[(*pointer)++] = 0xE3;

	New[(*pointer)++] = 0x80;				// sub cl, 30h
	New[(*pointer)++] = 0xE9;
	New[(*pointer)++] = 0x30;

	New[(*pointer)++] = 0x3;				// add eax, ecx
	New[(*pointer)++] = 0xC1;

	New[(*pointer)++] = 0xEB;				// jmp Loop_dec 
	New[(*pointer)++] = 0xEA;
	// loop_end:
	New[(*pointer)++] = 0x5D;				// pop ebp
	New[(*pointer)++] = 0x89;				// mov [ebp], eax
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0x0;

	New[(*pointer)++] = 0x58;				// pop eax
	New[(*pointer)++] = 0x83;				// add ebp, 4
	New[(*pointer)++] = 0xC5;
	New[(*pointer)++] = 0x04;

	New[(*pointer)++] = 0x59;				// pop ecx
	New[(*pointer)++] = 0x5A;				// pop edx
	New[(*pointer)++] = 0x5B;				// pop ebx
	return;
}

void trans_OUT(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x50;
	trans_Pop(New, pointer);
	put_4_bytes(0x5000458B, pointer, New, 0);
	put_4_bytes(0x40202068, pointer, New, 0);
	New[(*pointer)++] = 0;
	New[(*pointer)++] = 0xE8;
	put_4_bytes(0x12F4 - (*pointer + 4), pointer, New, 0);
	New[(*pointer)++] = 0x83;
	New[(*pointer)++] = 0xC4;
	New[(*pointer)++] = 0x8;
	New[(*pointer)++] = 0x58;
}

void trans_CMP(unsigned char* New, int* pointer)
{
	New[(*pointer)++] = 0x50;
	trans_Pop(New, pointer);
	New[(*pointer)++] = 0x8B;
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0x0;
	trans_Pop(New, pointer);
	New[(*pointer)++] = 0x3B;
	New[(*pointer)++] = 0x45;
	New[(*pointer)++] = 0x0;
	New[(*pointer)++] = 0x58;
	return;
}

void change_maket_exe(unsigned char* New, int* array_code, int length)
{
	assert(array_code);
	assert(New);
	int adress_of_line_in_86[SizeOfData] = { 0 };
	int label_on_line[SizeOfData] = { 0 };
	int		max_pos_of_label = 0,
		position = 0,
		number = 0,
		label = 0,
		cmd_now = 0,
		exe_pointer = 0x411,
		numb_line = 0,
		num_cmd = 0;
	for (num_cmd = 0; num_cmd <= length; num_cmd++)
	{
		adress_of_line_in_86[numb_line] = exe_pointer;
		numb_line++;
		cmd_now = array_code[num_cmd];
		switch (cmd_now)
		{
		case CMD_End:
			
			trans_End(New, &exe_pointer);
			break;

		case CMD_EF:

			trans_End(New, &exe_pointer);
			break;

		case CMD_push:

			numb_line++;
			number = array_code[++num_cmd];
			trans_Push(New, &exe_pointer, number);
			break;

		case CMD_pop:

			trans_Pop(New, &exe_pointer);
			break;

		case CMD_push_ax:

			New[exe_pointer++] = 0x89;
			New[exe_pointer++] = 0x45;
			New[exe_pointer++] = 0x0;
			add_ebp_4(New, &exe_pointer);
			break;

		case CMD_push_bx:

			New[exe_pointer++] = 0x89;
			New[exe_pointer++] = 0x5D;
			New[exe_pointer++] = 0x0;
			add_ebp_4(New, &exe_pointer);
			break;

		case CMD_push_cx:

			New[exe_pointer++] = 0x89;
			New[exe_pointer++] = 0x4D;
			New[exe_pointer++] = 0x0;
			add_ebp_4(New, &exe_pointer);
			break;

		case CMD_push_dx:

			New[exe_pointer++] = 0x89;
			New[exe_pointer++] = 0x55;
			New[exe_pointer++] = 0x0;
			add_ebp_4(New, &exe_pointer);
			break;

		case CMD_pop_ax:

			trans_Pop(New, &exe_pointer);
			New[exe_pointer++] = 0x8B;
			New[exe_pointer++] = 0x45;
			New[exe_pointer++] = 0x0;
			break;

		case CMD_pop_bx:

			trans_Pop(New, &exe_pointer);
			New[exe_pointer++] = 0x8B;
			New[exe_pointer++] = 0x5D;
			New[exe_pointer++] = 0x0;
			break;

		case CMD_pop_cx:

			trans_Pop(New, &exe_pointer);
			New[exe_pointer++] = 0x8B;
			New[exe_pointer++] = 0x4D;
			New[exe_pointer++] = 0x0;
			break;

		case CMD_pop_dx:

			trans_Pop(New, &exe_pointer);
			New[exe_pointer++] = 0x8B;
			New[exe_pointer++] = 0x55;
			New[exe_pointer++] = 0x0;
			break;


		case CMD_nop:
			New[exe_pointer] = 0x90;
			exe_pointer++;
			break;

		case CMD_OUTLN:
			New[exe_pointer] = 0x68;
			put_4_bytes(0x402025, &exe_pointer, New, 1);
			exe_pointer += 1;
			x86_printf(&exe_pointer, New);
			add_esp_4(New, &exe_pointer);
			break;

		case CMD_add:

			trans_Add(New, &exe_pointer);
			break;

		case CMD_sub:

			trans_Sub(New, &exe_pointer);
			break;

		case CMD_div:

			trans_Div(New, &exe_pointer);
			break;

		case CMD_OUT:

			trans_OUT(New, &exe_pointer);
			break;

		case CMD_jmp:

			New[exe_pointer++] = 0xE9;
			numb_line++;
			label_on_line[exe_pointer - 0x400 ] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_je:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x84;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;


		case CMD_jne:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x85;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_jbg:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x8F;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_jnsml:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x8D;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_jsml:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x8C;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;


		case CMD_jnbg:

			trans_CMP(New, &exe_pointer);
			New[exe_pointer++] = 0xF;
			New[exe_pointer++] = 0x8E;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_mul:

			trans_Mull(New, &exe_pointer);
			break;

		case CMD_dubl:

			trans_Dubl(New, &exe_pointer);
			break;

		case CMD_ret:

			New[exe_pointer++] = 0xC3;
			break;

		case CMD_call:

			New[exe_pointer++] = 0xE8;
			numb_line++;
			label_on_line[exe_pointer - 0x400] = array_code[++num_cmd];
			exe_pointer += 4;
			break;

		case CMD_IN:

			trans_In(New, &exe_pointer);
			break;
		}

	}
	adress_fill(New, adress_of_line_in_86, label_on_line, exe_pointer);
	return;
}
