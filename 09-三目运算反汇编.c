
int main()
{
	int a = 1;
	int b = 2;
	int c;
	c = ( a > b ? a : b );
	printf("c = %d\n", c);

	return 0;
}




push  ebp 
mov ebp,esp
sub esp,48h 
push  ebx 
push esi
push edi 
lea edi dword ptr [edi]
mov eax,0CCCCCCCCh 
mov ecx,12 
rep stos dword ptr [edi]

mov dword ptr [ebp-4],1 
mov dowrd ptr [ebp-8],2 
//堆栈预留  int c  ebp-0c  第三个局部变量

mov eax,dword ptr [ebp-4]
cmp eax,dword ptr [ebp-8] 
jle  JUMP to 条件判断2 
//中间变量赋值：
mov ecx,dword ptr [ebp-4]
mov dword ptr [ebp-0c],ecx 
jmp return END 结束 


条件判断2： 当a<=b时 
mov edx,dword ptr [ebp-8]
mov dword ptr [ebp-10h],edx 


//中间变量赋值
mov eax,dword ptr [ebp-10]
mov dword ptr [ebp-0c],eax 

//打印语句
mov eax,dword ptr [ebp-0c]
push eax 
push "c = %d\n"
call printf(xxxx)
add esp,8

xor eax,eax 

pop edi 
pop edi 
pop ebx 
add esp,48h 
cmp ebp,esp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 

