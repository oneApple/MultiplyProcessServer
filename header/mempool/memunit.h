#pragma once

#define UNITSIZE 64
class MemBlock;

struct MemUnit{
	unsigned icount;
	MemBlock *pBlock;
	unsigned istart;
};
typedef struct MemUnit MemUnit;
