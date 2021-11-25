
int main(int argc, char const *argv[])
{
	int a = 1; 
	do{
		a++;
		printf("a = %d\n", a);

	}while(a<10)


	return 0;
}


ASM 
堆栈初始化...

mov dword ptr [ebp-4],1 
//a++  直接进入循环体 
mov eax,dword ptr [ebp-4]
add eax,1 
mov dword ptr [ebp-4],eax 
mov eax,dword ptr [ebp-4]
push eax 
push "a = %d"
call printf("%s\n", );
add esp,8


cmp dword ptr [ebp-4],14h 
jl    跳转回 循环体  //注意这里生成的是 jl 和正向代码 a<10符合

xor eax,eax 
堆栈还原...


所以  do while 循环是至少执行一次循环体的语句 才能进入条件判断

