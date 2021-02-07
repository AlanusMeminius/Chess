#include "Engine.h"
#include <cctype>

Piece::Piece(char role, bool camp, int pos) : camp_(camp), pos_(pos) {
	std::vector<char> types = {'k', 'a', 'b', 'n', 'r', 'c', 'p'};
	const auto iter = std::find(types.begin(), types.end(), tolower(role));
	if (iter != types.end())
		role_ = std::distance(std::begin(types), iter); // NOLINT(clang-diagnostic-shorten-64-to-32)
	else
		role_ = 9;
}


Engine::Engine(int select) : mode_(select) {
	int index = 0;
	for (const auto& item : initChessBoard) {
		if (!ispunct(item)) {
			board_.emplace_back(item);
			pieces_.push_back(std::make_shared<Piece>(item, isupper(item) != 0, index));
			index++;
		}
	}
}

void Engine::choose_mode() {
}


void Engine::update_representation(int&) {
}


bool Engine::check_strategy(int&) {
	return true;
}
