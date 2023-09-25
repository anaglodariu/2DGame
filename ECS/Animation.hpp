#ifndef ANIMATION_HPP
#define ANIMATION_HPP

/*
class vs struct
- hiding implementation details => a structure by default
does not hide its implementation details => members are public by default
*/

struct Animation 
{
    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(int i, int f, int s) : index(i), frames(f), speed(s) {}
};

#endif /* Animation_hpp */