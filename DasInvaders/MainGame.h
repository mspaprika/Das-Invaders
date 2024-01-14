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


const Point2D PLAYER_POS = { LEFT_LIMIT, DISPLAY_HEIGHT / 2 + 300 };

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
	TYPE_UFO,
};

enum InvaderType
{
	INVADER_A,
	INVADER_B,
	INVADER_C,
	INVADER_UFO,
};

struct Invader
{
	InvaderType type;
	int id;
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

	int score = 0;
	int lives = 3;
	int level = 1;
};


// Functions
void Draw();
void DrawObjects(int TYPE);

void UpdateGameStates();
void CreateGameObjects();