#include "entity.h"

Entity::Entity() {
	mX = mY = 0;
	angle = 0;
	EPSILON = 0.01;
	initializeShader();
}

void Entity::initializeShader() {

	shader = new Shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
}


void Entity::applyTransitions() {
	//todo
	glm::mat4 transform;
	glm::mat4 view;
	glm::mat4 projection;
	//float tmp = 0.05;
	//if (angle != 0)tmp = 0.05;
	transform = glm::translate(transform, glm::vec3(mX, mY , 0.5));

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), (float)500 / (float)500, 0.1f, 100.0f);


	GLint transformLoc = glGetUniformLocation(shader->ID, "transform");
	GLint viewLoc = glGetUniformLocation(shader->ID, "view");


	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	shader->setMat4("projection", projection);

	
	//transform = glm::rotate(transform, (float)glfwGetTime()*glm::radians(-55.0f), glm::vec3(0.0f, 0.0f, 0.5f));
	//transformLoc = glGetUniformLocation(shader->ID, "transform");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Entity::outline() {
	if (COLORED_FLAG)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	shader->use();
	glBindVertexArray(VAO);
	applyTransitions();
	glDrawElements(GL_TRIANGLES, indeciesCount, GL_UNSIGNED_INT, 0); //why 32 though
	glBindVertexArray(0);
}


void Entity::assemble(std::vector<Primitive*> carcass, int points) {
	indeciesCount = carcass.size() * 6;  // two triangles for a square

	GLfloat* vertices = new GLfloat[carcass.size() * points * 3];  //points in single primitive, times {x, y, z}

	int index = 0; //account for outer loop
	for (Primitive* obj : carcass)
	{
		for (int a = 0; a < obj->getVertices() * 3; ++a)
		{
			vertices[index] = obj->getVertexAt(a);
			++index;

		}
	}


	GLuint* indecies = new GLuint[indeciesCount];
	constructIndecies(indecies, indeciesCount);
	setBuffers(vertices, carcass.size()*points * 3, indecies, indeciesCount);

	delete[] vertices;
	delete[] indecies;
}

void Entity::constructIndecies(GLuint* indc, int size) {
	// If it works it ain't stupid  
	for (int a = 0, index = 0; a < size; a += 6) {
		indc[a + 0] = index + 0;
		indc[a + 1] = index + 1;
		indc[a + 2] = index + 2;
		indc[a + 3] = index + 1;
		indc[a + 4] = index + 2;
		indc[a + 5] = index + 3;
		index += 4;
	}

}

void Entity::setBuffers(GLfloat* vertecies, int vSize, GLuint* indecies, int iSize) {
	GLuint VBO, EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(GLfloat), vertecies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize * sizeof(GLuint), indecies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
