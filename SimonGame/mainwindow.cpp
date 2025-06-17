/**
 * The view of the Simon Game application.
 *
 * Created by Logan Wood and Dylan Kelly
 * Modified March 12, 2025
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QSoundEffect>

MainWindow::MainWindow(Model* model, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSoundEffect* redSound = new QSoundEffect(this);
    QSoundEffect* blueSound = new QSoundEffect(this);
    QSoundEffect* loseSound = new QSoundEffect(this);

    redSound->setSource(QUrl("qrc:/Sounds/redSound.wav"));
    blueSound->setSource(QUrl("qrc:/Sounds/blueSound.wav"));
    loseSound->setSource(QUrl("qrc:/Sounds/loseSound.wav"));
    // Perform initial UI setup
    displayGameState(0);

    // From view to model
    connect(ui->button_Start, &QPushButton::clicked, model, &Model::startGame);
    connect(ui->button_Red, &QPushButton::clicked, model, &Model::performRedInput);
    connect(ui->button_Blue, &QPushButton::clicked, model, &Model::performBlueInput);
    connect(ui->button_Blue, &QPushButton::clicked, blueSound, &QSoundEffect::play);
    connect(ui->button_Red, &QPushButton::clicked, redSound, &QSoundEffect::play);

    // From model to view
    connect(model, &Model::redFakePress, this, &MainWindow::fakePressRedButton);
    connect(model, &Model::blueFakePress, this, &MainWindow::fakePressBlueButton);
    connect(model, &Model::redFakePress, redSound, &QSoundEffect::play);
    connect(model, &Model::blueFakePress, blueSound, &QSoundEffect::play);
    connect(model, &Model::gameStateChanged, this, &MainWindow::displayGameState);
    connect(model, &Model::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(model, &Model::gameOver, this, &MainWindow::gameOver);
    connect(model, &Model::gameOver, loseSound, &QSoundEffect::play);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fakePressRedButton(int delay){
    ui->button_Red->setStyleSheet( QString("QPushButton {background-color: rgb(255,0,0);}")); // "Pressed" color
    redSound.play();
    QTimer::singleShot(delay, this, [this](){
        ui->button_Red->setStyleSheet( QString("QPushButton {background-color: rgb(97,61,61);}")); // "Released" color
    });
}

void MainWindow::fakePressBlueButton(int delay){
    ui->button_Blue->setStyleSheet( QString("QPushButton {background-color: rgb(0,174,255);}")); // "Pressed" color
    blueSound.play();
    QTimer::singleShot(delay, this, [this](){
        ui->button_Blue->setStyleSheet( QString("QPushButton {background-color: rgb(75,114,131);}"));  // "Released" color
    });
}

void MainWindow::displayGameState(int state){
    if(state == 0){
        // SETUP UI ELEMENTS FOR INITIAL SETUP
        ui->button_Red->setEnabled(false);
        ui->button_Blue->setEnabled(false);
        ui->button_Red->setStyleSheet( QString("QPushButton {background-color: rgb(97,61,61);}"));
        ui->button_Blue->setStyleSheet( QString("QPushButton {background-color: rgb(75,114,131);}"));
        ui->progressBar->setValue(0);
    }
    else if(state == 1){
        // SETUP UI ELEMENTS FOR COMPUTER'S TURN
        ui->label_GameState->setText("Computer's Turn!");
        // Disable Simon buttons
        ui->button_Red->setEnabled(false);
        ui->button_Blue->setEnabled(false);
        ui->button_Red->setStyleSheet( QString("QPushButton::disabled {background-color: rgb(97,61,61);}"));
        ui->button_Blue->setStyleSheet( QString("QPushButton::disabled {background-color: rgb(75,114,131);}"));

        ui->button_Start->setEnabled(false);    // Make sure the start button is disabled
        ui->progressBar->setValue(0);
    }
    else if (state == 2){
        // SETUP UI ELEMENTS FOR PLAYER'S TURN
        ui->label_GameState->setText("Player's Turn!");
        // Enable Simon buttons
        ui->button_Red->setEnabled(true);
        ui->button_Blue->setEnabled(true);
        ui->button_Red->setStyleSheet( QString("QPushButton {background-color: rgb(97,61,61);} QPushButton::pressed {background-color: rgb(255,0,0);}"));
        ui->button_Blue->setStyleSheet( QString("QPushButton {background-color: rgb(75,114,131);} QPushButton::pressed {background-color: rgb(0,174,255);}"));
    }
    else{
        ui->label_GameState->setText("...");
    }
}

void MainWindow::gameOver(){
    ui->label_GameState->setText("Wrong button! Game over!");

    // Renable the start button
    QTimer::singleShot(500, this, [this](){
        ui->button_Start->setEnabled(true);
    });
}

