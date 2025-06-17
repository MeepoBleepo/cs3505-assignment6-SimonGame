/**
 * The entry point of the Simon Game application.
 *
 * Created by Logan Wood and Dylan Kelly, March 7, 2025
 * Github Usernames: MeepoBleepo and BlockerBuddy
 * Github Repo URL: https://github.com/UofU-CS3505/cs3505-assignment6-MeepoBleepo.git
 *
 * This application is a recreation of the classic Simon Game.
 * A pattern of button presses is presented to the player who
 * then has to copy the sequence back. Each round, the pattern
 * grows and the pattern is shown quicker.
 *
 * For an additional element to this project, we added sound effects
 * to the game to liven it up.
 */
#include "mainwindow.h"
#include "model.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    MainWindow w(&m);
    w.show();
    return a.exec();
}
