////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <iostream>
#include "GL/glu.h"
#include <vector>




////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////

int drawcube(float s, float dx, float dy, float dz){
    glBegin(GL_QUADS);//draw some squares
			glColor3i(0,1,1);
            glVertex3f(-s+dx, -s+dy, -s+dz);
            glVertex3f(-s+dx,  s+dy, -s+dz);
            glVertex3f( s+dx,  s+dy, -s+dz);
            glVertex3f( s+dx, -s+dy, -s+dz);

			glColor3f(0,1,1);
            glVertex3f(-s+dx, -s+dy, s+dz);
            glVertex3f(-s+dx,  s+dy, s+dz);
            glVertex3f( s+dx,  s+dy, s+dz);
            glVertex3f( s+dx, -s+dy, s+dz);

			glColor3f(0,1,1);
            glVertex3f(-s+dx, -s+dy, -s+dz);
            glVertex3f(-s+dx,  s+dy, -s+dz);
            glVertex3f(-s+dx,  s+dy,  s+dz);
            glVertex3f(-s+dx, -s+dy,  s+dz);

			glColor3f(0,1,1);
            glVertex3f( s+dx, -s+dy, -s+dz);
            glVertex3f( s+dx,  s+dy, -s+dz);
            glVertex3f( s+dx,  s+dy,  s+dz);
            glVertex3f( s+dx, -s+dy,  s+dz);

			glColor3f(0,1,1);
            glVertex3f(-s+dx, -s+dy,  s+dz);
            glVertex3f(-s+dx, -s+dy, -s+dz);
            glVertex3f( s+dx, -s+dy, -s+dz);
            glVertex3f( s+dx, -s+dy,  s+dz);

			glColor3f(0,1,1);
            glVertex3f(-s+dx, s+dy,  s+dz);
            glVertex3f(-s+dx, s+dy, -s+dz);
            glVertex3f( s+dx, s+dy, -s+dz);
            glVertex3f( s+dx, s+dy,  s+dz);

        glEnd();
}


int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML OpenGL");

    // Create a clock for measuring time elapsed
    sf::Clock Clock;
	
    //prepare OpenGL surface for HSR
	glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar

    std::vector<std::vector<std::vector<int>>> coords(10, std::vector<std::vector<int>>(10, std::vector<int>(10)));

    for(int x = 0;x<10;x++){
            for(int y = 0;y<10;y++){
                for(int z = 0;z<10;z++){
                    if(rand()%100>30){
                        coords[x][y][z]=1;
                    }else{
                        coords[x][y][z]=0;
                    }
                }
            }
        }

    bool rotate=true;
	float angle;
	
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
				rotate=!rotate;
			}
 
		}
        
        //Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
		
		if(rotate){
			angle=Clock.getElapsedTime().asSeconds();
		}
		glRotatef(angle * 50, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 90, 0.f, 0.f, 1.f);
			
		
		 
		//Draw a cube
        
        for(int x = 0;x<10;x++){
            for(int y = 0;y<10;y++){
                for(int z = 0;z<10;z++){
                    if(coords[x][y][z]==1){
                        drawcube(2.f,x*10.f,y*10.f,z*10.f);
                    }
                }
            }
        }
        

        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
