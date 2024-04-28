#pragma once
#include "Spline.h"
class BSpline : Spline {
private:
	unsigned int ID, VAO, VBO;
	unsigned int IDpos, VAOpos, VBOpos;
	std::vector<float> controlPoints = {};
	const Eigen::Matrix<float, 4, 4> N{
		{-1.0f, 3.0f, -3.0f, 1.0f},
		{3.0f, -6.0f, 3.0f, 0.0f},
		{-3.0f, 0.0f, 3.0f, 0.0f},
		{1.0f, 4.0f, 1.0f, 0.0f}
	};
public:
	BSpline();

	inline void Draw() override;

	inline void clear() override { controlPoints = {}; }

	inline void addControlPoints(float x, float y) { controlPoints.push_back(x); controlPoints.push_back(y); }
};