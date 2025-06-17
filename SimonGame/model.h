#ifndef MODEL_H
#define MODEL_H
/**
 * The logic of the Simon Game application.
 *
 * Created by Logan Wood and Dylan Kelly
 * Modified March 7, 2025
 */
#include <QObject>
#include <vector>

using std::vector;

class Model : public QObject
{
    Q_OBJECT

private:
    bool isPlayerTurn = false;
    /** Represents the pattern of buttonn presses which the player will have to copy */
    vector<int> pattern = {};
    int currentMove = 0;
    int currentProgress = 0;

    int pressDelay = 200; // Delay in ms computer presses the button for
    int moveDelay = 500; // Delay in ms between computer moves

    /**
     * Performs the computer's turn, displaying a sequence of moves.
     */
    void performComputersTurn();
    /**
     * Performs setup for and begins the player's turn.
     */
    void startPlayersTurn();
    /**
     * Helper method for updating the current progress for the round. This is calculated
     * as the # of moves inputed out of the total # of moves in the current pattern.
     * This method emits progressChanged signal.
     */
    void calculateProgress();
    /**
     * Add 1 new move to the pattern.
     */
    void addMove();

public:
    /**
     * Constructs the model, initializing the number of cats.
     * @param parent QObject
     */
    explicit Model(QObject *parent = nullptr);

public slots:
    /**
     * Begins the Simon Game.
     */
    void startGame();
    /**
     * Performs the game input of pressing the red simon button.
     */
    void performRedInput();
    /**
     * Performs the game input of pressing the blue simon button.
     */
    void performBlueInput();

signals:
    /**
     * Emitted every time the currentProgress value is changed.
     * @param num current progress number (0 - 100)
     */
    void progressChanged(int num);
    /** Emitted when the computer presses the red button. */
    void redFakePress(int delay);
    /** Emitted when the computer presses the blue button. */
    void blueFakePress(int delay);
    /** Emitted when the game's state changes.
     *  @param state the current game state
     *  (0 = Waiting to begin, 1 = computer's turn, 2 = player's turn)  */
    void gameStateChanged(int state);
    /** Emitted when the player presses the wrong button. */
    void gameOver();
};

#endif // MODEL_H
