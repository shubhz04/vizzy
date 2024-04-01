#pragma once
#include <glm/glm.hpp>

namespace Vizzy {
	struct CubicBezier {
		glm::vec2 sP;	// Start Point
		glm::vec2 cp1;	// Control Point 1
		glm::vec2 cp2;	// Control Point 2
		glm::vec2 eP;	// End Point
	};

	static glm::vec2 get_bezier_point(CubicBezier _curve, float t) {
		float x = pow((1 - t), 3) * _curve.sP.x
			+ 3 * pow(1 - t, 2) * pow(t, 1) * _curve.cp1.x
			+ 3 * pow(1 - t, 1) * pow(t, 2) * _curve.cp2.x
			+ pow(t, 3) * _curve.eP.x;
		float y = pow((1 - t), 3) * _curve.sP.y
			+ 3 * pow(1 - t, 2) * pow(t, 1) * _curve.cp1.y
			+ 3 * pow(1 - t, 1) * pow(t, 2) * _curve.cp2.y
			+ pow(t, 3) * _curve.eP.y;
		
		return glm::vec2(x, y);
	}
}