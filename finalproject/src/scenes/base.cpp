#include "base.h"
#include <sstream>
#include <iterator>

finalproject::Scene::~Scene() {
	if (constants::kDebugMode) {
		std::cout << "Scene Destroyed" << std::endl;
	}
}

std::string finalproject::Scene::wordWrap(std::string sentence, int width) {
	if (font.stringWidth(sentence) <= width) {
		return sentence;
	}

	// String splitting taken from https://stackoverflow.com/a/5607650
	std::stringstream word_stream(sentence);
	std::istream_iterator<std::string> begin(word_stream);
	std::istream_iterator<std::string> end;
	std::vector<std::string> words(begin, end);

	// Word wrap
	std::string wrapped = "";
	std::string last_line = "";
	for (int i = 0; i < words.size(); i++) {
		std::cout << words[i] << ": ";
		if (words[i].front() == '\n') {
			wrapped += last_line;
			last_line = words[i];
		} else if (last_line.empty() || font.stringWidth(last_line + words[i]) <= width) {
			last_line += words[i] + " ";
		} else {
			wrapped += last_line + "\n";
			last_line = words[i] + " ";
		}
	}
	wrapped += last_line;

	return wrapped;
}