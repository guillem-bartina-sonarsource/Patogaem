
#include "Engine/AnimatedSprite.hpp"

Frame::Frame(const sf::IntRect& frame)
{
    this->frame = frame;
}

Frame::~Frame() {}

KeyFrame::KeyFrame(unsigned int frame, const sf::Time& duration)
{
    this->frame = frame;
    this->duration = duration;
}

KeyFrame::~KeyFrame() {}

Animation::Animation(const KeyFrame& keyFrame, bool loop)
{
    keyFrames.push_back(keyFrame);
    this->loop = loop;
}

Animation::Animation(const std::vector<KeyFrame>& keyFrames, bool loop)
{
    this->keyFrames.insert(this->keyFrames.end(), keyFrames.begin(), keyFrames.end());
    this->loop = loop;
}

Animation::~Animation() {}

void Animation::addKeyFrame(const KeyFrame& keyFrame)
{
    keyFrames.push_back(keyFrame);
}

void Animation::addKeyFrames(const std::vector<KeyFrame>& keyFrames)
{
    this->keyFrames.insert(this->keyFrames.end(), keyFrames.begin(), keyFrames.end());
}

void Animation::setLoop(bool loop)
{
    this->loop = loop;
}