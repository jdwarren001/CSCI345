// Example program:
// Using SDL2 to create an application window

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

class Exception {
	string description;
	public:
	Exception(string newDescription) {
		description=newDescription;
	}
	void fun(/* Exception *this */) {
	}
	friend ostream & operator << (ostream &out,const Exception &e) {
	  return out << "Error: "<<e.description  << endl;
	}
};

class Game {
	protected:
	SDL_Window *window;
    SDL_Renderer *ren;
    int ticks; // ms ticks since start
	public:
	Game(string title,int w=640,int h=480) {
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(
          title.c_str(),                  // window title
          SDL_WINDOWPOS_UNDEFINED,           // initial x position
          SDL_WINDOWPOS_UNDEFINED,           // initial y position
          w,                               // width, in pixels
          h,                               // height, in pixels
          SDL_WINDOW_OPENGL                  // flags - see below
        );
        if (window==NULL) throw Exception("Could not create window: ");
        ren=SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
        if (ren==NULL) throw Exception("Could not create renderer ");
        ticks=SDL_GetTicks();
	}
	void run() {
	  int newTicks;
	  while (1) {
		newTicks=SDL_GetTicks();
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
              break;
          }
        }
        update(newTicks-ticks);
        ticks=newTicks;
        SDL_Delay(100);
      }
	}
	virtual void update(int dt/*ms of elapsed time*/)=0;
	~Game() {
	  SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(window);
      SDL_Quit();
	}
};

class MyGame:public Game{
	SDL_Texture *bitmapTex;
      SDL_Rect src,dest;
	public:
	MyGame(int w=640,int h=480):Game("Karl was here",w,h) {
	  SDL_Surface *ob;
	  ob=SDL_LoadBMP("media/obsticle.bmp");
      if (ob==NULL) throw Exception("Could not load media/obsticle.bmp");
      src.w=ob->w;
      src.h=ob->h;
      dest.w=src.w;
      dest.h=src.h;
      src.x=0;
      src.y=0;
      dest.x=0;
      dest.y=0;
    
	  bitmapTex = SDL_CreateTextureFromSurface(ren, ob);
      if (bitmapTex==NULL) throw Exception ("Could not create texture");
      SDL_FreeSurface(ob);
	}
	void update(int dt) {
	  dest.x++;
      dest.y++;
      SDL_RenderClear(ren);
      SDL_RenderCopy(ren, bitmapTex, &src, &dest);
      SDL_RenderPresent(ren);
	}
	~MyGame() {
	  SDL_DestroyTexture(bitmapTex);
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
