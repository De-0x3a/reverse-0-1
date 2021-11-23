

int main(void)
{
	int a = 1;
	int b = 2; 
	if(a>b)
	{
		printf("A > B\n");

	}else{
		printf("B > a \n");
	}

}



//////

if(a>b)   //生成jle 汇编指令 如果该指令成立则跳转到else分支语句，执行语句体2
	语句体1  //jle不成立执行语句体1  执行完毕通过jmp 结束
else{
	语句体2
}
/////////



push ebp 
mov ebp,esp 
sub esp,48h
push ebx 
push esi 
push edi 
lea edi,dword ptr [esp-48h]
mov eax,0CCCCCCCCh
mov ecx,12h 
rep stos dword ptr [edi]

mov dword ptr [ebp-4],1 
mov dword ptr [ebp-8],2 

mov eax,dword ptr [ebp-4]
cmp eax,dword ptr [ebp-8]

jle JUMP toelse 条件 执行语句体2     
语句体1：
push "A > b" 
call printf("%s\n", );
add esp,4 

jump  to return 结束位置 语句体1 执行完毕直接 jump 结束    

语句体2 开始:
push "B >Ａ　"
call printf();
add esp,4 

xor eax,eax 

pop edi
pop edi 
pop ebx 
add esp,48h 
cmp ebp,esp
call _chkesp
mov esp,ebp 
pop ebp 
ret 

