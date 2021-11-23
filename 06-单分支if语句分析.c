

int main(void)
{
	int a = 1;
	int b = 2; 
	if(a>b)
	{
		printf("A > B");

	}

}


/////////
if() 单分支语句逆向特点
直接就是左右操作数进行cmp比较
如果是 左操作数 > 右操作数 
有符号环境下 使用jle   jump if less equal  如果满足小于等于就跳转    
无符号环境下 使用jbe   jump if below equal 如果满足小于等于就跳转

如果是 左操作数 < 右操作数 有符号环境下
有符号环境下 使用jge   jump if greater equal 如果满足大于等于就跳转 
无符号环境下 使用jae   jump if above  equal 如果满足大于等于就跳转   


if(a>b)  只要是用大于号 汇编代码与之含义相反  jle 或者 jbe 
	当a>b 时进入语句体执行 printf语句  否则退出判断
if(a<b)  只要是用小于号 汇编代码与之含义相反  jge 或者 jae 
	当a<b 时进入语句体执行 printf语句  否则退出判断


/////////







push ebp 
mov ebp,esp 
sub esp,48h 
push ebx
push esi
push edi 
lea edi,dword ptr [ebp-48h]
mov eax,12h
mov ecx,0CCCCCCCCh
rep stos dword ptr [edi] 

mov dword ptr [ebp-4],1 
mov dword ptr [ebp-8],2 

mov eax,dword ptr [ebp-4]
cmp eax,dword ptr [ebp-8]  //a和b 进行比较 使用cmp指令
jle JUMP TO return  //如果jle直接jmp到return  生成的正好是和正向代码相反的汇编语句
//不满足jle就继续执行  
push offset string "A > B"
call printf(004010)
add esp,4 

xor eax,eax 

pop edi
pop esi
pop ebx 
add esp,48h 
cmp ebp,esp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 



/////

功能代码还原：
mov dword ptr [ebp-4],1     //int a1 = 1  第一个局部变量   
mov dword ptr [ebp-8],2     //int a2 = 2  第二个局部变量 

mov eax,dword ptr [ebp-4]   //将第一个局部变量放入eax 寄存器
cmp eax,dword ptr [ebp-8]   //使用cmp 将eax 和第二个局部变量比较
jle JUMP TO return         //jle  则正向代码为 if(a1 > a2)

push offset string "A > B"  //执行printf语句  当a1>a2时执行该语句
call printf(004010)
add esp,4 

xor eax,eax               //当a1<= a2时 直接跳转到return

////




