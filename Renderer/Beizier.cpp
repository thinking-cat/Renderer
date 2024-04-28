#include "Beizier.h"
#include "Shader.h"

Beizier::Beizier() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glGenVertexArrays(1, &VAOpos);
	glGenBuffers(1, &VBOpos);

	Shader BeizierShader;
	BeizierShader.addShader("../shader/Spline.vs", GL_VERTEX_SHADER);
	BeizierShader.addShader("../shader/Spline.fs", GL_FRAGMENT_SHADER);
	ID = BeizierShader.Compile();

	Shader ControlPointShader;
	ControlPointShader.addShader("../shader/ControlPoints.vs", GL_VERTEX_SHADER);
	ControlPointShader.addShader("../shader/ControlPoints.fs", GL_FRAGMENT_SHADER);
	IDpos = ControlPointShader.Compile();
}

inline void Beizier::Draw() {
	std::cout << controlPoints.size() << std::endl;
	DrawPoints(VAOpos, VBOpos, IDpos, controlPoints);

	if (controlPoints.size() < 8)
		return;
	std::vector<Eigen::Vector2f> toDraw;
	std::vector<float> curve;

	for (int i = 0; i < ((int)controlPoints.size() - 2) / 6; i++) {
		Eigen::Matrix<float, 4, 2> piecewise;
		piecewise <<
			controlPoints[6 * i], controlPoints[6 * i + 1],
			controlPoints[6 * i + 2], controlPoints[6 * i + 3],
			controlPoints[6 * i + 4], controlPoints[6 * i + 5],
			controlPoints[6 * i + 6], controlPoints[6 * i + 7];
		for (GLfloat t = 0; t <= 1; t += 0.0001) {
			Eigen::Vector4f T{1.0f, t, t* t, t* t* t};
			toDraw.push_back((Eigen::Vector2f)(T.transpose() * bernstien * piecewise).transpose());
		}
	}
	for (int i = 0; i < toDraw.size(); i++) {
		curve.push_back(toDraw[i][0]);
		curve.push_back(toDraw[i][1]);
	}
	DrawPoints(VAO, VBO, ID, curve);
}


