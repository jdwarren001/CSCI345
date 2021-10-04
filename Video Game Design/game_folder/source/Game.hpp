#pragma once

using namespace std;

class Game {
	protected:
	MediaManager *media;
	SDL_Window *window;
    SDL_Renderer *ren;
    int ticks; // ms ticks since start
    int w,h;
	public:
	Game(string title,int newW=640,int newH=480) {
		w=newW;
		h=newH;
		SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_GAMECONTROLLER|
		   SDL_INIT_AUDIO);
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
        if (Mix_Init(0)!=0) throw Exception("Mixer Error");
        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) throw Exception("Open Audio Failed");
        media=new MediaManager(ren);
        if(SDL_NumJoysticks()>0) SDL_JoystickOpen(0);
        ticks=SDL_GetTicks();
	}
	void run() {
	  int newTicks;
	  while (1) {
		newTicks=SDL_GetTicks();
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) break;
          else if (e.type==SDL_KEYDOWN) handleKeyDown(e);
          else if (e.type==SDL_KEYUP) handleKeyUp(e);
          else if (e.type==SDL_JOYBUTTONDOWN) handleButtonDown(e);
          else if (e.type==SDL_JOYBUTTONUP) handleButtonUp(e);
          else if (e.type==SDL_JOYAXISMOTION) handleAxisMovement(e);
        }
        update(double(newTicks-ticks)/1000.0);  // seconds of elapsed time
        ticks=newTicks;
      //  SDL_Delay(100);
      }
	}
	virtual void update(double dt/*s of elapsed time*/)=0;
	virtual void handleKeyDown(SDL_Event key)=0;
	virtual void handleKeyUp(SDL_Event key)=0;
	virtual void handleButtonDown(SDL_Event but){}
	virtual void handleButtonUp(SDL_Event but){}
	virtual void handleAxisMovement(SDL_Event move){}	
	~Game() {
	  SDL_DestroyRenderer(ren);
      SDL_DestroyWindow(window);
      SDL_Quit();
	}
};

