

#include <stdio.h>
int main(void)
{
	int i = 0;  
	int j = 0;  
	int array[3][4] = {0};

	int num = 0;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 4; j++)
		{
			array[i][j] = num++; 
		}
	}

	for(i = 0; i < 3 ; i++)
	{
		for(j = 0; j < 4; j++)
		{
			printf("%d\n",array[i][j]);
		}
	}
	return 0;
}




//首先说明一下for 循环执行流程
example:
	for(i = 0; i < 3; i++){
		printf("Hi!\n");
	}


第一次for循环  执行流程为： 1 2  3  4 
for (1;2;4)
{
	3;
}

首先执行变量初始化1
在执行条件判断 2 
在执行语句体 3
最后条件自增或自减 4 

第二次for循环 执行流程为：2  3  4 
直接从条件判断开始

这样在底层反汇编实现就为：
mov dword ptr [ebp-4],0 //第一次循环的 变量初始化 int i=0
jmp cmp 条件判断    //第一次循环的条件判断
//条件自增模块
mov eax,dword ptr [ebp-8]  //第一次循环的条件自增
add eax,1 
mod dword ptr [ebp-8],eax    

// 条件判断模块 
cmp dword ptr [ebp-4],3 //
jge JMP to retun  //结束for循环
//语句体
push "Hi!\n"
call printf(xxxx)
add esp,4 

jmp 条件自增模块   //这里就体现了第二次for循环的特点 2->3->4   不执行条件1

return;结束





//////
ASM 

push ebp
mov ebp,esp
sub esp,7ch

push ebx 
push esi
push edi 
lea edi,dword ptr [ebp-7ch]
mov ecx,1f
mov eax,0cccccccch
rep stos dword ptr [edi]

//i = ebp - 4 
//j = ebp - 8 
// int array[3][4]  first array address is : [ebp-38h]

mov dword ptr [ebp-4],0
mov dword ptr [ebp-8],0 

mov dwprd ptr [ebp-38h],0  //array[i][j] = {0};
mov ecx,0bh  //11 次循环
xor eax,eax  //eax 置为0 
lea edi,dword ptr [ebp-34h]  //首地址 [ebp-38h]已经置为0  开始处理后续11个数组元素
rep stos dword ptr [edi]  //使用填充缓冲区的方式 填充数组剩余元素为0


//进入for 循环 赋值语句

mov dword ptr [ebp-4],0 
jmp TO cmp i<3 条件判断 
//变量自增
mov eax,dword ptr [ebp-4]
add eax,1
mov dword ptr [ebp-4],eax 

cmp dword ptr [ebp-4],3 
jge JMP to 第二个for循环
//进入语句体 还是一个for 循环 用于二维数组变量赋值

	//内部赋值for 循环   这里要注意 只有内部赋值的这个for循环执行完毕才会退出  退出条件即 j<4 不成立  退出后跳转到外层for循环的条件自增模块 继续循环

	mov dword ptr [ebp-8],0
	jmp to cmp j<4 条件判断
	//内层for 循环条件自增
	mov ecx,dword ptr [ebp-8]
	add ecx,1
	mov dword ptr [ebp-8],ecx 


	cmp dword ptr [ebp-8],4 
	jge JMP TO 中间跳转指令 跳回外层for 循环的条件自增模块

	mov edx,dword ptr [ebp-4] //确定i的地址
	shl  edx,4   //逻辑左移4 
	//当前edx 存储的i值为0 则shl edx  仍然是0 
	//如果已经结束了当次内部for循环 i自增后
	//shl edx,4 ==>0000 0001 ==>0001 0000  ==>16
	//正好是4个4字节的宽度 也就是跳过二维数组的四个元素 

//第一次内部for循环 当i=0 j等于0时  
	0000   ebp-38h 
	0000
	0000
	0000
	0000
	0000
	....
	0000   ebp 
//循环完毕
	0000   //当i等于0时  内部for循环循环完毕 在堆栈里有四个数组元素已被赋值
	0001
	0002
	0003 
	0000  
	0000
	0000
	...
	0000 ebp






/////////////////////////////////
	lea eax,[ebp+edx-38h]  //获取当前数组赋值基址  因为edx在首次循环值为0 
	//在这个eax里存储的就是二维数组的首地址  
	mov ecx,dword ptr [ebp-8] //j变量的值
	mov edx,dword ptr [ebp-3ch]  //num变量值 
	mov dword ptr [eax+ecx*4],edx  //将num的值先赋值给二维数组首地址第一个元素的位置 

	//如果这时的i 已经变成1 则edx经过shl 变为10h     eax获取的基值为跳过4个元素的数组地址 
	//lea eax,[ebp+edx-38h] ==> ebp+16h-38h ==> ebp-20h 
	//mov dword ptr [eax+ecx*4],edx   //以[ebp-20h]作为基址 继续赋值


	0000   //当i等于1时  内部for循环循环完毕 在堆栈里有四个数组元素已被赋值
	0001
	0002
	0003 
	0000   //ebp-20h 作为赋值基址
	0000
	0000
	...
	0000 ebp


	////////////////////////


	mov eax,dword ptr [ebp-3ch] 
	add eax,1 
	mov dword ptr [ebp-3ch],eax   //num++  这里就体现了++num和num++的区别
	//num++先赋值在自增

	jmp  内层for 循环的条件自增模块继续内层循环
	jmp 外层for 循环的条件自增模块 继续进行i 变量条件判断



	//进入for打印语句循环

	mov dword ptr [ebp-4],0
	jmp to cmp 
	//i++ 汇编 和上面一样 不重复说明
	mov eax,dword ptr [ebp-4]
	add eax,1 
	mov dowrd ptr [ebp-4],eax  

	cmp dword ptr [ebp-4],3
	jge  TO retutn 语句结束打印

	//内层循环
	mov dword ptr [ebp-8],0
	jmp to cmp 
	mov eax,dword ptr [ebp-8]
	add eax,1 
	mov dword ptr [ebp-8]

	cmp dword ptr [ebp-8],4 
	jge jmp to 中间跳转指令  跳回外层for的条件自增

	mov eax,dword ptr [ebp-4] //确定i值
	shl eax,4  //左移4位  
	lea ecx, dword ptr [ebp+eax-38h] //确定基址
	mov edx,dword ptr [ebp-8]  //j 
	mov eax,dword ptr [eax+edx*4],edx  //将array[i][j]的值取出来 打印
	push eax
	push "%d\n" 
	call printf()
	add esp,8 

	jmp  内层for 循环的条件自增模块继续内层循环
	jmp 外层for 循环的条件自增模块 继续进行i 变量条件判断

	xor eax,eax 

	pop edi 
	pop esi 
	pop ebx 
	add esp,7ch 
	cmp ebp,esp 
	call _chkesp
	mov esp,ebp 
	pop ebp 
	ret 



