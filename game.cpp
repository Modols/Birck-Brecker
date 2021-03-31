#include "game.h"
#include "button.h"
#include "myrect.h"
#include "gold.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <fstream>
#include <QtDebug>
#include <QImage>

Game::Game(QWidget *parent)
{
    //creer la scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setScene(scene);
    setBackgroundBrush(QBrush(QImage(":/Images/images/Fond.png")));

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //Initialisation avec le txt
    initialisationVitesse();
    initialisationGameGold();
}

void Game::createMainMenu()
{

    // create the title text
    titleText = new QGraphicsTextItem(QString("Birk Brecker"));
    QFont titleFont("comic sans",50, QFont::Bold);
    titleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 100;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    playButton = new Button(QString("Play"));
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(deleteMainMenu()));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 240;
    playButton->setPos(bxPos,byPos);
    scene->addItem(playButton);

    //create the upgrade button
    upgradeButton = new Button(QString("Upgrade"));
    connect(upgradeButton,SIGNAL(clicked()),this,SLOT(createUpgrade()));
    connect(upgradeButton,SIGNAL(clicked()),this,SLOT(deleteMainMenu()));
    int vxPos = upgradeButton->boundingRect().width() - 10;
    int vyPos = 315;
    upgradeButton->setPos(vxPos,vyPos);
    scene->addItem(upgradeButton);

    //create the instruction button
    createInstruction = new Button(QString("Instruction"));
    connect(createInstruction,SIGNAL(clicked()),this,SLOT(createInstructions()));
    connect(createInstruction,SIGNAL(clicked()),this,SLOT(deleteMainMenu()));
    int xPos = this->width()/2 + createInstruction->boundingRect().width() - 190;
    int yPos = 315;
    createInstruction->setPos(xPos,yPos);
    scene->addItem(createInstruction);

    // create the quit button
    quitButton = new Button(QString("Quit"));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 450;
    quitButton->setPos(qxPos,qyPos);
    scene->addItem(quitButton);
}

void Game::start()
{
    //creation du player
    player = new MyRect();
    scene->addItem(player);

    //make the player focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(350,500);

    //creation score
    score = new Score();
    scene->addItem(score);

    //creation de Gold
    gold = new Gold();
    gold->setPos(gold->x(),gold->y()+25);
    scene->addItem(gold);

    //creation vie
    vie = new Vie();
    vie->setPos(vie->x() + this->width() - vie->boundingRect().width(),vie->y());
    scene->addItem(vie);

    //spawn enemies
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(1500);

    //spawn Etoiles
    timerEtoile = new QTimer();
    connect(timerEtoile,SIGNAL(timeout()),player,SLOT(spawnEtoile()));
    timerEtoile->start(800);

    timerEtoile2 = new QTimer();
    connect(timerEtoile2,SIGNAL(timeout()),player,SLOT(spawnEtoile()));
    timerEtoile2->start(1200);
}

void Game::displayEndGame()
{
    deleteStart();
    setAugmentationReducZero();
    scene->clear();

    //creation du text "Game Over"
    endTitleText = new QGraphicsTextItem(QString("Game Over"));
    QFont endtitleFont("comic sans",50, QFont::Bold);
    endTitleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    endTitleText->setFont(endtitleFont);
    int txPos = this->width()/2 - endTitleText->boundingRect().width()/2;
    int tyPos = 150;
    endTitleText->setPos(txPos,tyPos);
    scene->addItem(endTitleText);

    //creation du boutton Replay
    rePlayButton = new Button(QString("Replay"));
    connect(rePlayButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(rePlayButton,SIGNAL(clicked()),this,SLOT(deleteEndMenuStart()));
    int xPos = this->width()/2 - rePlayButton->boundingRect().width()/2;
    int yPos = 275;
    rePlayButton->setPos(xPos,yPos);
    scene->addItem(rePlayButton);

    //creation du boutton Retour menu
    endMenuButton = new Button(QString("Retour Menu"));
    connect(endMenuButton,SIGNAL(clicked()),this,SLOT(deleteEndMenu()));
    connect(endMenuButton,SIGNAL(clicked()),this,SLOT(slotMenuEndGame()));
    int bxPos = this->width()/2 - endMenuButton->boundingRect().width()/2;
    int byPos = 350;
    endMenuButton->setPos(bxPos,byPos);
    scene->addItem(endMenuButton);

    //creation du boutton Quit
    quitButton = new Button(QString("Quit"));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 425;
    quitButton->setPos(qxPos,qyPos);
    scene->addItem(quitButton);

}

void Game::createUpgrade()
{
    //creation du Titre Upgrade
    upgradeTitleText = new QGraphicsTextItem(QString("Upgrade"));
    QFont endtitleFont("comic sans",50, QFont::Bold);
    upgradeTitleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    upgradeTitleText->setFont(endtitleFont);
    int txPos = this->width()/2 - upgradeTitleText->boundingRect().width()/2;
    int tyPos = 30;
    upgradeTitleText->setPos(txPos,tyPos);
    scene->addItem(upgradeTitleText);

    //refresh des Golds
    string upgradeGold = to_string(getGameGold());
    QString goldstext = QString::fromStdString(upgradeGold);
    goldTitleText = new QGraphicsTextItem(QString("Gold : ") + goldstext);
    goldTitleText->setDefaultTextColor(QColor(Qt::yellow));
    QFont goldTitle("comic sans",30);
    goldTitleText->setFont(goldTitle);
    int axPos = this->width()/2 - goldTitleText->boundingRect().width()/2;
    int ayPos = 130;
    goldTitleText->setPos(axPos,ayPos);
    scene->addItem(goldTitleText);

    //creation du boutton upgrade vitesse de tir
    vitesseTirButton = new Button(QString("Vitesse de Tir : 10 Golds"));
    connect(vitesseTirButton,SIGNAL(clicked()),this,SLOT(upgradeVitesseTir()));
    int qxPos = this->width()/2 - vitesseTirButton->boundingRect().width()/2;
    int qyPos = 230;
    vitesseTirButton->setPos(qxPos,qyPos);
    scene->addItem(vitesseTirButton);

    //creation du boutton upgrade vitesse de deplacement
    vitesseDeplacementButton = new Button(QString("Vitesse de Déplacement : 10 Golds"));
    connect(vitesseDeplacementButton,SIGNAL(clicked()),this,SLOT(upgradeDeplacement()));
    int oxPos = this->width()/2 - vitesseDeplacementButton->boundingRect().width()/2;
    int oyPos = 305;
    vitesseDeplacementButton->setPos(oxPos,oyPos);
    scene->addItem(vitesseDeplacementButton);

    //creation du boutton upgrade vitesse de défilement
    vitesseDefilementButton = new Button(QString("Vitesse de défilement : 10 Golds"));
    connect(vitesseDefilementButton,SIGNAL(clicked()),this,SLOT(upgradeVitesseDefilement()));
    int ixPos = this->width()/2 - vitesseDefilementButton->boundingRect().width()/2;
    int iyPos = 380;
    vitesseDefilementButton->setPos(ixPos,iyPos);
    scene->addItem(vitesseDefilementButton);

    resetTxt = new Button(QString("Reset Upgrade"));
    connect(resetTxt,SIGNAL(clicked()),this,SLOT(resetDataTxt()));
    int bxPos = this->width()/2 - resetTxt->boundingRect().width()/2;
    int byPos = 455;
    resetTxt->setPos(bxPos,byPos);
    scene->addItem(resetTxt);

    //creation du boutton retour Menu
    menuButton = new Button(QString("Retour Menu"));
    connect(menuButton,SIGNAL(clicked()),this,SLOT(deleteUpgrade()));
    int yxPos = this->width()/2 - menuButton->boundingRect().width()/2;
    int yyPos = 530;
    menuButton->setPos(yxPos,yyPos);
    scene->addItem(menuButton);

}

void Game::deleteMainMenu()
{
    delete playButton;
    delete titleText;
    delete quitButton;
    delete upgradeButton;
    delete createInstruction;
}

void Game::deleteEndMenu()
{
    delete rePlayButton;
    delete endTitleText;
    delete quitButton;
}

void Game::deleteEndMenuStart()
{
    delete rePlayButton;
    delete endTitleText;
    delete quitButton;
    delete endMenuButton;
}

void Game::deleteUpgrade()
{
    delete upgradeTitleText;
    delete vitesseTirButton;
    delete vitesseDeplacementButton;
    delete vitesseDefilementButton;
    delete menuButton;
    delete goldTitleText;
    delete resetTxt;
    createMainMenu();
}

void Game::slotMenuWin()
{
    createMainMenu();
}

void Game::slotMenuEndGame()
{
    delete endMenuButton;
    createMainMenu();
}

void Game::upgradeVitesseTir()
{
    if(possibleUpgrade(10) == true)
    {
        vitesseTir += 5;
        int golds = stoi(getGolds());
        string nomFichier = "game.txt";
        golds -= 10;
        gameGold -=10;
        // ecriture dans un fichier
        ofstream monFichierOut(nomFichier);
        monFichierOut << golds << endl;
        monFichierOut << getVitesseEnemie() << endl;
        monFichierOut << getVitesseTir()  << endl;
        monFichierOut << getVitesseDeplacement() << endl;
        updateGold();
    }

}

void Game::upgradeDeplacement()
{
    if(possibleUpgrade(10) == true)
    {
        vitesseDeplacement = 30;
        int golds = stoi(getGolds());
        golds -= 10;
        gameGold -=10;
        string nomFichier = "game.txt";
        // ecriture dans un fichier
        ofstream monFichierOut(nomFichier);
        monFichierOut << golds << endl;
        monFichierOut << getVitesseEnemie() << endl;
        monFichierOut << getVitesseTir() << endl;
        monFichierOut << getVitesseDeplacement() << endl;
        updateGold();
    }

}

void Game::upgradeVitesseDefilement()
{
    if(possibleUpgrade(10) == true && getVitesseEnemie() >1)
    {
        vitesseEnemie -=1;
        int golds = stoi(getGolds());
        string nomFichier = "game.txt";
        golds -= 10;
        gameGold -= 10;
        // ecriture dans un fichier
        ofstream monFichierOut(nomFichier);
        monFichierOut << golds << endl;
        monFichierOut << getVitesseEnemie() << endl;
        monFichierOut << getVitesseTir()  << endl;
        monFichierOut << getVitesseDeplacement() << endl;
        updateGold();
    }

}

string Game::getGolds()
{
    //récupération dans le fichier txt
    string nomFichier = "game.txt";
    string golds;
    ifstream monFichierIn(nomFichier);
    if(monFichierIn.good())
    {
        string str;
        getline(monFichierIn,str);
        golds=str;
     }
    return golds;
}

void Game::initialisationGameGold()
{
    string nomFichier = "game.txt";
    //récupération dans le fichier txt
    ifstream monFichierIn(nomFichier);
    if(monFichierIn.good())
    {
        string str;
        getline(monFichierIn,str);
        gameGold=stoi(str);
    }else{
        gameGold = 0;
    }
}

void Game::setGameGold(int value)
{
    gameGold = value;
}

int Game::getGameGold() const
{
    return gameGold;
}

void Game::ecritureTxtEndGame(int temporaryGold)
{
    string nomFichier = "game.txt";
    // ecriture dans un fichier
    ofstream monFichierOut(nomFichier);
    monFichierOut << temporaryGold << endl;
    monFichierOut << getVitesseEnemie() << endl;
    monFichierOut << getVitesseTir()  << endl;
    monFichierOut << getVitesseDeplacement() << endl;
}

int Game::getAugmentationVitesseEnnemie() const
{
    return augmentationVitesseEnnemie;
}

void Game::setAugmentationVitesseEnnemie(int value)
{
    augmentationVitesseEnnemie = value;
}

int Game::getAugmentationVitesseDefilement() const
{
    return augmentationVitesseDefilement;
}

void Game::setAugmentationVitesseDefilement(int value)
{
    augmentationVitesseDefilement = value;
}

int Game::getReductionVitesseTir() const
{
    return reductionVitesseTir;
}

void Game::setReductionVitesseTir(int value)
{
    reductionVitesseTir = value;
}

void Game::setAugmentationReducZero()
{
    //remet les valeurs d'augmentation à 0
    augmentationVitesseEnnemie = 0;
    augmentationVitesseDefilement = 0;
    reductionVitesseTir = 0;
}

void Game::endGameDesired()
{
    delete endGameButton;
    int scoreGame = score->getScore();
    int temporaryGold = getGold()->getGold();
    gameGold = temporaryGold;
    setAugmentationReducZero();
    scene->clear();

    ecritureTxtEndGame(temporaryGold);
    displaySumGame(scoreGame, temporaryGold);
}

void Game::displaySumGame(int score, int temporaryGold)
{
    //creation du titre résumé
    resumeeTitleText = new QGraphicsTextItem(QString("Résumé de la Partie") );
    QFont remeeText("comic sans",50, QFont::Bold);
    resumeeTitleText->setFont(remeeText);
    resumeeTitleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    int bxPos = this->width()/2 - resumeeTitleText->boundingRect().width()/2;
    int byPos = 0;
    resumeeTitleText->setPos(bxPos,byPos);
    scene->addItem(resumeeTitleText);

    //creation du titre Golds
    goldTitleText = new QGraphicsTextItem(QString("Golds : ") + QString::number(temporaryGold));
    QFont goldTitle("comic sans",30);
    goldTitleText->setDefaultTextColor(QColor(Qt::yellow));
    goldTitleText->setFont(goldTitle);
    int axPos = this->width()/2 - goldTitleText->boundingRect().width()/2;
    int ayPos = 150;
    goldTitleText->setPos(axPos,ayPos);
    scene->addItem(goldTitleText);

    //creation du titre Score
    scoreTitleText = new QGraphicsTextItem(QString("Score : ") + QString::number(score));
    scoreTitleText->setFont(goldTitle);
    scoreTitleText->setDefaultTextColor(QColor(0xff, 0xff, 0xff, 0xff));
    int vxPos = this->width()/2 - scoreTitleText->boundingRect().width()/2;
    int vyPos = 225;
    scoreTitleText->setPos(vxPos,vyPos);
    scene->addItem(scoreTitleText);

    //creation du button Replay
    rePlayButton = new Button(QString("Replay"));
    connect(rePlayButton,SIGNAL(clicked()),this,SLOT(start()));
    connect(rePlayButton,SIGNAL(clicked()),this,SLOT(deleteDisplaySum()));
    int xPos = this->width()/2 - rePlayButton->boundingRect().width()/2;
    int yPos = 350;
    rePlayButton->setPos(xPos,yPos);
    scene->addItem(rePlayButton);

    //creation du button Retour Menu
    returnMenuButton = new Button(QString("Retour Menu"));
    connect(returnMenuButton,SIGNAL(clicked()),this,SLOT(slotMenuWin()));
    connect(returnMenuButton,SIGNAL(clicked()),this,SLOT(deleteDisplaySum()));
    int qxPos = this->width()/2 - returnMenuButton->boundingRect().width()/2;
    int qyPos = 425;
    returnMenuButton->setPos(qxPos,qyPos);
    scene->addItem(returnMenuButton);

    //creation du button Quit
    quitButtonWin = new Button(QString("Quit"));
    connect(quitButtonWin,SIGNAL(clicked()),this,SLOT(close()));
    int txPos = this->width()/2 - quitButtonWin->boundingRect().width()/2;
    int tyPos = 500;
    quitButtonWin->setPos(txPos,tyPos);
    scene->addItem(quitButtonWin);

}

void Game::resetDataTxt()
{
    remove("game.txt");
    //écriture fichier
    string nomFichier = "game.txt";
    ofstream monFichierOut(nomFichier);
    monFichierOut << 0 << endl;
    monFichierOut << 5 << endl;
    monFichierOut << 10  << endl;
    monFichierOut << 20 << endl;

    //initialisation des vitesses et golds
    int golds=0;
    golds=0;
    setVitesseEnemie(5);
    setVitesseTir(10);
    setVitesseDeplacement(20);
    setGameGold(0);

    delete goldTitleText;

    string upgradeGold = to_string(getGameGold());
    QString goldstext = QString::fromStdString(upgradeGold);
    goldTitleText = new QGraphicsTextItem(QString("Gold : ") + goldstext);
    goldTitleText->setDefaultTextColor(QColor(Qt::yellow));
    QFont goldTitle("comic sans",30);
    goldTitleText->setFont(goldTitle);
    int axPos = this->width()/2 - goldTitleText->boundingRect().width()/2;
    int ayPos = 130;
    goldTitleText->setPos(axPos,ayPos);
    scene->addItem(goldTitleText);
}

void Game::initialisationVitesse()
{
    vector<string> listeTxt;
    string nomFichier = "game.txt";

    ifstream monFichierIn(nomFichier);
    if(monFichierIn.is_open())
    {
        //ouverture du txt
        if(monFichierIn.good())
        {
            string str;
            while(getline(monFichierIn,str))
            {
                listeTxt.push_back(str);
            }
            int golds=0;
            golds=stoi(listeTxt[0]);
            setVitesseEnemie( stoi(listeTxt[1]));
            setVitesseTir( stoi(listeTxt[2]));
            setVitesseDeplacement( stoi(listeTxt[3]));

        }else{

            setVitesseEnemie(5);
            setVitesseTir(10);
            setVitesseDeplacement(20);
        }
    }else{
        //creation du txt
        string nomFichier = "game.txt";
        ofstream monFichierOut(nomFichier);
        monFichierOut << 0 << endl;
        monFichierOut << 5 << endl;
        monFichierOut << 10  << endl;
        monFichierOut << 20 << endl;

        //initialisation des vitesses et golds
        int golds=0;
        golds=0;
        setVitesseEnemie(5);
        setVitesseTir(10);
        setVitesseDeplacement(20);
    }
}

bool Game::possibleUpgrade(int value)
{
    int golds = stoi(getGolds());
    if (value <= golds)
    {
        return true;
    }
    return false;
}

void Game::testCleanEnemy()
{
    player->cleanEnemies();
}

void Game::updateGold()
{
    delete goldTitleText;
    string upgradeGold = to_string(getGameGold());
    QString goldstext = QString::fromStdString(upgradeGold);
    goldTitleText = new QGraphicsTextItem(QString("Golds : ") + goldstext);
    goldTitleText->setDefaultTextColor(QColor(Qt::yellow));
    QFont goldTitle("comic sans",30);
    goldTitleText->setFont(goldTitle);
    int axPos = this->width()/2 - goldTitleText->boundingRect().width()/2;
    int ayPos = 130;
    goldTitleText->setPos(axPos,ayPos);
    scene->addItem(goldTitleText);
}

void Game::deleteDisplaySum()
{
    delete goldTitleText;
    delete scoreTitleText;
    delete rePlayButton;
    delete quitButtonWin;
    delete returnMenuButton;
    delete resumeeTitleText;
}


void Game::deleteStart()
{
    delete timer;
    delete vie;
    delete gold;
    delete score;
    delete player;
}

void Game::setVitesseEnemie(int value)
{
    vitesseEnemie = value;
}

void Game::createInstructions()
{
    //creation du Titre Instructions
    instructionTitleText = new QGraphicsTextItem(QString("Instructions"));
    QFont text("comic sans",50, QFont::Bold);
    instructionTitleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    instructionTitleText->setFont(text);
    int bxPos = this->width()/2 - instructionTitleText->boundingRect().width()/2;
    int byPos = 0;
    instructionTitleText->setPos(bxPos,byPos);
    scene->addItem(instructionTitleText);

    //direction Text + Image
    directionText = new QGraphicsTextItem(QString("Bouger") );
    QFont imageDescription("comic sans",30);
    directionText->setDefaultTextColor(QColor(53, 105, 188, 255));
    directionText->setFont(imageDescription);
    int dxPos = 50;
    int dyPos = 150;
    directionText->setPos(dxPos,dyPos);
    scene->addItem(directionText);

    directionImage = new QGraphicsPixmapItem();
    directionImage->setPixmap(QPixmap(":/Images/images/Fleche.png"));
    int axPos = 30;
    int ayPos = 200;
    directionImage->setPos(axPos,ayPos);
    scene->addItem(directionImage);

    //pause Text + Image
    pauseText = new QGraphicsTextItem(QString("Pause") );
    pauseText->setDefaultTextColor(QColor(53, 105, 188, 255));
    pauseText->setFont(imageDescription);
    int rxPos = 325;
    pauseText->setPos(rxPos,dyPos);
    scene->addItem(pauseText);

    pauseImage = new QGraphicsPixmapItem();
    pauseImage->setPixmap(QPixmap(":/Images/images/Touche-P.png"));
    int zxPos = 300;
    int zyPos = 200;
    pauseImage->setPos(zxPos,zyPos);
    scene->addItem(pauseImage);

    //shoot Text + Image
    shootText = new QGraphicsTextItem(QString("Tirer"));
    shootText->setDefaultTextColor(QColor(53, 105, 188, 255));
    shootText->setFont(imageDescription);
    int vxPos = 600;
    shootText->setPos(vxPos,dyPos);
    scene->addItem(shootText);

    shootImage = new QGraphicsPixmapItem();
    shootImage->setPixmap(QPixmap(":/Images/images/Spacebar.png"));
    int exPos = 560;
    int eyPos = 260;
    shootImage->setPos(exPos,eyPos);
    scene->addItem(shootImage);

    //delete button
    deleteInstruction = new Button(QString("Retour Menu"));
    connect(deleteInstruction,SIGNAL(clicked()),this,SLOT(slotMenuWin()));
    connect(deleteInstruction,SIGNAL(clicked()),this,SLOT(deleteInstructions()));
    int qxPos = deleteInstruction->boundingRect().width() - 100 ;
    int pyPos = 475;
    deleteInstruction->setPos(qxPos,pyPos);
    scene->addItem(deleteInstruction);

    //suivant button
    suivantInstruction = new Button(QString("Suivant"));
    connect(suivantInstruction,SIGNAL(clicked()),this,SLOT(createSuivantInstruction()));
    connect(suivantInstruction,SIGNAL(clicked()),this,SLOT(deleteInstructions()));
    int pxPos = this->width() - suivantInstruction->boundingRect().width() -100 ;
    suivantInstruction->setPos(pxPos,pyPos);
    scene->addItem(suivantInstruction);
}

void Game::deleteInstructions()
{
    delete instructionTitleText;
    delete deleteInstruction;
    delete directionImage;
    delete suivantInstruction;
    delete pauseImage;
    delete shootImage;
    delete directionText;
    delete pauseText;
    delete shootText;
}

void Game::createSuivantInstruction()
{
    //creation du Titre Ennemis
    suivantMainText = new QGraphicsTextItem(QString("Ennemis"));
    QFont text("comic sans",50, QFont::Bold);
    suivantMainText->setDefaultTextColor(QColor(53, 105, 188, 255));
    suivantMainText->setFont(text);
    int bxPos = this->width()/2 - suivantMainText->boundingRect().width()/2;
    int byPos = 0;
    suivantMainText->setPos(bxPos,byPos);
    scene->addItem(suivantMainText);

    //enemy Standar Text + Image
    enemyStandarText = new QGraphicsTextItem(QString("Standard"));
    QFont imageDescription("comic sans",30);
    enemyStandarText->setDefaultTextColor(QColor(53, 105, 188, 255));
    enemyStandarText->setFont(imageDescription);
    int dxPos = 50;
    int dyPos = 150;
    enemyStandarText->setPos(dxPos,dyPos);
    scene->addItem(enemyStandarText);

    enemyStandarImage = new QGraphicsPixmapItem();
    enemyStandarImage->setPixmap(QPixmap(":/Images/images/Vaisseau-Orange.png"));
    int axPos = 90;
    int ayPos = 230;
    enemyStandarImage->setPos(axPos,ayPos);
    scene->addItem(enemyStandarImage);

    //Enemy non standar text + image
    enemyRareText = new QGraphicsTextItem(QString("Rare") );
    enemyRareText->setDefaultTextColor(QColor(53, 105, 188, 255));
    enemyRareText->setFont(imageDescription);
    int rxPos = 550;
    enemyRareText->setPos(rxPos,dyPos);
    scene->addItem(enemyRareText);

    enemyRareImage = new QGraphicsPixmapItem();
    enemyRareImage->setPixmap(QPixmap(":/Images/images/Vaisseau-Purple.png"));
    int zxPos = 450;
    int zyPos = 250;
    enemyRareImage->setPos(zxPos,zyPos);
    scene->addItem(enemyRareImage);

    enemyLegImage = new QGraphicsPixmapItem();
    enemyLegImage->setPixmap(QPixmap(":/Images/images/Vaisseau-Vert.png"));
    int exPos = 550;
    enemyLegImage->setPos(exPos,zyPos);
    scene->addItem(enemyLegImage);

    enemyEpicImage = new QGraphicsPixmapItem();
    enemyEpicImage->setPixmap(QPixmap(":/Images/images/Vaisseau-Rouge-Instruction.png"));
    int ixPos = 650;
    enemyEpicImage->setPos(ixPos,zyPos);
    scene->addItem(enemyEpicImage);

    //suivant button
    secondSuivantInstruction = new Button(QString("Suivant"));
    connect(secondSuivantInstruction,SIGNAL(clicked()),this,SLOT(createLastInstruction()));
    connect(secondSuivantInstruction,SIGNAL(clicked()),this,SLOT(deleteSuivantInstruction()));
    int pxPos = this->width() - secondSuivantInstruction->boundingRect().width() -100 ;
    int pyPos = 475;
    secondSuivantInstruction->setPos(pxPos,pyPos);
    scene->addItem(secondSuivantInstruction);

    //Precedent button
    precedentInstruction = new Button(QString("Précédent"));
    connect(precedentInstruction,SIGNAL(clicked()),this,SLOT(createInstructions()));
    connect(precedentInstruction,SIGNAL(clicked()),this,SLOT(deleteSuivantInstruction()));
    int qxPos = precedentInstruction->boundingRect().width() - 100 ;
    precedentInstruction->setPos(qxPos,pyPos);
    scene->addItem(precedentInstruction);

}

void Game::deleteSuivantInstruction()
{
    delete suivantMainText;
    delete enemyStandarText;
    delete enemyStandarImage;
    delete enemyRareText;
    delete enemyRareImage;
    delete enemyEpicImage;
    delete enemyLegImage;
    delete secondSuivantInstruction;
    delete precedentInstruction;
}

void Game::createLastInstruction()
{
    //creation de l'image Instruction
    instructionImage = new QGraphicsPixmapItem();
    instructionImage->setPixmap(QPixmap(":/Images/images/Instructions.png"));
    int ixPos = 60;
    int iyPos = 0;
    instructionImage->setPos(ixPos,iyPos);
    scene->addItem(instructionImage);

    //creation du button précedent
    lastprecedentInstruction = new Button(QString("Précedent"));
    connect(lastprecedentInstruction,SIGNAL(clicked()),this,SLOT(createSuivantInstruction()));
    connect(lastprecedentInstruction,SIGNAL(clicked()),this,SLOT(deleteLastInstruction()));
    int axPos = lastprecedentInstruction->boundingRect().width() - 100 ;
    int ayPos = 475;
    lastprecedentInstruction->setPos(axPos,ayPos);
    scene->addItem(lastprecedentInstruction);

    //creation du button retour menu
    retourMenuInstruction = new Button(QString("Retour Menu"));
    connect(retourMenuInstruction,SIGNAL(clicked()),this,SLOT(slotMenuWin()));
    connect(retourMenuInstruction,SIGNAL(clicked()),this,SLOT(deleteLastInstruction()));
    int pxPos = this->width() - lastprecedentInstruction->boundingRect().width() -100 ;
    retourMenuInstruction->setPos(pxPos,ayPos);
    scene->addItem(retourMenuInstruction);

}

void Game::deleteLastInstruction()
{
    delete instructionImage;
    delete lastprecedentInstruction;
    delete retourMenuInstruction;
}

QTimer *Game::getTimer() const
{
    return timer;
}

MyRect *Game::getPlayer() const
{
    return player;
}

int Game::getVitesseTir() const
{
    return vitesseTir;
}

void Game::setVitesseTir(int value)
{
    vitesseTir = value;
}

int Game::getVitesseDeplacement() const
{
    return vitesseDeplacement;
}

void Game::setVitesseDeplacement(int value)
{
    vitesseDeplacement = value;
}

void Game::pause()
{
    timer->stop();
    for(auto enemy:player->getLesMechants()){
        enemy->pause();
    }
    timerEtoile->stop();
    timerEtoile2->stop();

    //creation du Titre GAME PAUSED
    pausedTitleText = new QGraphicsTextItem(QString("GAME PAUSED"));
    QFont endtitleFont("comic sans",50, QFont::Bold);
    pausedTitleText->setDefaultTextColor(QColor(53, 105, 188, 255));
    pausedTitleText->setFont(endtitleFont);
    int bxPos = this->width()/2 - pausedTitleText->boundingRect().width()/2;
    int byPos = 200;
    pausedTitleText->setPos(bxPos,byPos);
    scene->addItem(pausedTitleText);

    //button retour menu
    endGameButton = new Button(QString("Fin de la partie"));
    connect(endGameButton,SIGNAL(clicked()),this,SLOT(endGameDesired()));
    int vxPos = this->width()/2 - endGameButton->boundingRect().width()/2;
    int vyPos = 350;
    endGameButton->setPos(vxPos,vyPos);
    scene->addItem(endGameButton);

}

void Game::resume()
{
    timer->start(1500);
    timerEtoile->start(800);
    timerEtoile2->start(1200);
    for(auto mechant:player->getLesMechants()){
        mechant->resume();
    }

    //suppression du button retour menu
    delete endGameButton;
    delete pausedTitleText;
}

Gold *Game::getGold() const
{
    return gold;
}

Vie *Game::getVie() const
{
    return vie;
}

Score *Game::getScore() const
{
    return score;
}

int Game::getVitesseEnemie() const
{
    return vitesseEnemie;
}
