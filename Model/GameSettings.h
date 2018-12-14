//
// Created by 小白白 on 2018-12-14.
//

#ifndef LAUNCHER_GAMESETTINGS_H
#define LAUNCHER_GAMESETTINGS_H

#include <map>


// handle ?/csmoe/gamesettings.cfg
class GameSettings
{
public:
	GameSettings(const std::string &rootdir);

	void Discard();
	bool HasChanged() const;
	void Save(const std::string &rootdir);
	const std::string &Read(const std::string &key) const;
	void Write(const std::string &key, const std::string &value);

private:
	std::map<std::string, const std::string> origin;
	std::map<std::string, std::string> changed;
};


#endif //LAUNCHER_GAMESETTINGS_H
