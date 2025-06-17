#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * The user interface for the Simon Game application.
 * This is the only place the button, spin box, and label should be known.
 * This does not hold an instance of the model, though one is needed in
 * the constructor.
 *
 * Created by Logan Wood and Dylan Kelly
 * Modified March 12, 2025
 */

#include <QMainWindow>
#include "model.h"
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    /**
     * Sets the RED button color to the pressed color then the released color to simulate a button press from the computer
     * @param delay in ms how long the computer presses for
     */
    void fakePressRedButton(int delay);
    /**
     * Sets the BLUE button color to the pressed color then the released color to simulate a button press from the computer
     * @param delay in ms how long the computer presses for
     */
    void fakePressBlueButton(int delay);
    /**
     * Sets up UI elements for the given game state change.
     * @param state the current game state (0 = Waiting to begin, 1 = computer's turn, 2 = player's turn)
     */
    void displayGameState(int state);
    /**
     * Displays game over text and re-enables the start button
     */
    void gameOver();

public:
    /**
     * Constructs the view.
     * @param model only used to set up connections, nothing else
     * @param parent QWidget
     */
    MainWindow(Model* model, QWidget *parent = nullptr);
    /**
     * Destructor destroys the ui.
     */
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QSoundEffect redSound;
    QSoundEffect blueSound;
    QSoundEffect loseSound;
};
#endif // MAINWINDOW_H
