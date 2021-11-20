#include "Engine/Resources.h"

Resources* Resources::instance = nullptr;

Resources* Resources::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Resources();
    }
    return instance;
}

Resources::~Resources()
{
    textures.clear();
    fonts.clear();
    sounds.clear();
}

void Resources::setPath(const std::string& path)
{
    this->path = path;
    if(this->path.back() != '/')
    {
        this->path.push_back('/');
    }
}

std::string Resources::getPath() const
{
    return path;
}

const sf::Texture* Resources::Texture(const std::string& name)
{
    if(textures.find(name) == textures.end())
    {
        std::lock_guard threadLock(texturesMutex);
        if(!textures[name].loadFromFile(path + name))
        {
            std::cerr << "Error loading texture <" << name << ">." << std::endl;
        }

    }

    return &textures.at(name);
}

const sf::Font* Resources::Font(const std::string& name)
{
    if(fonts.find(name) == fonts.end())
    {
        std::lock_guard threadLock(fontsMutex);
        if(!fonts[name].loadFromFile(path + name))
        {
            std::cerr << "Error loading font <" << name << ">." << std::endl;
        }
    }

    return &fonts.at(name);
}

const sf::SoundBuffer* Resources::Sound(const std::string& name)
{
    if(sounds.find(name) == sounds.end())
    {
        std::lock_guard threadLock(soundsMutex);
        if(!sounds[name].loadFromFile(path + name))
        {
            std::cerr << "Error loading sound <" << name << ">." << std::endl;
        }
    }

    return &sounds.at(name);
}

void Resources::clearTextures()
{
    textures.clear();
}

void Resources::clearFonts()
{
    fonts.clear();
}

void Resources::clearSounds()
{
    sounds.clear();
}

sf::Music&& Resources::Music(const std::string& name)
{
    sf::Music music;
    music.openFromFile(path + name);
    return std::move(music);
}

Resources::Resources() {}
