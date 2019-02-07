// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h" //ayuda a que compile mas rapido
#include <stdio.h> // esta cosa para librerias incluidas en c#
#include <stdlib.h>

#define GLEW_STATIC 

#include "GL/glew.h" //comillas para librerias personalizadas
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std; //aqui esta lo de c++

//Declaramos apuntador de ventana
GLFWwindow *window;
float posicionXTriangulo = 0;
float posicionYTriangulo = 0;
float angulo = 0;
enum Direccion {Izquierda,Derecha,Arriba,Abajo};
Direccion direccionHorizontalTriangulo=Direccion::Izquierda; //significa que es un miembro estatico
Direccion direccionVerticalTriangulo = Direccion::Arriba;

double seconds = glfwGetTime();
float xTriangulo = 0.0f;
float yTriangulo = 0.0f;
float speed = 0.05f;


void dibujarTriangulo() {

	//Utilizar matriz identidad (una matriz nueva)
	glPushMatrix();
	glTranslatef(xTriangulo, yTriangulo, 0.0f);

	

	//dibujar vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glEnd();

	//soltar la matriz
	glPopMatrix();
}
void moverTriangulo(){

	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if(estadoTeclaDerecha == GLFW_PRESS) {
		xTriangulo += speed;
	}
	if (estadoTeclaIzquierda == GLFW_PRESS) {
		xTriangulo -= speed;
	}if (estadoTeclaArriba == GLFW_PRESS) {
		yTriangulo += speed;
	}if (estadoTeclaAbajo == GLFW_PRESS) {
		yTriangulo -= speed;
	}
}
void dibujar() {
	dibujarTriangulo();
}


void actualizar() {
	moverTriangulo();
}

//Estructura del callback
void teclado_callback(GLFWwindow *window,int key,int scancode,int action,int mods) {

	//se dice que tecla fue la que disparo el evento, en este caso la flecha de la derecha
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo += speed;
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		xTriangulo -= speed;
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo += speed;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		yTriangulo -= speed;
	}
}

int main()
{


	//Si no se pudo iniciar glfw terminamos ejecución

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo iniciar GLFW entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido e contexto activamos funciones modernas
	glewExperimental = true; //permite trabajar con gpu y cpu al mismo tiempo,solo va a funcionar si ya esta establecido el contexto

	//en caso de haber error se guarda en la variable errorGlew que es tipo GLenum 
	GLenum errorGlew = glewInit(); //inicializa glew

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	//se obtiene la version de OpenGL y se imprime
	const GLubyte *versionGL = glGetString(GL_VERSION); 
	cout << "Version OpenGL: " << versionGL; 

	//se asigna la funcion para que se reciban los eventos del teclado y se realice la funcion
	//glfwSetKeyCallback(window, teclado_callback);

	//ciclo de dibujo (draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768); //dice donde va a empezar a renderear y donde va a terminar
		//Establecer color de borrado
		glClearColor(1, 0,0, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffer
		glfwSwapBuffers(window); //cambia el buffer de la pantalla por el otro que se lleno
		//reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window); //terminamos los procesos y eliminamos la ventana
	glfwTerminate();
	return 0;
}



