#include "QuadTree.hpp"
#include <iostream>
#include "inline.h"

QuadTree::QuadTree( int x, int y, int w, int h, int capacity ) :
    m_x(x), m_y(y), m_w(w), m_h(h),
    m_c(capacity),
    m_qt1(nullptr), m_qt2(nullptr), m_qt3(nullptr), m_qt4(nullptr)
{
    m_rect.setFillColor(sf::Color::White);
    m_rect.setPosition(x,y);
    m_rect.setSize(sf::Vector2f(w,h));
    m_rect.setOutlineThickness(-1);
    m_rect.setOutlineColor(sf::Color::Black);


    m_point.setFillColor(sf::Color::Black);
    m_point.setSize(sf::Vector2f(5,5));
}

bool QuadTree::ObjectIsInsideQuadrant( int x, int y ) const
{
    if(x >= m_x && x <= m_x + m_w && y >= m_y && y <= m_y + m_h) { 
        return true; 
    }
    
    return false;
}

bool QuadTree::AreaIsInsideQuadrant( int x, int y, int w, int h ) const
{
    if(std::min(x+w, this->m_x+this->m_w) < std::max(x, this->m_x) && std::min(y+h, this->m_y+this->m_h) < std::max(y, this->m_y)) {
        return true; 
    }

    return false;
}

bool QuadTree::ObjectIsInsideArea( int ox, int oy, int ax, int ay, int aw, int ah ) const
{
    if(ox > ax && ox < ax + aw && oy > ay && oy < ay + ah) {
        return true; 
    }

    return false;
}

bool QuadTree::insert( int x, int y )
{
    if(!ObjectIsInsideQuadrant(x,y)) {
        return false;
    }

    if(m_points.size() < size_t(m_c)) { 
        m_points.push_back(sf::Vector2f(x,y));
        return true;
    } 

    if(m_qt1 == nullptr) { subdivide(); }
    if(m_qt1->insert(x,y)) { return true; }
    if(m_qt2->insert(x,y)) { return true; }
    if(m_qt3->insert(x,y)) { return true; }
    if(m_qt4->insert(x,y)) { return true; }

    return false;
}

void QuadTree::subdivide( void )
{
    m_qt1 = new QuadTree(m_x        , m_y        , m_w/2, m_h/2, m_c);
    m_qt2 = new QuadTree(m_x + m_w/2, m_y        , m_w/2, m_h/2, m_c);
    m_qt3 = new QuadTree(m_x + m_w/2, m_y + m_h/2, m_w/2, m_h/2, m_c);
    m_qt4 = new QuadTree(m_x        , m_y + m_h/2, m_w/2, m_h/2, m_c);
}

void QuadTree::show( void ) const
{
    std::cout << "[ ";
    for(size_t i=0; i < m_points.size(); i++)
    {
        std::cout << "(" << m_points[i].x << "," << m_points[i].y << ")"; 
    }
    if(m_qt1 != nullptr) { m_qt1->show(); }
    if(m_qt2 != nullptr) { m_qt2->show(); }
    if(m_qt3 != nullptr) { m_qt3->show(); }
    if(m_qt4 != nullptr) { m_qt4->show(); }
    std::cout << " ]";

}

std::vector<sf::Vector2f> QuadTree::searchIn( int x, int y, int w, int h )
{
    std::vector<sf::Vector2f> PointInArea;

    if(AreaIsInsideQuadrant(x,y,w,h)) {
        return PointInArea;
    }

    for(int i=0; i< int(m_points.size()); i++) {
        if(ObjectIsInsideArea(m_points[i].x, m_points[i].y, x, y, w, h)) {
            PointInArea.push_back(m_points[i]);
        }
    }

    if(m_qt1 == nullptr) { return PointInArea; }
    if(m_qt1 != nullptr) {
        std::vector<sf::Vector2f> Pqt1 = m_qt1->searchIn(x, y, w, h);
        
        PointInArea.insert(PointInArea.end(), Pqt1.begin(), Pqt1.end());
    }
    if(m_qt2 != nullptr) {
        std::vector<sf::Vector2f> Pqt2 = m_qt2->searchIn(x, y, w, h);
        PointInArea.insert(PointInArea.end(), Pqt2.begin(), Pqt2.end());
    }
    if(m_qt3 != nullptr) {
        std::vector<sf::Vector2f> Pqt3 = m_qt3->searchIn(x, y, w, h);
        PointInArea.insert(PointInArea.end(), Pqt3.begin(), Pqt3.end());
    }
    if(m_qt4 != nullptr) {
        std::vector<sf::Vector2f> Pqt4 = m_qt4->searchIn(x, y, w, h);
        PointInArea.insert(PointInArea.end(), Pqt4.begin(), Pqt4.end());
    }

    return PointInArea;
}

void QuadTree::draw( sf::RenderWindow& target )
{
    target.draw(m_rect);
    if(m_qt1 != nullptr) { m_qt1->draw(target); }
    if(m_qt2 != nullptr) { m_qt2->draw(target); }
    if(m_qt3 != nullptr) { m_qt3->draw(target); }
    if(m_qt4 != nullptr) { m_qt4->draw(target); }

    for(size_t i=0; i < m_points.size(); i++)
    {
        m_point.setPosition(m_points[i].x, m_points[i].y);
        target.draw(m_point);
    }
}

QuadTree::~QuadTree() {}