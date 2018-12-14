//
// Created by 小白白 on 2018-12-14.
//

#include "GameSettings.h"
#include <fstream>
#include <string>
#include <algorithm>

static inline std::string remove_quotation(const std::string &str)
{
	if(str.front() == '\"' && str.back() == '\"')
		return std::string(str.cbegin()+1, str.cend()-1);
	return str;
}

GameSettings::GameSettings(const std::string &rootdir)
{
	std::ifstream ifs(rootdir + "/csmoe/gamesettings.cfg");

	for(std::string line; std::getline(ifs, line); )
	{
		if(line[0]=='/' && line[1]=='/')
			continue;

		if(!std::equal(line.begin(), line.begin() + 4, "set "))
			continue;

		auto key_start = line.begin() + 4;
		auto iter_space = std::find_if(key_start, line.end(), isspace);
		if(iter_space == line.end())
			continue;
		auto key_end = iter_space;


		auto value_begin = key_end + 1;
		auto value_end = line.end();

		origin.insert({{key_start, key_end}, remove_quotation({value_begin, value_end})});
	}
}

void GameSettings::Save(const std::string &rootdir)
{
	if(changed.empty())
		return;

	std::map<std::string, const std::string> merged_map;

	for(auto &&kv : changed)
	{
		merged_map.insert(kv);
	}
	for(auto &&kv : origin)
	{
		merged_map.insert(kv);
	}

	std::ofstream ofs(rootdir + "/csmoe/gamesettings.cfg");

	for(auto &&kv : merged_map)
	{
		ofs << "set " << kv.first << " \"" << kv.second << '\"'<< std::endl;
	}

	origin = std::move(merged_map);
	changed.clear();
}

void GameSettings::Discard()
{
	changed.clear();
}

const std::string &GameSettings::Read(const std::string &key) const
{

	auto iter1 = changed.find(key);
	if (iter1 != changed.end())
		return iter1->second;

	auto iter2 = origin.find(key);
	if (iter2 != origin.end())
		return iter2->second;

	static std::string invalid_result; // ""
	return invalid_result;
}

void GameSettings::Write(const std::string &key, const std::string &value)
{
	changed[key] = value;
}

bool GameSettings::HasChanged() const
{
	return !changed.empty();
}
