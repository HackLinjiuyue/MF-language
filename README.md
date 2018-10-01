# MF-language
This is a computer language that designed by myself.
Now it has many problems that I have to deal with.
I will show this to you and wish you can help me deal with difficulties or communicate with me to develop it.Thanks~

I will rewrite the code in c++ after I solve all the basic problems.
Of course we can do this together.

# MF语言
这是我自己设计的一门计算机语言，现在还存在着许多的问题等待解决。
我将会将源代码公布出来，希望各位能和我一起来解决问题或是一起做开发，谢谢~

我将会在所有基础问题解决后用c++重写代码。
当然我们可以一起来做这件事情。

# grammar(wait to improve)
'def valuename value'----define a value

'fun functionname parm1 parm2……'--use a function

'let valuename value'----change the value

'out toObj value'----output

## already finished
out(only support toobj:console)

def

let

## need recursion
### if
'if condition;sentence1;sentence2;……;end;'

### loop
'rep conditon;sentence1;sentence2;……;end;'

### end
'end'

### rules
1.all the symbol`\n`must be neglected.

2.`;` is seen as the split symbol of each sentence.

3.each sentence must use ` `(space)as the word split symbol.

4.sign symbol:

`~`:the letters after this are seen as strings.

### calculate
#### number
`+-*/`

`#x`:# means root and x is the power number.

`^x`:power

`$x`:$ means get negative number.

#### logic
`><=!|&`

`>`:greater than

`<`:less than

`=`:equal

`!`:not equal

`|`:or

'&':and

#### object
`.`:get object member value

# 语法（待完善）
`def 变量名 变量值`———————|定义变量

`fun 函数名 参数1 参数2……`——- |执行函数

`let 变量名 变量值`———————|设置变量，出现未定义的变量时报错

`out 目标 值`-————————————|输出，原则遵从值标识

##已完成
out（当前只支持目标console)

def

let

## 需要嵌套：
### 条件语句
`if a<b;语句1;语句2;……;end;`
### 循环语句
`rep a<b;语句1;语句2;……;end;`
### 结束语句
统一使用`end`作为结束语句，用于调整所在栈的位置

### 规则：
1.所有的换行(`'\n'`)全部忽略

2.以`';'`作为句子与句子间的分割符

3.每一句中每空一格`' '`算一个单词

4.变量标识符：

`~`：~后的字符将视作字符串处理

### 计算表达式 规定所有运算为:
算数：`+-*/  ^平n次方 #开n次根 $取负`

逻辑：`><=!&|`

对象：`.`取对象成员
