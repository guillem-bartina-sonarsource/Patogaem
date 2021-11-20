#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>

typedef std::pair<unsigned short, unsigned short> Codepair; 

typedef std::pair<char, char> Coord;

class Level 
{
  public:

  Level();
  ~Level();

  std::string getName() const;
  void setName(const std::string& name);

  std::string getBackground() const;
  void setBackground(const std::string& background);

  void add(Coord coord, short code);
  void del(Coord coord, short code);
  bool tryDel(Coord coord, short code);

  bool isEmpty(Coord coord) const;
  bool contains(Coord coord, short code);
  bool containsTarjet(Coord coord, Codepair codepair) const;

  const std::set<unsigned short>& get(Coord coord) const;

  void serialize() const;
  void deserialize(unsigned int index);

  static char** getLevelNames(unsigned int& size);
  static void deleteLevel(unsigned int index);

  private:

  std::string name;
  std::string background;
  std::map<Coord, std::set<unsigned short>> items;
  std::vector<Coord> spawns;

};

#endif