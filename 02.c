编写一个程序 打印你的年龄 并显示天数


int main(void)
{

	int year,days;
	year = 20;
	days = year * 365; 
	printf("You age is:%d,and you days is :%d",year,days);
	return 0;
}



//////////////////////////////////
push ebp 
mov ebp,esp 
sub esp,48h   //和默认的40h堆栈空间相比  多了8字节 说明可能存在2个局部变量
push ebx 
push esi 
push edi 
lea edi,dword ptr [esp-48h]
mov eax,0CCCCCCCCh
mov ecx,12           //18次
rep stos dword ptr [edi]
//堆栈初始化  

  
mov dword ptr [ebp-4],14h   //给第一个局部变量赋值  14h为十进制的20    [ebp-4]为第一个局部变量堆栈地址
mov eax,dword ptr [ebp-4]   //通过eax 获取第一个局部变量 
imul        eax,eax,16Dh     //imul 乘法指令  16D为十进制的365 
mov dword ptr [ebp-8],eax   //将相乘后的结果保存到 [ebp-8]  也就是第二个局部变量 


mov ecx,dword ptr [ebp-8]    
push ecx                 //局部变量2入栈   默认从右往左入栈
mov eax,dword ptr [ebp-4]
push eax                 //局部变量1入栈
push "you age is %d...."   //字符串入栈
call printf(00401260); //call printf函数地址
add esp,0ch         //外部调用者main平衡堆栈 

xor eax,eax   //return 0;   默认返回值保存在eax寄存器中 通过xor eax 将值置为0   效率比mov eax,0 高

pop edi 
pop esi 
pop ebx 
add esp,48h 
cmp esp,ebp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 
