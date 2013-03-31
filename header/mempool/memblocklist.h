#pragma once
#include"memblock.h"

#include<stdio.h>

class MemBlockList{
private:
	MemBlock *plist;
	size_t icount;
public:
	MemBlockList():icount(0)
	{
		plist = NULL;
	}
public:
	void createList(MemBlock * pmem,int num);
	void pushFront(MemBlock *block);
	MemBlock *popFront();
	MemBlock *getBlock(size_t size);
	void deleteBlock(MemBlock *block);
public:
	void test()
	{
		printf("icount:%d\nidata:",this->icount);
		MemBlock *temp = this->plist;
		while(temp != NULL)
		{
			if(temp->pUnit != NULL)
			{
				printf("%d,",temp->pUnit->icount);
			}
			temp = temp->next;
		}
		printf("\n");
	}
};
