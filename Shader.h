#pragma once

class Shader {
	// Handles the shader we use 
public:
	Shader();
	void start();
	void stop();
	void uploadMatrix(float* matrix);
	void cleanUp();
private:
	unsigned int programID = 0;
	unsigned int matrixLocation = 0;
};

