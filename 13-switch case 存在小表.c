当存在case 值不连续且常量跨度较大时 会生成大表及小表

int main()
{
	char c;  //使用int 类型 
	c = getchar();

	switch (c) //参数只能是整型变量
	{
	 case 101:
        printf("%d\n",1);
        break;
       case 107:
        printf("%d\n",2);
        break;
        case 108:
        printf("%d\n",2);
        break;
        case 115:
        printf("%d\n",3);
        break;
        default:
        printf("%d\n",4);
        break;
	}
	return 0;
}


堆栈初始化 ...
ebp-4 存储键入值

movsx edx,byte ptr [ebp-4]
mov dword ptr [ebp-0ch],edx  //保存到中间变量
mov eax,dword ptr [ebp-0ch] 
sub eax,65h    //获取键入值然后键入 case 常量里最小的数 这里是101
mov dword ptr [ebp-0ch],eax
cmp dword ptr [ebp-0ch],0Eh  //和差值做比较  115-101=14 /E 
ja JMP to default 语句 
mov edx,dword ptr [ebp-0ch] 
xor ecx,ecx //清空ecx寄存器 用于计算
mov cl,byte ptr  (00401117)[edx]
jmp dword ptr [ecx*4 + 401103h] //根据小表取出来的值进行跳转
///////
	VC 在这里进行了反汇编语句优化 
	mov cl,byte ptr  (00401117)[edx]
	实际语句应该为 mov cl,byte ptr [00401117 + edx] 
	00401117 里存储了一个小表 只有当常量跨度较大,且常量最大值小于FF 才可能出现。


	00401117  00 04 04 04  .... 
	0040111B  04 04 01 02  ....
	0040111F  04 04 04 04  ....
	00401123  04 04 03 CC  ....
          04 肯定不存在的常量数  也就是最终拿04 出去 会计算得到default 的地址

如果键入值为102 不存在对应的case常量，102-101=1 
1 < 14  
00401117+1 ==》 00401118 对应的值为04
将04放入cl寄存器
jump dword ptr [4*4+401103h]  ==》 00401113 然后取值==》004010E1

401103h 为大表地址 
00401103  9D 10 40 00  ..@.
00401107  AE 10 40 00  ..@.
0040110B  BF 10 40 00  ..@.
0040110F  D0 10 40 00  ..@.
00401113  E1 10 40 00  ..@.   default 语句地址所在
00401117  00 04 04 04  ....   
0040111B  04 04 01 02  ....
0040111F  04 04 04 04  ....
00401123  04 04 03 CC 


所以如果键入值不存在对应case 语句 则在小表中均为一个值 
将这个值加上大表地址 取出来一个指向default的地址 



如果键入的值为101  101-101=0
0 < 14 
将0 放入cl寄存器里
jmp dword ptr [0*4 + 401103h] ==> 401103h 取值 ==》 0040109D

跳转到对应地址..
13:        case 101:
14:           printf("%d\n",1);
0040109D   push        1
0040109F   push        offset string "are u ok?\n" (0042301c)
004010A4   call        printf (00401150)
004010A9   add         esp,8
15:           break;
004010AC   jmp         $L536+20h (004010f0)
16:          case 107:
17:           printf("%d\n",2);
004010AE   push        2
004010B0   push        offset string "are u ok?\n" (0042301c)
004010B5   call        printf (00401150)
004010BA   add         esp,8
18:           break;
004010BD   jmp         $L536+20h (004010f0)
19:           case 108:
20:           printf("%d\n",2);
004010BF   push        2
004010C1   push        offset string "are u ok?\n" (0042301c)
004010C6   call        printf (00401150)
004010CB   add         esp,8
21:           break;
004010CE   jmp         $L536+20h (004010f0)
22:           case 115:
23:           printf("%d\n",3);
004010D0   push        3
004010D2   push        offset string "are u ok?\n" (0042301c)
004010D7   call        printf (00401150)
004010DC   add         esp,8
24:           break;
004010DF   jmp         $L536+20h (004010f0)
25:           default:
26:           printf("%d\n",4);
004010E1   push        4
004010E3   push        offset string "are u ok?\n" (0042301c)
004010E8   call        printf (00401150)
004010ED   add         esp,8
27:           break;
28:       }
29:       return 0;
004010F0   xor         eax,eax
30:   }


恢复堆栈...



第一种情况：
1.当case 的常量值大于三参数且连续时 
一个switch语句里 所有case 常量连续，按照输入数减入 case 常量中最大值的方法 确定 操作数1 
最大值减入最小值 确定 判断条件
操作数1和判断条件比较 决定是否跳到default 
在根据大表进行语句跳转。

2.当case 的常量值大于三参数 但不连续时 
一个switch语句里 所有case 常量不连续但跨度较小，依然按照输入数减入 case 常量中最大值的方法 确定 操作数1 
最大值减入最小值 确定判断条件
操作数1和判断条件比较 决定是否跳到default 
在根据大表进行语句跳转。但这里的大表会空缺位置会被填充为default 地址。

3.当case 常量值大于三参数 不连续 且跨度较大时
依然按照输入数减入 case 常量中最大值的方法 确定 操作数1 
最大值减入最小值 确定判断条件
操作数1和判断条件比较 决定是否跳到default 
  mov cl,byte ptr  (00401117)[edx]   实际语句应该为 mov cl,byte ptr [00401117 + edx] 
  jmp dword ptr [ecx*4 + 401103h] //根据小表取出来的值进行跳转
会生成小表和大表,小表内不存在的case常量值会被填充为04 一个不存在的常量值
在通过 [ecx*4 + 401103h] 跳转到对应语句。


switch case 语句的反汇编情况是最多的一种，遇到后在深究吧..

