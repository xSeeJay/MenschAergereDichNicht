#ifndef GAME_H
#define GAME_H

#include <QRandomGenerator>
#include <QVector>

class Pawn;
class Board;
class SaveGameEngine;
enum class PlayerColor;

class Game {

public:
    /* This is a configuration constant.
     * True value means pawn require a six to get out of homes.
     * TODO: This should be under user-control */
    static constexpr bool SIX_FOR_HOME = true;

    /* players: no of players playing the game */
    Game(unsigned int players);

    /* Creates a new instance and copies data from save state */
    Game(SaveGameEngine *save);

    /* Copies data into save state */
    void serializeInto(SaveGameEngine *save);

    /* Deletes and frees ALL the resources used */
    virtual ~Game();

    /* Returns an int between 1 to 6 which can be used as dice */
    int rollDice();

    /* Returns a pointer to the GameBoard instance used */
    Board* getGameBoard();

    /* Returns a QVector of Pawns that can move by the passed dice face value */
    QVector<Pawn*> getPlayablePawns(int diceFace);

    /* Returns the predicted relative position of the pawn if it would move by
     * the given dice value */
    unsigned int predictRel(Pawn* p, unsigned int diceFace);

    /* Moves the pawn by the value of dice face, handles additional consequences
     * (such as, an another Pawn getting knoked off) and allows the next player to
     * play if dice does not shows a 6.

     * NOTE: This should be called after you've updated the UI forehand using
     * to the dice value (see: Game::rollDice())

     * Returns: true if the player gets another chance to throw the dice (by
     * getting a 6 on dice or by hitting other pawn), false otherwise */
    bool playMove(Pawn* pawn, int diceFace);

    /* Returns the PlayerColor handle of the player who should play the current turn */
    PlayerColor getCurrentPlayer();

    /* Shifts the turn to next player */
    void changeCurrentPlayer();

    /* Returns the vector indicating the sequence of turns of players */
    QVector<PlayerColor> getCurrentPlayerSequence();

    /* Get the last value rolled by the dice */
    unsigned int getLastDiceValue();

    /* Returns true if given player has finished playing. i.e When his all pawns have
     * reached destination */
    bool playerHasFinished(PlayerColor p);

    /* Returns true when game has finished. i.e. When only one player is left to get
     * all pawns home */
    bool isFinished();

private:
    unsigned int players_count {}; //Number of players playing the game
    Board* mBoard {}; //Game board
    QVector<PlayerColor> *currentSequence {}; //Player Turns sequence
    unsigned int current {}; //Current player's index in the sequence
    unsigned int lastDiceValue {}; //Stores the value of dice rolled last time
    QRandomGenerator random {}; //For randomization of dice
};

#endif //Game.h
