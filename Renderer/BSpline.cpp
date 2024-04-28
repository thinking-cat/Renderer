#include "BSpline.h"
#include "Shader.h"

BSpline::BSpline() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAOpos);
	glGenBuffers(1, &VBOpos);

	Shader BSplineShader;
	BSplineShader.addShader("../shader/Spline.vs", GL_VERTEX_SHADER);
	BSplineShader.addShader("../shader/Spline.fs", GL_FRAGMENT_SHADER);
	ID = BSplineShader.Compile();

	Shader ControlPointShader;
	ControlPointShader.addShader("../shader/ControlPoints.vs", GL_VERTEX_SHADER);
	ControlPointShader.addShader("../shader/ControlPoints.fs", GL_FRAGMENT_SHADER);
	IDpos = ControlPointShader.Compile();
}

inline void BSpline::Draw() {
	DrawPoints(VAOpos, VBOpos, IDpos, controlPoints);

	if (controlPoints.size() < 8)
		return;

	std::vector<float> BPoints;

	//knot vector
	/*std::vector<int> KnotVector;
	for (int t = 0; t <= controlPoints.size() + 3; t++) {
		if (t < 3)
			KnotVector.push_back(0);
		else if (t >= 3 && t < controlPoints.size())
			KnotVector.push_back(t - 3);
		else
			KnotVector.push_back(controlPoints.size() - 1);
	}*/
	//compute Basic function
	std::vector<Eigen::Vector2f> toDraw;
	for (int i = 0; i < controlPoints.size() - 6; i += 2) {
		Eigen::Matrix<float, 4, 2> piecewise;
		piecewise <<
			controlPoints[i], controlPoints[i + 1],
			controlPoints[i + 2], controlPoints[i + 3],
			controlPoints[i + 4], controlPoints[i + 5],
			controlPoints[i + 6], controlPoints[i + 7];
		for (float t = 0.0f; t <= 1.0f; t += 0.001f) {
			Eigen::Vector<float, 4> T{t* t* t, t* t, t, 1.0f};
			toDraw.push_back((Eigen::Vector2f)(1.0f / 6.0f * T.transpose() * N * piecewise).transpose());
		}
	}
	for (int i = 0; i < toDraw.size(); i++) {
		BPoints.push_back(toDraw[i][0]);
		BPoints.push_back(toDraw[i][1]);
	}

	DrawPoints(VAO, VBO, ID, BPoints);
}