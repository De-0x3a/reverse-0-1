#simple example 

```c
#include <stdio.h>

void Bulltest(void); //函数声明

int main(void)
{

printf("1\n");   //printf 1 
Bulltest();     //printf 2
printf("3\n");   //printf 3
}

void Bulltest(void){

	printf("2\n");
}

```



自写ASM 

```assembly
//main 主函数堆栈初始化
push ebp       //老ebp入栈
mov esp,ebp   //提升ebp至esp处 
sub esp,40h   //提升堆栈   
//40h为默认堆栈大小 即68字节 根据编译器及其版本不同存在差异 后续不对其进行深究
push edx   
push esi 
push edi 
lea edi,dword ptr [esp-40h]  //通过lea 指令获取堆栈起始地址 [esp-40h] 
mov eax,0xcccccccc   //eax 用于rep stos 串处理指令的 源地址  4字节0xcccccccc
mov ecx,10h          //ecx 循环计数器 确定循环次数  68字节的堆栈大小/4字节的0xcc = 16次   
rep stos dword ptr [edi]  //rep stos 处理指令 将eax指向的数据 复制到edi指向的地址中  复制次数由eax 决定  每复制一次 sub edi,4 
// 递增递减方向取决于df寄存器
//当df等于0时  递增 
//当df等于1时 递减

/////////////////main 函数堆栈初始化完毕//////////////

//进入第一个printf函数
push "1\n" (00123456)   //将常量区的字符串“1\n”入栈
call printf(004010d0);    //call printf函数地址  函数本质就是一个地址
add esp,4         //默认为_cdecl 外部平衡堆栈 前面push了一个 参数"1"  默认堆栈传参都是4字节 便于寻址

call Bulltest();
	push ebp 
	mov esp,ebp
	sub esp,40h
	push ebx
	push esi 
	push edi 
	lea edi,dword ptr [esp-40h]
	mov ecx,10
	mov eax,0xcccccccc 
	rep stos dword ptr [edi]
	//Bulltest() 堆栈初始化
	push "2\n"
	call printf()   
	add esp,4

	pop edi 
	pop esi 
	pop ebx 
	add esp,40h   //恢复堆栈
	cmp ebp,esp   //比较ebp,esp 是否相等
	call __chkesp  //call 检查函数
	mov esp,ebp   //恢复esp 
	pop ebp      //恢复老ebp
	ret          //返回主调函数 main 


push "3\n"
call printf();
add esp,4  

xor eax,eax 
pop edi 
pop esi 
pop ebx 
add esp,40h 
cmp esp,ebp
call __chkesp
mov esp,ebp 
pop ebp
ret 
