/*
 * Vertex.h
 *
 *  Created on: May 17, 2017
 *      Author: Simon
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <Gl\glew.h>
#include <Gl\gl.h>
namespace Engine {

struct Color {
	Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) {

	}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Position {
	float x;
	float y;
};

struct UV {
	float u, v;
};

struct Vertex {
	Position position;
	Color color;
	UV uv;

	Vertex() :
			color(255, 255, 255, 255) {

	}

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
};
}
#endif /* VERTEX_H_ */
