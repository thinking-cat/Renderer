#pragma once
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>


class Spline {
public:
	inline virtual void Draw() = 0;
	inline virtual void clear() = 0;
};

inline void DrawPoints(unsigned int VAO, unsigned int VBO, unsigned int programID, const std::vector<float>& Points)
{
	if (Points.size() == 0)
		return;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, Points.size() * sizeof(float), Points.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_PROGRAM_POINT_SIZE);

	glUseProgram(programID);
	glDrawArrays(GL_POINTS, 0, Points.size() / 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glDisable(GL_PROGRAM_POINT_SIZE);

}