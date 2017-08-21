////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>



////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////
int ymax = 600;

class Sand{
    
        double x;
        double y;
        double vx;
        double vy;
        double ax;
        double ay;
    public:
        Sand(double, double);
        void draw(sf::Image*);
        void undraw(sf::Image*);
        void update(sf::Image*);
        void physic();
};
Sand::Sand(double mx, double my){
    x = mx;
    y = my;
    vx=0;
    vy=rand()%3;
    ax=0;
    ay=.00000000098;
    std::cout<<"once";
}
void Sand::physic(){
            x = x+vx;
            y = y+vy;
            //if(y>ymax) y=ymax;
            vx = vx+ax;
            vy = vy+ay;
}
void Sand::draw(sf::Image* buffer){
        std::cout<<x;
        std::cout<<"\n";
        buffer->setPixel(x,y,sf::Color(255,255,255));
}
void Sand::undraw(sf::Image* buffer){
        buffer->setPixel(x,y,sf::Color(0,0,0));
}
void Sand::update(sf::Image* buffer){
        undraw(buffer);
        physic();
        draw(buffer);
}
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML");
	
    sf::Image buffer;
    buffer.create(800,600,sf::Color(0,0,0));
    sf::Texture texture;
    
    sf::Sprite sprite;

    std::vector<Sand*> arr;
    
    

    srand(10);

    sf::Clock clock;
	// Start game loop
	while (App.isOpen())
    {

        // Process events
        sf::Event Event;
        while (App.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                App.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
				
			}

            if((Event.type == sf::Event::MouseButtonPressed)){
                int x = Event.mouseButton.x;
                int y = Event.mouseButton.y;
                arr.push_back(new Sand((double)x,(double)y));
            }
 
		}
        
        sf::Time elapsed = clock.restart();
        
        App.clear();
        for(Sand* i : arr){
            i->update(&buffer);
        }
        texture.loadFromImage(buffer);
        sprite.setTexture(texture, true);
        App.draw(sprite);
        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
