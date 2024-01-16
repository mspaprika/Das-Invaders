#pragma once


constexpr int DISPLAY_WIDTH = 1280;
constexpr int DISPLAY_HEIGHT = 720;
constexpr int DISPLAY_SCALE = 1;


// Sprites
const char* SPR_INVADER_A = "invaderA";
const char* SPR_INVADER_B = "invaderB";
const char* SPR_INVADER_C = "invaderC";

const char* SPR_CANNON = "cannon";
const char* SPR_BOMB = "bomb";
const char* SPR_LASER = "laser";
const char* SPR_UFO = "ufo";

const char* SPR_EXPLODE = "explode";
const char* SPR_DEAD = "dead";

const char* SPR_SHIELD_1 = "SpaceInvadersShield1";
const char* SPR_SHIELD_2 = "SpaceInvadersShield2";
const char* SPR_SHIELD_3 = "SpaceInvadersShield3";
const char* SPR_SHIELD_4 = "SpaceInvadersShield";

const float SPRITE_SCALE = 3.f;


// Sounds
const char* SND_UFO = "ufo";
const char* SND_UFO_KILL = "ufo_kill";
const char* SND_SHOOT = "shoot";
const char* SND_EXPLODE = "explode";
const char* SND_DEAD = "dead";
const char* SND_KILL = "kill";
const char* SND_INVADER_KILL = "invader_kill"; // .ogg
const char* SND_MOVE_A = "moveA";
const char* SND_MOVE_B = "moveB";


// constants
const int LEFT_LIMIT = DISPLAY_WIDTH / 2 - 300;
const int RIGHT_LIMIT = DISPLAY_WIDTH / 2 + 300;
const int TOP_LIMIT = DISPLAY_HEIGHT / 2 - 280;

const int INVADER_LIM_LEFT = LEFT_LIMIT - 50;
const int INVADER_LIM_RIGHT = RIGHT_LIMIT + 50;

const Point2D PLAYER_POS = { LEFT_LIMIT, DISPLAY_HEIGHT / 2 + 300 };
const float PLAYER_SPEED = 5.f;
const float LASER_SPEED = -10.f;
const float BOMB_SPEED = 5.f;
const float UFO_SPEED = 5.f;
const float INVADER_MOVE = 10.f;
const float INVADER_SPEED = 0.3f;
const float INVADER_DROP = 10.f;


const int MAX_INVADERS_A = 11;
const int MAX_INVADERS_B = 11;
const int MAX_INVADERS_C = 11;

const int INVADER_SPACING = 60;	
const int SHIELD_SPACING = 160;

// Structs and Enums
enum GameFlow
{
	STATE_IDLE,
	STATE_PLAY,
	STATE_GAMEOVER,
	STATE_WIN,
	STATE_PAUSE,
};

enum GameObjectType
{
	TYPE_PLAYER,
	TYPE_INVADER,
	TYPE_SHIELD,
	TYPE_BOMB,
	TYPE_LASER,
	TYPE_INVADER_LASER,
	TYPE_UFO,
	TYPE_DESTROYED,
};

enum InvaderType
{
	INVADER_A,
	INVADER_B,
	INVADER_C,
	INVADER_UFO,
};

struct Player
{
	int health{ 3 };
	int hits{ 0 };
};

struct Invader
{
	InvaderType type;
	int id;
	int vectorID;	
	bool active{ false };
	bool shot{ false };
	bool targetSet{ false };
	int targetPos{ 0 };

	float prevSpeed{ 0.f };
};

struct Shield
{
	int id;
	int health = 4;
	int hits = 0;
};

struct GameState
{
	GameFlow state = STATE_PLAY;

	int score{ 0 };
	int lives{ 3 };
	int level{ 1 };
};


// Functions
void Draw();
void DrawObjects(int TYPE);
void DrawGameStats();

void UpdateGameStates();
void CreateGameObjects();

void PlayerControls(GameObject& player);
void UpdateInvaders();
void UpdateShields();
void UpdatePlayer();
void UpdateLasers();

void UpdateDestroyed();
void LaserCollisions(Invader& invader);
void InvaderControls(Invader& invader);
void InvaderMovement(Invader& invader);
void AllDrop();
void SetTarget(GameObject& invader, Invader& sInvader);
void AllMove();
void AllStop();
void AllReverse();

