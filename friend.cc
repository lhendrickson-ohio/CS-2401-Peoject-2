/***************************************

	Liam Hendrickson
	CS 2401 - John Dolan
	Project 2
	Ohio University

**************************************/


#include "friend.h"
#include "date.h"
#include <iostream>
#include <string>

using namespace std;

Friend::Friend()
{
	Date x;

	bday = x;
	name = "";
}

bool Friend::operator ==(const Friend& other)const
{
	if((bday == other.get_bday()) && (name == other.get_name()))
		return true;
}

bool Friend::operator !=(const Friend& other)const
{
        if((bday != other.get_bday()) || (name != other.get_name()))
                return true;
}

void Friend::output(std::ostream& outs)const
{
	outs<<name<<endl;
	outs<<bday<<endl;
}

void Friend::input(std::istream& ins)
{
	while(ins.peek() == '\n' || ins.peek() == '\r')
		ins.ignore();

	getline(ins,name);

	if(ins.eof())
		return;

	while(ins.peek() == '\n' || ins.peek() == '\r')
		ins.ignore();

	ins>>bday;
}

std::istream& operator >>(std::istream& ins, Friend& f)
{
	f.input(ins);
	return ins;

}

std::ostream& operator <<(std::ostream& outs, const Friend& f)
{
	f.output(outs);
	return outs;
}
