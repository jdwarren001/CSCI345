// Example program:
// Using SDL2 to create an application window

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <map>
#include "Exception.hpp"
#include "MediaManager.hpp"
#include "Game.hpp"
#include "Particle.hpp"
#include <math.h>

using namespace std;

class MyParticle:public Particle {
	Mix_Chunk *sample;
	public:
	MyParticle(SDL_Renderer *ren,Animation *a,Mix_Chunk *newSample,SDL_Rect *src,
	  double x,double y,double vx,double vy,double ax,double ay):
	  Particle(ren,a,src,x,y,vx,vy,ax,ay) {
		  sample=newSample;
	}
	void collision() {
		Mix_PlayChannel(-1,sample,0);
	}
};

class MyGame:public Game{	  
    SDL_Rect src;
    vector<Particle *> particles;
    Animation a,b,c;
	Mix_Chunk *sound;
    int jx,jy;
	double theta;
	public:
	MyGame(int w=640,int h=480):Game("Galatic Battle Star",w,h) {
		theta = 0;
	  sound=media->readWav("media/crash.wav");
		c.read(media,"media/anim2.txt");
		src.x=0; src.y=0;
		SDL_QueryTexture(c.getTexture(), NULL, NULL, &src.w, &src.h);
		particles.push_back(new MyParticle(ren,&c,sound,&src,w/2-100,h/2-100,0,0,0,0));
		particles[0]->setBound(0,0,w,h);
      for (int i=1;i<=1;i++) { 
		 int vx=rand()%500 - 250;
		 int vy=rand()%500 - 250;
		 a.read(media,"media/anim1.txt");
	//	 SDL_Texture *bitmapTex=media->read("media/obsticle.bmp");
		 src.x=0; src.y=0;
		 SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
         particles.push_back(new MyParticle(ren,&a,sound,&src,w/2,h/2,0,0,0,0));
         particles[i]->setBound(0,0,w,h);
       }
       jx=w/2;
       jy=w/2;
       b.read(media,"media/background.txt");
       src.x=0; src.y=0; src.w=640; src.h=480;
	}
	void handleKeyUp(SDL_Event keyEvent) {
	}
	void handleKeyDown(SDL_Event keyEvent) {
		//cout << "KeyPress" << endl;
		if (keyEvent.key.keysym.sym==SDLK_SPACE)
		  particles[0]->incVelocity(0,-100);
	}
	void handleButtonDown(SDL_Event joyEvent) {
		if (joyEvent.jbutton.button==0 && joyEvent.jbutton.which==0)
		  particles[0]->incVelocity(0,-100);
	}
	void handleAxisMovement(SDL_Event joyEvent) {
		if (joyEvent.jaxis.axis==0 && joyEvent.jaxis.which==0)
		  jx=((joyEvent.jaxis.value)*100)/32768;
		if (joyEvent.jaxis.axis==1 && joyEvent.jaxis.which==0)
		  jy=((joyEvent.jaxis.value)*100)/32768;
		particles[0]->setAcceleration(jx,jy);
	}
	void update(double dt) {
      SDL_RenderClear(ren);

	  // Orbit Code
	  double orbitx=0;
	  double orbity=0;
	  double radius = 50;
	  int temp;

	  if(theta >= 45 && theta < 135 || theta >= 225 && theta < 315) { 
		temp = theta;
		temp %= 90;
		if (temp >= 45) {
			temp = 90-temp;
		}
		cout << temp << "blue" << endl;
		orbitx = radius * asin(temp * 3.14159 / 180.0);
	    orbity = radius * acos(temp * 3.14159 / 180.0);
	  }

	 else if(theta >= 315 || theta < 45  || theta >= 135 && theta < 225) {
		temp = theta;
		temp %= 90;
		if (temp >= 45) {
			temp = 90-temp;
		}
		cout << temp << "red" << endl;
		orbitx = radius * acos(temp * 3.14159 / 180.0);
	    orbity = radius * asin(temp * 3.14159 / 180.0);
	  }

	  if(theta >= 0 && theta <= 90) {
		  orbitx = particles[0]->getx() + orbitx;
		  orbity = particles[0]->gety() - orbity;
	  }
	  if(theta > 90 && theta <= 180) {
		  orbitx = particles[0]->getx() - orbitx;
		  orbity = particles[0]->gety() - orbity;
	  }
	  if(theta > 180 && theta <= 270) {
		  orbitx = particles[0]->getx() - orbitx;
		  orbity = particles[0]->gety() + orbity;
	  }
	  if(theta > 270 && theta <= 360) {
		  orbitx = particles[0]->getx() + orbitx;
		  orbity = particles[0]->gety() + orbity;
	  }

	  theta += 1;
	  if(theta >= 360) theta = 0;
	  particles[1]->setPosition(orbitx, orbity);
	  // End Orbit Code

      b.update(dt);
      
      SDL_RenderCopy(ren, b.getTexture(), &src, &src);
      for (unsigned i=0;i<particles.size();i++) 
        particles[i]->update(dt);
      SDL_RenderPresent(ren);
	}
	~MyGame() {
	}
};

int main(int argc, char* argv[]) {
    try {
		MyGame g;
		g.run();
	} catch (Exception e) {
		cerr << e ;
	}
	return 0;
}
