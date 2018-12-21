/***************************************************
	Liam Hendrickson
	CS 2401 - John Dolan
	Project 2
	Ohio University
***************************************************/

#include "friend.h"
#include "date.h"
#include "fbfriends.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void FBFriends::resize()
{
	Friend* new_data;
    	new_data = new Friend[capacity + 5];
    	copy(data, data + used, new_data);
    	delete []data;
    	data = new_data;
    	capacity += 5; //increases memory by 5
}

FBFriends::FBFriends()
{
	capacity = 10;
	used = 0;
	current_index = 0;
	data = new Friend[capacity];
}

FBFriends::~FBFriends()
{
	delete [] data;
}

FBFriends::FBFriends(const FBFriends& other)
{
	data = new Friend[other.capacity];
    	capacity = other.capacity;
    	used = other.used;
    	copy(other.data, other.data + used, data);
}

void FBFriends::operator =(const FBFriends& other)
{
	Friend *new_;

	if(this ==&other)
		return;
	if(capacity !=other.capacity)
	{
		new_ = new Friend[other.capacity];
		delete [] data;
		data = new_;
		capacity = other.capacity;
	}

	used = other.used;
	copy(other.data, other.data +used, data);
}


void FBFriends::start()
{
	current_index = 0;

}

void FBFriends::advance()
{
	current_index=+ 1;
}

bool FBFriends::is_item()
{
	return current_index <used;
}

void FBFriends::load(std::istream& ins)
{
	Friend tmp;
	ins>>tmp;
	while(!ins.eof())
	{
		insert(tmp);
		ins>>tmp;
	}
}

void FBFriends::save(std::ostream& outs)
{
	start();
	for(int i=0; i<used; i++)
		outs<<data[i];
}

Friend FBFriends::current()
{
	return data[current_index];
}

void FBFriends::remove_current()
{

	for(int i=current_index; i<used-1; i++)
		data[i] = data[i+1];
	used--;
}

void FBFriends::insert(const Friend& f)
{
	if(used == capacity)
		resize();
	if(used<capacity)
	{
		if(!is_item())
			current_index=0;
		for(int i=used;i>current_index;i--)
			data[i] = data[i-1];
		data[current_index]=f;
		used++;
	}
}

void FBFriends::attach(const Friend& f)
{
	if(used==capacity)
		resize();
	if(!is_item())
		return;
	for(int i=used;i>current_index;i--)
		data[i+1]= data[i];
	data[current_index]=f;
	used++;
}
void FBFriends::show_all(std::ostream& outs)const
{
	for(int i=0;i<used;i++)
		outs<<data[i]<<endl;
}

void FBFriends::bday_sort()
{
	Friend tmp;

	for(int i=0; i<used; i++)
	{
		for(int j=0; j<used; j++)
		{
			if(data[i].get_bday() >data[j].get_bday())
			{
				tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}
}

bool FBFriends::is_friend(const Friend& f)const
{

	for(int i=0; i<used; i++)
	{
		if((data[i].get_name() == f.get_name()) && (data[i].get_bday() == f.get_bday()))
			return false;

	}

	return true;
}

Friend FBFriends::find_friend(const std::string& name)const
{
	for( int i=0;i<used;i++)
	{
		if(data[i].get_name() == name)
			return data[i];
	}
}
