/**
 * The model of the Simon Game application.
 *
 * Created by Logan Wood and Dylan Kelly
 * Modified March 7, 2025
 */
#include <QTimer>
#include "model.h"

Model::Model(QObject *parent) : QObject{parent}
{}

void Model::startGame(){
    pattern.clear();
    addMove();
    currentMove = 0;
    isPlayerTurn = false;
    QTimer::singleShot(1000, this, &Model::performComputersTurn);
}

void Model::addMove(){
    // Generate a random move and push it to the end of the pattern
    int randMove = std::rand() % 2; // Random move (0 = Red, 1 = Blue)
    pattern.push_back(randMove);

    // Speed up the game
    // Descrease delay by 20ms
    if(moveDelay > pressDelay)
        moveDelay -= 20;
    // Cap the minimum delay so it doesn't go too low
    else if(moveDelay < pressDelay)
        moveDelay = pressDelay;
}

void Model::performComputersTurn(){
    emit gameStateChanged(1);
    isPlayerTurn = false;
    int delay = 1000; // Initial delay before playing sequence

    for(int move : pattern){
        // Display the button being pressed
        QTimer::singleShot(delay, this, [this, move, delay](){
            //Determine which button is pressed
            if(move == 0) emit redFakePress(pressDelay);
            else emit blueFakePress(pressDelay);
        });

        // Update the delay before next move
        delay += pressDelay + moveDelay;
    }
    // Delay before starting the player's turn
    QTimer::singleShot(delay, this, &Model::startPlayersTurn);
}

void Model::startPlayersTurn(){
    emit gameStateChanged(2);
    isPlayerTurn = true;
    currentMove = 0;
}

void Model::calculateProgress(){
    double progressRatio = (double)currentMove / pattern.size();
    currentProgress = progressRatio * 100;

    // Notify any relevant UI elements that the progress has changed
    emit progressChanged(currentProgress);
}

void Model::performRedInput(){
    // Check if this matches the current move in the pattern (0 for red)
    if(pattern.at(currentMove) == 0){
        currentMove++;
        calculateProgress();

        if(currentMove >= pattern.size()){
            // No more moves; start the computer's turn
            addMove();
            performComputersTurn();
        }
    }
    else{
        // GAME OVER
        emit gameOver();
        QTimer::singleShot(500, this, [this](){ emit gameStateChanged(0); });
    }
}

void Model::performBlueInput(){
    // Check if this matches the current move in the pattern (0 for red)
    if(pattern.at(currentMove) == 1){
        currentMove++;
        calculateProgress();

        if(currentMove >= pattern.size()){
            // No more moves; start the computer's turn
            addMove();
            performComputersTurn();
        }
    }
    else{
        // GAME OVER
        emit gameOver();
        QTimer::singleShot(500, this, [this](){ emit gameStateChanged(0); });
    }
}
