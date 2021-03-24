#pragma once
class Shader {
public:
	void LoadShader(std::string first, std::string second) {
		shaderProgram = LoadShaders(first, second);
	}

	void glUseProgramr() {
		glUseProgram(shaderProgram);
	}

	void glUniGet(std::string type,const math4& mat) {
		glm::mat4 res = Math4(mat);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, type.c_str()), 1, GL_FALSE, &res[0][0]);
	}

private:
	glm::mat4 Math4(const math4& mat) {
		return glm::mat4(mat.matrix[0][0], mat.matrix[0][1], mat.matrix[0][2], mat.matrix[0][3],
			mat.matrix[1][0], mat.matrix[1][1], mat.matrix[1][2], mat.matrix[1][3],
			mat.matrix[2][0], mat.matrix[2][1], mat.matrix[2][2], mat.matrix[2][3],
			mat.matrix[3][0], mat.matrix[3][1], mat.matrix[3][2], mat.matrix[3][3]);
	}
	int shaderProgram;
};