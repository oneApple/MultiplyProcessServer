/*
 * globalDataControl.cpp
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#include"globalDataControl.h"
#include"commondata/magicNum.h"

#include<assert.h>
#include<iostream>

void globalDataControl::AddFreeSockfd(const int sockfd)
{
	this->_mclientfdAndAlloc[sockfd] = true;
}

const int globalDataControl::AllocFreeSockfd()
{
	std::map<int,bool>::iterator _iter = this->_mclientfdAndAlloc.begin();
	while(_iter != this->_mclientfdAndAlloc.end())
	{
		if(_iter->second)
		{
			++ this->_uallocnum;
			std::cout<<"allocnum:"<<this->_uallocnum<<std::endl;
			_iter->second = false;
			return _iter->first;
		}
		++ _iter;
	}
	return magicnum::FAILIED;
}

void globalDataControl::ReleaseBusySockfd(int sockfd)
{
	std::map<int,bool>::iterator _iter = this->_mclientfdAndAlloc.find(sockfd);
	assert(_iter != this->_mclientfdAndAlloc.end());
	_iter->second = true;
	-- this->_uallocnum;
	std::cout<<"allocnum:"<<this->_uallocnum<<std::endl;
}

void globalDataControl::DelCloseSockfd(int sockfd)
{
	std::map<int,bool>::iterator _iter = this->_mclientfdAndAlloc.find(sockfd);
	//assert(_iter != this->_mclientfdAndAlloc.end());
	if(_iter == this->_mclientfdAndAlloc.end())
	{
		return;
	}
	if(!_iter->second)
	{
		-- this->_uallocnum;
	}
    this->_mclientfdAndAlloc.erase(_iter);
    std::cout<<"current mapsize:"<<this->_mclientfdAndAlloc.size()<<std::endl;

}
