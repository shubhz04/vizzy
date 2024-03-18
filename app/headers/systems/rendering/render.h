#pragma once

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
	};
	class Material {};
	class Mesh {};
	class RenderQueue{};
}