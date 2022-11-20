#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Player.h"
#include "Item.h"
#include "Animation.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	Player* player;

	int scoreFont = -1;

	uint score;

	char scoreText[10] = { "\0" };

	PhysBody* lever1_left; 

	PhysBody* lever2_left;

	PhysBody* lever3_left; 

	PhysBody* lever1_right; 

	PhysBody* lever2_right; 

	PhysBody* lever3_right; 

	uint leverMove = 0;

private:

	SDL_Texture* mapaPinball;

	SDL_Texture* leftLever;
	SDL_Texture* rightLever;

	Animation star;

	Animation starryBall;
	Animation eyeCloud;
	Animation quintupleEye;
	Animation moon;
	Animation sun;
	Animation whiteFace;
	Animation blackFace;

	SDL_Texture* star_tex;

	SDL_Texture* starryBall_tex;
	SDL_Texture* eyeCloud_tex;
	SDL_Texture* quintupleEye_tex;
	SDL_Texture* moon_tex;
	SDL_Texture* sun_tex;
	SDL_Texture* whiteFace_tex;
	SDL_Texture* blackFace_tex;

};

#endif // __SCENE_H__