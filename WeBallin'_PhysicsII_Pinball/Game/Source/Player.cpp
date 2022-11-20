#include "Player.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"

Player::Player() : Entity(EntityType::BALL)
{
	name.Create("Player");

}

Player::~Player() {

}

bool Player::Awake() {


	return true;
}

bool Player::Start() {

	//initilize textures

	ball = app->tex->Load("Assets/Textures/KirbyBall.png");

	KirbyBall = app->physics->CreateCircle(50, 50, 8, bodyType::DYNAMIC);

	KirbyBall->listener = this;

	KirbyBall->ctype = ColliderType::BALL;

	enemies = app->audio->LoadFx("Assets/Audio/Fx/Enemies.wav");

	bounce = app->audio->LoadFx("Assets/Audio/Fx/Bounce.wav");

	return true;
}

bool Player::Update()
{

	b2Transform transform = KirbyBall->body->GetTransform();
	b2Vec2 pos = transform.p;

	int positionX = METERS_TO_PIXELS(pos.x) - 16;

	int positionY = METERS_TO_PIXELS(pos.y) - 16;

	app->render->DrawTexture(ball, positionX, positionY, NULL, 1.0f, KirbyBall->GetRotation());

	return true;
}

bool Player::CleanUp()
{

	return true;
}

void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::WALL:
		LOG("Collision WALL");

		app->audio->PlayFx(bounce);

		break;
	case ColliderType::ENEMY:
		LOG("Collision ENEMY");

		app->audio->PlayFx(enemies);

		app->scene->score += 240;

		break;
	case ColliderType::LEVER:
		LOG("Collision LEVER");

		app->audio->PlayFx(bounce);

		break;

	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");



		break;
	}

}