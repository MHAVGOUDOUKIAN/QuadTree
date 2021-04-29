#include "Engine.hpp"

Engine::Engine(): m_window(sf::VideoMode(600,600), "Application SFML"), my_qt(0,0,600,600,4)
{
    srand(std::chrono::steady_clock::now().time_since_epoch().count());
    TimePerFrame = sf::seconds(1.f/120.f);
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            processEvents();
            timeSinceLastUpdate -= TimePerFrame;
            update(TimePerFrame);
        }
        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
                
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;

            default:
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::Escape) { this-> Echap = isPressed; }
    if(key == sf::Keyboard::Left) {
        this-> Left = isPressed;
        if(!isPressed) { this->LeftPressed=false; }
    }
    if(key == sf::Keyboard::Right) {
        this-> Right = isPressed;
        if(!isPressed) { this->RightPressed=false; }
    }
    if(key == sf::Keyboard::Down) {
        this-> Down = isPressed;
        if(!isPressed) { this->DownPressed=false; }
    }
    if(key == sf::Keyboard::Up) {
        this-> Up = isPressed;
        if(!isPressed) { this->UpPressed=false; }
    }
    if(key == sf::Keyboard::Space) {
        this-> Space = isPressed;
        if(!isPressed) { this->SpacePressed=false; }
    }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { 
        this-> MouseL = isPressed; 
        if(!isPressed) { this->MouseLPressed=false; }
    }
    if(mouse == sf::Mouse::Right) {
        this-> MouseR = isPressed;
        if(!isPressed) { this->MouseRPressed=false; }
    }
}

void Engine::update(sf::Time deltaTime)
{
    //////////////////////////////////////////////////////////////
    ////////////// R�ponse aux inputs ////////////////////////////
    //////////////////////////////////////////////////////////////

    if(Echap) { m_window.close(); }
    if(MouseL && !MouseLPressed) {         
        my_qt.insert(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
        MouseLPressed = true;}
    if(MouseR && !MouseRPressed) { 

    }
    if(Left && !LeftPressed) { }
    if(Right) { }
    if(Up) {  }
    if(Down) {  }
    if(Space) { }


    //////////////////////////////////////////////////
    ////////////// Update ////////////////////////////
    //////////////////////////////////////////////////

}

void Engine::render(void)
{
    m_window.clear();
    my_qt.draw(m_window);
    m_window.display();
}

Engine::~Engine()
{}
