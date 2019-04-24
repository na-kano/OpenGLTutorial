/*
*@file Shader.cpp
*/

#include "Shader.h"
#include <vector>
#include <iostream>
#include <fstream>


/*
*�V�F�[�_�[�Ɋւ���@�\���i�[���閼�O���
*/
namespace Shader {

	/*
	*�V�F�[�_�[�E�v���O�������R���p�C������
	*@param type �V�F�[�_�[�̎��
	*@param string �V�F�[�_�[�E�v���O�����ւ̃|�C���^
	*
	*@retval 0���傫�� �쐬�����V�F�[�_�[�E�I�u�W�F�N�g
	*@retval 0			 �V�F�[�_�[�E�I�u�W�F�N�g�̍쐬�Ɏ��s
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
		//�R���p�C���Ɏ��s�����ꍇ�A�������R���\�[���ɏo�͂���0��Ԃ�
		if (!compiled){
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				std::vector<char> buf;
				buf.resize(infoLen);
				if (static_cast<int>(buf.size()) >= infoLen){
					glGetShaderInfoLog(shader, infoLen, NULL, buf.data());
					std::wcerr << "ERROR: �V�F�[�_�[�̃R���p�C���Ɏ��s�B\n" << buf.data() << std::endl;
				}
			}
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	/*
	*�v���O�����E�I�u�W�F�N�g���쐬����
	*
	*@param vsCode ���_�V�F�[�_�[�E�v���O�����ւ̃|�C���^
	*@param fsCode �t���O�����g�V�F�[�_�[�E�v���O�����ւ̃|�C���^
	*
	*@retval 0���傫�� �쐬�����v���O�����E�I�u�W�F�N�g
	*@retval 0			 �v���O�����E�I�u�W�F�N�g�̍쐬�Ɏ��s
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
					std::cerr << "ERROR: �V�F�[�_�[�̃����N�Ɏ��s�B\n" << buf.data() << std::endl;
				}
			}
			glDeleteProgram(program);
			return 0;
		}
		return program;
	}

	/*
	*�t�@�C����ǂݍ���
	*
	*@param path �ǂݍ��ރt�@�C����
	*
	*@return �ǂݍ��񂾃f�[�^
	*/

	std::vector<GLchar> ReadFile(const char* path) {
		std::basic_ifstream<GLchar> ifs;
		ifs.open(path, std::ios_base::binary);
		if (!ifs.is_open())
		{
			std::cerr << "ERROR: " << path << " ���J���܂���B\n";
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
	*�t�@�C������v���O�����E�I�u�W�F�N�g���쐬����
	*
	*@param vsPath�@���_�V�F�[�_�[�E�t�@�C����
	*@param fsPath�@�t���O�����g�V�F�[�_�[�E�t�@�C����
	*
	*@return �쐬�����v���O�����E�I�u�W�F�N�g
	*/

	GLuint BuildFromFile(const char* vsPath, const char* fsPath) {
		const std::vector<GLchar> vsCode = ReadFile(vsPath);
		const std::vector<GLchar> fsCode = ReadFile(fsPath);
		return Build(vsCode.data(), fsCode.data());
	}

} //Shader namespace