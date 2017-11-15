/*
 * exceptions.h
 *
 *  Created on: Nov 11, 2016
 *      Author: arocha
 */

#ifndef SRC_EXCEPTIONS_H_
#define SRC_EXCEPTIONS_H_

#include <string>
using namespace std;


class FilaVazia {
private:
	string msg;
public:
	FilaVazia(const string & msg) : msg(msg) { }
	string getMsg() const { return msg; }
};


#endif /* SRC_EXCEPTIONS_H_ */
