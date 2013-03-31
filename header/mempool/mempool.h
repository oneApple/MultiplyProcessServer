#pragma once
#include"memblocklist.h"

class MemPool{
private:
	void *pbuf;
	int isize;
private:
	int iusedsize;
	int itotalsize;
private:
	int iunitcount;
	MemUnit *punit;
	void *pmem;
	size_t imemcount;
	MemBlockList blockpool;
	MemBlockList freeblock;
private:
	static MemPool *_instance;
	class release{
	public:
		~release()
		{
			if(MemPool::_instance != NULL)
			{
				delete MemPool::_instance;
				MemPool::_instance = NULL;
			}
		}
	};
	static release rel;
public:
	static MemPool *getInstance()
	{
		if(MemPool::_instance == NULL)
		{
			MemPool::_instance = new MemPool(new char[10000],10000);
		}
		return MemPool::_instance;
	}
	MemPool(void *mem,int size);
public:
	void *getMem(size_t size);
	void freeMem(void *mem);
public:
	void test()
	{
		printf("...........................\n");
		printf("itotalsize:%d,iunitcount:%d,imemcount:%d\n",this->itotalsize,this->iunitcount,this->imemcount);
		this->blockpool.test();
		this->freeblock.test();
		printf("...........................\n");
	}
};

