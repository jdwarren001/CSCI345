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
    Animation a,b;
	Mix_Chunk *sound;
    int jx,jy;
	public:
	MyGame(int w=640,int h=480):Game("Karl was here",w,h) {
	  sound=media->readWav("media/crash.wav");
      for (int i=0;i<16;i++) { 
		 int vx=rand()%500 - 250;
		 int vy=rand()%500 - 250;
		 a.read(media,"media/anim1.txt");
	//	 SDL_Texture *bitmapTex=media->read("media/obsticle.bmp");
		 src.x=0; src.y=0;
		 SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
         particles.push_back(new MyParticle(ren,&a,sound,&src,w/2,h/2,vx,vy,0,50));
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
