#ifndef INONCOPYABLE_HPP
#define INONCOPYABLE_HPP

class INonCopyable
{
    public:

    INonCopyable(const INonCopyable&) = delete;
    INonCopyable& operator=(const INonCopyable&) = delete;

    protected:

    INonCopyable() = default;
    ~INonCopyable() = default;

};

#endif