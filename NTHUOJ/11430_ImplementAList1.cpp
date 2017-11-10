#include<cstddef>
#include<iosfwd>
#include<iostream>
#include<string>
#include "function.h"

namespace oj
{

	// Constructor
	List::List()
	{
		begin_ = nullptr;
	}
	
	// Destructor
	List::~List()
	{
		Node *cur = begin_;
		while(cur != nullptr)
		{
			Node *d = cur;
			cur = cur->next;
			delete d;
		}
	}
	
	// Erase
	void List::erase(size_type pos)
	{
		if(pos == 0)
		{
			if(begin_->next != nullptr)
			{
				begin_ = begin_->next;
				delete begin_->prev;
				begin_->prev = nullptr;
			}
			else
			{
				delete begin_;
				begin_ = nullptr;
			}
			
		}
		else
		{
			Node *cur = begin_;
			for(int i = 0; i < pos && cur != nullptr; i++, cur = cur->next);
			
			cur->prev->next = cur->next;
			if(cur->next != nullptr) cur->next->prev = cur->prev;
			delete cur;
		}
	}
	
	// Insert
	void List::insert(List::size_type pos, List::const_reference val)
	{
		Node *n = new Node(), *cur = begin_, *last;
		n->next = n->prev = nullptr;
		n->data = val;
		
		if(begin_ == nullptr)
		{
			begin_ = n;
			return;
		}
		
		for(int i = 0; i < pos; i++, last = cur, cur = cur->next);
		n->next = cur;
		n->prev = cur->prev;
			
		if(cur->prev != nullptr) cur->prev->next = n;
		cur->prev = n;
		
		if(pos == 0) begin_ = n;
		
	}
	
	// Output
	std::ostream& operator<<(std::ostream & out,const List & l)
	{
		List::Node *cur = l.begin_;
		while(cur != nullptr)
		{
			out << cur->data << " ";
			cur = cur->next;
		}
		return out;
	}
}
