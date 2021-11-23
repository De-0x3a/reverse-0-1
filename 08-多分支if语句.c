
int main(void)
{

	unsigned int a;
	scanf("%u",&a); //输入正数

	if(a>10){

		printf("个位\n");
	}else if(a < 100){
		printf("十位数\n");
	}else if(a<1000)
	{

		printf("百位数\n");
	}else{
		printf("很大的数\n");
	}

	return 0;
}

////////

多分支if语句框架：
if(a>b)   第一个判断条件     //生成与之相反的汇编指令   jbe  满足就跳到第二个判断条件
 语句体1                    //不满足就执行语句体1 
else if(a<c) 第二个判断条件  //生成与之相反的汇编指令   jae  满足就跳到第三个判断条件
	语句体2 					//不满足就执行语句体2
else if(a<d) 第三个判断条件  //生成与之相反的汇编指令   jae  满足就跳到最后一个else 语句体
	语句体3 					//不满足就执行语句体3
else{
	语句体4
}

//if多分支特征：存在多个条件判断，且每次执行完语句体必定存在一个jmp 跳转，几个语句体都跳转到同一地址。
////////






push ebp 
mov ebp,esp 
sub esp,44h 
push ebx 
push esi 
push edi 
lea edi,dword ptr [esp-44h]
mov eax,0CCCCCCCCh
mov ecx,11h 
rep stos dword ptr [edi]

mov eax,dword ptr [ebp-4]
push eax 
push "%u"
call scanf(); 
add esp,8   //获取键入的数值

mov eax, dword ptr [ebp-4]
cmp eax,0A     //进入第一个判断条件 和 10 比较  
jbe  JUMP TO 第二个判断条件//如果左操作数 小于等于右操作数 则JUMP to 第二个判断条件
//不满足 左操作数大于右操作数 执行语句体1
语句体1：
push "个位"
call printf("%s\n", );
add esp,4 

jmp END

第二个判断语句:
cmp dword ptr [ebp-4],64h  //输入数和100比较
jae  满足判断条件 JUMP TO 第三个判断语句 

语句体2：
push "十位数"
call printf("%s\n", );
add esp,4 

jmp END 

cmp dword ptr [ebp-4],1000
jae   满足 判断条件大于等于 则跳转到最后一个else 语句体

push "百位数"
call printf("%s\n", );
add esp,4 

jmp END 


push "很大的数据"
call printf("%s\n", );
add esp,4 


END： 结束地址
xor eax,eax 
pop edi
pop esi 
pop ebx 
add esp,44h 
cmp ebp,esp 
call __chkesp
mov esp,ebp 
pop ebp 
ret 
