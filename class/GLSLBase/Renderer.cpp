#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include <Windows.h>
#include <cstdlib>
#include <cassert>
#include <stdlib.h>
#include <time.h>

float g_Time = 0.f;


Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	//m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	//m_SolidRectShader2 = CompileShaders("./Shaders/SolidRect2.vs", "./Shaders/SolidRect2.fs");	// fillallShader
	//m_SimpleVelShader = CompileShaders("./Shaders/SimpleVel.vs", "./Shaders/SimpleVel.fs");
	//m_SimpleVelShader2 = CompileShaders("./Shaders/SimpleVel2.vs", "./Shaders/SimpleVel2.fs");
	//m_TextureRectShader = CompileShaders("./Shaders/TextRect.vs", "./Shaders/TextRect.fs");
	m_DrawNumShader = CompileShaders("./Shaders/DrawNumber.vs", "./Shaders/DrawNumber.fs");
	
	//m_Texture = CreatePngTexture("./Shaders/rgb.png");
	//m_Texture2 = CreatePngTexture("./Shaders/Light.png");
	m_NumTexture = CreatePngTexture("./Shaders/Numbers.png");
	//Create VBOs
	CreateVertexBufferObjects();
}

void Renderer::CreateVertexBufferObjects()
{
	float color[]
		=
	{
		1, 0, 0, 1, 
		1, 0, 0, 1,
		1, 0, 0, 1, //Triangle1
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 0, 0, 1,//Triangle2
	};

	glGenBuffers(1, &m_VBORectColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);


	// Lecture2
	float tri[]
		=
	{
		0.f, 0.f, 0.f,
		1.0, 0.f, 0.f, 
		1.0, 1.0, 0.f,	// Triangle3
	};

	glGenBuffers(1, &m_VBOTri);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTri);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);

	float fill[]
		=
	{
		-250, 250, 0,
		250, 250, 0,
		-250, -250, 0, //Triangle1
		-250, -250, 0,
		250, 250, 0,
		250, -250, 0,//Triangle2
	};

	glGenBuffers(1, &m_VBORect2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fill), fill, GL_STATIC_DRAW);

	//RandomRect(300);

	//MakeRect(20000);

	//Solid7();

	float size = 0.5f;
	float textrect[]
		=
	{
		-size, size, 0, 0.0f, 1.0f,
		-size, -size, 0, 0.0f, 0.0f,
		size, size, 0, 1.0f, 1.0f,//Triangle1
		size, size, 0, 1.0f, 1.0f,
		-size, -size, 0, 0.0f, 0.0f,
		size, -size, 0, 1.0f, 0.0f,//Triangle2
	};

	glGenBuffers(1, &m_VBOTextRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textrect), textrect, GL_STATIC_DRAW);

	// chechkboard
	static const GLulong checkboard[] =
	{
		0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,
		0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,
		0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,
		0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,
		0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000,0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	};

	glGenTextures(1, &m_CheckBoard);
	glBindTexture(GL_TEXTURE_2D, m_CheckBoard);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE,checkboard );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}
unsigned char * Renderer::loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	std::cout << "Loading bmp file " << imagepath << " ... " << std::endl;
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = NULL;
	fopen_s(&file, imagepath, "rb");
	if (!file)
	{
		std::cout << "Image could not be opened, " << imagepath << " is missing. " << std::endl;
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		std::cout << imagepath << " is not a correct BMP file. " << std::endl;
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth * outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	std::cout << imagepath << " is succesfully loaded. " << std::endl;

	return data;
}

GLuint Renderer::CreatePngTexture(char * filePath)
{
	//Load Pngs: Load file and decode image.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);
	if (error != 0)
	{
		lodepng_error_text(error);
		assert(error == 0);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return temp;
}

GLuint Renderer::CreateBmpTexture(char * filePath)
{
	//Load Bmp: Load file and decode image.
	unsigned int width, height;
	unsigned char * bmp
		= loadBMPRaw(filePath, width, height);

	if (bmp == NULL)
	{
		std::cout << "Error while loading bmp file : " << filePath << std::endl;
		assert(bmp != NULL);
		return -1;
	}

	GLuint temp;
	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bmp);

	return temp;
}

void Renderer::Test()
{
	glUseProgram(m_SolidRectShader);

	g_Time += 0.01f;
	if (g_Time > 1.f)
		g_Time = 0.f;

	GLuint uTime = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(uTime, g_Time);

	GLint aPos = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint aColor = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(aPos);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(aPos, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glEnableVertexAttribArray(aColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORectColor);
	glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}

// 랜덤 사각형 (파티클)
void Renderer::RandomRect(int count)
{
	m_count = count;
	float rectSize = 0.01f;
	int verticesPerQuad = 6;
	int floatsPerVertex = 3 + 3 + 2;
	int size = count * verticesPerQuad * floatsPerVertex;
	float *point = new float [size];

	for (int i = 0; i < m_count; i++) {
		// RandRect
		float randX, randY;
		float randVelX = 0, randVelY = 0, randVelZ = 0;

		int index = i * verticesPerQuad * floatsPerVertex;
		float startTime, lifeTime;
		float startTimeMax = 6.f;
		float lifeTimeMax = 2.f;

		startTime = ((float)(rand() / (float)RAND_MAX)*startTimeMax);
		lifeTime = ((float)(rand() / (float)RAND_MAX)*lifeTimeMax);

		randX = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);
		randY = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);

		randVelX = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);
		randVelY = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);

		point[index] = randX-rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;

		point[index] = randX - rectSize; index++;
		point[index] = randY+ rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;

		point[index] = randX+ rectSize; index++;
		point[index] = randY+ rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;

		point[index] = randX - rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;

		point[index] = randX+ rectSize; index++;
		point[index] = randY+ rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;

		point[index] = randX+ rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime;
	}
	glGenBuffers(1, &m_VBORandRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VBORandRect) * size, point, GL_STATIC_DRAW);
	vertex_count_array = count * verticesPerQuad;
}

void Renderer::MakeRect(int count)
{
	m_count = count;
	float rectSize = 0.01f;
	int verticesPerQuad = 6;
	int floatsPerVertex = 3 + 3 + 2 + 2 + 1 + 4 + 2;
	int size = count * verticesPerQuad * floatsPerVertex;
	float *point = new float[size];

	for (int i = 0; i < m_count; i++) {
		// RandRect
		float randX, randY;
		float randVelX = 0, randVelY = 0, randVelZ = 0;

		int index = i * verticesPerQuad * floatsPerVertex;
		float startTime, lifeTime;
		float startTimeMax = 2.f;
		float lifeTimeMax = 6.f;
		float ratio, amp;
		float ratioMin = 2.f;
		float ampMin = 1.f;
		float value = 0.f;
		float thre = 1.f;
		float r, g, b, a;

		startTime = ((float)(rand() / (float)RAND_MAX)*startTimeMax);
		lifeTime = ((float)(rand() / (float)RAND_MAX)*lifeTimeMax);
		ratio = ((float)(rand() / (float)RAND_MAX))*ratioMin;
		amp = ((float)(rand() / (float)RAND_MAX))*ampMin;
		value = value + ((float)(rand() / (float)RAND_MAX))*thre;
		r = ((float)(rand() / (float)RAND_MAX));
		g = ((float)(rand() / (float)RAND_MAX));
		b = ((float)(rand() / (float)RAND_MAX));
		a = 1.f;

		randX = 0;
		randY = 0;

		randVelX = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);
		randVelY = 2.f*((float)(rand() / (float)RAND_MAX) - 0.5f);

		point[index] = randX - rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 0.0f; index++;
		point[index] = 0.0f; index++;

		point[index] = randX - rectSize; index++;
		point[index] = randY + rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 0.0f; index++;
		point[index] = 1.0f; index++;

		point[index] = randX + rectSize; index++;
		point[index] = randY + rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 1.0f; index++;
		point[index] = 1.0f; index++;

		point[index] = randX - rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 0.0f; index++;
		point[index] = 0.0f; index++;

		point[index] = randX + rectSize; index++;
		point[index] = randY + rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 1.0f; index++;
		point[index] = 1.0f; index++;

		point[index] = randX + rectSize; index++;
		point[index] = randY - rectSize; index++;
		point[index] = 0.f; index++;
		point[index] = randVelX; index++;
		point[index] = randVelY; index++;
		point[index] = randVelZ; index++;
		point[index] = startTime; index++;
		point[index] = lifeTime; index++;
		point[index] = ratio; index++;
		point[index] = amp; index++;
		point[index] = value; index++;
		point[index] = r; index++;
		point[index] = g; index++;
		point[index] = b; index++;
		point[index] = a; index++;
		point[index] = 1.0f; index++;
		point[index] = 0.0f; index++;
	}
	glGenBuffers(1, &m_VBORandRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VBORandRect) * size, point, GL_STATIC_DRAW);
	vertex_count_array = count * verticesPerQuad;
}

void Renderer::CreateProxyGeometry()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 32;
	int pointCountY = 32;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX*pointCountY * 2];
	float* vertices = new float[(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3];
	GridCount = (pointCountX - 1)*(pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y*pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y*pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1)*pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_VBO_GridMesh);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_GridMesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(pointCountX - 1)*(pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}

void Renderer::Lecture3()
{
	glUseProgram(m_SolidRectShader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_GridMesh);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, GridCount*3);

	glDisableVertexAttribArray(0);
}

void Renderer::Lecture4()
{
	glUseProgram(m_SimpleVelShader);

	GLuint uTime = glGetUniformLocation(m_SimpleVelShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.001;

	GLuint aPos = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint aVel = glGetAttribLocation(m_SimpleVelShader, "a_Vel");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aVel);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(float)*3));

	glDrawArrays(GL_TRIANGLES, 0, m_count * 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aVel);
}

void Renderer::Lecture5()
{
	glUseProgram(m_SimpleVelShader);

	GLuint uTime = glGetUniformLocation(m_SimpleVelShader, "u_Time");
	//GLuint uRepeat = glGetUniformLocation(m_SimpleVelShader, "u_Repeat");
	glUniform1f(uTime, g_Time);
	//glUniform1d(uRepeat);
	g_Time += 0.001;

	GLuint aPos = glGetAttribLocation(m_SimpleVelShader, "a_Position");
	GLuint aVel = glGetAttribLocation(m_SimpleVelShader, "a_Vel");
	GLuint aStartLife = glGetAttribLocation(m_SimpleVelShader, "a_StartLife");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aVel);
	glEnableVertexAttribArray(aStartLife);
	// x, y, z, vx, vy, vz, sT, lT, x2, y2,...
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aStartLife, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (GLvoid*)(sizeof(float) * 6));

	glDrawArrays(GL_TRIANGLES, 0, vertex_count_array);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aVel);
	glDisableVertexAttribArray(aStartLife);
}

void Renderer::Lecture6()
{
	glUseProgram(m_SimpleVelShader2);

	GLuint Shader = m_SimpleVelShader2;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint uTime = glGetUniformLocation(Shader, "u_Time");
	//GLuint uRepeat = glGetUniformLocation(Shader, "u_Repeat");
	glUniform1f(uTime, g_Time);
	//g_Time += ((float)(rand() / (float)RAND_MAX) - 0.5f)*0.0001f; cute
	g_Time += 0.0002;

	GLuint uniformTex = glGetUniformLocation(Shader, "uTexSampler");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	GLuint aPos = glGetAttribLocation(Shader, "a_Position");
	GLuint aVel = glGetAttribLocation(Shader, "a_Vel");
	GLuint aStartLifeRatioAmp = glGetAttribLocation(Shader, "a_StartLifeRatioAmp");
	GLuint aValue = glGetAttribLocation(Shader, "a_Value");
	GLuint aColor = glGetAttribLocation(Shader, "a_Color");
	GLuint aTexPos = glGetAttribLocation(Shader, "a_TexPos");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aVel);
	glEnableVertexAttribArray(aStartLifeRatioAmp);
	glEnableVertexAttribArray(aValue);
	glEnableVertexAttribArray(aColor);
	glEnableVertexAttribArray(aTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORandRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 17, 0);
	glVertexAttribPointer(aVel, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 17, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aStartLifeRatioAmp, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 17, (GLvoid*)(sizeof(float)*6));
	glVertexAttribPointer(aValue, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 17, (GLvoid*)(sizeof(float) * 10));
	glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 17, (GLvoid*)(sizeof(float) * 11));
	glVertexAttribPointer(aTexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 17, (GLvoid*)(sizeof(float) * 15));

	glDrawArrays(GL_TRIANGLES, 0, vertex_count_array);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aVel);
	glDisableVertexAttribArray(aStartLifeRatioAmp);
	glDisableVertexAttribArray(aValue);
	glDisableVertexAttribArray(aColor);
	glDisableVertexAttribArray(aTexPos);

	glDisable(GL_BLEND);
}

void Renderer::Solid7()
{
	float size = 0.5f;

	int verticesPerQuad = 6;
	int floatsPerVertex = 3 + 4 + 2;
	int Allsize = verticesPerQuad * floatsPerVertex;

	int index = 0;

	float r = 1;
	float g = 1;
	float b = 1;
	float a = 1.f;

	float *rect = new float[Allsize];

	rect[index] = -size; ++index;
	rect[index] = -size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 0; ++index;
	rect[index] = 0; ++index;

	rect[index] = -size; ++index;
	rect[index] = size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 0; ++index;
	rect[index] = 1; ++index;

	rect[index] = size; ++index;
	rect[index] = size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 1; ++index;
	rect[index] = 1; ++index;

	rect[index] = -size; ++index;
	rect[index] = -size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 0; ++index;
	rect[index] = 0; ++index;

	rect[index] = size; ++index;
	rect[index] = size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 1; ++index;
	rect[index] = 1; ++index;

	rect[index] = size; ++index;
	rect[index] = -size; ++index;
	rect[index] = 0; ++index;
	rect[index] = r; ++index;
	rect[index] = g; ++index;
	rect[index] = b; ++index;
	rect[index] = a; ++index;
	rect[index] = 1; ++index;
	rect[index] = 0;

	/*
	float rect[]=
	{
		-size, -size, 0, r, g, b, a,
		-size, size, 0, r, g, b, a,
		size, size, 0, r, g, b, a,
		-size, -size, 0, r, g, b, a,
		size, size, 0, r, g, b, a,
		size, -size, 0, r, g, b, a,
	};
	//*/

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VBORect) * Allsize, rect, GL_STATIC_DRAW);
}

void Renderer::Lecture7()
{
	glUseProgram(m_SolidRectShader);

	GLfloat points[] = { 0.0, 0.0, -0.5, -0.5, -0.3, -0.3, 0.1, 0.1, 0.3, 0.3 };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint uPoint = glGetUniformLocation(m_SolidRectShader, "u_Points");
	glUniform2fv(uPoint, 5, points);

	GLuint uTime = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.002;

	GLuint aPos = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLuint aColor = glGetAttribLocation(m_SolidRectShader, "a_Color");
	GLuint aUV = glGetAttribLocation(m_SolidRectShader, "a_Uv");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aColor);
	glEnableVertexAttribArray(aUV);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);

	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float) * 7));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aColor);
	glDisableVertexAttribArray(aUV);

	glDisable(GL_BLEND);
}

void Renderer::Fillfloat(float n)
{
	glUseProgram(m_SolidRectShader2);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint aPos = glGetAttribLocation(m_SolidRectShader2, "a_Position");

	glEnableVertexAttribArray(aPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect2);

	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(aPos);

	glDisable(GL_BLEND);
}

void Renderer::DrawTextRect()//GLuint tex)
{
	GLuint shader = m_TextureRectShader;

	glUseProgram(shader);

	GLuint uTime = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uTime, g_Time);
	g_Time += 0.2;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_CheckBoard);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_Texture2);
	//glActiveTexture(GL_TEXTURE3);
	//glBindTexture(GL_TEXTURE_2D, m_NumTexture);

	int uniformTex = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(uniformTex, 0);					// 0 , glTex의 0번을 쓰겠다.
	int uniformTex1 = glGetUniformLocation(shader, "u_TexSampler1");
	glUniform1i(uniformTex1, 1);
	int uniformTex2 = glGetUniformLocation(shader, "u_TexSampler2");
	glUniform1i(uniformTex2, 2);
	//int uniformTex3 = glGetUniformLocation(shader, "u_TexSampler3");
	//glUniform1i(uniformTex3, 3);

	GLuint aPos = glGetAttribLocation(shader, "a_Position");
	GLuint aTex = glGetAttribLocation(shader, "a_Tex");

	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aTex);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextRect);

	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aTex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aTex);
}

void Renderer::DrawNumber(int * num)
{
	GLuint shader = m_DrawNumShader;

	glUseProgram(shader);

	GLuint uNumber = glGetUniformLocation(shader, "u_Number");
	glUniform1iv(uNumber, 3, num);

	
	// Vertex Settings
	GLuint aPos = glGetAttribLocation(shader, "a_Position");
	GLuint aTex = glGetAttribLocation(shader, "a_Tex");
	glEnableVertexAttribArray(aPos);
	glEnableVertexAttribArray(aTex);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextRect);
	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(aTex, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	// Texture Settings
	GLuint uniformTex = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_NumTexture);

	// Draw here
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Restore to Default
	glDisableVertexAttribArray(aPos);
	glDisableVertexAttribArray(aTex);
}