
#include "Level.hpp"

#include <fstream>

#include "json.hpp"

#include "Utils.hpp"
#include "EntityCreator.hpp"

Level::Level() {}

Level::~Level() {}

std::string Level::getName() const
{
    return name;
}

void Level::setName(const std::string& name)
{
    this->name = name;
}

std::string Level::getBackground() const
{
    return background;
}

void Level::setBackground(const std::string& background)
{
    this->background = background;
}

void Level::add(Coord coord, short code)
{
    items[coord].insert(code);
}

void Level::del(Coord coord, short code) //NOT SECURE
{
    items[coord].erase(code);

    if(items[coord].empty()) items.erase(items.find(coord));
}

bool Level::tryDel(Coord coord, short code)
{
    std::map<Coord, std::set<unsigned short>>::iterator it1 = items.find(coord);
    if(it1 != items.end())
    {
        for(std::set<unsigned short>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
        {
            if(*it2 == code)
            {
                it1->second.erase(it2);

                if(it1->second.empty()) items.erase(it1);                
                return true;
            }
        }
    }

    return false;
}

bool Level::isEmpty(Coord coord) const
{
    return (items.find(coord) == items.end());
}

bool Level::contains(Coord coord, short code)
{
    if(not isEmpty(coord))
    {
        return (items.at(coord).find(code) != items.at(coord).end());
    }
    return false;
}

bool Level::containsTarjet(Coord coord, Codepair codepair) const
{
    if(not isEmpty(coord))
    {
        for(std::set<unsigned short>::const_iterator it = items.at(coord).cbegin(); it != items.at(coord).cend(); it++)
        {
            if(isTarjet(*it, codepair)) return true;
        }
    }
    return false;
}

const std::set<unsigned short>& Level::get(Coord coord) const
{
    std::map<Coord, std::set<unsigned short>>::const_iterator it = items.find(coord);
    
    if(it != items.end()) return it->second;
    else return ZEROSET_S;
}

void Level::serialize() const
{
    std::fstream filein("rsc/levels.json", std::ios_base::in);
    std::string page = "", tmp;
    while(getline(filein, tmp)) page += tmp;
    filein.close();

    json::JSON obj;
    obj = json::Load(page);

    unsigned int numLevels = obj["Levels"].length();

    bool found = false;
    unsigned int num;
    for(unsigned int i = 0; i < numLevels and not found; i++)
    {
        if(obj["Levels"][i]["name"].ToString() == name)
        {
            found = true;
            num = i;
        }
    }

    if(not found)
    {
        obj["Levels"].append(json::Object());
        num = numLevels;
    }

    obj["Levels"][num]["name"] = name;
    obj["Levels"][num]["background"] = background;
    obj["Levels"][num]["items"] = json::Array();
    obj["Levels"][num]["spawns"] = json::Array();

    unsigned int i = 0;
    for(std::map<Coord, std::set<unsigned short>>::const_iterator it1 = items.begin(); it1 != items.end(); it1++)
    {
        obj["Levels"][num]["items"].append(json::Array(it1->first.first, it1->first.second));

        for(std::set<unsigned short>::const_iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
        {
            obj["Levels"][num]["items"][i].append(*it2);
        }
        i++;
    }

    for(unsigned int i = 0; i < spawns.size(); i++)
    {
        obj["Levels"][num]["spawns"].append(json::Array(spawns[i].first, spawns[i].second));
    }

    std::fstream fileout("rsc/levels.json", std::ios_base::out | std::ios_base::trunc);
    fileout << obj.dump();
    fileout.close();
}

void Level::deserialize(unsigned int index)
{
    std::fstream filein("rsc/levels.json", std::ios_base::in);
    std::string page = "", tmp;
    while(getline(filein, tmp)) page += tmp;
    filein.close();

    json::JSON obj;
    obj = json::Load(page);

    name = obj["Levels"][index]["name"].ToString();
    background = obj["Levels"][index]["background"].ToString();

    unsigned int numItems = obj["Levels"][index]["items"].length();

    for(int i = 0; i < numItems; i++)
    {
        unsigned int rowSize = obj["Levels"][index]["items"][i].length();
        std::pair<std::map<Coord, std::set<unsigned short>>::iterator, bool> it = items.insert(std::make_pair(Coord(obj["Levels"][index]["items"][i][0].ToInt(), obj["Levels"][index]["items"][i][1].ToInt()), std::set<unsigned short>()));
        for(int j = 2; j < rowSize; j++)
        {
            it.first->second.insert(obj["Levels"][index]["items"][i][j].ToInt());
        }
    }

}

char** Level::getLevelNames(unsigned int& size)
{
    char** names;

    std::fstream filein("rsc/levels.json", std::ios_base::in);
    std::string page = "", tmp;
    while(getline(filein, tmp)) page += tmp;
    filein.close();

    json::JSON obj;
    obj = json::Load(page);

    size = obj["Levels"].length();

    if(size != 0)
    {
        names = new char*[size];
        for(unsigned int i = 0; i < size; i++)
        {
            std::string tmp = obj["Levels"][i]["name"].ToString();
            names[i] = new char[tmp.length()+1];
            strcpy(names[i], tmp.c_str());
        }
    }

    return names;
}

void Level::deleteLevel(unsigned int index)
{
    std::fstream filein("rsc/levels.json", std::ios_base::in);
    std::string page = "", tmp;
    while(getline(filein, tmp)) page += tmp;
    filein.close();

    json::JSON obj;
    obj = json::Load(page);

    unsigned int numLevels = obj["Levels"].length();

    json::JSON levels[numLevels];

    for(unsigned int i = 0 ; i < numLevels; i++)
    {
        levels[i] = obj["Levels"][i];
    }

    obj["Levels"] = json::Array();

    for(unsigned int i = 0 ; i < numLevels; i++)
    {
        if(i != index)
        {
            obj["Levels"].append(levels[i]);
        }
    }

    std::fstream fileout("rsc/levels.json", std::ios_base::out | std::ios_base::trunc);
    fileout << obj.dump();
    fileout.close();
}