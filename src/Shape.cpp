#include "Shape.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Statics.h"

using namespace std;

void Shape::initShape()
{
	if (posBuf.empty()) {
		cerr << "Error: attempted initializing shape with no data." << endl;
		exit(1);
	}

	//set vao for just posbuf for now
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &posBufID);
	//bind our VAO
	glBindVertexArray(vaoID);

	//copy vertices to the GPU
	glBindBuffer(GL_ARRAY_BUFFER, posBufID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * posBuf.size(), &posBuf, GL_STATIC_DRAW);
	//point openGL in the right direction for this context
	//our shader uses location = 0, so we set the location to 0.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //doesnt necessarily need to be done but it helps in case of multiple VAOs.

	cerr << "vaoID: " << vaoID << "\n posBufID: " << posBufID << endl;

}

void Shape::setShaders(std::string& v, std::string& f)
{
	int success;
	char infoLog[512];

	unsigned int vShader;
	char* vShaderSrc = Statics::Instance().textFileRead(v.c_str());
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//cerr << "vertex shader source: " << vShaderSrc << endl;
	glShaderSource(vShader, 1, &vShaderSrc, NULL);
	glCompileShader(vShader);

	cerr << "VERTEX SHADER /////////////////////////" << endl;
	cerr << vShaderSrc << endl;
	cerr << "///////////////////////////////////////" << endl;

	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		cerr << "ERROR compiling " << v << ":\n";
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		cerr << infoLog << endl;
		exit(1);
	}



	unsigned int fShader;
	char* fShaderSrc = Statics::Instance().textFileRead(f.c_str());
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fShader, 1, &fShaderSrc, NULL);
	glCompileShader(fShader);

	cerr << "FRAGMENT SHADER /////////////////////////" << endl;
	cerr << fShaderSrc << endl;
	cerr << "///////////////////////////////////////" << endl;

	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		cerr << "ERROR compiling " << f << ":\n\n";
		glGetShaderInfoLog(fShader, 512, NULL, infoLog);
		cerr << infoLog << endl;
		exit(1);
	}


	//create and link program
	progID = glCreateProgram();
	glAttachShader(progID, vShader);
	glAttachShader(progID, fShader);
	glLinkProgram(progID);

	glGetProgramiv(progID, GL_LINK_STATUS, &success);
	if (!success) {
		cerr << "failed to link shaders " << v << " & " << f << " to program:\n\n" << endl;
		glGetProgramInfoLog(progID, 512, NULL, infoLog);
		cerr << infoLog << endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);


	
}

void Shape::draw()
{
	glUseProgram(progID);
	glBindVertexArray(vaoID);

	//drawcall
	glDrawArrays(GL_TRIANGLES, 0, 3);
	/*
	cerr << "=======" << endl;
	for (int i = 0; i < posBuf.size(); i+=3) {
		cerr << "(" << posBuf[i] << ", " << posBuf[i + 1] << ", " << posBuf[i + 2] << ")" << endl;
	}
	cerr << "=======" << endl;
	*/
	Statics::Instance().checkError(GET_FILE_LINE);

	//glDisableVertexAttribArray();
	//glUseProgram(0);

}
