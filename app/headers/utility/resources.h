#pragma once

#include <unordered_map>

#include "files.h"
#include "../systems/rendering/render.h"
#include "../utility/debug.h"
#pragma once
class Resources {
private:
	static std::unordered_map<const char*, Vizzy::Shader> shaders;
	static std::unordered_map<const char*, Vizzy::Texture2D> textures;

public:

	static void LoadShader(const char* _name, const char* _vertShaderFilename, const char* _fragShaderFilename) {
		shaders.insert(std::make_pair(_name, Vizzy::Shader(_vertShaderFilename, _fragShaderFilename)));
		Debug::log("Loaded Shader {", _name, "} from :", _vertShaderFilename, " ", _fragShaderFilename);
	}
	static void LoadTexture2D(const char* _name, const char* _filename) {
		textures.insert(std::make_pair(_name, Vizzy::Texture2D(_filename)));
		
	}

	static Vizzy::Shader GetShader(const char* _name) {

		if (shaders.count(_name) == 0)
			throw std::out_of_range("Shader not found, please load the shader before using it");

		return shaders[_name];
	};


	static Vizzy::Texture2D GetTexture2D(const char* _name) {

		if (textures.count(_name) == 0)
			throw std::out_of_range("Texture not found, please load the texture before using it");

		return textures[_name];
	};
};



//[ExtraNotes that i learned]
//tip: throw by value and catch by reference: