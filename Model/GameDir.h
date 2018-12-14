//
// Created by 小白白 on 2018/11/28.
//

#ifndef LAUNCHER_GAMEDIR_H
#define LAUNCHER_GAMEDIR_H

#include <string>

class CGameDir {
public:
	void set(std::string s) { path=std::move(s); }
	const std::string &get() const { return path; }
private:
	std::string path;
};

inline CGameDir &GameDir()
{
	static CGameDir x;
	return x;
}


#endif //LAUNCHER_GAMEDIR_H
