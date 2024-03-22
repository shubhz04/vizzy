#pragma once
#include <glm/glm.hpp>
#include <vector>
namespace Vizzy
{
	class Shader {
	private:
		void attach_vertex_shader(const char* _srcData);
		void attach_fragment_shader(const char* _srcData);
		void link_shader_program();

		bool has_compile_error(unsigned int _shader, const char* _shaderType);
		bool has_link_error();
	public:
		unsigned int refID = 0;

		Shader() {};
		Shader(const char* _vertShaderFilename, const char* _fragShaderFilename);

		static void U1f(unsigned int _shader,const char* _param, float _value);
		static void Vec2f(unsigned int _shader, const char* _param, glm::vec2 _value);
		static void Vec4f(unsigned int _shader, const char* _param, glm::vec4 _value);
		static void Mat4f(unsigned int _shader, const char* _param, glm::mat4 _val);
	};

	
	class Material {
	public:
		Shader shader;
		glm::vec4 mainColor = glm::vec4(0);

		Material() {};
		Material(Shader _shader) { shader = _shader; };
	};


	class Mesh {
	private:
		std::vector<float> bufferData; // final bufferobject to be uploaded
		void calculate_buffer();
	public:
		unsigned int VAO = 0, VBO = 0, EBO = 0;
		std::vector<float> vertices, uv;
		std::vector<int> triangles;
		
		Mesh() {};

		void initialize();
		void create_default_mesh();
		void set_vertices(float* _data, size_t _dataSize);
		void set_uv(float* _data, size_t _dataSize);
		void set_triangles(int* _data, size_t _dataSize);

		void apply();

		//extra-stuff
		void print_buffer();
	};
	
}
