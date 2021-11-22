//在VS中是通过call 和 jmp 实现函数间跳转，为了方便查看函数的嵌套逻辑，这里直接采用内嵌方式编写ASM。

/*对于函数之间的内嵌调用来说，实际就是俄罗斯套娃的问题，每个函数都有自己的堆栈空间，每次调用一个函数就是给他开辟自己的堆栈空间，通过寄存器或者内存传参进去，然后
通过eax 或者其他寄存器获取返回值。。
main
  main 堆栈初始化;
  main 自己的函数功能代码;
  mov eax,dword ptr [ebp-4]  //main 中的局部变量1
  mov ecx,dword pte [ebp-8]  //main 中的局部变量2
  push eax
  push ecx
  call one() //调用函数 将main中2个局部变量作为参数传入one()函数  
    one() 堆栈初始化 
    one() 传入参数保存在 ebp+8 和 ebp+c 中         
    one函数计算结果
    ret    //结果保存在eax中  
  mov 通过 eax 获取计算结果 
ret

*/

#include <stdio.h>

void one_there(void);
void two(void);



int main(void)
{

	printf("starting now!\n");
	one_there();
	printf("done!\n");
	return 0;
}


void one_there(void)
{
	printf("one!\n");
	two();   
	printf("three!\n");
}

void two(void)
{
	printf("two\n");

}


//main 函数堆栈初始化
push ebp 
mov ebp,esp 
sub esp 48h 
push ebx 
push esi
push edi 
lea edi,dword ptr [ebp-48h]
mov eax,0CCCCCCCCh
mov ecx,12h 
rep stos dword ptr [edi]

push "starting  now!"...
call printf("%s\n", );
add esp,4   //调用一次printf 平衡堆栈  

//进入one_three()函数
call one_there();
	push ebp
	mov ebp,esp 
	sub esp,40h 
	push ebx 
	push  edi 
	push esi 
	lea edi, dword ptr [ebp-40h] 
	mov eax,0CCCCCCCCh
	mov ecx,10h 
	rep stos dword ptr [edi]
	//one_three()函数堆栈初始化

	push "one\n"
	call printf("%s\n", );
	add esp,4

	call two();   //函数嵌套调用 在one_three() 函数中调用two()函数 
		push ebp 
		mov ebp,esp 
		sub esp,40h 
		push ebx 
		push edi
		push esi 
		lea edi,dword ptr [ebp-40h]
		mov eax,0CCCCCCCCh
		mov ecx,10h 
		//two()函数堆栈初始化
		push "two\n"
		call printf("%s\n", );
		add esp,4 

		pop edi 
		pop esi 
		pop ebx 
		add esp,40h
		cmp esp,ebp 
		call __chkesp
		mov esp,ebp 
		pop ebp 
		ret  //回到 one_there()主调函数
	push "three\n"
	call printf("%s\n", );
	add esp,4 

	pop edi
	pop esi 
	pop ebx 
	add esp,40h 
	cmp ebp,esp 
	call __chkesp
	mov esp,ebp 
	pop ebp
	ret    //回到main 主调函数

push "done\n"
call printf("%s\n", );
add esp,4

pop edi
pop esi
pop ebx 
add esp,40h 
cmp esp,ebp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 

//////////////////////////////////VS 中的函数嵌套//////////////////////////////////////


11:   int main(void)
12:   {
00401030   push        ebp
00401031   mov         ebp,esp
00401033   sub         esp,40h
00401036   push        ebx
00401037   push        esi
00401038   push        edi
00401039   lea         edi,[ebp-40h]
0040103C   mov         ecx,10h
00401041   mov         eax,0CCCCCCCCh
00401046   rep stos    dword ptr [edi]
13:
14:       printf("starting now!\n");
00401048   push        offset string "starting now!\n" (00422024)
0040104D   call        printf (00401140)
00401052   add         esp,4
15:       one_there();              
00401055   call        @ILT+5(one_there) (0040100a)   //跳转到one_three() 函数地址
16:       printf("done!\n");
0040105A   push        offset string "done!\n" (0042201c)
0040105F   call        printf (00401140)
00401064   add         esp,4
17:       return 0;
00401067   xor         eax,eax
18:   }
00401069   pop         edi
0040106A   pop         esi
0040106B   pop         ebx
0040106C   add         esp,40h
0040106F   cmp         ebp,esp
00401071   call        __chkesp (004011c0)
00401076   mov         esp,ebp
00401078   pop         ebp
00401079   ret
--- No source file  --------------------------------------------------------------------------------------------------------------------------------
0040107A   int         3
0040107B   int         3
0040107C   int         3
0040107D   int         3
0040107E   int         3
0040107F   int         3
00401080   int         3
00401081   int         3
00401082   int         3
00401083   int         3
00401084   int         3
00401085   int         3
00401086   int         3
00401087   int         3
00401088   int         3
00401089   int         3
0040108A   int         3
0040108B   int         3
0040108C   int         3
0040108D   int         3
0040108E   int         3
0040108F   int         3
--- C:\C\stu\stu\add.cpp  --------------------------------------------------------------------------------------------------------------------------
19:
20:
21:   void one_there(void)
22:   {
00401090   push        ebp
00401091   mov         ebp,esp
00401093   sub         esp,40h
00401096   push        ebx
00401097   push        esi
00401098   push        edi
00401099   lea         edi,[ebp-40h]
0040109C   mov         ecx,10h
004010A1   mov         eax,0CCCCCCCCh
004010A6   rep stos    dword ptr [edi]
23:       printf("one!\n");
004010A8   push        offset string "one!\n" (00422044)
004010AD   call        printf (00401140)   
004010B2   add         esp,4
24:       two();    
004010B5   call        @ILT+0(two) (00401005)   //跳转到two()函数地址
25:       printf("three!\n");
004010BA   push        offset string "three!\n" (00422038)
004010BF   call        printf (00401140)
004010C4   add         esp,4
26:   }
004010C7   pop         edi
004010C8   pop         esi
004010C9   pop         ebx
004010CA   add         esp,40h
004010CD   cmp         ebp,esp
004010CF   call        __chkesp (004011c0)
004010D4   mov         esp,ebp
004010D6   pop         ebp
004010D7   ret

004010D8   int         3
004010D9   int         3
004010DA   int         3

27:
28:   void two(void)
29:   {
004010F0   push        ebp
004010F1   mov         ebp,esp
004010F3   sub         esp,40h
004010F6   push        ebx
004010F7   push        esi
004010F8   push        edi
004010F9   lea         edi,[ebp-40h]
004010FC   mov         ecx,10h
00401101   mov         eax,0CCCCCCCCh
00401106   rep stos    dword ptr [edi]
30:       printf("two\n");
00401108   push        offset string "two\n" (0042204c)
0040110D   call        printf (00401140)
00401112   add         esp,4
31:
32:   }
00401115   pop         edi
00401116   pop         esi
00401117   pop         ebx
00401118   add         esp,40h
0040111B   cmp         ebp,esp
0040111D   call        __chkesp (004011c0)
00401122   mov         esp,ebp
00401124   pop         ebp
00401125   ret




