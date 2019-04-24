/*
*@file GLFWEW.cpp
*/

#include "GLFWEW.h"
#include <iostream>

//GLFW��GLEW�����b�v���邽�߂̖��O���
namespace GLFWEW {

	/*
	*GLFW����̃G���[�񍐂���������
	*
	*@param error �G���[�ԍ�
	*@prarm desc �G���[�̓��e
	*/

	void ErrorCallback(int error, const char* desc) {
		std::cerr << "ERROR: " << desc << std::endl;
	}

	/*
	*�V���O���g���C���X�^���X���擾����
	*
	*@return Window�̃V���O���g���C���X�^���X
	*/

	Window& Window::Intance() {
		static Window instance;
		return instance;
	}

	/*
	*�R���X�g���N�^
	*/

	Window::Window() {
	}

	/*
	*�f�X�g���N�^
	*/
	Window::~Window() {
		if (isGLFWInitialized)
		{
			glfwTerminate();
		}
	}

	/*
	*GLFW/GLEW�̏�����
	*
	*@param w �E�B���h�E�̕`��͈͂̕�(�s�N�Z��)
	*@param h �E�B���h�E�̕`��͈͂̍���(�s�N�Z��)
	*@param title �E�B���h�E�^�C�g��(UTF-8��0�I�[������)
	*
	*@retval true ����������
	*@retvel false ���������s
	*/

	bool Window::Init(int w, int h, const char* title) {

		if (isInitialized)
		{
			std::cerr << "ERROR:GLFWEW�͂��łɏ���������Ă��܂��B" << std::endl;
			return false;
		}

		if (!isGLFWInitialized)
		{
			glfwSetErrorCallback(ErrorCallback);
			if (glfwInit() != GL_TRUE)
			{
				return false;
			}
			isGLFWInitialized = true;
		}

		if (!window)
		{
			window = glfwCreateWindow(w, h, title, nullptr, nullptr);
			if (!window)
			{
				return false;
			}
			glfwMakeContextCurrent(window);
		}

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "ERROR:GLEW�̏������Ɏ��s���܂����B" << std::endl;
			return false;
		}


		//OpenGL�̏����R���\�[���E�B���h�E�֏o�͂���
		const GLubyte* renderer = glGetString(GL_RENDERER);
		std::cout << "Renderer:" << renderer << std::endl;
		const GLubyte* version = glGetString(GL_VERSION);
		std::cout << "Version:" << version << std::endl;
		const GLubyte* vendor = glGetString(GL_VENDOR);
		std::cout << "Vendor:" << vendor << std::endl;
		const GLubyte* shading_language_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::cout << "Shading Language Version:" << shading_language_version << std::endl;
		const GLubyte* extensions = glGetString(GL_EXTENSIONS);
		std::cout << "Extentions:" << extensions << std::endl;
	
		isInitialized = true;
		return true;
	}

	/*
	*�E�B���h�E�����ׂ������ׂ�
	*
	*@retval true ����
	*@retval false ���Ȃ�
	*/

	bool Window::ShoudClose() const {
		return glfwWindowShouldClose(window) != 0;
	}

	/*
	*�t�����g�o�b�t�@�ƃo�b�N�A�b�v�o�b�t�@��؂�ւ���
	*/

	void Window::SwapBuffers() const {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	/*
	*�L�[��������Ă��邩���ׂ�
	*
	*@param key ���ׂ����L�[�E�R�[�h
	*
	*@retval true �L�[��������Ă���
	*@retval false �L�[��������Ă��Ȃ�
	*
	*�g�p�ł���L�[�E�R�[�h�̈ꗗ��glfw3.h�ɂ���܂�(�ukeyboard�v�Ō���)
	*/

	bool Window::IsKeyPressed(int key) const 
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	/*
	*�^�C�}�[������������
	*/
	void Window::InitTimer() {
		glfwSetTime(0.0);
		previousTime = 0.0;
		deltaTime = 0.0;
	}


	/*
	*�^�C�}�[���X�V����
	*/
	void Window::UpdateTimer() {
		//�o�ߎ��Ԃ��v��
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		//�o�ߎ��Ԃ������Ȃ肷���Ȃ��悤�ɒ���
		const float upperLimit = 0.25f;//�o�ߎ��ԂƂ��ċ��e�������
		if (deltaTime > upperLimit)
		{
			deltaTime = 0.1f;
		}
	}

	/*
	*�o�ߎ��Ԃ��擾����
	*
	*@return ���O��2���UpdateTimer()�Ăяo���̊ԂɌo�߂�������
	*/
	double Window::DeltaTime() const {
		return deltaTime;
	}
}// namespace GLFWEW