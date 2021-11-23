#include <stdio.h>
#define PARSE "also,you first name has %d letter."
int main(void)
{
	char name[40];   
	printf("what your name?\n");
	scanf("%s",name);
	printf("Hello,%s. %s\n",name,PARSE );
	return 0;

}


push ebp
mov ebp,esp 
add esp,68h    //提升堆栈 数组堆栈空间预留
push ebx
push esi
push edi 
lea edi,dword ptr [ebp-68h]
mov eax,0cccccccch
mov ecx,1Ah   //68h = 108字节 / 4字节 = 26次
rep stos dword ptr [edi]


push offset string  "what your name?\n"
call  printf(00401100)
add esp,4

lea eax,[ebp-28h]  //获取数组首地址   lea 为取地址符 
push eax
push offset string "%s"  //常量区字符串入栈
call scanf()
add esp,8   //外平栈 


///////////////////////

0012FF20  61 62 63 64  abcd   //ebp-28h  为char name[40] 数组首地址
0012FF24  65 66 67 68  efgh   //数组赋值从栈顶往栈底赋值
0012FF28  69 6A 6B 6C  ijkl   
0012FF2C  6D 6E 00 CC  mn..
0012FF30  CC CC CC CC  烫烫
0012FF34  CC CC CC CC  烫烫
0012FF38  CC CC CC CC  烫烫
0012FF3C  CC CC CC CC  烫烫
0012FF40  CC CC CC CC  烫烫
0012FF44  CC CC CC CC  烫烫
0012FF48  88 FF 12 00  ....   ebp 栈底

///////////////





push  offset string "also,you first name has %d lette"...
lea ecx,dword ptr [ebp-28h]  //获取数组首地址
push ecx
push  offset string "Hello,%s.%s\n"
call printf(00401100)
add esp,0ch 


xor eax,eax 

pop ebx
pop edi
pop esi 
add esp,68h 
cmp ebp,esp 
call _chkesp
mov esp,ebp 
pop ebp
ret 

