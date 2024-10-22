#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


//Idenficadores de los objetos de la escena
int objId = -1;
int objId2 = -1;

// Variables para la cámara
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f; // Inicialmente apuntamos hacia -Z
float pitch = 0.0f;
float cameraSpeed = 0.05f; // Velocidad de la cámara
float sensitivity = 0.1f;  // Sensibilidad para el giro

//Declaraci�n de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);

//Actualiza la vista de la cámara
void updateCamera() {
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	IGlib::setViewMat(view);
}


int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P1/shader.v9.vert", "../shaders_P1/shader.v9.frag"))
		return -1;

	// Se ajusta la cámara
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); // Inicializamos la vista
	glm::mat4 proj = glm::mat4(1.0f);

	
	
	//Si no se da valor se cojen valores por defecto
	

	view[3].z = -6.f;

	float n = 1.f;
	float f = 10.f;

	proj[0][0] = 1.732f; //proj[0].x
	proj[1][1] = 1.732f; //proj[1].y
	proj[2][2] = (f + n) / (n - f);
	proj[2][3] = -1.f;
	proj[3][2] = 2.f * f * n / (n - f);

	IGlib::setProjMat(proj);
	IGlib::setViewMat(view);
	
	//Creamos el objeto que vamos a visualizar
	objId = IGlib::createObj(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);


	glm::mat4 modelMat = glm::mat4(1.0f);
	IGlib::setModelMat(objId, modelMat);

	//Creamos el segundo objeto

	objId2 = IGlib::createObj(cubeNTriangleIndex, cubeNVertex, cubeTriangleIndex,
		cubeVertexPos, cubeVertexColor, cubeVertexNormal, cubeVertexTexCoord, cubeVertexTangent);

	IGlib::setModelMat(objId2, modelMat);
	//Incluir texturas aqu�.
	IGlib::addColorTex(objId, "../img/sonrisa.png");
	IGlib::addColorTex(objId2, "../img/sonrisa.png");



	//CBs
	IGlib::setResizeCB(resizeFunc);
	IGlib::setIdleCB(idleFunc);
	IGlib::setKeyboardCB(keyboardFunc);
	IGlib::setMouseCB(mouseFunc);
	IGlib::setMouseMoveCB(mouseMotionFunc);


	//Mainloop
	IGlib::mainLoop();
	IGlib::destroy();
	return 0;


}

void resizeFunc(int width, int height)
{
	
		//Creación de la matriz de projección que mantiene el aspecto de la ventana
		glm::mat4 proj = glm::mat4(1.0f);


		float a_ratio = static_cast<float>(width) / height;

		float n = 1.0f;
		float f = 10.0f;

		float r = a_ratio;
		float l = -a_ratio;
		float t = 1.0f;
		float b = -1.0f;

		proj[0][0] = (2 * n) / ((r - l) / 1.732f);
		proj[1][1] = (2 * n) / ((t - b) / 1.732f);
		proj[2][2] = (f + n) / (n - f);
		proj[2][3] = -1.f;
		proj[3][2] = 2.f * f * n / (n - f);

		IGlib::setProjMat(proj);
	

}
	


void idleFunc()
{
	static float angle = 0;

	angle = (angle < 6.28318530718) ? angle + 0.001f : 0.0f;

	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 1.0f, 0.0f));

	IGlib::setModelMat(objId, rot);


	//Rotaci�n del segundo objeto

	glm::mat4 rot2 = glm::mat4(1.0);
	rot2 = glm::rotate(rot2, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	rot2 = glm::translate(rot2, glm::vec3(2.5f, 0.0f, 0.0f));
	rot2 = glm::rotate(rot2, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	rot2 = glm::scale(rot2, glm::vec3(0.5f, 0.5f, 0.5f));
	IGlib::setModelMat(objId2, rot2);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		cameraPos += cameraSpeed * cameraFront;  // Mover hacia adelante
		break;
	case 's':
		cameraPos -= cameraSpeed * cameraFront;  // Mover hacia atrás
		break;
	case 'a':
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;  // Mover a la izquierda
		break;
	case 'd':
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;  // Mover a la derecha
		break;
	case 'q':
		yaw -= sensitivity;  // Girar a la izquierda
		break;
	case 'e':
		yaw += sensitivity;  // Girar a la derecha
		break;
	}

	// Actualizamos la dirección de la cámara según el yaw y el pitch
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);

	updateCamera();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (state == 0)
		std::cout << "Se ha pulsado el botón ";
	else
		std::cout << "Se ha soltado el botón ";

	if (button == 0) std::cout << "de la izquierda del ratón " << std::endl;
	if (button == 1) std::cout << "central del ratón " << std::endl;
	if (button == 2) std::cout << "de la derecha del ratón " << std::endl;

	std::cout << "en la posición " << x << " " << y << std::endl << std::endl;
}

void mouseMotionFunc(int x, int y)
{
}
