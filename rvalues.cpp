/***************************************************************************
 * 
 * Copyright (c) 2012 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file rvalues.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2012/07/04 14:13:30
 * @version 1.0 
 * @brief 
 *  
 **/

#include <iostream>
#include <vector>
using namespace std;

bool is_r_value(int &&)
{
	return true;
}

bool is_r_value(const int &)
{
	return false;
}

void test(int &&i)
{
	cout<<is_r_value(i)<<endl; // false
	cout<<is_r_value(std::move(i))<<endl; // true
}

int main()
{
	int b = 1;
	int &a = b;
	int &&ra = 1;
	cout<<a<<b<<ra<<endl;
	test(1);
	return 0;
}








/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
