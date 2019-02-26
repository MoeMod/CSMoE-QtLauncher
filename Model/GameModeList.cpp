//
// Created by 小白白 on 2018/11/28.
//


#include "GameModeList.h"

const std::pair<const char *, const char *> GameModeList::gamemodes[] = {
		{"none", "Original"},
		{"dm",   "DeathMatch"},
		{"tdm",  "TeamDeathMatch"},
		{"zb1",  "ZombieMod 1"},
		{"zb2",  "ZombieMod 2"},
		{"zb3",  "ZombieMod 3"},
		{"zbs",  "ZombieScenario"}
};

auto GameModeList::begin() const -> const_iterator {
	return std::begin(gamemodes);
}

auto GameModeList::end() const -> const_iterator {
	return std::end(gamemodes);
}