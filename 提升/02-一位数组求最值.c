 #include <stdio.h>

//需要一个数组 里面有一些元素
//需要一个中间变量保存最大值
 //需要一个循环 遍历数组内所有值 
 //需要一个if 判断中间变量和数组内各元素哪个大

 int main(void)
 {
 	int array[10] = {1,44,22,55,432,6,7,44,767,4};
 	int max = array[0]; //中间变量 和 数组元素值比较
 	

 	int i= 1; //for 循环起始变量

 	for (i = 1; i < sizeof(array)/sizeof(array[0]); i++)
 	{
 		//10个元素的数组 只需要循环9次就能遍历完毕 
 		if(max<array[i]){
 			max = array[i];
 		}
 	}

 	printf("max value is :%d\n",max);
 	return 0;
 }




堆栈初始化...

//数组赋值..
//因为给定了初始值 所以直接赋值 从栈顶--》栈底 
00401028   mov         dword ptr [ebp-28h],1
0040102F   mov         dword ptr [ebp-24h],2Ch   
00401036   mov         dword ptr [ebp-20h],16h
0040103D   mov         dword ptr [ebp-1Ch],37h
00401044   mov         dword ptr [ebp-18h],1B0h
0040104B   mov         dword ptr [ebp-14h],6
00401052   mov         dword ptr [ebp-10h],7
00401059   mov         dword ptr [ebp-0Ch],2Ch
00401060   mov         dword ptr [ebp-8],2FFh
00401067   mov         dword ptr [ebp-4],4

mov eax,dword ptr [ebp-28h] //获取数组首地址 array[0]
mov dword ptr [ebp-2ch],eax  //赋值给max 

mov dword ptr [ebp-30h],1  //for 变量初始化i为1
//因为array[0] 已经被赋值给max了 所以直接从array[1]进行比较
jmp  to  cmp 比较
//i++
mov eax,dword ptr [ebp-30h]
add eax,1 
mov dword ptr [ebp-30h],eax 

cmp dword ptr [ebp-30h],0ah  //直接在编译完成后就确定了 sizeof(array)/sizeof(array[0])的值 
jge jmp to printf 语句 

执行if语句 

mov eax,dword ptr [ebp-30h] //获取i当前的值 
mov edx,dword ptr [ebp-2ch] //max 当前值
cmp edx,dword ptr [ebp+eax*4-28h] //一维数组寻址 
jge 中间跳转指令 用于跳出if循环 返回for

//赋值  
mov ecx,dword ptr [ebp-30h] //i值获取 
mov edx,dword ptr [ebp+ecx*4-28h] 
mov dword ptr [ebp-2ch],edx   //max = array[i] 


jmp jge的中间跳转指令 jmp to for循环的 条件自增模块

mov eax,dword ptr [ebp-2ch] 
push eax  //max 值入栈
push offset string "max..."
call printf(xxx)
add esp,8


xor eax,eax 

...
堆栈还原..




