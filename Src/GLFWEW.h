/*
*@file GLFWEW.h
*/

#ifndef GLFWEW_H_INCLUDED
#define GLFWEW_H_INCLUDED
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GLFWEW {

	/*
	*GLFW��GLEW�̃��b�p�[�N���X
	*/
	
	class Window
	{
	public:
		static Window& Intance();
		bool Init(int w, int h, const char* title);
		bool ShoudClose() const;
		void SwapBuffers() const;

		void InitTimer();
		void UpdateTimer();
		double DeltaTime() const;
	
		bool IsKeyPressed(int key) const;


	private:
		Window();	//�f�t�H���g�R���X�g���N�^(�ϐ����쐬�����Ƃ�)
		~Window();	//�f�X�g���N�^(�ϐ����폜�����Ƃ�)
		Window(const Window&) = delete;	//�R�s�[�R���X�g���N�^(�ϐ�������������Ƃ�)
		Window& operator = (const Window&) = delete;	//�R�s�[������Z�q
		bool isGLFWInitialized = false;
		bool isInitialized = false;
		GLFWwindow* window = nullptr;
		double previousTime = 0;
		double deltaTime = 0;

	};

}	// namespace GLFWEW

#endif // !GLFWEW_H_INCLUDED
