#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Fonts.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	// Loading Player

	player = (Player*)app->entityManager->CreateEntity(EntityType::BALL);
	player->parameters = config.child("player");

	// Enemy Animations

	for (int i = 0; i < 3; i++) {

		star.PushBack({ 32 * i,0,32,32 });

	}
	star.loop = true;
	star.speed = 0.04f;

	for (int i = 0; i < 2; i++) {

		starryBall.PushBack({32 * i,0,32,32});

	}
	starryBall.loop = true;
	starryBall.speed = 0.04f;

	for (int i = 0; i < 3; i++) {

		eyeCloud.PushBack({ 48 * i,0,48,46 });

	}
	eyeCloud.loop = true;
	eyeCloud.speed = 0.04f;

	for (int i = 0; i < 4; i++) {

		quintupleEye.PushBack({ 68 * i,0,68,68 });

	}
	quintupleEye.loop = true;
	quintupleEye.speed = 0.04f;

	for (int i = 0; i < 3; i++) {

		moon.PushBack({ 44 * i,0,44,42 });

	}
	moon.loop = true;
	moon.speed = 0.04f;

	for (int i = 0; i < 6; i++) {

		sun.PushBack({ 48 * i,0,48,56 });

	}
	sun.loop = true;
	sun.speed = 0.04f;

	for (int i = 0; i < 4; i++) {

		whiteFace.PushBack({ 32 * i,0,32,32 });

	}
	whiteFace.loop = true;
	whiteFace.speed = 0.04f;

	for (int i = 0; i < 4; i++) {

		blackFace.PushBack({ 32 * i,0,32,32 });

	}
	blackFace.loop = true;
	blackFace.speed = 0.04f;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	app->win->SetTitle("Pinball");

	// SCORE

	char lookupTable[] = { "0123456789" };

	scoreFont = app->fonts->Load("Assets/Fonts/SpriteSheet-Numbers.png", lookupTable, 1);

	score = 0;

	// MAP

	mapaPinball = app->tex->Load("Assets/Maps/MapaPinball.png");

	star_tex = app->tex->Load("Assets/Textures/Spritesheet_Star.png");

	app->audio->PlayMusic("Assets/Audio/Music/StageTheme.ogg");

	int pinballWalls[] = { 226 * 1.75,0 * 1.4,
					 0 * 1.75,0 * 1.4,
					 0 * 1.75,604 * 1.4,
					 55 * 1.75,604 * 1.4,
					 33 * 1.75,594 * 1.4,
					 20 * 1.75,588 * 1.4,
					 17 * 1.75,581 * 1.4,
					 17 * 1.75,535 * 1.4,
					 23 * 1.75,526 * 1.4,
					 32 * 1.75,523 * 1.4,
					 32 * 1.75,501 * 1.4,
					 19 * 1.75,490 * 1.4,
					 9 * 1.75,476 * 1.4,
					 8 * 1.75,435 * 1.4,
					 13 * 1.75,425 * 1.4,
					 22 * 1.75,420 * 1.4,
					 62 * 1.75,419 * 1.4,
					 72 * 1.75,425 * 1.4,
					 76 * 1.75,433 * 1.4,
					 76 * 1.75,454 * 1.4,
					 84 * 1.75,443 * 1.4,
					 84 * 1.75,415 * 1.4,
					 51 * 1.75,398 * 1.4,
					 16 * 1.75,378 * 1.4,
					 16 * 1.75,329 * 1.4,
					 21 * 1.75,320 * 1.4,
					 30 * 1.75,316 * 1.4,
					 30 * 1.75,278 * 1.4,
					 7 * 1.75,254 * 1.4,
					 7 * 1.75,228 * 1.4,
					 16 * 1.75,217 * 1.4,
					 87 * 1.75,217 * 1.4,
					 87 * 1.75,210 * 1.4,
					 20 * 1.75,178 * 1.4,
					 16 * 1.75,170 * 1.4,
					 16 * 1.75,124 * 1.4,
					 22 * 1.75,114 * 1.4,
					 30 * 1.75,110 * 1.4,
					 30 * 1.75,102 * 1.4,
					 13 * 1.75,99 * 1.4,
					 9 * 1.75,91 * 1.4,
					 9 * 1.75,23 * 1.4,
					 12 * 1.75,15 * 1.4,
					 21 * 1.75,10 * 1.4,
					 203 * 1.75,10 * 1.4,
					 212 * 1.75,15 * 1.4,
					 216 * 1.75,23 * 1.4,
					 216 * 1.75,90 * 1.4,
					 211 * 1.75,98 * 1.4,
					 203 * 1.75,102 * 1.4,
					 194 * 1.75,102 * 1.4,
					 194 * 1.75,110 * 1.4,
					 203 * 1.75,114 * 1.4,
					 207 * 1.75,120 * 1.4,
					 208 * 1.75,124 * 1.4,
					 208 * 1.75,170 * 1.4,
					 205 * 1.75,176 * 1.4,
					 137 * 1.75,211 * 1.4,
					 137 * 1.75,219 * 1.4,
					 207 * 1.75,219 * 1.4,
					 214 * 1.75,223 * 1.4,
					 217 * 1.75,227 * 1.4,
					 217 * 1.75,253 * 1.4,
					 215 * 1.75,258 * 1.4,
					 196 * 1.75,277 * 1.4,
					 194 * 1.75,280 * 1.4,
					 194 * 1.75,316 * 1.4,
					 204 * 1.75,320 * 1.4,
					 207 * 1.75,329 * 1.4,
					 208 * 1.75,330 * 1.4,
					 208 * 1.75,377 * 1.4,
					 205 * 1.75,382 * 1.4,
					 140 * 1.75,415 * 1.4,
					 140 * 1.75,442 * 1.4,
					 146 * 1.75,454 * 1.4,
					 147 * 1.75,454 * 1.4,
					 147 * 1.75,435 * 1.4,
					 148 * 1.75,434 * 1.4,
					 150 * 1.75,430 * 1.4,
					 154 * 1.75,424 * 1.4,
					 163 * 1.75,420 * 1.4,
					 202 * 1.75,420 * 1.4,
					 212 * 1.75,425 * 1.4,
					 216 * 1.75,434 * 1.4,
					 217 * 1.75,435 * 1.4,
					 217 * 1.75,474 * 1.4,
					 215 * 1.75,479 * 1.4,
					 194 * 1.75,501 * 1.4,
					 194 * 1.75,521 * 1.4,
					 203 * 1.75,525 * 1.4,
					 207 * 1.75,534 * 1.4,
					 208 * 1.75,535 * 1.4,
					 208 * 1.75,581 * 1.4,
					 205 * 1.75,587 * 1.4,
					 170 * 1.75,604 * 1.4,
					 226 * 1.75,604 * 1.4,
					 226 * 1.75,0 * 1.4 };

	PhysBody* c_pinballWalls = app->physics->CreateChain(0, 0, pinballWalls, sizeof(pinballWalls) / sizeof(pinballWalls[0]), bodyType::STATIC);

	int lever1Left_Support[] = { 59,178,
				67,178,
				67,212,
				121,234,
				116,239,
				114,247,
				59,225,
				59,178 };

	PhysBody* c_lever1Left_Support = app->physics->CreateChain(0, 0, lever1Left_Support, sizeof(lever1Left_Support) / sizeof(lever1Left_Support[0]), bodyType::STATIC);

	int lever2Left_Support[] = { 59,178 + 288,
					67,178 + 288,
					67,212 + 288,
					121,234 + 288,
					116,239 + 288,
					114,247 + 288,
					59,225 + 288,
					59,178 + 288 };

	PhysBody* c_lever2Left_Support = app->physics->CreateChain(0, 0, lever2Left_Support, sizeof(lever2Left_Support) / sizeof(lever2Left_Support[0]), bodyType::STATIC);

	int lever3Left_Support[] = { 59,178 + 576,
					67,178 + 576,
					67,212 + 576,
					121,234 + 576,
					116,239 + 576,
					114,247 + 576,
					59,225 + 576,
					59,178 + 576 };

	PhysBody* c_lever3Left_Support = app->physics->CreateChain(0, 0, lever3Left_Support, sizeof(lever3Left_Support) / sizeof(lever3Left_Support[0]), bodyType::STATIC);

	int lever1Right_Support[] = { 335,178,
								327,178,
								327,211,
								273,234,
								278,239,
								279,247,
								335,225,
								335,178 };

	PhysBody* c_lever1Right_Support = app->physics->CreateChain(0, 0, lever1Right_Support, sizeof(lever1Right_Support) / sizeof(lever1Right_Support[0]), bodyType::STATIC);

	int lever2Right_Support[] = { 335,178 + 288,
								327,178 + 288,
								327,211 + 288,
								273,234 + 288,
								278,239 + 288,
								279,247 + 288,
								335,225 + 288,
								335,178 + 288 };

	PhysBody* c_lever2Right_Support = app->physics->CreateChain(0, 0, lever2Right_Support, sizeof(lever2Right_Support) / sizeof(lever2Right_Support[0]), bodyType::STATIC);

	int lever3Right_Support[] = { 335,178 + 576,
								327,178 + 576,
								327,211 + 576,
								273,234 + 576,
								278,239 + 576,
								279,247 + 576,
								335,225 + 576,
								335,178 + 576 };

	PhysBody* c_lever3Right_Support = app->physics->CreateChain(0, 0, lever3Right_Support, sizeof(lever3Right_Support) / sizeof(lever3Right_Support[0]), bodyType::STATIC);

	int triangle1Left[] = { 101,177,
							123,203,
							123,210,
							113,210,
							92,200,
							93,177,
							101,177 };

	PhysBody* c_triangle1Left = app->physics->CreateChain(0, 0, triangle1Left, sizeof(triangle1Left) / sizeof(triangle1Left[0]), bodyType::STATIC);

	int triangle2Left[] = { 101,177 + 288,
							123,203 + 288,
							123,210 + 288,
							113,210 + 288,
							92,200 + 288,
							93,177 + 288,
							101,177 + 288 };

	PhysBody* c_triangle2Left = app->physics->CreateChain(0, 0, triangle2Left, sizeof(triangle2Left) / sizeof(triangle2Left[0]), bodyType::STATIC);

	int triangle3Left[] = { 101,177 + 576,
							123,203 + 576,
							123,210 + 576,
							113,210 + 576,
							92,200 + 576,
							93,177 + 576,
							101,177 + 576 };

	PhysBody* c_triangle3Left = app->physics->CreateChain(0, 0, triangle3Left, sizeof(triangle3Left) / sizeof(triangle3Left[0]), bodyType::STATIC);

	int triangle1Right[] = { 300,178,
							295,178,
							272,204,
							272,210,
							284,210,
							304,201,
							303,178,
							300,178 };

	PhysBody* c_triangle1Right = app->physics->CreateChain(0, 0, triangle1Right, sizeof(triangle1Right) / sizeof(triangle1Right[0]), bodyType::STATIC);

	int triangle2Right[] = { 300,178 + 288,
							295,178 + 288,
							272,204 + 288,
							272,210 + 288,
							284,210 + 288,
							304,201 + 288,
							303,178 + 288,
							300,178 + 288 };

	PhysBody* c_triangle2Right = app->physics->CreateChain(0, 0, triangle2Right, sizeof(triangle2Right) / sizeof(triangle2Right[0]), bodyType::STATIC);

	int triangle3Right[] = { 300,178 + 576,
							295,178 + 576,
							272,204 + 576,
							272,210 + 576,
							284,210 + 576,
							304,201 + 576,
							303,178 + 576,
							300,178 + 576 };

	PhysBody* c_triangle3Right = app->physics->CreateChain(0, 0, triangle3Right, sizeof(triangle3Right) / sizeof(triangle3Right[0]), bodyType::STATIC);

	// LEVERS

	leftLever = app->tex->Load("Assets/Maps/Left_Lever.png");

	rightLever = app->tex->Load("Assets/Maps/Right_Lever.png");

	lever1_left = app->physics->CreateLeftLever(132, 247, 53, 16, 15, bodyType::DYNAMIC);
	lever1_left->ctype = ColliderType::LEVER;

	lever2_left = app->physics->CreateLeftLever(132, 535, 53, 16, 15, bodyType::DYNAMIC);
	lever2_left->ctype = ColliderType::LEVER;

	lever3_left = app->physics->CreateLeftLever(132, 823, 53, 16, 15, bodyType::DYNAMIC);
	lever3_left->ctype = ColliderType::LEVER;

	lever1_right = app->physics->CreateRightLever(266, 247, 53, 16, 165, bodyType::DYNAMIC);
	lever1_right->ctype = ColliderType::LEVER;

	lever2_right = app->physics->CreateRightLever(266, 535, 53, 16, 165, bodyType::DYNAMIC);
	lever2_right->ctype = ColliderType::LEVER;

	lever3_right = app->physics->CreateRightLever(266, 823, 53, 16, 165, bodyType::DYNAMIC);
	lever3_right->ctype = ColliderType::LEVER;

	// REVOLUTE JOINT

	PhysBody* rectangleJoint1_left = app->physics->CreateRectangle(132, 247, 5, 5, bodyType::STATIC);

	PhysBody* rectangleJoint2_left = app->physics->CreateRectangle(132, 535, 5, 5, bodyType::STATIC);

	PhysBody* rectangleJoint3_left = app->physics->CreateRectangle(132, 823, 5, 5, bodyType::STATIC);

	PhysBody* rectangleJoint1_right = app->physics->CreateRectangle(264, 245, 5, 5, bodyType::STATIC);

	PhysBody* rectangleJoint2_right = app->physics->CreateRectangle(264, 535, 5, 5, bodyType::STATIC);

	PhysBody* rectangleJoint3_right = app->physics->CreateRectangle(264, 823, 5, 5, bodyType::STATIC);

	app->physics->CreateRevoluteJoint(rectangleJoint1_left, { 0, 0 }, lever1_left, { 0, 0 }, 30, 15, 0, false, true);

	app->physics->CreateRevoluteJoint(rectangleJoint2_left, { 0, 0 }, lever2_left, { 0, 0 }, 30, 15, 0, false, true);

	app->physics->CreateRevoluteJoint(rectangleJoint3_left, { 0, 0 }, lever3_left, { 0, 0 }, 30, 15, 0, false, true);

	app->physics->CreateRevoluteJoint(rectangleJoint1_right, { 0, 0 }, lever1_right, { 0, 0 }, 0, 45, 165, false, true);

	app->physics->CreateRevoluteJoint(rectangleJoint2_right, { 0, 0 }, lever2_right, { 0, 0 }, 0, 45, 165, false, true);

	app->physics->CreateRevoluteJoint(rectangleJoint3_right, { 0, 0 }, lever3_right, { 0, 0 }, 0, 45, 165, false, true);

	leverMove = app->audio->LoadFx("Assets/Audio/Fx/LeverMove.wav");

	// ENEMIES

	starryBall_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy1.png");
	eyeCloud_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy2.png");
	quintupleEye_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy3.png");
	moon_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy4.png");
	sun_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy5.png");
	whiteFace_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy6.png");
	blackFace_tex = app->tex->Load("Assets/Textures/SpriteSheet-Enemy7.png");

	PhysBody* starryBall_coll_left = app->physics->CreateCircleEnemy(76, 646, 16, bodyType::STATIC);
	starryBall_coll_left->ctype = ColliderType::ENEMY;

	PhysBody* starryBall_coll_right = app->physics->CreateCircleEnemy(321, 646, 16, bodyType::STATIC);
	starryBall_coll_right->ctype = ColliderType::ENEMY;

	PhysBody* eyeCloud_coll = app->physics->CreateCircleEnemy(198, 169, 24, bodyType::STATIC);
	eyeCloud_coll->ctype = ColliderType::ENEMY;

	/*PhysBody* quintupleEye_coll = app->physics->CreateCircleEnemy(76, 646, 16, bodyType::STATIC);
	quintupleEye_coll->ctype = ColliderType::ENEMY;*/

	PhysBody* moon_coll = app->physics->CreateCircleEnemy(123, 422, 18, bodyType::STATIC);
	moon_coll->ctype = ColliderType::ENEMY;

	PhysBody* sun_coll = app->physics->CreateCircleEnemy(279, 423, 20, bodyType::STATIC);
	sun_coll->ctype = ColliderType::ENEMY;

	PhysBody* whiteFace_coll = app->physics->CreateCircleEnemy(321, 350, 16, bodyType::STATIC);
	whiteFace_coll->ctype = ColliderType::ENEMY;

	PhysBody* blackFace_coll = app->physics->CreateCircleEnemy(76, 350, 16, bodyType::STATIC);
	blackFace_coll->ctype = ColliderType::ENEMY;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L03: DONE 3: Request App to Load / Save when pressing the keys F5 (save) / F6 (load)

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {

		app->audio->PlayFx(leverMove);

	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {

		app->audio->PlayFx(leverMove);

	}


	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {

		lever1_left->body->ApplyForce({ 10, 80 }, { 0, 0 }, true);

		lever2_left->body->ApplyForce({ 10, 80 }, { 0, 0 }, true);

		lever3_left->body->ApplyForce({ 10, 80 }, { 0, 0 }, true);

	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {

		lever1_right->body->ApplyForce({ -10, -80 }, { 0, 0 }, true);

		lever2_right->body->ApplyForce({ -10, -80 }, { 0, 0 }, true);

		lever3_right->body->ApplyForce({ -10, -80 }, { 0, 0 }, true);

	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {

		if (!app->physics->debug) app->physics->debug = true;
		else app->physics->debug = false;

	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {

		app->scene->player->KirbyBall->body->SetTransform({ PIXEL_TO_METERS(50),PIXEL_TO_METERS(50) }, 0);

	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

		score = 0;

	}

	if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {

		score = 99999999;

	}

	// Map

	app->render->DrawTexture(mapaPinball, 0, 0, nullptr, 1.0f);

	// Levers

	app->render->DrawTexture(leftLever, 132 - 12, 247 - 10, NULL, 1.0f, lever1_left->GetRotation(), 10, 10);

	app->render->DrawTexture(rightLever, 266 - 13, 245 - 12, NULL, 1.0f, lever1_right->GetRotation(), 11, 11);

	app->render->DrawTexture(leftLever, 132 - 12, 535 - 10, NULL, 1.0f, lever2_left->GetRotation(), 10, 10);

	app->render->DrawTexture(rightLever, 266 - 13, 523, NULL, 1.0f, lever2_right->GetRotation(), 11, 11);

	app->render->DrawTexture(leftLever, 132 - 12, 823 - 10, NULL, 1.0f, lever3_left->GetRotation(), 10, 10);

	app->render->DrawTexture(rightLever, 266 - 13, 811, NULL, 1.0f, lever3_right->GetRotation(), 11, 11);

	sprintf_s(scoreText, 10, "%8d", score);

	app->fonts->BlitText(63, 57, scoreFont, scoreText);

	star.Update();
	starryBall.Update();
	eyeCloud.Update();
	//quintupleEye.Update();
	moon.Update();
	sun.Update();
	whiteFace.Update();
	blackFace.Update();

	SDL_Rect star_rect = star.GetCurrentFrame();
	app->render->DrawTexture(star_tex, 36, 36, &star_rect);

	SDL_Rect starryBall_rect = starryBall.GetCurrentFrame();
	app->render->DrawTexture(starryBall_tex, 60, 630, &starryBall_rect);

	app->render->DrawTexture(starryBall_tex, 305, 630, &starryBall_rect);

	SDL_Rect eyeCloud_rect = eyeCloud.GetCurrentFrame();
	app->render->DrawTexture(eyeCloud_tex, 174, 145, &eyeCloud_rect);

	/*SDL_Rect quintupleEye_rect = quintupleEye.GetCurrentFrame();
	app->render->DrawTexture(quintupleEye_tex, 164, 145, &quintupleEye_rect);*/

	SDL_Rect moon_rect = moon.GetCurrentFrame();
	app->render->DrawTexture(moon_tex, 100, 400, &moon_rect);

	SDL_Rect sun_rect = sun.GetCurrentFrame();
	app->render->DrawTexture(sun_tex, 255, 395, &sun_rect);

	SDL_Rect whiteFace_rect = whiteFace.GetCurrentFrame();
	app->render->DrawTexture(whiteFace_tex, 60, 335, &whiteFace_rect);

	SDL_Rect blackFace_rect = blackFace.GetCurrentFrame();
	app->render->DrawTexture(blackFace_tex, 305, 335, &blackFace_rect);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
