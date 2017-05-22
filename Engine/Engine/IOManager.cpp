/*
 * IOManager.cpp
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#include "IOManager.h"
#include <fstream>
namespace Engine {

bool IO_Manager::readFileToBuffer(const std::string& filePath,
		std::vector<unsigned char>& buffer) {
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	file.seekg(0, std::ios::end); //Seek to end of file
	int fileSize = file.tellg(); //Get filesize in bytes
	file.seekg(0, std::ios::beg); //Go back to start
	fileSize -= file.tellg(); //subtract off header

	buffer.resize(fileSize);
	file.read((char*) &(buffer[0]), fileSize);

	file.close();

	return true;
}
}
