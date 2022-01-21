#pragma once
#include <vector>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

class Shape
{
public:
	std::vector<float> posBuf;
	std::vector<float> norBuf;

	int numBuffers;

	//buffer IDs
	unsigned int vaoID;
	unsigned int posBufID;
	unsigned int norBufID;
	unsigned int progID;
	

	std::string vShad;
	std::string fShad;

	Shape() : numBuffers(0) {}
	Shape(std::vector<float>& _pos) : posBuf(_pos) { numBuffers = 1; }
	Shape(std::vector<float>& _pos, std::vector<float>& _nor) : posBuf(_pos), norBuf(_nor) { numBuffers = 2; }


	void initShape();
	void setShaders(std::string& v, std::string& f);
	void draw();
};

