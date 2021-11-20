#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <unordered_map>
#include <mutex>

#include "INonCopyable.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Audio/Music.hpp"


class Resources : private INonCopyable
{
    public:

    ~Resources();

    static Resources* getInstance();

    void setPath(const std::string& path);
    std::string getPath() const;

    const sf::Texture* Texture(const std::string& name);
    const sf::Font* Font(const std::string& name);
    const sf::SoundBuffer* Sound(const std::string& name);

    void clearTextures();
    void clearFonts();
    void clearSounds();

    sf::Music&& Music(const std::string& id);

    private:

    Resources();

    static Resources* instance;

    std::string path;

    std::mutex texturesMutex;
    std::mutex fontsMutex;
    std::mutex soundsMutex;

    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sounds;

};

#endif