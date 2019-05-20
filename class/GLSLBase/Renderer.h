#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\wglew.h"
#include "Dependencies\glm/glm.hpp"
#include "Dependencies\glm/gtc/matrix_transform.hpp"
#include "Dependencies\glm/gtx/euler_angles.hpp"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	GLuint CreatePngTexture(char * filePath);
	GLuint CreateBmpTexture(char * filePath);
	   
	void Test();
	void Lecture2();
	void Lecture3();
	void Lecture4();
	void Lecture5();
	void Lecture6();
	void Lecture7();

	void RandomRect(int count);
	void MakeRect(int count);
	void Solid7();
	void Fillfloat(float n);
	void DrawTextRect();//GLuint tex);
	void DrawNumber(int * num);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects(); 
	unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight);
	void CreateProxyGeometry();

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;
	
	int GridCount = 0;
	int m_count = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBORect2 = 0;
	GLuint m_VBOTri = 0;
	GLuint m_VBORandRect = 0;
	GLuint m_VBO_GridMesh = 0;
	GLuint m_VBORectColor = 0;
	GLuint m_VBOTextRect = 0;
	GLuint m_CheckBoard = 0;

	unsigned int vertex_count_array;

	GLuint m_SolidRectShader = 0;
	GLuint m_SolidRectShader2 = 0;
	GLuint m_SimpleVelShader = 0;
	GLuint m_SimpleVelShader2 = 0;
	GLuint m_Texture = 0;
	GLuint m_Texture2 = 0;
	GLuint m_NumTexture = 0;
	GLuint m_TextureRectShader = 0;
	GLuint m_DrawNumShader = 0;
};

