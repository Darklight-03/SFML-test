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
int xmax = 800;

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
        double getX() const;
        double getY() const;
        void reverse(sf::Image*);
        //bool operator==(const Sand&, const sf::RectangleShape&);
};
Sand::Sand(double mx, double my){
    x = mx;
    y = my;
    vx=((rand()%1000)*.0001)-.05;
    vy=((rand()%1000)*.0001)-.05;
    ax=((rand()%1000)*.0000001)-.00005;
    ay=((rand()%1000)*.0000001)-.00005;
    std::cout<<"once";
}
double Sand::getX() const{
    return x;
}
double Sand::getY() const{
    return y;
}
bool operator==(const Sand& s, const sf::RectangleShape& r){
    if(s.getX()<r.getPosition().x+40&&s.getX()>r.getPosition().x){
        if(s.getY()<r.getPosition().y+40&&s.getY()>r.getPosition().y){
            return true;
        }
    }
    return false;
}
void Sand::physic(){
            x = x+vx;
            y = y+vy;
            //if(y>ymax) y=ymax;
            vx = vx+ax;
            vy = vy+ay;
            if(x>xmax){
                x = (int)x%xmax;
            }
            if(x<0){
                x= x+xmax;
            }
            if(y>ymax){
                y = (int)y%ymax;
            }
            if(y<0){
                y= y+ymax;
            }
}
void Sand::reverse(sf::Image* buffer){
    undraw(buffer);
    x=x-vx;
    y=y-vy;
    vx = -1*vx/1.5;
    vy = -1*vy/1.5;
}
void Sand::draw(sf::Image* buffer){
        //std::cout<<x<<" "<<y;
        //std::cout<<"\n";
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
    float fintime=0;
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML");
	
    sf::Image buffer;
    buffer.create(800,600,sf::Color(0,0,0));
    sf::Texture texture;
    
    sf::Sprite sprite;

    std::vector<Sand*> arr;
    sf::RectangleShape rectangle;
    
    sf::Font font;
    font.loadFromFile("segoeui.ttf");

    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("Hello world");
    // set the character size
    text.setCharacterSize(24); // in pixels, not points
    // set the color
    text.setFillColor(sf::Color::Red);

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
            if((Event.type == sf::Event::MouseMoved)){
                int x = Event.mouseMove.x;
                int y = Event.mouseMove.y;
                rectangle.setPosition(x-20,y-20);
                rectangle.setSize(sf::Vector2f(40,40));
            }
 
		}
        
       // sf::Time elapsed = clock.restart();
       float secs;
       if(fintime==0){
            secs = clock.getElapsedTime().asSeconds();
       }else{
           secs = fintime;
       }
        
        text.setString(std::to_string(secs));
        if(rand()%1000==1){
            arr.push_back(new Sand(0,0));
        }
        App.clear();
        for(Sand* i : arr){
            i->update(&buffer);
            if(*i==rectangle){
                rectangle.setFillColor(sf::Color(255,0,0));
                if(fintime == 0){
                    fintime = clock.restart().asSeconds();
                }
                i->reverse(&buffer);
            }
        }
        texture.loadFromImage(buffer);
        sprite.setTexture(texture, true);
        App.draw(sprite);
        App.draw(rectangle);
        App.draw(text);
        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
