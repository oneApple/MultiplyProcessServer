/*
 * fixmemorypool.h
 *
 *  Created on: 2013-3-30
 *      Author: keym
 */

#ifndef FIXMEMORYPOOL_H_
#define FIXMEMORYPOOL_H_

#include<stdlib.h>
#include<stdio.h>

template<class type>
union mem_node{
	type node;
	union mem_node<type> *next;
};

template<typename type>
struct mem_block{
	mem_node<type> *head;
	mem_node<type> *tail;
	struct mem_block<type> *next;
};

template<typename type>
class fixmemorypool{
private:
	enum {MAXNUM = 2};
	static fixmemorypool<type> *Instance;
	fixmemorypool(int num = MAXNUM):head(NULL),tail(NULL),nhead(NULL),total(0),left(0),block_size(num){}

	class release{
	public:
		~release()
		{
			if(Instance != NULL)
			{
				delete Instance;
				Instance = NULL;
			}
		}
	};
	static release rel;
private:
	mem_block<type> *head;
	mem_block<type> *tail;
	mem_node<type> *nhead;
	unsigned total;
	unsigned left;
	unsigned block_size;
private:
	int add_block(int num);
public:
	void destory()
	{
		mem_block<type> *next,*cur;
		cur = this->head;
		next = NULL;
		while(cur != NULL)
		{
			next = cur->next;
			free(cur->head);
			free(cur);
			cur = next;
		}
		this->head = this->tail = NULL;
		this->nhead = NULL;
		this->total = this->left = this->block_size = 0;
	}
	static fixmemorypool<type> *getInstance()
				{
		if(fixmemorypool<type>::Instance == NULL)
		{
			fixmemorypool<type>::Instance = new fixmemorypool<type>;
		}
		return fixmemorypool<type>::Instance;
				}
public:
	type *mem_pool_alloc();
	void mem_pool_release(type *ret);
	~ fixmemorypool()
	{
		this->destory();
	}

};

template<typename type>
fixmemorypool<type>* fixmemorypool<type>::Instance = NULL;

template<class type>
typename fixmemorypool<type>::release fixmemorypool<type>::rel;

template<typename type>
int fixmemorypool<type>::add_block(int num)
{
	mem_block<type> *btemp = new mem_block<type>;
	if((btemp->head = (mem_node<type> *)malloc(sizeof(mem_node<type>) * num)) == NULL)
	{
		return 0;
	}
	btemp->tail = btemp->head + this->block_size - 1;
	mem_node<type> *p;
	for(p = btemp->head;p < btemp->tail;++ p)
	{
		p->next = (p + 1);
	}
	p->next = NULL;

	btemp->next = this->head;
	this->head = btemp;
	this->nhead = btemp->head;
	if(this->tail == NULL)
	{
		this->tail = btemp;
	}
	this->total += num;
	this->left  += num;
	return 1;
}

template<typename type>
type *fixmemorypool<type>::mem_pool_alloc()
{
	if(this->nhead == NULL)
	{
		if(!this->add_block(this->block_size))
		{
			return 0;
		}
	}
	mem_node<type> *p = this->nhead;
	this->nhead = p->next;
	-- this->left;
	printf("alloc:%d,%d\n",this->total,this->left);
	return &p->node;
}

template<typename type>
void fixmemorypool<type>::mem_pool_release(type *ret)
{
	if(ret == NULL)
	{
		return;
	}
	((mem_node<type> *)ret)->next = this->nhead;
	this->nhead = (mem_node<type> *)ret;
	++ this->left;
	printf("release:%d,%d\n",this->total,this->left);
}

#endif /* FIXMEMORYPOOL_H_ */
