#pragma once

#include <vector>
#include "Texture.h"


namespace uGLy
{

	class TextureManager {
	private:
		std::vector<Texture*> textures;
	public:
		TextureManager();
		~TextureManager();

		Texture* CreateTextureFromFile(std::string &pathName);
		Texture* CheckIfTextureAlreadyExists(std::string &pathName);
		void Clear();
	};

}
