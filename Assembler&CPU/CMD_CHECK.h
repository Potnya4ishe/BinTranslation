#ifndef CMD_CHECK_H_INCLUDED
#define CMD_CHECK_H_INCLUDED

#define CMD_CHECK(word,namecmd) if( !strcmp( word, #namecmd)) numb_of_cmd = CMD_##namecmd; else


            CMD_CHECK(cmd,push)
            CMD_CHECK(cmd,pop)
            CMD_CHECK(cmd,add)
            CMD_CHECK(cmd,mul)
            CMD_CHECK(cmd,div)
            CMD_CHECK(cmd,sub)
            CMD_CHECK(cmd,sin)
            CMD_CHECK(cmd,cos)
            CMD_CHECK(cmd,tan)
            CMD_CHECK(cmd,pow)
            CMD_CHECK(cmd,sqrt)
            CMD_CHECK(cmd,End)
            CMD_CHECK(cmd,push_ax)
            CMD_CHECK(cmd,push_bx)
            CMD_CHECK(cmd,push_cx)
            CMD_CHECK(cmd,push_dx)
            CMD_CHECK(cmd,pop_ax)
            CMD_CHECK(cmd,pop_bx)
            CMD_CHECK(cmd,pop_cx)
            CMD_CHECK(cmd,pop_dx)
            CMD_CHECK(cmd,jmp)
            CMD_CHECK(cmd,je)
            CMD_CHECK(cmd,jne)
            CMD_CHECK(cmd,jbg)
            CMD_CHECK(cmd,jnbg)
            CMD_CHECK(cmd,jsml)
            CMD_CHECK(cmd,jnsml)
            CMD_CHECK(cmd,dubl)
            CMD_CHECK(cmd,IN)
            CMD_CHECK(cmd,OUT)
            CMD_CHECK(cmd,call)
            CMD_CHECK(cmd,ret)
            CMD_CHECK(cmd,EF)
            CMD_CHECK(cmd,OUTLN)


#endif // CMD_CHECK_H_INCLUDED
