#include <stdio.h>

int main()
{
	char c;  //使用int 类型 
	c = getchar();

	switch (c) //参数只能是整型变量
	{
	case '1':
		printf("OK\n");
		break;//switch遇到break就中断了
	case '2':
		printf("not OK\n");
		break;
	default://如果上面的条件都不满足，那么执行default
		printf("are u ok?\n");
	}
	return 0;
}


//小于三个参数的switch case 语句 直接通过cmp 将键入值和预留值进行比较 相等就执行对应的语句


堆栈初始化...

c = getchar();  
//执行完毕 保存c 的值到 [ebp-4] 
//但在调用getchar函数时 发现 ebp-8 的位置也被占用 应该是中间变量

mov dl,byte ptr [ebp-4] //dl 8位寄存器保存c的值
mov bytr ptr [ebp-0ch],dl  //将c键入的结果给 一个中间变量 
//这里键入了 2  对应ASCII码为 32h /16进制
cmp byte ptr [ebp-0ch],31h   //直接cmp进行比较
je  jmp to 对应的打印函数 
cmp byte ptr [ebp-0ch],32h 
je jmp to 对应打印函数 
jmp to default  打印语句 


push "ok\n"
call printf(xxx)
add esp,4 
jmp to return 结束语句  对应break

push "not OK\n"
call printf(xxx);
add esp,4 
jmp to return 结束语句  对应break


push "are U ok?"
call printf(xxx)
add esp,4 

xor eax,eax 

堆栈还原...


