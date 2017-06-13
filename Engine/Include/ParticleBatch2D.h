/*
 * ParticleBatch2D.h
 *
 *  Created on: Jun 4, 2017
 *      Author: Simon
 */

#ifndef PARTICLEBATCH2D_H_
#define PARTICLEBATCH2D_H_

#include <glm/glm.hpp>
#include "vertex.h"
#include "GLTexture.h"


namespace Engine {

class SpriteBatch;

class Particle2D {
public:
	friend class ParticleBatch2D;

	void update();
private:
	glm::vec2 _position = glm::vec2(0, 0);
	glm::vec2 _velocity = glm::vec2(0,0);
	Color _color = Color(255, 255, 255, 255);
	float _life = 0;
	float _size = 0;
};

class ParticleBatch2D {
public:
	ParticleBatch2D();
	virtual ~ParticleBatch2D();

	void init(int maxParticles, float decayRate, GL_Texture texture);
	void addParticle(const glm::vec2& position, const glm::vec2& velocity, const Color& color);
	void update();
	void draw(SpriteBatch & batcher);
private:
	float _decayRate = 0;
	Particle2D* _particles = nullptr;
	int _maxParticles = 0;
	GL_Texture _texture;
};

} /* namespace Engine */

#endif /* PARTICLEBATCH2D_H_ */
