#include <SFML/Graphics.hpp>
#include <vector>

#include "../view/Layer.hpp"
#include "../model/GameState.hpp"
#include "PlayerController.hpp"
#include "AliensController.hpp"
#include "../view/GameDrawer.hpp"
#include "BunkersController.hpp"
#include "SoundsController.hpp"



// Game class
class Game {

public:
    Game();

    

   /**
    * Start the game loop.
    */
    void start();



private:

    

    /**
     * Handle user input.
     * @return true if the window has been closed, false otherwise.
     */
    bool input();

    /**
     * Update the game state based on the elapsed time.
     * @param time_passed The time passed since the last update in seconds.
     */
    void update(float time_passed);

    /**
     * Draw the scene.
     */
    void draw();

    /**
     * Finish the game and close the window.
     */
    void finish();

    /**
     * Check for collisions between aliens and the player's lasers.
     */
    void check_alien_hits();

    /**
     * Check for collisions between the player and alien lasers.
     */
    void check_player_hits();

    /**
     * Check for collisions between two positionable objects.
     * @param s1 first object.
     * @param s2 second object.
     * @return true if the objects are colliding, false otherwise.
     */
    bool check_collision(Positionable& s1, Positionable& s2);
    void check_bunker_hits();


    // current state of the game including the position and state of the entities
    GameState state;

    // controllers
    PlayerController player_controller;
    AliensController aliens_controller;
    BunkersController bunkers_controller;
    SoundsController sounds_controller;

    // window for rendering the game
    sf::RenderWindow window; // unfortunately needed here for start and input (->dependence on sfml)

    // drawer for rendering the game state
    std::unique_ptr<GameDrawer> drawer;


    friend class TestGame;
};