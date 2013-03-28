/*
 * globalDataControl.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef GLOBALDATACONTROL_H_
#define GLOBALDATACONTROL_H_

#include<map>
#include<sys/types.h>
class globalDataControl{
private:
	std::map<int,bool> _mclientfdAndAlloc;
	size_t _uallocnum;
public:
	globalDataControl():_uallocnum(0){}
	void AddFreeSockfd(const int sockfd);
	const int AllocFreeSockfd();
	void ReleaseBusySockfd(const int sockfd);
	void DelCloseSockfd(const int sockfd);
};

#endif /* GLOBALDATACONTROL_H_ */
