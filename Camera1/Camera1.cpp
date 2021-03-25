#pragma once
#include <iostream>

//glew
#include <GL/glew.h>

//sfml
#include <SFML/Window.hpp>

//glm
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/geometric.hpp"
#include "glm/mat2x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_access.hpp"
#include "glm/trigonometric.hpp"
#include "math4.h"
#include "vec3.h"

// shaders
#include "stb_image.h"
#include "shaderLoader.h"

//class_camera
#include "Class_camera.h"
#include "shader.h"


int main() {
	sf::ContextSettings settings;
	settings.depthBits = 24; // количество битов буффера глубины
	settings.stencilBits = 8; //количество битов буфера трафарета, используется с буфером глубины для ограничения области рендеринга
	settings.majorVersion = 4;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	//sf::VideoMode(ширина, высота, кол-во бидля для цвета на 1 пиксель)
	sf::Window window(sf::VideoMode(800, 600, 24), "First Window",
		sf::Style::Titlebar | sf::Style::Close);

	glewExperimental = GL_TRUE; // включить все современные функции ogl

	if (GLEW_OK != glewInit()) { // включить glew
		std::cout << "Error:: glew not init =(" << std::endl;
		return -1;
	}
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	
	Shader myshader;
	myshader.LoadShader("e4.vs", "e4.fs");

	Class_camera camera;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//EBO позволит использовать одни и те же вершины в разных треугольниках
	unsigned int indices[] = {
		0, 1, 3, // первый треугольник
		1, 2, 3  // второй треугольник
	};
	
	vec3 CubePosition(1.5f,  0.2f, -1.5f);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); // сгенерили id для массивов вершин (у нас это один id)
	glBindVertexArray(VAO); // и связали массив с opengl

	glGenBuffers(1, &VBO); // сгенерили буфер данных размером 1
	glBindBuffer(GL_ARRAY_BUFFER, VBO);// и связали буфер с opengl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // прокинули наш масив вершин в opengl

	//Создали и связали EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // прописали параметры для объекта
	glEnableVertexAttribArray(0); //тк layout у позиции 0

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Загрузка и создание текстуры
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // все последующие GL_TEXTURE_2D-операции теперь будут влиять на данный текстурный объект

	// Установка параметров наложения текстуры
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Установка параметров фильтрации текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Загрузка изображения, создание текстуры и генерирование мипмап-уровней
	int width, height, nrChannels;
	/*
	 * По дефолту текстура перевернута вверх ногами.
	 * Это происходит потому, что OpenGL ожидает, что координата 0.0 на оси Y будет
	 * находиться в нижней части изображения, но изображения обычно имеют 0.0 в верхней
	 * части оси Y. stbi_set_flip_vertically_on_load исправит это!
	 */
	stbi_set_flip_vertically_on_load(true);

	//проверка на загрузку текстуры
	unsigned char* data = stbi_load("1.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// цикл рендера
	bool isGo = true;
	while (isGo) {
		// обработка ивентов от SFML (тут и мышь и клавиши обрабатываются)
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) { // обработка ивентов      pollEvent-Поместите событие в начало очереди событий, если таковая имеется, и верните его.
				//обработка клавиш и обновление позиции камеры
				//обработка мыши и обновления повотора камеры например с помошью углов эйлера
			switch (windowEvent.type) {
			case sf::Event::Closed:
				isGo = false;
				break;
			case sf::Event::KeyPressed:
				camera.KeyboardInput();
				break;
			case sf::Event::MouseMoved:
				camera.MouseInput(window);
				break;
			default:
				break;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //задали цвет отчистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture); //связали текстуру

		myshader.glUseProgramr(); // установили нужную шейдерную программу
		glBindVertexArray(VAO);      // установили нужный массив для рендеринга
		//glDrawArrays(GL_TRIANGLES, 0, 6); //отрисовали
		
		math4 view = camera.GetViewMatrix();
		math4 prj = camera.GetProjectionMatrix();
		
		myshader.glUniGet("view", view);
		myshader.glUniGet("projection", prj);
		
		// calculate the model matrix for each object and pass it to shader before drawing
		math4 model = math4(1.0f); // make sure to initialize matrix to identity matrix first
		model = model.Translate(CubePosition);
		myshader.glUniGet("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//для отрисовки с EBO ипользуется glDrawElements

		window.display();
	}
	window.close();
	return 0;
}