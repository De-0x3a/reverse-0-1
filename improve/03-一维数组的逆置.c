//一位数组的逆置

#include <stdio.h>

//需求： 将第一个元素和最后一个元素不变 其他元素首尾交换位置
//需要一个数组 10个元素 
//需要中间变量 保存临时结果
//需要两个变量 保存第一个元素首地址和最后一个元素地址

int main(void)
{
	int array[] = {12,15,2,36,49,58,69,74,85,104};
	int i = 0;
	int j = sizeof(array)/sizeof(array[0])-1; //指向末尾数组元素
	int tmp;
	while(i<j){
		i++;   //跳过第一个元素
		j--;   //跳过最后一个元素 
		tmp = array[i]; 
		array[i] = array[j];
		array[j] = tmp;

	}
	for(i = 0;i<9;i++)
	{
		printf("value is :%d\n",array[i]);
	}

}



堆栈初始化...
数组初始化  首地址为ebp-28h
00401028   mov         dword ptr [ebp-28h],0Ch
0040102F   mov         dword ptr [ebp-24h],0Fh
00401036   mov         dword ptr [ebp-20h],2
0040103D   mov         dword ptr [ebp-1Ch],24h
00401044   mov         dword ptr [ebp-18h],31h
0040104B   mov         dword ptr [ebp-14h],3Ah
00401052   mov         dword ptr [ebp-10h],45h
00401059   mov         dword ptr [ebp-0Ch],4Ah
00401060   mov         dword ptr [ebp-8],55h
00401067   mov         dword ptr [ebp-4],60h


mov dword ptr [ebp-2ch],0 // i 赋值
mov dowrd ptr [ebp-30h],9 //j 赋值 
//tmp 中间变量堆栈地址为  ebp-34h

//开始while循环
//while 循环特征最直接 先判断条件  然后执行语句体  执行完在jmp 跳回判断

mov eax,dword ptr [ebp-2ch] //i存入eax 
cmp eax,dword ptr [ebp-30h] //比较
jge jmp to for 打印语句 

//进入语句体
//i++不涉及运算
mov eax,dword ptr [ebp-2ch]
add eax,1 
mov dword ptr [ebp-2ch],eax 


//j++
mov ecx,dword ptr [ebp-30h]
sub ecx,1 
mov dword ptr [ebp-30h],ecx 

mov edx,dword ptr [ebp-2ch]
mov eax,dword ptr [ebp-34h]
mov eax,dword ptr [ebp+edx*4-28h] //tmp变量赋值 


//array[i] = array[j] 
mov eax,dword ptr [ebp-28h]
mov edx,dword ptr [ebp-30h]
mov ecx,dword ptr [ebp+edx*4-28h] //ecx存储了array[j]的值
mov dword ptr [ebp+eax*4-28h],ecx  



mov eax,dword ptr [ebp-34h]
mov ecx,dword ptr [ebp-28h]
mov dword ptr [ebp+ecx*4-28h],eax 


jmp to while的条件判断


进入for循环打印数组各元素.. 
堆栈还原...



