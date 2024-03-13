#ifndef HEALTH_POINTS
#define HEALTH_POINTS

#include <ostream>
using std::ostream;

class HealthPoints {

    int m_maxHP;
    int m_hp;
    static const int DEFAULT_MAX_HP = 100;

public:
    /*
     * C'tor of HealthPoints class
     *
     * @param name - The max number of health points.
     * @return
     *      A new instance of HealthPoints.
    */
    HealthPoints(int maxHP = DEFAULT_MAX_HP);

    /*
     * Explicitly telling the compiler to use the defualt methods of copy constuctor, destructor, and operator=
    */
    ~HealthPoints() = default;
    HealthPoints(const HealthPoints& healthPoints) = default;
    HealthPoints& operator=(const HealthPoints& hp) = default;

    /*
     * Gets the current health points of HealthPoints:
     * 
     * @return
     *      The current health points.
    */
    int getHP() const;

    /*
     * Get the max health points of HealthPoints:
     * 
     * @return
     *      The max health points.
    */
    int getMaxHP() const;

    /*
     * Adds health points to the current HealthPoints, at most to the maximum health points:
     * 
     * @param hp - The health points to be added.
     * @return
     *      A reference to the HealthPoints object.
    */
    HealthPoints& operator+=(const int hp);

    /*
     * reduces health points from the current HealthPoints, at most to zero:
     * 
     * @param hp - The health points to be reduced.
     * @return
     *      A reference to the HealthPoints object.
    */
    HealthPoints& operator-=(const int hp);

    /*
     * reduces health points from a copy of the current HealthPoints, at most to zero:
     * 
     * @param hp - The health points to be reduced.
     * @return
     *      A new HealthPoints object.
    */
    HealthPoints operator-(const int hp) const;

    /* Class InvalidArgument to use as exceptions for a situation of an invalid argument given to a constuctor/operator */
    class InvalidArgument{};
};

/*
 * Adds health points to a copy of the given HealthPoints , at most to the maximum health points of the given HealthPoints:
 * 
 * @param healthPoints - The given HealthPoints.
 * @param hp - The health points to be reduced.
 * @return
 *      A new HealthPoints object.
*/
HealthPoints operator+(const HealthPoints& healthPoints, const int hp);

/*
 * Adds health points to a copy of the given HealthPoints , at most to the maximum health points of the given HealthPoints:
 * 
 * @param hp - The health points to be reduced.
 * @param healthPoints - The given HealthPoints.
 * @return
 *      A new HealthPoints object.
*/
HealthPoints operator+(const int hp, const HealthPoints& healthPoints);

/*
 * Checks if two given HealthPoints are equal:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The second HealthPoints.
 * @return
 *      True if the two given HealthPoints are equal
 *      False otherwise
*/
bool operator==(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Checks if two given HealthPoints are not equal:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The second HealthPoints.
 * @return
 *      True if the two given HealthPoints are not equal
 *      False otherwise
*/
bool operator!=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Checks if one given HealthPoints is bigger than another given HealthPoints:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The other HealthPoints.
 * @return
 *      True if the first given HealthPoints is bigger than the other given HealthPoints
 *      False otherwise
*/
bool operator>(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Checks if one given HealthPoints is smaller than another given HealthPoints:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The other HealthPoints.
 * @return
 *      True if the first given HealthPoints is smaller than the other given HealthPoints
 *      False otherwise
*/
bool operator<(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Checks if one given HealthPoints is smaller or equal to another given HealthPoints:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The other HealthPoints.
 * @return
 *      True if the first given HealthPoints is smaller or equal to the other given HealthPoints
 *      False otherwise
*/
bool operator<=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Checks if one given HealthPoints is bigger or equal to another given HealthPoints:
 * 
 * @param healthPointsOne - The first HealthsPoint.
 * @param healthPointsTwo - The other HealthPoints.
 * @return
 *      True if the first given HealthPoints is bigger or equal to the other given HealthPoints
 *      False otherwise
*/
bool operator>=(const HealthPoints& healthPointsOne, const HealthPoints& healthPointsTwo);

/*
 * Print operator:
 * 
 * @param os - An ostream object.
 * @param healthPoints - The HealthPoints to be printed.
 * @return
 *      A reference to an ostream object.
*/
ostream& operator<<(ostream& os, const HealthPoints& healthPoints);

#endif