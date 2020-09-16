#pragma once

class Shader {
	// Handles the shader we use 
public:
	Shader();
	void start();
	void stop();
	void cleanUp();
private:
	unsigned int programID = 0;
};

