#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class QuadTree
{
    public:
        QuadTree( int x, int y, int w, int h, int capacity );
        ~QuadTree();

        bool insert( int x, int y );
        bool ObjectIsInsideQuadrant( int x, int y );
        void subdivide( void );
        void show( void );
        void draw( sf::RenderWindow& target );

    private:
        int m_x, m_y, m_w, m_h;
        int m_c;

        bool m_divided;

        QuadTree* m_qt1 /*Haut gauche*/, *m_qt2 /*Haut droite*/, *m_qt3 /*Bas droite*/, *m_qt4 /*Bas gauche*/;   
        std::vector<sf::Vector2f> m_points;     
        sf::RectangleShape m_rect;
        sf::RectangleShape m_point;
};