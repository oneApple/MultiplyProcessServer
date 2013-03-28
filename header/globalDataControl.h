/*
 * globalDataControl.h
 *
 *  Created on: Mar 28, 2013
 *      Author: keym
 */

#ifndef GLOBALDATACONTROL_H_
#define GLOBALDATACONTROL_H_

#include<map>
class globalDataControl{
private:
	std::map<int,bool> _mclientfdAndAlloc;
public:
	void AddFreeSockfd(const int sockfd);
	const int AllocFreeSockfd();
	void ReleaseBusySockfd(const int sockfd);
	void DelCloseSockfd(const int sockfd);
};

#endif /* GLOBALDATACONTROL_H_ */
