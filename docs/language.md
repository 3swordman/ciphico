#### phico0.x是在phico发布1.0之前做的准备版本。
##### 这个phico0.1实现的功能主要有：输出和输入整数小数，字符串，变量定义
1. 输出：
输出语句格式：```out(value,value2,...)```  。
如果参数是表达式或整数小数字符串，会直接运算后输出。
如果参数是变量，那么变量一定要提前声明，默认会按变量类型输出。
如果变量没有定义，也可以用```out(a=1)```输出```1```。
2. 变量：
变量可以不声明直接使用。
若需赋值，请用```xx=xx```来进行赋值。
3. 输入：
输入语句格式：```xx=get()```，
如果变量已定义，会根据类型进行储存。
如果变量没有定义或者想改变输出的类型，请用强制转化语句。
4. 强制转化语句
仅仅一次转化：```type(xxx)``` ，
支持转化的类型有：```int str float``` ，xxx为变量名。
可以代入表达式内。如```out(float(a))```，
若要更改变量的类型，必须要用另一个变量，如：```a = float(b)```。
5. 表达式
phico0.1表达式分为两种，一种为字符串表达式，一种为数学表达式。

字符串表达式:
1. ```a+b```：将两个字符串拼接 
2. ```a[1`3]```：获取字符串的第一位至第三位
3. ```del(a[3])```：a去除第3位

数学表达式：包括加减乘除取模
特别说明：phico从1开始计数