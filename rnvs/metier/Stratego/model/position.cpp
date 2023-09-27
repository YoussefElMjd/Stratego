#include "model/position.h"


Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX() const
{
    return this->x;
}

int Position::getY() const
{
    return this->y;
}

std::string Position::tostring()
{
    std::string positionString = std::to_string(this->getX()) + "-" +
                                 std::to_string(this->getY());
    return positionString;
}

// Position Position::operator+(Position const & p) // rnvs : comm
Position Position::operator+(Position const & p)
const   // rnvs : ajout
{
    Position addPos =  Position(this->x + p.x, this->y + p.y);
    return addPos;
}

Position & Position::operator+=(Position const & p)
{
    this->x += p.x;
    this->y += p.y;
    return *this;
}


