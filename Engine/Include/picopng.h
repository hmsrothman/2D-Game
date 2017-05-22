/*
 * picopng.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef PICOPNG_H_
#define PICOPNG_H_

#include <vector>
namespace Engine {

extern int decodePNG(std::vector<unsigned char>& out_image,
		unsigned long& image_width, unsigned long& image_height,
		const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 =
				true);

}
#endif /* PICOPNG_H_ */
