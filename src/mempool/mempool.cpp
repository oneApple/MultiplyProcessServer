#include"mempool/mempool.h"
#include<assert.h>

#include<string.h>

#define ALIGN 8

MemPool* MemPool::_instance = NULL;

static size_t check_align_addr(void*& pBuf)  
{  
	size_t align = 0;  
	size_t addr = (size_t)pBuf;
	align = (ALIGN - addr % ALIGN) % ALIGN;  
	pBuf = (char*)pBuf + align;  
	return align;  
}  


static size_t check_align_block(size_t size)  
{  
	size_t align = size % UNITSIZE;  

	return size - align;   
}  

static size_t check_align_size(size_t size)  
{  
	size = (size + UNITSIZE - 1) / UNITSIZE * UNITSIZE;  
	return size;  
}  

MemPool::MemPool(void *mem,int size)
{
	assert(mem != NULL);
	this->pbuf = mem;
	this->isize = size;

	this->iunitcount = (this->isize + UNITSIZE - 1) / UNITSIZE;
	this->punit = (MemUnit*)this->pbuf;

	this->blockpool.createList((MemBlock*)(this->punit + this->iunitcount),this->iunitcount);

	this->pmem = (char*)this->pbuf + this->iunitcount * (sizeof(MemUnit) + sizeof(MemBlock));

	size_t align = check_align_addr(this->pmem);
	this->itotalsize = this->isize - align - this->iunitcount * (sizeof(MemUnit) + sizeof(MemBlock));
	this->itotalsize = check_align_block(this->itotalsize);
	this->imemcount = this->itotalsize / UNITSIZE;

	MemBlock *temp = this->blockpool.popFront();
	temp->pUnit = this->punit;
	this->freeblock.pushFront(temp);

	this->punit[0].icount = this->imemcount;
	this->punit[0].pBlock = temp;
	this->punit[this->imemcount - 1].istart = 0;

	this->iusedsize = 0;
}

static void* index2addr(void* pmem, size_t index)  
{  
    void* ret = (void*)((char*)pmem + index *UNITSIZE);  
    return ret;  
}  

static size_t addr2index(void* pmem, void* addr)  
{   
    size_t index = ((char*)addr - (char*)pmem) / UNITSIZE;  
    return index;  
}  

void *MemPool::getMem(size_t size)
{
	size_t memsize = check_align_size(size);
	MemBlock *temp = this->freeblock.getBlock(memsize);
	if(temp == NULL)
	{
		perror("can not alloc");
		return NULL;
	}

	this->iusedsize += memsize;
	//������
	if(temp->pUnit->icount * UNITSIZE == memsize)
	{
		size_t index = temp->pUnit - this->punit;
		this->freeblock.deleteBlock(temp);
		this->blockpool.pushFront(temp);
		return index2addr(this->pmem,index);
	}
	else
	{
		MemUnit *allocunit = temp->pUnit;
		size_t origcount = allocunit->icount;

		size_t allocindex = allocunit - this->punit;
		allocunit->icount = memsize / UNITSIZE;
		//printf("allocindex:%d,icount:%d\n",allocindex,allocunit->icount);
		allocunit->pBlock = NULL;//�����������Ϊ��
		this->punit[allocindex + allocunit->icount - 1].istart = allocindex;

		this->punit[allocindex + allocunit->icount].icount = origcount - allocunit->icount;
		this->punit[allocindex + allocunit->icount].pBlock = temp;
		this->punit[allocindex + origcount - 1].istart =  allocindex + allocunit->icount;
		temp->pUnit = &this->punit[allocindex + allocunit->icount];

		return index2addr(this->pmem,allocindex);
	}
}

void MemPool::freeMem(void *mem)
{
	size_t index = addr2index(this->pmem,mem);
	size_t startindex = this->punit[index - 1].istart;
	MemUnit *cur = &this->punit[index];
	MemUnit *pre = NULL;
	MemUnit *next = NULL;
	
	this->iusedsize -= cur->icount * UNITSIZE;
	//���ǵ�һ��
	if(index != 0)
	{
		pre = &this->punit[startindex];
	}
	//�������һ��
	if(index + cur->icount != this->imemcount)
	{
		next = &this->punit[index + cur->icount];
	}
	//ǰ���ǿհף��ϲ�
	if(pre != NULL && next != NULL && pre->pBlock != NULL && next->pBlock != NULL)
	{
		this->punit[index + cur->icount + next->icount - 1].istart = startindex;
		pre->icount += cur->icount + next->icount;
		this->freeblock.deleteBlock(next->pBlock);
		this->blockpool.pushFront(next->pBlock);
		cur->pBlock = next->pBlock = NULL;
	}
	//ǰ��հף���ǰ��ϲ�
	else if(pre != NULL && pre->pBlock != NULL)
	{
		this->punit[index + cur->icount - 1].istart = startindex;
		pre->icount += cur->icount;
		cur->pBlock = NULL;
	}
	//����հף��ͺ���ϲ�
	else if(next != NULL && next->pBlock != NULL)
	{
		next->pBlock->pUnit = cur;
		this->punit[index + cur->icount + next->icount - 1].istart = index;
		cur->icount += next->icount;
		cur->pBlock = next->pBlock;
		next->pBlock = NULL;
	}
	//ǰ�󶼲��ɺϲ�
	else
	{
		MemBlock *newblock = this->blockpool.popFront();
		newblock->pUnit = cur;
		cur->pBlock = newblock;
		this->freeblock.pushFront(newblock);
	}
}

