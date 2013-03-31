#include"mempool/memblocklist.h"
#include<assert.h>

void MemBlockList::createList(MemBlock *pmem,int num)
{
	assert(pmem != NULL && num != 0);
	this->plist = pmem;
	int i;
	for(i = 1;i < num;++ i)
	{
		this->plist[i - 1].next = &this->plist[i];
		this->plist[i - 1].pUnit = NULL;
	}
	this->plist[num - 1].pUnit = NULL;
	this->plist[num - 1].next = NULL;
	this->icount = num;
}

MemBlock *MemBlockList::popFront()
{
	if(this->plist == NULL)
	{
		return NULL;
	}
	MemBlock *temp = this->plist;
	this->plist = this->plist->next;
	-- this->icount;
	return temp;
}

void MemBlockList::pushFront(MemBlock *block)
{
	assert(block != NULL);
	if(this->plist == NULL)
	{
		this->plist = block;
		block->next = NULL;
	}
	else
	{
		block->next = this->plist;
		this->plist = block;
	}
	++ this->icount;
}

void MemBlockList::deleteBlock(MemBlock *block)
{
	assert(this->plist != NULL && block != NULL);
	if(block == this->plist)
	{
		this->plist = this->plist->next;
	}
	else
	{
		MemBlock *pre = this->plist;
		MemBlock *cur = NULL;
		while(pre != NULL)
		{
			cur = pre->next;
			if(block == cur)
			{
				cur->pUnit = NULL;
				pre->next = cur->next;
				break;
			}
			pre = cur;
		}
	}
	-- this->icount;
}

MemBlock *MemBlockList::getBlock(size_t size)
{
   MemBlock *temp = this->plist;
   while(temp != NULL)
   {
	   if(temp->pUnit->icount * UNITSIZE >= size)
	   {
		   return temp;
	   }
	   temp = temp->next;
   }
   return temp;
}
