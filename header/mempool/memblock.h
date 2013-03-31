#pragma once
#include"memunit.h"
class MemBlock{
public:
	MemUnit *pUnit;
	MemBlock *next;
};