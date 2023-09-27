#ifndef POSITION_H
#define POSITION_H
#include <iostream>

/**
* @brief The Position class represents a position in a board
*/
class Position{
private:
    int x;
    int y;
public:
    /**
    * @brief Position Constructor of the class position
    * @param x column of the board
    * @param y row of the board
    */
    Position(int x, int y);
    Position() = default;
    /**
    * @brief getX Give the coordinate of a position in x
    * @return an integer
    */
    int getX() const;
    /**
    * @brief getY Give the coordinate of a position in Y
    * @return an integer
    */
    int getY() const;
    /**
    * @brief tostring Allows you to display a position
    * @return a string
    */
    std::string tostring();
    /**
    * @brief operator += redefining the operator +=
    * @param p The position to be used with the operator
    * @return a new position modified
    */
    Position & operator+=(Position const & p);
    /**
    * @brief operator + redefining the operator +
    * @param p The position to be used with the operator
    * @return a new position modified
    */
    Position operator+(Position const & p);
};
inline std::ostream& operator<<(std::ostream& os, const Position& pos)
{
    os << " La position est : "<< pos.getX() << " , " << pos.getY()<< std::endl;
    return os;
}

#endif // POSITION_H
