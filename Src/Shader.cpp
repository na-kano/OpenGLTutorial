/*
*@file Shader.cpp
*/

#include "Shader.h"
#include <vector>
#include <iostream>
#include <fstream>


/*
*シェーダーに関する機能を格納する名前空間
*/
namespace Shader {

	/*
	*シェーダー・プログラムをコンパイルする
	*@param type シェーダーの種類
	*@param string シェーダー・プログラムへのポインタ
	*
	*@retval 0より大きい 作成したシェーダー・オブジェクト
	*@retval 0			 シェーダー・オブジェクトの作成に失敗
	*/

	GLuint Compile(GLenum type,const GLchar* string) {
		if (!string)
		{
			return 0;
		}

		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &string, nullptr);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		//コンパイルに失敗した場合、原因をコンソールに出力して0を返す
		if (!compiled){
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				std::vector<char> buf;
				buf.resize(infoLen);
				if (static_cast<int>(buf.size()) >= infoLen){
					glGetShaderInfoLog(shader, infoLen, NULL, buf.data());
					std::wcerr << "ERROR: シェーダーのコンパイルに失敗。\n" << buf.data() << std::endl;
				}
			}
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	/*
	*プログラム・オブジェクトを作成する
	*
	*@param vsCode 頂点シェーダー・プログラムへのポインタ
	*@param fsCode フラグメントシェーダー・プログラムへのポインタ
	*
	*@retval 0より大きい 作成したプログラム・オブジェクト
	*@retval 0			 プログラム・オブジェクトの作成に失敗
	*/

	GLuint Build(const GLchar* vsCode, const GLchar* fsCode) {
		GLuint vs = Compile(GL_VERTEX_SHADER, vsCode);
		GLuint fs = Compile(GL_FRAGMENT_SHADER, fsCode);
		if (!vs || !fs)
		{
			return 0;
		}
		GLuint program = glCreateProgram();
		glAttachShader(program, fs);
		glDeleteShader(fs);
		glAttachShader(program, vs);
		glDeleteShader(vs);
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE)
		{
			GLint infoLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				std::vector<char> buf;
				buf.resize(infoLen);
				if (static_cast<int>(buf.size()) >= infoLen)
				{
					glGetProgramInfoLog(program, infoLen, NULL, buf.data());
					std::cerr << "ERROR: シェーダーのリンクに失敗。\n" << buf.data() << std::endl;
				}
			}
			glDeleteProgram(program);
			return 0;
		}
		return program;
	}

	/*
	*ファイルを読み込む
	*
	*@param path 読み込むファイル名
	*
	*@return 読み込んだデータ
	*/

	std::vector<GLchar> ReadFile(const char* path) {
		std::basic_ifstream<GLchar> ifs;
		ifs.open(path, std::ios_base::binary);
		if (!ifs.is_open())
		{
			std::cerr << "ERROR: " << path << " を開けません。\n";
			return {};
		}
		ifs.seekg(0, std::ios_base::end);
		const size_t lengh = (size_t)ifs.tellg();
		ifs.seekg(0, std::ios_base::beg);
		std::vector<GLchar> buf(lengh);
		ifs.read(buf.data(), lengh);
		buf.push_back('\0');
		return buf;
	}

	/*
	*ファイルからプログラム・オブジェクトを作成する
	*
	*@param vsPath　頂点シェーダー・ファイル名
	*@param fsPath　フラグメントシェーダー・ファイル名
	*
	*@return 作成したプログラム・オブジェクト
	*/

	GLuint BuildFromFile(const char* vsPath, const char* fsPath) {
		const std::vector<GLchar> vsCode = ReadFile(vsPath);
		const std::vector<GLchar> fsCode = ReadFile(fsPath);
		return Build(vsCode.data(), fsCode.data());
	}

} //Shader namespace