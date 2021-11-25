

//switch case 生成大表情况
//存在连续case值的情况会生成大表

[ebp-4] //getchar函数获取键入值 保存在ebp-4 
movsx edx,byte ptr [ebp-4] //将键入值放入edx寄存器 
mov dword ptr [ebp-0ch],edx //放入中间变量 
mov eax,dword ptr [ebp-0ch] 
sub eax,32h // 将键入的值减去这些条件里最小的那个数
这里键入2 需要减去2 
mov dword ptr [ebp-0ch],eax  //处理后放回中间变量
cmp dword ptr [ebp-0ch],4  // case 条件最大值-最小值获取
//6 - 2 = 4
ja  JMP to default 打印条件
//这里就是当键入的值比我们这些条件最大最小的差值还大时 直接就是default
mov ecx,dword ptr [ebp-0ch]
jmp dword ptr [ecx*4+ 0040DED0]  

0040DED0  65 DE 40 00  e轅.  //打印OK
0040DED4  74 DE 40 00  t轅.  //打印3 
0040DED8  83 DE 40 00  冝@.  //打印4 
0040DEDC  92 DE 40 00  掁@.  //打印5 
0040DEE0  A1 DE 40 00  ∞@.   //打印6 

0040DED0 保存了一张表 通过这张表可以方便的获取每个条件的跳转地址

根据表中的地址决定跳转的case 语句块

14:           printf("OK\n");
0040DE65   push        offset string "OK\n" (00423034)
0040DE6A   call        printf (00401100)
0040DE6F   add         esp,4
15:           break;//switch遇到break就中断了
0040DE72   jmp         $L540+1Ch (0040debd)
16:       case '3':
17:           printf("3");
0040DE74   push        offset string "3" (00423030)
0040DE79   call        printf (00401100)
0040DE7E   add         esp,4
18:           break;
0040DE81   jmp         $L540+1Ch (0040debd)
19:           case '4':
20:           printf("4");
0040DE83   push        offset string "4" (00423028)
0040DE88   call        printf (00401100)
0040DE8D   add         esp,4
21:           break;
0040DE90   jmp         $L540+1Ch (0040debd)
22:               case '5':
23:           printf("5");
0040DE92   push        offset string "5" (00423038)
0040DE97   call        printf (00401100)
0040DE9C   add         esp,4
24:           break;
0040DE9F   jmp         $L540+1Ch (0040debd)
25:               case '6':
26:           printf("6");
0040DEA1   push        offset string "6" (0042302c)
0040DEA6   call        printf (00401100)
0040DEAB   add         esp,4
27:           break;
0040DEAE   jmp         $L540+1Ch (0040debd)

28:       default:
29:           printf("are u ok?\n");
0040DEB0   push        offset string "are u ok?\n" (0042301c)
0040DEB5   call        printf (00401100)
0040DEBA   add         esp,4
30:       


xor eax，eax 

堆栈还原 .....
