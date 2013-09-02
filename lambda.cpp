/***************************************************************************
 * 
 * Copyright (c) 2013 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file lambda.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2013/09/02 10:59:09
 * @version 1.0 
 * @brief
 * 理解lambda的关键点在于，lambda其实是一个匿名函数，这种使用方法在多种脚本语言中
 * 均有所体现，例如js、python等等；
 * 本页的程序参考文章：http://www.cnblogs.com/allenlooplee/archive/2012/07/03/2574119.html
 * 使用时请附带原作者信息
 *  
 **/


#include <iostream>
#include <vector>
#include <algorithm>//for generate

using namespace std;

/*
 * the example for using sample lambda
 */
int randNum(vector<int>&numbers)
{
	generate(numbers.begin(), numbers.end(), 
				[]{//使用lambda,[]是Lambda的捕获子句，也是引出Lambda的语法
					return rand() % 100;
				}
			);
	return 0;
}

template<typename T>
void debugVector(const vector<T> &numbers)
{
	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		cout<<*it<<"\t";
	}
	cout<<endl;
}

/*
 * using varibales
 */
int oddCount(const vector<int> &vec)
{
	int nCnt = 0;
	for_each(vec.begin(), vec.end(), 
			[&nCnt](int value){//lambda使用local变量
			/*
			 * C++要求我们在Lambda的捕获子句里显式指定想要捕获的变量
			 * C++还要求我们指定这些变量的传递方式，可以选择的传递：按值传递和按引用传递.
			 * 如果你希望按引用传递捕获当前上下文的所有变量，可以把捕获子句写成[&]；
			 * 如果你希望按值传递捕获当前上下文的所有变量，可以把捕获子句写成[=]。
			 * 如果你希望把按引用传递设为默认的传递方式，同时指定个别变量按值传递，可以把捕获子句写成[&,a,b]；
			 * 同理；如果默认的传递方式是按值传递，个别变量按引用传递，可以把捕获子句写成[=,&a, &b]。
			 * 值得提醒的是，像[&, a, &b]和[=, &a,b]这些写法是无效的,
			 * 因为默认的传递方式均已覆盖b变量，无需单独指定，有效的写法应该是[&,a]和[=, &a]。
			 */
				if (value % 2) {
					++nCnt;
				}
			}
			);
	return nCnt;
}

//pass in the reference
int arithmeticSequence(vector<int> &vec)
{
	int nStep = 2;
	int nBg = -2;
	generate(vec.begin(), vec.end(),
			[&nBg, nStep]{
				return (nBg += nStep);
			}
			);
	cout<<nBg<<endl;
	return 0;
}

int arithmeticSequenceExt(vector<int> &vec)
{
	int nStep = 2;
	int nBg = -2;
	/*
	 * 如果我们加上mutable声明，参数列表就不能省略了，即使里面没有包含任何参数
	 * mutable声明使得我们可以在Lambda的函数体修改按值传递的变量，
	 * 但这些修改对Lambda以外的世界是不可见的，有趣的是，这些修改在Lambda的多次调用之间是共享的。
	 * 换句话说，代码4的generate函数调用了10次Lambda，
	 * 前一次调用时对i变量的修改结果可以在后一次调用时访问得到。
	 * 这听起来就像有个对象，i变量是它的成员字段，而Lambda则是它的成员函数，
	 * 事实上，======Lambda是函数对象（FunctionObject）的语法糖，================
	 * Lambda最终会被转换成Functor类
	 */
	generate(vec.begin(), vec.end(),
			[nBg, nStep]()mutable{
				return (nBg += nStep);
			}
			);
	cout<<nBg<<endl;
	return 0;
}

//===============how to definition a lambda========================
//1st: using auto
//void lambdaAutoDefine()
//{
//	auto f = [](int x, int y){
//		return x+y;
//	};
//	cout<<f(1, 2)<<endl;
//}
//
////2nd: using function template
//void lambdaTemplateDefine()
//{
//	function<int (int , int)> f;
//	cout<< f(1, 2)<<endl;
//}
//
////3rd: using template function declaration
//	template<typename Fn>
//void LambdaTemplateFnDefine(Fn f)
//{
//	cout<<f(1, 2)<<endl;
//}

//==============================捕获变量的值确定时间============================== 
//因为按值传递在声明Lambda的那一刻就已经确定变量的值了，
//无论之后外面怎么修改，里面只能访问到声明时传过来的版本
int testVarible()
{
	int x = 1, y = 2;
	auto f = [x, &y]{return x+y;};
	x = 3;
	y = 4;
	cout<<f()<<endl;
	return 0;
}
//==============================the definition for return value============================== 
/*
有两种情况可以在声明Lambda时省略返回值类型:
1. 函数体只包含一条返回语句
2. Lambda没有返回值
当需要加上返回值的类型时，必须把它放在参数列表后面，并且在返回值类型前面加上"->"符号
*/

int testReturnValue()
{
	auto f = [](int x, int y) -> std::string{
		return std::string("hello word");
	};

	cout<<f(1, 2)<<endl;
	return 0;
}

int main()
{
	vector<int>numbers(10);
	
	randNum(numbers);
	debugVector(numbers);
	
	cout<<oddCount(numbers)<<endl;
	
	arithmeticSequence(numbers);
	debugVector(numbers);
	
	arithmeticSequenceExt(numbers);
	debugVector(numbers);

	testVarible();

	testReturnValue();
	return 0;
}















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
