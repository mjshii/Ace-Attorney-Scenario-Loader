#pragma once
#include "scenelist.h"
#include <memory>
#include <vector>

using ScenePtr = std::shared_ptr<finalproject::Scene>;

namespace finalproject {

	class SceneManager {
		std::vector<ScenePtr> scene_list;

		public:
			void add(Scene* scene);
			void add(ScenePtr scene);

			void replace(Scene* scene);
			void replace(ScenePtr scene);

			void pop();

			void update();
			void draw();
			void processKey(int key);

			bool empty();
			bool isActive(const Scene* scene);
	};

	// global variable
	extern SceneManager scenes;
}

