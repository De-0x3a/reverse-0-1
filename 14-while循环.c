
#include <stdio.h>

int main(int argc, char const *argv[])
{
	
	int a = 20;
	while(a>10)
	{
		scanf("%d",&a);
		printf("a = %d\n", a);
	}

	return 0;
}


基本流程：
  首先cmp 进行条件判断
  然后符合条件跳走
  不符合执行语句体
  执行完jmp到条件判断
  
 while 是流程最简单的循环语句。。




ASM 

push ebp 
mov ebp,esp 
sub esp,44h 
push ebx 
push esi 
push edi 
lea edi,dword ptr [ebp-44h]
mov eax,0CCCCCCCCh
mov ecx,11h 
rep stos dword ptr [edi]


mov dword ptr [ebp-4],14h 
mov eax,dword ptr [ebp-4]
	//while(a>10)
cmp eax,0ah 
jle JUMP END  如果小于等于10 就跳出循环 return 0 

lea eax,dword ptr [ebp-4]
push eax 
push "%d"
call scanf
add esp,8 

mov ecx,dword ptr [ebp-4]
push ecx 
push "a = %d"
call printf("\n");
add esp,8 

jmp  cmp 继续判断条件

xor eax,eax 
pop edi 
pop esi 
pop ebx 
add esp,44h 
cmp ebp,esp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 




