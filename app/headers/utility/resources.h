#include <unordered_map>

#include "files.h"
#include "../systems/rendering/render.h"
#include "../utility/debug.h"
#pragma once
class Resources {
private:
	static std::unordered_map<const char*, Vizzy::Shader> shaders;
public:

	static void LoadShader(const char* _name, const char* _vertShaderFilename, const char* _fragShaderFilename) {
		shaders.insert(std::make_pair(_name, Vizzy::Shader(_vertShaderFilename, _fragShaderFilename)));
		Debug::log("Loaded Shader {", _name, "} from :", _vertShaderFilename, " ", _fragShaderFilename);
	}
	static Vizzy::Shader GetShader(const char* _name) { return shaders[_name]; };
};