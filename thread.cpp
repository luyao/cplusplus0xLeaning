/***************************************************************************
 * 
 * Copyright (c) 2012 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file thread.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2012/07/14 20:31:25
 * @version 1.0 
 * @brief 
 *  
 **/

#include <thread>
#include <iostream>

using namespace std;

void hello()
{
	cout<<"Hello world"<<endl;
}

int main()
{
	std::thread t1(hello);
	t1.join();
	return 0;
}

















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
