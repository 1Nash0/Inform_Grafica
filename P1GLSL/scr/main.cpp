#include "BOX.h"
#include <IGL/IGlib.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


//Idenficadores de los objetos de la escena
int objId = -1;
int objId2 = -1;

//Declaraci�n de CB
void resizeFunc(int width, int height);
void idleFunc();
void keyboardFunc(unsigned char key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void mouseMotionFunc(int x, int y);

/*
// Variables de la cámara
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.3f, 2.0f);
// posición de la cámara en el espacio
glm::vec3 targetPosition = glm::vec3(0.0f, 0.0f, 30.0f);
// posición hacia donde mira la cámara
glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
// vector de la cámara hacia arriba
glm::vec3 front = normalize(targetPosition - cameraPosition);
// dirección de la cámara hacia delante
glm::vec3 rigth = normalize(cross(upVector, front));
// dirección de la cámara hacia la derecha
glm::vec3 up = normalize(cross(front, rigth));
// dirección de la cámara hacia arriba
float cameraSpeed = 0.5f; // velocidad de movimiento de la cámara
glm::mat4 view; // Necesitamos que sean globales para que las funciones call-backs
glm::mat4 proj; // puedan acceder a ellas
*/

int main(int argc, char** argv)
{
	std::locale::global(std::locale("spanish"));// acentos ;)
	if (!IGlib::init("../shaders_P1/shader.v7.vert", "../shaders_P1/shader.v7.frag"))
		return -1;

	//Se ajusta la c�mara
	/*
	view = glm::mat4(1.0); // Inicializamos las que hemos creado arriba
	proj = glm::mat4(1.0);
	*/
	//Si no se da valor se cojen valores por defecto
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(0.0f);

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
	IGlib::addColorTex(objId, "../img/color.png");
	IGlib::addColorTex(objId2, "../img/color.png");



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
	std::cout << "Se ha pulsado la tecla " << key << std::endl << std::endl;
	/*glm::mat4 aux = glm::mat4(1.0f);
	// Creamos una matriz auxiliar en la que definimos los cambios
	if (key == 'W' || key == 'w') // Si pulsamos w
		aux[3].z = (aux[3].z + 1.0f) * cameraSpeed;
	// la cámara se mueve hacia delante (la escena hacia atrás, eje z negativo)
	if (key == 'S' || key == 's') // si pulsamos s
		aux[3].z = (aux[3].z - 1.0f) * cameraSpeed; // lo contrario
	if (key == 'A' || key == 'a') // si pulsamos a
		aux[3].x = (aux[3].x + 1.0f) * cameraSpeed;
	// se despaza a la derecha (escena a la izquierda)
	if (key == 'D' || key == 'd') // si pulsamos d
		aux[3].x = (aux[3].x - 1.0f) * cameraSpeed; // lo contrario
	if (key == 'E' || key == 'e') // si pulsamos e
		aux = rotate(aux, 0.1f, glm::vec3(0.0, 1.0, 0.0));
	// rota hacia la izquierda sobre el eje y
	if (key == 'Q' || key == 'q') // y si pulsamos q
		aux = rotate(aux, 0.1f, glm::vec3(0.0, -1.0, 0.0)); // a la derecha
	view = aux * view; // multiplicamos la matriz de vista por nuestra matriz auxiliar
	IGlib::setViewMat(view); // y la actualizamo
	*/
}

void mouseFunc(int button, int state, int x, int y)
{
	if (state == 0)
		std::cout << "Se ha pulsado el bot�n ";
	else
		std::cout << "Se ha soltado el bot�n ";

	if (button == 0) std::cout << "de la izquierda del rat�n " << std::endl;
	if (button == 1) std::cout << "central del rat�n " << std::endl;
	if (button == 2) std::cout << "de la derecha del rat�n " << std::endl;

	std::cout << "en la posici�n " << x << " " << y << std::endl << std::endl;
}

void mouseMotionFunc(int x, int y)
{
}
