#include "QuadTree.hpp"
#include <iostream>
#include "inline.h"

QuadTree::QuadTree( int x, int y, int w, int h, int capacity ) :
    m_x(x), m_y(y), m_w(w), m_h(h),
    m_c(capacity),
    m_divided(false),
    m_qt1(nullptr), m_qt2(nullptr), m_qt3(nullptr), m_qt4(nullptr)
{
    m_rect.setFillColor(sf::Color(randomi(0,255),randomi(0,255),randomi(0,255)));
    m_rect.setPosition(x,y);
    m_rect.setSize(sf::Vector2f(w,h));

    m_point.setFillColor(sf::Color::Black);
    m_point.setSize(sf::Vector2f(5,5));
}

bool QuadTree::ObjectIsInsideQuadrant( int x, int y )
{
    if(x >= m_x && x <= m_x + m_w && y >= m_y && y <= m_y + m_h) { 
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

void QuadTree::show( void )
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