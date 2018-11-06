# MF-language
This is a computer language(compile-explain type) that designed by myself.

I design it to learn how to compile.

communication:qq group:916289058

if you interested in it,please join in with your github name or tell me how you know this.

It runs successfully on the MacOS(OS X).

please don't use it for any other purpose except study and communication.

# MF语言
这是我自己用来学习编译程序时设计的一门编译解释型计算机语言

请勿用于除交流学习外的其它用途

联系方式：
qq群：916289058

请在加群时附带你的github名称或是简略描述你的得知渠道。

目前在苹果系统上能够成功运行。

# grammar(wait to improve)

### define
`def valuename value`

special value
`false`
`true`

### change value
`let valuename value`

### output
`out console value`

### if(\n means key:enter)
`if condition\nsentence1\nsentence2\n……\nendif`

### loop
`rep conditon\nsentence1\nsentence2\n……\nendrep\n`

### end
`endif`
`endrep`

# sign symbol:
`"`:the letters after this are seen as strings.

### calculate
#### number
`+-*/`

#### logic
`><=!|&`

`>`:greater than

`<`:less than

`=`:equal

`!`:not equal

`|`:or

`&`:and

#### string
`~`:connect strings together

# 语法
`def 变量名 值`———————|定义变量

`let 变量名 值`———————|设置变量，出现未定义的变量时报错

`out console 值`-————————————|输出语句

### 定义变量时的特殊值
`true`
`false`

### 条件语句(\n表示回车)
`if a<b\n语句1\n语句2\n……\nendif\n`

### 循环语句
`rep a<b\n语句1\n语句2\n……\nendrep\n`

### 结束语句
`endif`

`endrep`

4.变量标识符：
`"`："后的字符将视作字符串处理

### 计算表达式 规定所有运算为:
算数：`+-*/`

字符串连接：`~`

逻辑：`><=!&|`
