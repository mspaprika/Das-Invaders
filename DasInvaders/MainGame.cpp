#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "MainGame.h"


GameState gState;

std::vector <Invader> vInvaders;
std::vector <Shield> vShields;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();

	CreateGameObjects();
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	UpdateGameStates();
	Draw();

	return Play::KeyDown( VK_ESCAPE );
}


// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


// Functions
void UpdateGameStates()
{
	switch (gState.state)
	{
		case STATE_IDLE:
		{
			break;
		}
		case STATE_PLAY:
		{
			break;
		}
		case STATE_GAMEOVER:
		{
			break;
		}
		case STATE_WIN:
		{
			break;
		}
		case STATE_PAUSE:
		{
			break;
		}
	}
}

void Draw()
{
	Play::ClearDrawingBuffer(Play::cBlack);

	DrawObjects(TYPE_INVADER);
	DrawObjects(TYPE_PLAYER);
	DrawObjects(TYPE_SHIELD);


	Play::PresentDrawingBuffer();
}

void DrawObjects(int TYPE)
{
	std::vector <int> vObjects = Play::CollectGameObjectIDsByType(TYPE);
	for (int id : vObjects) Play::DrawObjectRotated(Play::GetGameObject(id));
}


void CreateGameObjects()
{
	int id = Play::CreateGameObject(TYPE_PLAYER, { PLAYER_POS }, 10, SPR_CANNON);
	Play::GetGameObject(id).scale = SPRITE_SCALE;


	for (int i = 0; i < MAX_INVADERS_A; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + i * INVADER_SPACING, TOP_LIMIT + j * INVADER_SPACING }, 10, SPR_INVADER_A);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Invader invader;
			invader.type = INVADER_A;
			invader.id = id;
			vInvaders.push_back(invader);
		}
	}

	for (int i = 0; i < MAX_INVADERS_B; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + i * INVADER_SPACING, TOP_LIMIT + (INVADER_SPACING * 1) + j * INVADER_SPACING }, 10, SPR_INVADER_B);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Invader invader;
			invader.type = INVADER_B;
			invader.id = id;
			vInvaders.push_back(invader);
		}
	}
	
	for (int i = 0; i < MAX_INVADERS_C; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + i * INVADER_SPACING, TOP_LIMIT + (INVADER_SPACING * 3) + j * INVADER_SPACING }, 10, SPR_INVADER_C);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Invader invader;
			invader.type = INVADER_C;
			invader.id = id;
			vInvaders.push_back(invader);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		id = Play::CreateGameObject(TYPE_SHIELD, { LEFT_LIMIT + i * SHIELD_SPACING + 60, DISPLAY_HEIGHT / 2 + 250 }, 10, SPR_SHIELD_1);
		Play::GetGameObject(id).scale = SPRITE_SCALE + 1.f;
		Shield shield;
		shield.id = id;
		vShields.push_back(shield);
	}

}







