#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class QuadTree
{
    public:
        QuadTree( int x, int y, int w, int h, int capacity );
        ~QuadTree();

        bool insert( int x, int y );
        bool ObjectIsInsideQuadrant( int x, int y ) const;
        bool AreaIsInsideQuadrant( int x, int y, int w, int h ) const;
        bool ObjectIsInsideArea( int ox, int oy, int ax, int ay, int aw, int ah ) const;
        void subdivide( void );
        std::vector<sf::Vector2f> searchIn( int x, int y, int w, int h ); // Recherche d'éléments dans la zone indiquée
        void show( void ) const; // Afficher l'arbre dans la console
        void draw( sf::RenderWindow& target ); // Afficher l'arbre dans une fenêtre

    private:
        int m_x, m_y, m_w, m_h;
        int m_c;

        QuadTree* m_qt1 /*Haut gauche*/, *m_qt2 /*Haut droite*/, *m_qt3 /*Bas droite*/, *m_qt4 /*Bas gauche*/;   
        std::vector<sf::Vector2f> m_points;     
        sf::RectangleShape m_rect;
        sf::RectangleShape m_point;
};