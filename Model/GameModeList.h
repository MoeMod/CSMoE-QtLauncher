//
// Created by 小白白 on 2018/11/28.
//

#ifndef LAUNCHER_GAMEMODE_H
#define LAUNCHER_GAMEMODE_H

#include <utility>
#include <iterator>

class GameModeList {
public:
	// (code, name) , ...
	using gamemode_t = const std::pair<const char *, const char *>;
	static gamemode_t gamemodes[];
	using const_iterator = gamemode_t *;

public:
	const_iterator begin() const;

	const_iterator end() const;

	const_iterator cbegin() { return begin(); }

	const_iterator cend() { return end(); }
};

#endif //LAUNCHER_GAMEMODE_H
