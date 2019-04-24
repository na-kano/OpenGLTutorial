/**
*@file Main.cpp
*/

#include "GLFWEW.h"
#include "Shader.h"
#include "Texture.h"
#include "glm\gtc\matrix_transform.hpp"
#include<iostream>
#include<vector>

//2Dベクトル型
struct Vector2
{
	float x, y;
};

//3Dベクトル型
struct Vector3
{
	float x, y, z;
};

//RGBAカラー型
struct Color
{
	float r, g, b, a;
};

//頂点データ型
struct Vertex
{
	Vector3 position; ///< 座標
	Color color; ///< 色
	Vector2 texCoord; ///<テクスチャ座標
	Vector3 normal;///<法線
};

//頂点データ
const Vertex vertices[] = {

	//木
	{ {  0.00f, 5.0f, 0.00f },{ 0.5f,0.8f,0.3f,1.0f },{0.0f,1.0f},{0.00f,1.00f,0.00f} },
	{ {  0.00f, 1.5f,-1.10f },{ 0.1f,0.3f,0.0f,1.0f },{0.0f,1.0f},{0.00f,-0.49f,-0.87f} },
	{ { -0.75f, 1.5f, 0.40f },{ 0.1f,0.3f,0.0f,1.0f },{0.0f,1.0f},{-0.76f,-0.49f,0.43f} },
	{ {  0.75f, 1.5f, 0.40f },{ 0.1f,0.3f,0.0f,1.0f },{0.0f,1.0f},{0.76f,-0.49f,0.43f} },
	{ {  0.00f, 4.0f, 0.00f },{ 0.2f,0.1f,0.0f,1.0f },{0.0f,1.0f},{0.00f,1.00f,0.00f} },
	{ {  0.00f, 0.0f,-0.37f },{ 0.5f,0.3f,0.2f,1.0f },{0.0f,1.0f},{0.00f,-0.49f,-0.87f} },
	{ { -0.25f, 0.0f, 0.13f },{ 0.5f,0.3f,0.2f,1.0f },{0.0f,1.0f},{-0.76f,-0.49f,0.43f} },
	{ {  0.25f, 0.0f, 0.13f },{ 0.5f,0.3f,0.2f,1.0f },{0.0f,1.0f},{0.76f,-0.49f,0.43f} },

	//家
	{ {  2.8f,0.0f,3.0f },{ 0.4f,0.3f,0.2f,1.0f },{1.000f,0.00f}},//0
	{ {  3.0f,4.0f,3.0f },{ 0.6f,0.5f,0.3f,1.0f },{1.000f,0.69f}},//1
	{ {  0.0f,6.0f,3.0f },{ 0.5f,0.4f,0.2f,1.0f },{0.875f,1.00f}},//2
	{ { -3.0f,4.0f,3.0f },{ 0.6f,0.5f,0.3f,1.0f },{0.750f,0.69f}},//3
	{ { -2.8f,0.0f,3.0f },{ 0.4f,0.3f,0.2f,1.0f },{0.750f,0.00f}},//4

	{ { -2.8f,0.0f,-3.0f },{ 0.4f,0.3f,0.2f,1.0f },{0.500f,0.00f}},//5
	{ { -3.0f,4.0f,-3.0f },{ 0.6f,0.5f,0.3f,1.0f },{0.500f,0.69f}},//6
	{ {  0.0f,6.0f,-3.0f },{ 0.5f,0.4f,0.2f,1.0f },{0.375f,1.00f}},//7
	{ {  3.0f,4.0f,-3.0f },{ 0.6f,0.5f,0.3f,1.0f },{0.250f,0.69f}},//8
	{ {  2.8f,0.0f,-3.0f },{ 0.4f,0.3f,0.2f,1.0f },{0.250f,0.00f}},//9

	{ {  2.8f,0.0f, 3.0f },{ 0.4f,0.3f,0.2f,1.0f },{0.000f,0.00f}},//10
	{ {  3.0f,4.0f, 3.0f },{ 0.6f,0.5f,0.3f,1.0f },{0.000f,0.69f}},//11
	{ {  0.0f,6.0f, 3.0f },{ 1.0f,1.0f,1.0f,1.0f },{0.750f,1.00f}},//12
	{ {  0.0f,6.0f,-3.0f },{ 1.0f,1.0f,1.0f,1.0f },{0.500f,1.00f}},//13
	{ {  0.0f,6.0f,-3.0f },{ 1.0f,1.0f,1.0f,1.0f },{0.250f,1.00f}},//14
	{ {  0.0f,6.0f, 3.0f },{ 1.0f,1.0f,1.0f,1.0f },{0.000f,1.00f}},//15

	//地面
	{ {-10.0f,0.0f,10.0f},{0.75f,0.75f,0.25f,0.75f},{},{0.0f,1.0f,0.0f} },
	{ {-10.0f,0.0f,-10.0f},{ 0.75f,0.75f,0.25f,0.75f },{},{ 0.0f,1.0f,0.0f } },
	{ {10.0f,0.0f,-10.0f},{ 0.75f,0.75f,0.25f,0.75f },{}, { 0.0f,1.0f,0.0f } },
	{ {10.0f,0.0f,10.0f},{ 0.75f,0.75f,0.25f,0.75f },{},{ 0.0f,1.0f,0.0f } },

	//岩
	{ { 5.0f,0.0f,0.0f },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 5.0f,0.5f,0.0f },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 4.5f,0.5f,0.0f },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 4.5f,0.0f,0.0f },{ 0.2f,0.2f,0.2f,1.0f },{} },

	{ { 4.5f,0.0f,-0.5f },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 5.00f,0.0f,-0.5 },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 5.00f,0.5f,-0.5 },{ 0.2f,0.2f,0.2f,1.0f },{} },
	{ { 4.5f,0.5f,-0.5f },{ 0.2f,0.2f,0.2f,1.0f },{} },

	
};

//インデックスデータ
const GLushort indices[] = {

	//木
	0,1,2,0,2,3,0,3,1,1,2,3,
	4,5,6,4,6,7,4,7,5,

	//家(中央)
	0,1,3,3,4,0,1,2,3,
	5,6,8,8,9,5,6,7,8,
	9,8,11,11,10,9,
	4,3,6,6,5,4,
	3,12,13,13,6,3,
	8,14,15,15,11,8,

	//地面
	0,3,1,3,2,1,

	//岩

	0,1,2,2,3,0,
	5,6,7,7,4,5,
	5,6,1,1,0,5,
	4,7,2,2,3,4,
	1,6,7,7,2,1,
	0,5,4,4,3,0,

};

/*
*描画データ
*/

struct Mesh
{
	GLenum mode;///プリミティブの種類
	GLsizei count; ///描画するインデックス数
	const GLvoid* indices;///描画開始インデックスのバイトオフセット
	GLint baseVertex; ///インデックス0番とみなされる頂点配列内の位置
};

/*
*描画データリスト
*/

const Mesh meshList[] = {
	{GL_TRIANGLES,21,(const GLvoid*)0,0},//木
	{GL_TRIANGLES,42,(const GLvoid*)(21 * sizeof(GLshort)),8},//家
	{GL_TRIANGLES,6,(const GLvoid*)(63 * sizeof(GLshort)),24},//地面
	{GL_TRIANGLES,36,(const GLvoid*)(69 * sizeof(GLshort)),28},//岩
};

/*
*Vertex Buffer Object を作成する
*
*@param size 頂点データのサイズ
*@param data 頂点データへのポインタ
*
*@return 作成したVBO
*/

GLuint CreateVBO(GLsizeiptr size, const GLvoid* data) {
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vbo;
}

/*
*Index Buffer Object を作成する
*
*@param size インデックスデータのサイズ
*@param data インデックスデータへのポインタ
*
*@return 作成したIBO
*/

GLuint CreateIBO(GLsizeiptr size, const GLvoid*data) {
	GLuint ibo = 0;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return ibo;
}


/*
*Vertex Array Objectを作成する
*
*@param vbo VAOに関連付けられるVBO
*@param ibo VAOに関連付けられるIBO
*
*@return 作成したVAO
*/

GLuint CreateVAO(GLuint vbo,GLuint ibo) {
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(Vertex::position) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, sizeof(Vertex::color) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, sizeof(Vertex::texCoord) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, texCoord)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, sizeof(Vertex::texCoord) / sizeof(float),
		GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(Vertex, normal)));
	glBindVertexArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	return vao;
}



/**
*エントリーポイント
*/

int main()
{
	
	GLFWEW::Window& window = GLFWEW::Window::Intance();
	if (!window.Init(800,600,"OpenGL Tutorial"))
	{
		return 1;
	}

	const GLuint vbo = CreateVBO(sizeof(vertices), vertices);
	const GLuint ibo = CreateIBO(sizeof(indices), indices);
	const GLuint vao = CreateVAO(vbo, ibo);
	const GLuint shaderProgram =
		Shader::BuildFromFile("Res/Simple.vert", "Res/Simple.frag");
	const GLuint progLighting =
		Shader::BuildFromFile("Res/VertexLighting.vert", "Res/Simple.frag");
	if (!vbo || !ibo || !vao || !shaderProgram || !progLighting)
	{
		return 1;
	}

	//uniformの変数の位置を取得
	const GLint matMVPLoc = glGetUniformLocation(shaderProgram, "matMVP");
	if (matMVPLoc < 0)
	{
		std::cerr << "ERROR: uniform変数'matMVP'が見つかりません。\n";
		return 1;
	}
	glUseProgram(shaderProgram);
	const GLint texColorLoc = glGetUniformLocation(shaderProgram, "texColor");
	if (texColorLoc >= 0)
	{
		glUniform1i(texColorLoc, 0);
	}

	const GLint locMatMVP = glGetUniformLocation(progLighting, "matMVP");
	const GLint locAmbLightCol =
		glGetUniformLocation(progLighting, "ambientLight.color");
	const GLint locDirLightDir =
		glGetUniformLocation(progLighting, "directionalLight.direction");
	const GLint locDirLightCol =
		glGetUniformLocation(progLighting, "directionalLight.color");
	const GLint locPointLightPos =
		glGetUniformLocation(progLighting, "pointLight.position");
	const GLint locPointLightCol =
		glGetUniformLocation(progLighting, "pointLight.color");

	if (locDirLightDir < 0 || locDirLightCol < 0 || locAmbLightCol < 0 ||
		locPointLightPos <0 || locPointLightCol < 0)
	{
		std::cerr << "ERROR: uniform変数の位置を取得できません。\n";
		return 1;
	}
	{
		glUseProgram(progLighting);
		const GLint locTexCol = glGetUniformLocation(progLighting, "texColor");
		if (locTexCol >= 0)
		{
			glUniform1i(locTexCol, 0);
		}
	}
	glUseProgram(0);

	//テクスチャを作成する
	const int imageWidth = 8;	//画像の幅
	const int imageHeight = 8;	//画像の高さ
	const uint32_t B = 0xff'00'00'00;//黒
	const uint32_t W = 0xff'ff'ff'ff;//白
	const uint32_t imageData[imageWidth*imageHeight] = {
		W,W,W,B,B,W,W,W,
		W,W,W,B,B,W,W,W,
		W,W,W,B,B,W,W,W,
		B,B,B,B,B,B,B,B,
		B,B,B,B,B,B,B,B,
		W,W,W,B,B,W,W,W,
		W,W,W,B,B,W,W,W,
		W,W,W,B,B,W,W,W,
	};

	GLuint texId = Texture::CreateImage2D(imageWidth, imageHeight, imageData,GL_RGBA,GL_UNSIGNED_BYTE);
	GLuint texHouse = Texture::LoadImage2D("Res/House.tga");

	//ライトの設定
	const glm::vec3 ambLightCol = glm::vec3(0.15f, 0.05f, 0.15f);//環境光の色
	const glm::vec3 dirLightDir = glm::normalize(glm::vec3(1, -1, -1)); //指向性ライトの方向
	const glm::vec3 dirLightCol = glm::vec3(1.0f, 0.70f, 0.70f);//指向性ライトの色

	glm::vec3 pointLightPos[8] = {};
	glm::vec3 pointLightCol[8] = {};
	pointLightPos[0] = glm::vec3(5, 4, 0);
	pointLightCol[0] = glm::vec3(1.0f, 0.8f, 0.4f) * 100.0f;

	//メインループ
	while (!window.ShoudClose())
	{
		while (!window.ShoudClose())
		{
			window.UpdateTimer();
			const float deltaTime = (float)window.DeltaTime();
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//視点を設定する
		const glm::vec3 viewPos(20, 30, 30);

		glUseProgram(progLighting);

		//座標変換行列を作成してシェーダーに転送する
		const glm::mat4x4 matProj =
			glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
		const glm::mat4x4 matView =
			glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		//ライトをGPUメモリに転送する
		glUniform3fv(locAmbLightCol, 1, &ambLightCol.x);
		glUniform3fv(locDirLightDir, 1, &dirLightDir.x);
		glUniform3fv(locDirLightCol, 1, &dirLightCol.x);
		glUniform3fv(locPointLightCol, 8, &pointLightCol[0].x);

		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texId);
		
		const float treeCount = 10; //木の本数
		const float radius = 8;//木を植える円の半径
		for (float i = 0; i < treeCount; ++i) {
			const float theta = 3.14f * 2 / treeCount * i;
			const float x = std::cos(theta) * radius;
			const float z = std::sin(theta)* radius;
			const glm::mat4x4 matModelT = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));
			const glm::mat4x4 matModelR =
				glm::rotate(glm::mat4(1), theta * 5, glm::vec3(0, 1, 0));
			const glm::mat4x4 matMVP = matProj * matView*matModelT*matModelR;
			glUniformMatrix4fv(locMatMVP, 1, GL_FALSE, &matMVP[0][0]);

			//指向性ライトの向きをモデル座標系に変換してGPUメモリに転送する
			const glm::vec3 dirLightDirOnModel =
				glm::inverse(glm::mat3(matModelR))*dirLightDir;
			glUniform3fv(locDirLightDir, 1, &dirLightDirOnModel.x);

			//ポイント・ライトの位置をモデル座標系に変換してGPUメモリに転送する
			const glm::mat4 matInvModel = glm::inverse(matModelT * matModelR);
			glm::vec3 pointLightPosOnModel[8];
			for (int i = 0; i < 8; ++i)
			{
				pointLightPosOnModel[i] = matInvModel * glm::vec4(pointLightPos[i], 1);
			}
			glUniform3fv(locPointLightPos, 8, &pointLightPosOnModel[0].x);

			glDrawElementsBaseVertex(meshList[0].mode, meshList[0].count,
				GL_UNSIGNED_SHORT, meshList[0].indices, meshList[0].baseVertex);
		}

		//ポイント・ライトの位置が分かるように適当なモデルを表示
		{
			//0番のポイント・ライトを移動する
			const float speed = 10.0f * deltaTime;
			if (window.IsKeyPressed(GLFW_KEY_A))
			{
				pointLightPos[0].x -= speed;
			}
			else if (window.IsKeyPressed(GLFW_KEY_D))
			{
				pointLightPos[0].x += speed;
			}

			if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
			{
				if (window.IsKeyPressed(GLFW_KEY_W))
				{
					pointLightPos[0].y += speed;
				}
				else if (window.IsKeyPressed(GLFW_KEY_S))
				{
					pointLightPos[0].y -= speed;
				}
			}
			else
			{
				if (window.IsKeyPressed(GLFW_KEY_W))
				{
					pointLightPos[0].z -= speed;
				}
				else if (window.IsKeyPressed(GLFW_KEY_S))
				{
					pointLightPos[0].z += speed;
				}
			}


			//モデルのY軸回転角を更新
			static float angleY = 0;
			angleY += glm::radians(1.0f);
			if (angleY > glm::radians(360.0f))
			{
				angleY -= glm::radians(360.0f);
			}

			//ライトの位置に木のモデルを表示
			glUseProgram(shaderProgram);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texId);
			for (int i = 0; i < 8; ++i)
			{
				const glm::mat4 matModelT = glm::translate(glm::mat4(1), pointLightPos[i]);
				const glm::mat4 matModelR = glm::rotate(glm::mat4(1), angleY, glm::vec3(0, 1, 0));
				const glm::mat4 matModelS = glm::scale(glm::mat4(1), glm::vec3(1, -0.25f, 1));
				const glm::mat4 matMVP = matProj * matView * matModelT * matModelR * matModelS;
				glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
				glDrawElementsBaseVertex(meshList[0].mode, meshList[0].count,
					GL_UNSIGNED_SHORT,meshList[0].indices,meshList[0].baseVertex);
			}
		}

		glUseProgram(shaderProgram);
		
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texHouse);

			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(1,0,1));
			const glm::mat4x4 matMVP = matProj * matView*matModel;
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			glDrawElementsBaseVertex(meshList[1].mode, meshList[1].count,
				GL_UNSIGNED_SHORT, meshList[1].indices, meshList[1].baseVertex);
		}
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texHouse);

			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(0,0,0));
			const glm::mat4x4 matMVP = matProj * matView*matModel;
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);

			const glm::vec3 dirLightDirOnModel =
				glm::inverse(glm::mat3(matModel))*dirLightDir;
			glUniform3fv(locDirLightDir, 1, &dirLightDirOnModel.x);

			glDrawElementsBaseVertex(meshList[2].mode, meshList[2].count,
				GL_UNSIGNED_SHORT, meshList[2].indices, meshList[2].baseVertex);
		}
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texHouse);

			const glm::mat4x4 matModel = glm::translate(glm::mat4(1), glm::vec3(0, 0, 0));
			const glm::mat4x4 matMVP = matProj * matView*matModel;
			glUniformMatrix4fv(matMVPLoc, 1, GL_FALSE, &matMVP[0][0]);
			glDrawElementsBaseVertex(meshList[3].mode, meshList[3].count,
				GL_UNSIGNED_SHORT, meshList[3].indices, meshList[3].baseVertex);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		window.SwapBuffers();
	}

	glDeleteTextures(1, &texHouse);
	glDeleteTextures(1, &texId);
	glDeleteProgram(progLighting);
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);


	return 0;
}