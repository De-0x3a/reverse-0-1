
int main(int argc, char const *argv[])
{
	
	int i; //ebp-4
	int sum = 0; 
	for(i=0;i<=100;i++){

		sum = sum+i; 
	}
	printf("sum = %d\n",sum);
	return 0;
}



堆栈初始化

mov dword ptr [ebp-8],0   //sum 
mov dword ptr [ebp-4],0   //i 

jmp 条件判断语句 i<=100
//变量自增位置
mov　eax,dword ptr [ebp-4]
add eax,1 
mov dword ptr [ebp-4],eax 

//条件判断
cmp dword ptr [ebp-4],64h 
jg //JUMP 到printf 打印sum
//语句体 
//sum = sum +i 
mov eax,dword ptr [ebp-8]
add eax,dword ptr [ebp-4]
mov dword ptr [ebp-8],eax 

jmp 变量自增位置

mov eax,dword ptr [ebp-8]
push eax 
push offset string "sum = %d\n"
call printf(xxxx)
add esp,8


xor eax,eax 


堆栈还原...

for循环的执行在二维数组里说过

for(1,2,4)
{
	3
}


1=>2=>3=>4 
第二次循环 
2=>3 =>4

