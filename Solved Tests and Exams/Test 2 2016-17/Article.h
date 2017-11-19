/*
 * Article.h
 *
 *  Created on: 16/11/2016
 *      Author: hlc
 */

#ifndef SRC_ARTICLE_H_
#define SRC_ARTICLE_H_

class Article {
	const long client;
	const long barCode;
	bool present;
	bool deliverHome;
	int presentNumber;
	int arrivalNumber;
public:
	Article(long client, long barCode);
	long getClient() const;
	long getBarCode() const;
	bool getPresent() const;
	void setPresent(bool present);
	bool getDeliverHome() const;
	void setDeliverHome(bool deliverHome);
	int getPresentNumber() const;
	void setPresentNumber(int presentNumber);
	int getArrivalNumber() const;
	void setArrivalNumber(int arrivalNumber);
};

#endif /* SRC_ARTICLE_H_ */
