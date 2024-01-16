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


// Main Functions
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
			UpdateLasers();
			UpdatePlayer();
			UpdateInvaders();
			UpdateShields();
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

	UpdateDestroyed();
}

void Draw()
{
	Play::ClearDrawingBuffer(Play::cBlack);

	DrawObjects(TYPE_INVADER);
	DrawObjects(TYPE_PLAYER);
	DrawObjects(TYPE_SHIELD);
	DrawObjects(TYPE_LASER);

	DrawGameStats();

	Play::PresentDrawingBuffer();
}

void DrawObjects(int TYPE)
{
	std::vector <int> vObjects = Play::CollectGameObjectIDsByType(TYPE);
	for (int id : vObjects) Play::DrawObjectRotated(Play::GetGameObject(id));
}

void DrawGameStats()
{
	//Play::DrawFontText("64", std::to_string(gState.invTimer), { 150, 150 }, Play::CENTRE);
}

void CreateGameObjects()
{
	int id = Play::CreateGameObject(TYPE_PLAYER, { PLAYER_POS }, 10, SPR_CANNON);
	Play::GetGameObject(id).scale = SPRITE_SCALE;
	Player player;

	int vectorID = 0;


	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < MAX_INVADERS_A; j++)
		{
			int id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + j * INVADER_SPACING, TOP_LIMIT + i * INVADER_SPACING }, 10, SPR_INVADER_A);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Play::GetGameObject(id).velocity.x = INVADER_SPEED;
			Invader invader;
			invader.type = INVADER_A;
			invader.id = id;
			invader.vectorID = vectorID;
			invader.active = false;
			invader.prevSpeed = INVADER_SPEED;
			vInvaders.push_back(invader);
			vectorID++;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVADERS_B; j++)
		{
			int id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + j * INVADER_SPACING, TOP_LIMIT + (INVADER_SPACING * 1) + i * INVADER_SPACING }, 10, SPR_INVADER_B);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Play::GetGameObject(id).velocity.x = INVADER_SPEED;
			Invader invader;
			invader.type = INVADER_B;
			invader.id = id;
			invader.vectorID = vectorID;
			invader.active = false;
			invader.prevSpeed = INVADER_SPEED;
			vInvaders.push_back(invader);
			vectorID++;
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVADERS_C; j++)
		{
			int id = Play::CreateGameObject(TYPE_INVADER, { LEFT_LIMIT + j * INVADER_SPACING, TOP_LIMIT + (INVADER_SPACING * 3) + i * INVADER_SPACING }, 10, SPR_INVADER_C);
			Play::GetGameObject(id).scale = SPRITE_SCALE;
			Play::GetGameObject(id).velocity.x = INVADER_SPEED;
			Invader invader;
			invader.type = INVADER_C;
			invader.id = id;
			invader.vectorID = vectorID;
			invader.active = (i > 0) ?  true : false;
			invader.prevSpeed = INVADER_SPEED;

			vInvaders.push_back(invader);
			vectorID++;


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


// Player
void PlayerControls(GameObject& player)
{
	if (Play::KeyDown(VK_LEFT))
	{
		player.pos.x -= PLAYER_SPEED;
	}
	if (Play::KeyDown(VK_RIGHT))
	{
		player.pos.x += PLAYER_SPEED;
	}
	if (Play::KeyPressed(VK_SPACE))
	{
		std::vector <int> vLasers = Play::CollectGameObjectIDsByType(TYPE_LASER);
		if (vLasers.size() == 0)
		{
			int id = Play::CreateGameObject(TYPE_LASER, { player.pos.x, player.pos.y - 50 }, 10, SPR_LASER);
			Play::GetGameObject(id).velocity.y = LASER_SPEED;
		}
	}
}


// Update Game Objects
void UpdatePlayer()
{
	GameObject& objPlayer = Play::GetGameObjectByType(TYPE_PLAYER);
	PlayerControls(objPlayer);

	Play::UpdateGameObject(objPlayer);
}

void UpdateInvaders()
{
	for (Invader& invader : vInvaders)
	{
		if (invader.active)	LaserCollisions(invader);
		if (invader.active)	InvaderControls(invader);

		InvaderMovement(invader);

		Play::UpdateGameObject(Play::GetGameObject(invader.id));
	}
}

void UpdateShields()
{
	for (Shield& shield : vShields)
	{
		GameObject& objShield = Play::GetGameObject(shield.id);

		Play::UpdateGameObject(objShield);
	}
}

void UpdateLasers()
{
	std::vector <int> vLasers = Play::CollectGameObjectIDsByType(TYPE_LASER);
	for (int id : vLasers)
	{
		GameObject& objLaser = Play::GetGameObject(id);

		if (objLaser.pos.y < 0.f) objLaser.type = TYPE_DESTROYED;

		Play::UpdateGameObject(objLaser);
	}
}

void UpdateDestroyed()
{
	std::vector <int> vObjects = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
	for (int id : vObjects) Play::DestroyGameObject(id);
}


// Invaders
void LaserCollisions(Invader& invader)
{
	std::vector <int> vLasers = Play::CollectGameObjectIDsByType(TYPE_LASER);
	GameObject& objInvader = Play::GetGameObject(invader.id);

	for (int id : vLasers)
	{
		GameObject& objLaser = Play::GetGameObject(id);

		if (Play::IsColliding(objInvader, objLaser))
		{
			objLaser.velocity.y = 0.f;
			objLaser.type = TYPE_DESTROYED;
			objInvader.type = TYPE_DESTROYED;
			invader.active = false;
			invader.shot = true;

			if (invader.type != INVADER_A) vInvaders[invader.vectorID - MAX_INVADERS_C].active = true;
		}
	}
}

void InvaderControls(Invader& invader)
{
	GameObject& objInvader = Play::GetGameObject(invader.id);
	GameObject& objPlayer = Play::GetGameObjectByType(TYPE_PLAYER);

	if (objInvader.pos.x > objPlayer.pos.x - 10 && objInvader.pos.x < objPlayer.pos.x + 10)
	{
		int id = Play::CreateGameObject(TYPE_INVADER_LASER, { objInvader.pos.x, objInvader.pos.y + 50 }, 10, SPR_LASER);
		Play::GetGameObject(id).velocity.y = -LASER_SPEED;
	}

	
}

void InvaderMovement(Invader& invader)
{
	GameObject& objInvader = Play::GetGameObject(invader.id);
	
	if (objInvader.pos.x > INVADER_LIM_RIGHT || objInvader.pos.x < INVADER_LIM_LEFT )
	{
		if (objInvader.pos.x != 0.f)
		{
			invader.prevSpeed = objInvader.velocity.x;
			AllDrop();
			AllReverse();
		}
	}
}

void SetTarget(GameObject& invader, Invader& sInvader)
{
	if (invader.velocity.x > 0.f) sInvader.targetPos = invader.oldPos.x + INVADER_MOVE;
	else if (invader.velocity.x < 0.f) sInvader.targetPos = invader.oldPos.x - INVADER_MOVE;

	sInvader.targetSet = true;
	
}

void AllDrop()
{
	for (Invader& invader : vInvaders)
	{
		if (invader.shot) continue;
		GameObject& objInvader = Play::GetGameObject(invader.id);

		(objInvader.velocity.x > 0.f) ? objInvader.pos.x -= 1 : objInvader.pos.x += 1;
		objInvader.pos.y += INVADER_DROP;
		invader.prevSpeed = objInvader.velocity.x;
		objInvader.velocity.x = 0.f;
	}
}

void AllReverse()
{
	for (Invader& invader : vInvaders)
	{
		GameObject& objInvader = Play::GetGameObject(invader.id);

		objInvader.velocity.x = invader.prevSpeed * (-1);
	}
}



void AllMove()
{
	for (Invader& invader : vInvaders)
	{
		GameObject& objInvader = Play::GetGameObject(invader.id);

		objInvader.velocity.x = invader.prevSpeed;
	}
}

void AllStop()
{
	for (Invader& invader : vInvaders)
	{
		GameObject& objInvader = Play::GetGameObject(invader.id);

		objInvader.velocity.x = 0.f;
	}
}	








