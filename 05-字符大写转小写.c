int main(void)
{
	char A = 'A';
	char b = 'B';

	printf("A = %d",A);
	printf("B = %d",B);

	printf("小写A=: %d",A + 32);
	printf("小写A=: %d",B + 32);

	return 0;

}



////////////////////

A ASCII值为 41h  十进制65
B ASCII值为 42h  十进制66 

a ASCII值为 61h  十进制97 
b ASCII值为 62h  十进制98

a = 'A' + 32 ==>65+32 = 97 
b = 'B' + 32 ==>66+32 = 98
///////////////////



push ebp
mov ebp,esp
sub ebp,48h
push ebx
push esi
push edi 
lea edi, dword ptr [ebp-48h]
mov eax,12h
mov ecx,0cccccccch
rep stos dword ptr [edi]

mov byte ptr [ebp-4],41h   //char宽度为byte
mov byte ptr [ebp-8],42h   
//
堆栈里默认4字节对齐 虽然只有1字节数据 但实际还是按4字节寻址
0012FF34  CC CC CC CC  烫烫
0012FF38  CC CC CC CC  烫烫
0012FF3C  CC CC CC CC  烫烫
0012FF40  42 CC CC CC  B烫.  ebp-8
0012FF44  41 CC CC CC  A烫.  ebp-4
0012FF48  88 FF 12 00  ....  esp
//

//movsx 带符号扩展 最高位需要补符号位  适用于signed类型 
//movzx  不带符号扩展 扩展时高位直接补0  适用于unsigned 类型
movsx eax,byte ptr [ebp-4] //movsx 带符号扩展为4字节  
push eax 
push offset string "A = %d\n" (0042201c)
call printf(00401140)
add esp,8 

movsx ecx,byte ptr [ebp-8]
push ecx
push offset string "B = %d"
call printf(00401140)
add esp,8


movsx edx,byte ptr [ebp-4]
add edx,20h     //A+32  得到a的ASCII值 
push edx
push offset string "Hello,%s.%s\n"
call printf(00401140)
add esp,8


movsx eax,bytr ptr [ebp-8]
add eax,20h			//B+32 得到b的ASCII值
push eax
push offset string "Hello,%s.%s\n"
call printf(00401140)
add esp,8

xor eax,eax    //return 0 

pop edi
pop esi
pop ebx 
add esp,48h
cmp ebp,esp 
call _chkesp
mov esp,ebp 
pop ebp 
ret 
//还原堆栈



