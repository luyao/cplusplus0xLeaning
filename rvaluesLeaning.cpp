/***************************************************************************
 * 
 * Copyright (c) 2013 izptec.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/



/**
 * @file rvaluesLeaning.cpp
 * @author YAO LU(luyao@izptec.com)
 * @date 2013/09/03 15:44:50
 * @version 1.0 
 * @brief 
 *  
 **/

#include <iostream>
#include <utility>
using namespace std;

int g_nTest;

int& getRef()
{
	return g_nTest;
}

//getLocal() = 4; //reference to local variable ‘x’ returned
//this function cant be compailed
/*
   int& getLocal()
   {
   int x = 4;
   return x;
   }
   */

//this function is ok
int& getStatic()
{
	static int x = 4;
	return x;
}

//this function works, but no use at all
int& getPointer()
{
	int *x = new int(1);
	return *x;
}

string getName()
{
	return "hitrose";
}

class MetaData
{
public:
	MetaData (int size, const std::string& name): _name( name ), _size( size ){}

	// copy constructor
	MetaData (const MetaData& other): _name( other._name ), _size( other._size ){}

	// move constructor
	MetaData (MetaData&& other): _name( std::move(other._name) ), _size( other._size ){}

	std::string getName ()const { return _name; }
	int getSize ()const { return _size; }
private:
	std::string _name;
	int _size;
};

class ArrayWrapper
{
public:
	// default constructor produces a moderately sized array
	ArrayWrapper (): _p_vals( new int[ 64 ] ), _metadata( 64, "ArrayWrapper" ){}

	ArrayWrapper (int n): _p_vals( new int[ n ] ), _metadata( n, "ArrayWrapper" ){}

	// move constructor
	ArrayWrapper(ArrayWrapper&& other): 
		_p_vals(other._p_vals), 
		_metadata( std::move(other._metadata) ){//to avoid _metadata is modified, we should use move
		other._p_vals = NULL;
	}

	//move copy assignment operator
	ArrayWrapper& operator=(ArrayWrapper &&other)
	{
		_p_vals = other._p_vals;
	}

	//copy	constructor
	ArrayWrapper(const ArrayWrapper &other):
		_p_vals(new int[other._metadata.getSize()]), _metadata(other._metadata){
		for(int i=0;i<_metadata.getSize();++i){
			_p_vals[i] = other._p_vals[i];
		}
	}

	~ArrayWrapper(){
		delete []_p_vals;
	}
private:
	int	*_p_vals;
	MetaData	_metadata;
};
int main()
{
	int a = 0;
	a = 1;           //a是左值
	cout<<a<<endl;
	//1 = a;        //error: lvalue required as left operand of assignment
	getRef() = 2;   //
	cout<<getRef()<<endl;

	cout<<getName()<<endl;
	//string &rString = getName();//error invalid initialization of non-const reference of type ‘std::string& {aka std::basic_string<char>&}’ from an rvalue of type
	const string &rString = getName(); //ok
	cout<<rString<<endl;

	const string &&crrString = getName();//ok
	string &&rrString = getName();//ok
	cout<<rrString<<endl<<crrString<<endl;
	return 0;
}



















/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
