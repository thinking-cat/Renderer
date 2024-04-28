#pragma once
#include "Spline.h"
#include "Shader.h"

class Beizier :Spline {
private:
	unsigned int ID, VAO, VBO;
	unsigned int IDpos, VAOpos, VBOpos;
	std::vector<float> controlPoints = {};
	const Eigen::Matrix<float, 4, 4> bernstien{
		{1.0, 0.0, 0.0, 0.0, },
		{ -3.0, 3.0, 0.0, 0.0, },
		{ 3.0, -6.0, 3.0, 0.0, },
		{ -1.0, 3.0, -3.0, 1.0 }
	};
	
public:
	Beizier();

	void Draw() override;

	inline void clear() override { controlPoints = {}; }

	inline void addControlPoints(float x, float y) { controlPoints.push_back(x); controlPoints.push_back(y); }
};