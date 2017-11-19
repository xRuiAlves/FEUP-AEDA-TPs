/*
 * AfterSalesService.h
 *
 *  Created on: 16/11/2016
 *      Author: hlc
 */

#ifndef SRC_AFTERSALESSERVICE_H_
#define SRC_AFTERSALESSERVICE_H_

#include <vector>
#include <queue>
#include <vector>
#include "Article.h"

class AfterSalesService {
	std::vector<Article*> presentsTable;
	const std::queue<Article*>::size_type toWrapQueueSize;
	std::queue<Article*> toWrap;
	std::queue<Article*> toDeliver;
public:
	static int tableOrdinal;
	AfterSalesService(int toWrapQueueSize);
	AfterSalesService(int twqs, std::queue<Article*> tw) : toWrapQueueSize(twqs), toWrap(tw) {};
	std::vector<Article*> getPresentsTable() const;
	std::queue<Article*> getToWrap() const;
	std::queue<Article*> getToDeliver() const;
	void dropPresentsOnTable(std::vector<Article*> presents);

	//--- TO IMPLEMENT
	std::vector<Article*> pickPresentsFromTable(long client);
	void sortArticles();
	void enqueueArticles();
	Article* wrapNext();
};

#endif /* SRC_AFTERSALESSERVICE_H_ */
