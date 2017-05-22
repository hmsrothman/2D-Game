/*
 * IOManager.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef IOMANAGER_H_
#define IOMANAGER_H_

#include <vector>
#include <string>
namespace Engine{

class IO_Manager {
public:
	static bool readFileToBuffer(const std::string& filePath,std::vector<unsigned char>& buffer);
};
}
#endif /* IOMANAGER_H_ */
