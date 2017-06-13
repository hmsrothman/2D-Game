/*
 * ParticleBatch2D.cpp
 *
 *  Created on: Jun 4, 2017
 *      Author: Simon
 */

#include <ParticleBatch2D.h>
#include "SpriteBatch.h"

namespace Engine {

void Particle2D::update() {
	_position += _velocity;
}

void ParticleBatch2D::init(int maxParticles, float decayRate,
		GL_Texture texture) {
	_maxParticles = maxParticles;
	_particles = new Particle2D[maxParticles];
	_decayRate = decayRate;
	_texture = texture;
}

void ParticleBatch2D::addParticle(const glm::vec2& position,
		const glm::vec2& velocity, const Color& color) {

}

void ParticleBatch2D::draw(SpriteBatch & batcher) {
	for (int i = 0; i < _maxParticles; i++) {
		auto&p = _particles[i];
		glm::vec4 destRect(p._position.x, p._position.y, p._size, p._size);
		glm::vec4 uvRect(0, 0, 1, 1);
		batcher.draw(destRect, uvRect, _texture.id, 0, p._color);
	}
}

void ParticleBatch2D::update() {
	for (int i = 0; i < _maxParticles; i++) {
		if (_particles[i]._life > 0) {
			_particles[i].update();
			_particles[i]._life -= _decayRate;
		}
	}
}

ParticleBatch2D::ParticleBatch2D() {
	// TODO Auto-generated constructor stub

}

ParticleBatch2D::~ParticleBatch2D() {
	delete[] _particles;
}

} /* namespace Engine */
