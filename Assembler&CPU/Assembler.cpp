//{===========================================================
//! @file Assembler.c
//============================================================}

#define _CRT_SECURE_NO_WARNINGS

#define CMD_CHECK(word,namecmd) if( !strcmp( word, #namecmd)) numb_of_cmd = CMD_##namecmd; else

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Commands.h"
#include "Stacklib.h"



int assembler ( FILE* read_file, FILE* assem_code );

int main()
{
    FILE* input = fopen ("Factorial2.txt", "r");
    FILE* output = fopen ("Out_code.txt", "w");
    assembler( input, output);
    fclose( input);
    fclose( output);
	system("pause");
	return 0;
}

int assembler(FILE *read_file, FILE* assem_code)
    {
        assert( read_file );
        assert( assem_code);
        //char ok_sign[2];
        //fscanf(read_file, "%s", ok_sign);
        //SIGN[2] = '\0';
        //if (strcmp( SIGN, ok_sign))
        //{
        //    printf("It seems the file has wrong signature!\nYours one is '%s', but it should be '%s'\nSorry, program is aborting...\n ", ok_sign, SIGN);
        //    assert( 0 );
        //}
        printf("The signature is correct! Thanks!\n");
        //fprintf(assem_code, "%s\n", SIGN);
        int labels[MAX_LABELS] = {0};
        int use_of_label[MAX_LABELS][MAX_LABELS] = {0};
        int numb_of_uses[MAX_LABELS] = {0};
        int file_code[MAX_SIZE_OF_CODE] = {0};
        char        neof = 1,
            expected_end = 0,
             length_prog = 0;
        int   numb_of_cmd = -1,
                        i =  0,
                 position =  0,
                label_now =  0;
        for ( i = 0; i < MAX_LABELS; i++)
            labels[i] = -2;
        char cmd[MAX_CHAR_SIZE] = {' '};
        while ( neof)
        {
            assert( 0 <= position && position <= MAX_SIZE_OF_CODE);
            int length = 0;
            fscanf( read_file, "%s%n", cmd, &length);
            //printf("command is '%s'\n", cmd);
            if (length > MAX_CHAR_SIZE)
            {
                printf("Too much symbols in the command!\n");
                assert( 0 );
            }
            #include "CMD_CHECK.h"
            if (!strcmp(cmd, ":"))
            {
                //printf("we found a label!! %d\n", position);
                numb_of_cmd = CMD_label;
            }
            else
            {
            printf( "You command is incorrect! Program will ignore this command!\n");
            printf( "Command '%s' doesn`t exist! Program is aborting!...\n", cmd);
            assert( 0);
            }
            if ( numb_of_cmd == CMD_push)
            {
                double d = 0;
                assert( position < MAX_SIZE_OF_CODE);
                file_code[position] = CMD_push;
                fscanf( read_file, "%lf", &d);
                file_code[position+1] = (double) d;
                position++;
            }
            else if (numb_of_cmd == CMD_EF)
            {
                file_code[position] = CMD_EF;
                neof = 0;
            }
            else if (numb_of_cmd == CMD_End)
            {
                length_prog = position;
                file_code[position] = CMD_End;
            }
            else if (numb_of_cmd == CMD_label)
            {
                fscanf( read_file, "%d", &label_now);
                //printf("work with label!\nlabel was not used - %d\n", labels[label_now]);
                if ( labels[label_now] != -1)
                {
                    labels[label_now] = position;
                    //printf("positiont of label %d is line #%d\n", label_now, position);
                }
                else
                {
                    labels[label_now] = position;
                    for ( i = 0; i < numb_of_uses[label_now]; i++)
                        file_code[use_of_label[label_now][i]] = position;

                    //printf("positiont of label %d is line #%d\n", label_now, position);
                }
                position--;
            }

            else if (
            #include "JMP.h"
                             )
            {
                fscanf(read_file, " :%d", &label_now);
                file_code[position] = numb_of_cmd;
                position ++;
                if (labels[label_now] != -1 && labels[label_now] != -2)
                {
                    file_code[position] = labels[label_now];
                }
                else
                {
                    labels[label_now] = -1;
                    use_of_label[label_now][numb_of_uses[label_now]] = position;
                    numb_of_uses[label_now]++;
                }
            }
            else file_code[position] = numb_of_cmd;
            position++;
            if ( strcmp( cmd, "EF") && feof( read_file))
            {
                printf("Command 'EF' expected!\nWe will write it for you this time, but don`t forget it again!\n");
                file_code[position++] = CMD_EF;
                neof = 0;
            }
        }
        for ( i = 0; i < position; i++)
        fprintf(assem_code, "%d\n", file_code[i]);
        return length_prog;
    }

#undef CMD_CHECK
