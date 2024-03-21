#include <glad/glad.h>
#include "../../../headers/systems/rendering/render.h"
#include "../../../headers/utility/debug.h"
using namespace Vizzy;

void Mesh::initialize() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	create_default_mesh();
}

void Mesh::create_default_mesh() {

	float vertices[] = {
		0.0f , 0.0f , 0.0f,
		0.0f , 1.0f , 0.0f,
		1.0f , 1.0f , 0.0f,
		0.0f , 1.0f , 0.0f
	};
	float uv[] = {
		0.0f , 0.0f,
		1.0f , 0.0f,
		1.0f , 1.0f,
		0.0f , 1.0f
	};
	int triangles[] = {
		0 , 1 , 2,
		0 , 2 , 3
	};

	set_vertices(vertices, sizeof(vertices));
	set_uv(uv, sizeof(uv));
	set_triangles(triangles, sizeof(triangles));
	calculate_buffer();
	apply();
}
void Mesh::set_vertices(float* _data, size_t _dataSize) {
	
	vertices.clear();

	int vertCount = _dataSize / sizeof(float);
	vertices = std::vector<float>(vertCount);

	//assigning from first pointer to the last 
	vertices.assign(_data, _data + vertCount);

}
void Mesh::set_uv(float* _data, size_t _dataSize) {

	uv.clear();

	int uvCount = _dataSize / sizeof(float);
	uv = std::vector<float>(uvCount);
	uv.assign(_data, _data + uvCount);

}
void Mesh::set_triangles(int* _data, size_t _dataSize) {

	triangles.clear();

	int trisCount = _dataSize / sizeof(float);
	triangles = std::vector<int>(trisCount);
	triangles.assign(_data, _data + trisCount);
}


void Mesh::calculate_buffer() {

	bufferData.clear();

	// [ x x x y y |  x x x y y | x x x y y ] 
	// here we have 3 blocks total , so we are actually doin total vertex pos (float) / 3 
	// data blocks are like no of vertex we are adding
	int bufferDataBlocks = vertices.size() / 3;
	
	// resizing the buffer to allocate new data
	bufferData = std::vector<float>(vertices.size() + uv.size());


	for (int i = 0; i < bufferDataBlocks; i++)
	{
		bufferData[(i * 5) + 0] = vertices[i * 3 + 0];	// POSITION_X
		bufferData[(i * 5) + 1] = vertices[i * 3 + 1];	// POSITION_Y
		bufferData[(i * 5) + 2] = vertices[i * 3 + 2];	// POSITION_Z

		bufferData[(i * 5) + 3] = uv[i * 2 + 0];	// UV_X
		bufferData[(i * 5) + 4] = uv[i * 2 + 1];	// UV_Y
	}
}
void Mesh::apply() {

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//marking as static for now as we'll be reusing this data a lot but not write too often
	glBufferData(GL_ARRAY_BUFFER, sizeof(bufferData), &bufferData, GL_STATIC_DRAW);

	//vertices layout declaration
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); // tells opengl that we can access the first index for reading the vertices

	//uvs layout declaration
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//binding the triangle array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), &triangles, GL_STATIC_DRAW);


	//resetting the current binded buffer to null like state
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Vizzy::Mesh::print_buffer()
{
	for (auto& i : bufferData) {
		Debug::log(i, " ");
	}
}
;


//Need to learn rn -
//Stack allocation lifetime of local scope variables 


//learned concepts-
//in the loop overflow may happen if (int+int) is very large, so it tells us to use size_t which generates a larger one
//but we dont need it here say we willl be hardly goin over a hundred if even required :)