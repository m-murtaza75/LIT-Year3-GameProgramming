/*
	STUDENT NAME: MUHAMMAD MURTAZA
	STUDENT ID: K00223470
	CA: 3
	SUBJECT: GAME PROGRAMMING

*/


#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "ZombieBullet.h"
#include "Pickup.h"

using namespace sf;

int main()
{
	// Here is the instabce of TextureHolder
	TextureHolder holder;

	// The game will always be in one of these states
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING, MAIN_MENU, HIGHSCORES, INSTRUCTIONS};

	// Start with the MAIN MENU state
	State state = State::MAIN_MENU;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);
	
	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// clock for everything else
	Clock clock;

	// clock for the shield pickup
	Clock shieldTimer;

	// clock for the zombie firing
	Clock zombieFireTimer;


	// How long has the PLAYING state been active
	Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = NULL;

	// 100 bullets
	Bullet bullets[100];

	int currentBullet = 0;
	int bulletsSpare = 6;
	int bulletsInClip = 6;
	int clipSize = 6;
	int bulletsToLoad = 0;
	float fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;


	// Zombie bullets
	const int ZOMBIE_BULLETS = 5;
	ZombieBullet zBullets[ZOMBIE_BULLETS];
	int currentZombieBullet = 0;
	
	

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);
	Pickup shieldPickup(3);

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/main-menu/game-over screen
	Sprite backgroundSprite;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/gameBackground.png");
	backgroundSprite.setTexture(textureGameOver);
	backgroundSprite.setPosition(0, 0);

	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	// Create sprite for the health icon
	Sprite spriteHealthIcon;
	Texture textureHealthIcon = TextureHolder::GetTexture("graphics/heart.png");
	spriteHealthIcon.setTexture(textureHealthIcon);
	spriteHealthIcon.setPosition(10, 70);

	// Load the font
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");


	//MAIN MENU
	Text mainMenuText;
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(90);
	mainMenuText.setFillColor(Color::White);
	mainMenuText.setPosition(500, 200);
	std::stringstream mainmenuStream;
	mainmenuStream <<
		"P- PLAY GAME\n\n" <<
		"I- INSTRUCTIONS\n\n" <<
		"H- HIGHSCORES\n\n" <<
		"E- EXIT\n";
	mainMenuText.setString(mainmenuStream.str());


	// Message to go back to main-menu
	Text goBackMessage;
	goBackMessage.setFont(font);
	goBackMessage.setCharacterSize(40);
	goBackMessage.setFillColor(Color::Red);
	goBackMessage.setPosition(500, 800);
	goBackMessage.setString("Press 'Backspace' to go back to Main-Menu");


	// Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	// Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(95);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(220, 320);
	gameOverText.setString("GameOver! Press Enter to play");

	// Levelling up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(60);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(170, 100);
	std::stringstream levelUpStream;
	levelUpStream <<
		"\t\t\tCongratulations! Level Cleared" <<
		"\n\n\nPlease choose an upgrade by pressing the number\n" <<
		"\n1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	// Instructions 
	Text instructionsText;
	instructionsText.setFont(font);
	instructionsText.setCharacterSize(60);
	instructionsText.setFillColor(Color::White);
	instructionsText.setPosition(170, 100);
	std::stringstream instructionsStream;
	instructionsStream <<
		"\t\t\t\t\t\tCONTROL INSTRUCTIONS \n\n" <<
		"W: Move Up\t\t\t" <<
		"    A: Move left\n\n" <<
		"S: Move Down\t\t\t" <<
		"D: Move Right\n\n" <<
		"Spacebar:  Reload\n\n" <<
		"Mouse-Left:  Fire";
	instructionsText.setString(instructionsStream.str());


	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/highscore.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1350, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// HIGHSCORE STATE TEXTS
	Text highscoreLabel;
	highscoreLabel.setFont(font);
	highscoreLabel.setCharacterSize(100);
	highscoreLabel.setFillColor(Color::Red);
	highscoreLabel.setPosition(580, 75);
	highscoreLabel.setString(" HIGH-SCORES ");

	Text ranks;
	ranks.setFont(font);
	ranks.setCharacterSize(80);
	ranks.setFillColor(Color::Red);
	ranks.setPosition(460, 270);
	std::stringstream ranksStream;
	ranksStream <<
		"Ranks\t\t\tScores\n" <<
		"\n1." <<
		"\n2." <<
		"\n3.";

	ranks.setString(ranksStream.str());

	std::string _1st;
	std::string _2nd;
	std::string _3rd;

	Text first;
	Text second;
	Text third;

	// Zombies remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1400, 980);
	zombiesRemainingText.setString("Zombies: ");

	// Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(1180, 980);
	waveNumberText.setString("Wave: ");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(70, 85);
		
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{

				/* START NEW-GAME from Main Menu */
				
				//If P key pressed

				if (event.key.code == Keyboard::P && state == State::MAIN_MENU)
				{
					//state = State::LEVELING_UP;
					state = State::PLAYING;


					// Increase the wave number
					wave++;

					// Prepare thelevel
					arena.width = 600 * wave;
					arena.height = 600 * wave;
					arena.left = 0;
					arena.top = 0;

					// Pass the vertex array by reference 
					// to the createBackground function
					int tileSize = createBackground(background, arena);

					// Spawn the player in the middle of the arena
					player.spawn(arena, resolution, tileSize);

					// Configure the pick-ups
					healthPickup.setArena(arena);
					ammoPickup.setArena(arena);
					shieldPickup.setArena(arena);

					// Create a horde of zombies
					numZombies = 4 * wave;

					// Delete the previously allocated memory (if it exists)
					delete[] zombies;
					zombies = createHorde(numZombies, arena);
					numZombiesAlive = numZombies;

					// Play the powerup sound
					powerup.play();

					// Reset the clock so there isn't a frame jump
					clock.restart();

				}
				else if (event.key.code == Keyboard::I && state == State::MAIN_MENU)
				{
					state = State::INSTRUCTIONS;
				}
				else if (event.key.code == Keyboard::H && state == State::MAIN_MENU)
				{
					state = State::HIGHSCORES;
				}
				else if(event.key.code == Keyboard::E && state == State::MAIN_MENU)
				{
					window.close();
				}


				// Pause a game while playing
				else if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
					wave = 0;
					score = 0;

					// Prepare the gun and ammo for next game
					currentBullet = 0;
					bulletsSpare = 24;
					bulletsInClip = 6;
					clipSize = 6;
					fireRate = 1;

					// Reset the player's stats
					player.resetPlayerStats();
				}
				// Going Back to MAIN_MENU
				else if (event.key.code == Keyboard::Backspace && state == State::INSTRUCTIONS)
				{
					state = State::MAIN_MENU;

				}
				else if (event.key.code == Keyboard::BackSpace &&
					state == State::GAME_OVER)
				{
					state = State::MAIN_MENU;
				}
				else if (event.key.code == Keyboard::Backspace && state == State::HIGHSCORES)
				{
					state = State::MAIN_MENU;

				}


				// Spin and zoom the world
				
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					mainView.rotate(.5f);
				}

				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					mainView.rotate(-.5f);
				}

				if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					mainView.zoom(.99f);
				}

				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					mainView.zoom(1.01f);
				}
				// End spinning and zooming

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::Space)
					{
						if (bulletsSpare >= clipSize && bulletsInClip < clipSize)
						{
							//Calculating how many bullets to add
							bulletsToLoad = clipSize - bulletsInClip;

							bulletsInClip = clipSize;
							bulletsSpare -= bulletsToLoad;
							reload.play();
						}
						else if (bulletsSpare < clipSize && bulletsSpare > 0)
						{
							//Calculating how many bullets to add
							bulletsToLoad = clipSize - bulletsInClip;

							if (bulletsToLoad > bulletsSpare)
							{
								bulletsInClip += (bulletsToLoad - bulletsSpare);
								bulletsSpare = 0;
							}
							else
							{
								bulletsInClip += bulletsToLoad;

								bulletsSpare -= bulletsToLoad;
							}
							
							reload.play();
						}
						else
						{
				
							reloadFailed.play();
						}
					}
				}

			}
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
				{

					// Pass the centre of the player and the centre of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
				}

			}// End fire a bullet



		}// End WASD while playing


		// Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			//player.increaseHealthLevel(100);

			// Handle the player levelling up
			if (event.key.code == Keyboard::Num1)
			{
				// Increase fire rate
				fireRate++;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				// Increase clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				// Increase health
				player.upgradeHealth();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				// Increase speed
				player.upgradeSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				healthPickup.upgrade();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				ammoPickup.upgrade();
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Increase the wave number
				wave++;

				// Prepare thelevel
				
				arena.width = 500 * wave;
				arena.height = 500 * wave;
				arena.left = 0;
				arena.top = 0;

				// Pass the vertex array by reference 
				// to the createBackground function
				int tileSize = createBackground(background, arena);

				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pick-ups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);
				shieldPickup.setArena(arena);

				// Create a horde of zombies
				numZombies = 5 * wave;

				// Delete the previously allocated memory (if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				// Play the powerup sound
				powerup.play();

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}

		}// End levelling up


		
		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;
			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position
			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player				
			mainView.setCenter(player.getCenter());

			// Loop through each Zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);

					//long t = zombies[i].getFireTimer();

					if (zombies[i].isFiring() && zombies[i].getFireTimer() > 3500)
					{
						zBullets[currentZombieBullet].shoot(
							zombies[i].getCenter().x, zombies[i].getCenter().y,
							player.getCenter().x, player.getCenter().y);

						currentZombieBullet++;
						if (currentZombieBullet > (ZOMBIE_BULLETS - 1))
						{
							currentZombieBullet = 0;
						}

						zombies[i].resetFireTimer();

						//zombies[i].resetFireTimer();
					
					}
				}
			}

			

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update  zombie bullets if they are in-flight
			for (int i = 0; i < ZOMBIE_BULLETS; i++)
			{
				if (zBullets[i].isInFlight())
				{
					zBullets[i].update(dtAsSeconds);
				}
			}



			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);
			shieldPickup.update(dtAsSeconds);

			// Collision detection
			// Have any zombies been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() && 
						zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects
							(zombies[j].getPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was a kill
							if (zombies[j].hit()) 
							{
								// Not just a hit but a kill too
								score += 10;
								if (score >= hiScore)
								{
									hiScore = score;

									std::ofstream outputFile("gamedata/highscore.txt");
									outputFile << hiScore;
									outputFile.close();

								}

								numZombiesAlive--;

								// When all the zombies are dead (again)
								if (numZombiesAlive == 0) 
								{
									state = State::LEVELING_UP;
								}
							}	

							// Make a splat sound
							splat.play();
							
						}
					}

				}
			}// End zombie being shot


			// Have player been shoot
			for (int i = 0; i < ZOMBIE_BULLETS; i++)
			{
				if (zBullets[i].isInFlight() && !player.isShielded())
				{
					if (zBullets[i].getPosition().intersects(player.getPosition()))
					{
						// Stop the bullet
						zBullets[i].stop();

						if (player.hit(gameTimeTotal))
						{
							// Play hit sound
							hit.play();
						}

						if (player.getHealth() <= 0)
						{
							state = State::GAME_OVER;

							std::ofstream outputFile("gamedata/scores.txt", std::fstream::app);
							outputFile << score << std::endl;
							outputFile.close();

							break;

						}
					}
				}
			}


			// Have any zombies touched the player			
			for (int i = 0; i < numZombies; i++)
			{
				if (!player.isShielded())
				{

					if (player.getPosition().intersects
					(zombies[i].getPosition()) && zombies[i].isAlive())
					{

						if (player.hit(gameTimeTotal))
						{
							// Play hit sound
							hit.play();
						}

						if (player.getHealth() <= 0)
						{
							state = State::GAME_OVER;

							std::ofstream outputFile("gamedata/scores.txt", std::fstream::app);
							outputFile << score << std::endl;
							outputFile.close();

							break;

						}
					}
				}
			}// End player touched

			// Has the player touched health pickup
			if (player.getPosition().intersects
				(healthPickup.getPosition()) && healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
				// Play a sound
				pickup.play();
				
			}

			// Has the player touched ammo pickup
			if (player.getPosition().intersects
				(ammoPickup.getPosition()) && ammoPickup.isSpawned())
			{
				bulletsSpare += ammoPickup.gotIt();
				// Play a sound
				reload.play();
				
			}

			// Has the player touched shield pickup
			if (player.getPosition().intersects
			(shieldPickup.getPosition()) && shieldPickup.isSpawned())
			{

				player.shieldTimeValue(shieldPickup.gotIt());
				// 1 Indicates true
				player.setShield(1);
				
				// Play a sound
				pickup.play();

				shieldTimer.restart();
			}

			// Has the shield pickup time exceeds
			if (player.isShielded() && shieldTimer.getElapsedTime().asMilliseconds() > player.getShieldTime())
			{
				// 0 Indicates false
				player.setShield(0);
			}


			// size up the health bar
			healthBar.setSize(Vector2f(player.getHealth() * 1, 20));

			// Increment the amount of time since the last HUD update
			timeSinceLastUpdate += dt;
			// Increment the number of frames since the last HUD calculation
			framesSinceLastHUDUpdate++;
			// Calculate FPS every fpsMeasurementFrameInterval frames
			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
			{

				// Update game HUD text
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;

				// Update the ammo text
				ssAmmo << bulletsInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				// Update the score text
				ssScore << "Score:" << score;
				scoreText.setString(ssScore.str());

				// Update the high score text
				ssHiScore << "Hi Score:" << hiScore;
				hiScoreText.setString(ssHiScore.str());

				// Update the wave
				ssWave << "Wave:" << wave;
				waveNumberText.setString(ssWave.str());

				// Update the high score text
				ssZombiesAlive << "Zombies:" << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

				framesSinceLastHUDUpdate = 0;
				timeSinceLastUpdate = Time::Zero;
			}// End HUD update

		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			// Draw the player bullets if they are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the zombie bullets if they are in-flight
			for (int i = 0; i < 30; i++)
			{
				if (zBullets[i].isInFlight())
				{
					window.draw(zBullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the pickups is currently spawned
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}
			if (shieldPickup.isSpawned())
			{
				window.draw(shieldPickup.getSprite());
			}

			//Draw the crosshair
			window.draw(spriteCrosshair);

			// Switch to the HUD view
			window.setView(hudView);

			// Draw all the HUD elements
			window.draw(spriteAmmoIcon);
			window.draw(spriteHealthIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
		}

		/** Drawing LEVELING-UP STATE **/
		if (state == State::LEVELING_UP)
		{
			window.draw(backgroundSprite);
			window.draw(levelUpText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
		}

		/* Drawing Game-Over State */
		if (state == State::GAME_OVER)
		{
			window.draw(backgroundSprite);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(goBackMessage);

			wave = 0;
			score = 0;

			// Prepare the gun and ammo for next game
			currentBullet = 0;
			bulletsSpare = 24;
			bulletsInClip = 6;
			clipSize = 6;
			fireRate = 1;

			// Reset the player's stats
			player.resetPlayerStats();

		}

		/** Drawing INSTRUCTIONS STATE **/
		if (state == State::MAIN_MENU)
		{
			window.draw(backgroundSprite);
			window.draw(mainMenuText);
		}

		/** Drawing INSTRUCTIONS STATE **/
		if (state == State::INSTRUCTIONS)
		{
			window.clear();

			//Background Sprite
			window.draw(backgroundSprite);

			window.draw(instructionsText);

			window.draw(goBackMessage);
		}

		/** Drawing HIGHSCORE STATE **/
		if (state == State::HIGHSCORES)
		{

			window.clear();

			//Background Sprite
			window.draw(backgroundSprite);

			extractTopScores(_1st, _2nd, _3rd);

			first.setFont(font);
			first.setCharacterSize(80);
			first.setFillColor(Color::Red);
			first.setPosition(955, 430);
			first.setString(_1st);

			second.setFont(font);
			second.setCharacterSize(80);
			second.setFillColor(Color::Red);
			second.setPosition(955, 520);
			second.setString(_2nd);

			third.setFont(font);
			third.setCharacterSize(80);
			third.setFillColor(Color::Red);
			third.setPosition(955, 610);
			third.setString(_3rd);

			window.draw(highscoreLabel);
			window.draw(ranks);

			window.draw(first);

			window.draw(second);

			window.draw(third);

			window.draw(goBackMessage);
		}

		window.display();

	}// End game loop

	return 0;
}