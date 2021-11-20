#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <string>
#include <vector>
#include <map>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class Frame
{
    public:

    Frame(const sf::IntRect& frame);
    ~Frame();

    sf::IntRect frame;
};

class KeyFrame
{
    public:

    KeyFrame(unsigned int frame, const sf::Time& duration);
    ~KeyFrame();

    unsigned int frame;
    sf::Time duration;
};

class Animation
{
    public:

    Animation();
    Animation(const KeyFrame& keyFrame, bool loop);
    Animation(const std::vector<KeyFrame>& keyFrames, bool loop);
    ~Animation();

    void addKeyFrame(const KeyFrame& keyFrame);
    void addKeyFrames(const std::vector<KeyFrame>& keyFrames);
    void setLoop(bool loop);

    std::vector<KeyFrame> keyFrames;
    bool loop;
};

template<class T, T idDefault = T()>
class AnimatedSprite : public sf::Sprite
{
    public:

    AnimatedSprite(const sf::Texture& texture);
    ~AnimatedSprite();

    unsigned int addFrame(Frame frame);
    unsigned int addFrames(const std::vector<Frame>& frames);
    void addAnimation(T id, Animation animation);

    bool getPlaying() const;
    void setPlaying(bool playing);
    T getAnimation() const;
    void setAnimation(T id);
    bool hasAnimationEnded() const;

    void update(const sf::Time& deltatime);

    private:

    std::vector<Frame> frames;
    std::map<T, Animation> animations;

    bool playing;
    T currentAnimationId;
    Animation* currentAnimation;
    unsigned int currentKeyFrameId;
    KeyFrame* currentKeyFrame;
    sf::Time timer;
    bool hasEnded;

};

template<class T, T idDefault>
AnimatedSprite<T, idDefault>::AnimatedSprite(const sf::Texture& texture) : sf::Sprite(texture)
{
    playing = false;
    unsigned int index = addFrame(Frame(sf::IntRect(sf::Vector2i(), sf::Vector2i(texture.getSize()))));
    addAnimation(idDefault, Animation(KeyFrame(index, sf::Time::Zero), false));
    setAnimation(idDefault);
}

template<class T, T idDefault>
AnimatedSprite<T, idDefault>::~AnimatedSprite() {}

template<class T, T idDefault>
unsigned int AnimatedSprite<T, idDefault>::addFrame(Frame frame)
{
    unsigned int size = frames.size();
    frames.push_back(frame);
    return size;
}

template<class T, T idDefault>
unsigned int AnimatedSprite<T, idDefault>::addFrames(const std::vector<Frame>& frames)
{
    unsigned int size = this->frames.size();
    this->frames.insert(this->frames.end(), frames.begin(), frames.end());
    return size;
}

template<class T, T idDefault>
void AnimatedSprite<T, idDefault>::addAnimation(T id, Animation animation)
{
    animations.insert(std::make_pair(id, animation));
}

template<class T, T idDefault>
bool AnimatedSprite<T, idDefault>::getPlaying() const
{
    return playing;
}

template<class T, T idDefault>
void AnimatedSprite<T, idDefault>::setPlaying(bool playing)
{
    this->playing = playing;
}

template<class T, T idDefault>
T AnimatedSprite<T, idDefault>::getAnimation() const
{
    return currentAnimationId;
}

template<class T, T idDefault>
void AnimatedSprite<T, idDefault>::setAnimation(T id)
{
    currentAnimationId = id;
    currentAnimation = &animations.at(id);
    currentKeyFrameId = 0;
    currentKeyFrame = &currentAnimation->keyFrames[0];
    timer = sf::Time::Zero;
    hasEnded = false;
    setTextureRect(frames[currentKeyFrame->frame].frame);
}

template<class T, T idDefault>
bool AnimatedSprite<T, idDefault>::hasAnimationEnded() const
{
    return hasEnded;
}

template<class T, T idDefault>
void AnimatedSprite<T, idDefault>::update(const sf::Time& deltatime)
{
    if(playing and not hasEnded)
    {
        timer += deltatime;
        while(currentKeyFrame->duration > sf::Time::Zero and timer >= currentKeyFrame->duration)
        {
            if(not currentAnimation->loop and currentKeyFrameId == currentAnimation->keyFrames.size() - 1)
            {
                hasEnded = true;
                break;
            }
            
            timer -= currentKeyFrame->duration;

            currentKeyFrameId++;
            currentKeyFrameId %= currentAnimation->keyFrames.size();
            currentKeyFrame = &currentAnimation->keyFrames[currentKeyFrameId];

            setTextureRect(frames[currentKeyFrame->frame].frame);
        }
    }
}

#endif