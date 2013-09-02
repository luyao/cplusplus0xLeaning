/***************************************************************************
 * 
 * Copyright (c) 2012 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
  
 
 
/**
 * @file autoTest.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2012/07/04 11:48:00
 * @version 1.0 
 * @brief 
 *  
 **/

#include <vector>
#include <iostream>
#include <string>
using namespace std;


int main()
{
	vector<int>vec_int = {1,2,3,4,5,6};
	for (auto &num : vec_int) {
		cout<<num<<endl;
	}
	
	string cmd(R"abc("/(.*)/")abc");
	cout<<cmd<<endl;
	return 0;
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
