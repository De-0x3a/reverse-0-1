
while嵌套if循环

#include <stdio.h>

int main()
{
	int i = 0;
	while (1)
	{
		i++;
		printf("i = %d\n", i);

		if (i == 10)
		{
			break; //跳出while循环
		}
	}

	return 0;
}

/////////////////////
rep stos dword ptr [edi]

mov dword ptr [ebp-4],0
//while(1) ？   
//  mov eax,1
//  test eax,eax   1和1 进行与运算  永远为1
// 
je  //跳转到return pop
	mov eax,dword ptr [ebp-4]
	add eax,1 
	mov dword ptr [ebp-4],eax


	mov eax,dword ptr [ebp-4]
	push eax 
	push "i = %d"
	call printf("%s\n");
	add esp,8 
         mov eax,dword ptr [ebp-4]
         cmp eax,0A 
         jne JMP to 中间跳转指令  跳到jmp2 
         jmp return 结束语句
         jmp2 JMP to 条件判断进行变量自增

xor eax,eax  
堆栈还原
