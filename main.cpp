/*
 * main.cpp
 *
 *  Created on: 2013-1-24
 *      Author: keym
 */

#include"parentProcess.h"

#include<iostream>

int main()
{
	parentProcess p;
	try{
		p.InitializeManage(4);
		p.CommunicationHandle();
	}
	catch(std::exception &e)
	{
		std::cout<<"exception:"<<e.what()<<std::endl;
	}
	return 0;
}
