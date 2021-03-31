#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "gold.h"
#include "myrect.h"
#include "score.h"
#include "vie.h"
#include <QGraphicsView>



class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);
    void createMainMenu();
    void deleteStart();
    void setAugmentationReducZero();

    Score *getScore() const;
    Vie *getVie() const;
    Gold *getGold() const;
    QTimer *getTimer() const;
    MyRect *getPlayer() const;
    string getGolds();

    int getVitesseEnemie() const;
    int getVitesseTir() const;
    void setVitesseTir(int value);

    int getVitesseDeplacement() const;
    void setVitesseDeplacement(int value);

    void pause();
    void resume();

    void initialisationVitesse();
    bool possibleUpgrade(int value);

    void initialisationGameGold();
    void setGameGold(int value);
    int getGameGold() const;

    void ecritureTxtEndGame(int temporaryGold);

    int getAugmentationVitesseEnnemie() const;
    void setAugmentationVitesseEnnemie(int value);

    int getAugmentationVitesseDefilement() const;
    void setAugmentationVitesseDefilement(int value);

    int getReductionVitesseTir() const;
    void setReductionVitesseTir(int value);

private:
    int vitesseEnemie=0;
    int vitesseTir=0;
    int vitesseDeplacement=0;
    int gameGold=0;

    int augmentationVitesseEnnemie=0;
    int augmentationVitesseDefilement=0;
    int reductionVitesseTir=0;

    QGraphicsScene *mainMenu;
    QGraphicsScene *scene;
    QGraphicsScene *endScene;

    QGraphicsTextItem *titleText;
    QGraphicsTextItem *goldTitleText;
    QGraphicsTextItem *endTitleText;
    QGraphicsTextItem *upgradeTitleText;
    QGraphicsTextItem *scoreTitleText;
    QGraphicsTextItem *pausedTitleText;
    QGraphicsTextItem *resumeeTitleText;
    QGraphicsTextItem *instructionTitleText;
    QGraphicsTextItem *directionText;
    QGraphicsTextItem *pauseText;
    QGraphicsTextItem *shootText;
    QGraphicsTextItem *suivantMainText;
    QGraphicsTextItem *enemyStandarText;
    QGraphicsTextItem *enemyRareText;

    QGraphicsPixmapItem *directionImage;
    QGraphicsPixmapItem *pauseImage;
    QGraphicsPixmapItem *shootImage;
    QGraphicsPixmapItem *enemyStandarImage;
    QGraphicsPixmapItem *enemyRareImage;
    QGraphicsPixmapItem *enemyLegImage;
    QGraphicsPixmapItem *enemyEpicImage;
    QGraphicsPixmapItem *instructionImage;

    Button *playButton;
    Button *rePlayButton;
    Button *quitButton;
    Button *upgradeButton;
    Button *menuButton;
    Button *endMenuButton;
    Button *endGameButton;
    Button *returnMenuButton;
    Button *quitButtonWin;
    Button *createInstruction;
    Button *deleteInstruction;
    Button *suivantInstruction;
    Button *secondSuivantInstruction;
    Button *precedentInstruction;
    Button *retourMenuInstruction;
    Button *lastprecedentInstruction;
    Button *resetTxt;

    Button *vitesseTirButton;
    Button *vitesseDeplacementButton;
    Button *vitesseDefilementButton;

    MyRect *player;
    Score *score;
    Vie *vie;
    QTimer *timer;
    QTimer *timerEtoile;
    QTimer *timerEtoile2;
    Gold *gold;

public slots:

    void start();
    void displayEndGame();
    void deleteMainMenu();
    void deleteEndMenu();
    void deleteEndMenuStart();
    void createUpgrade();
    void deleteUpgrade();
    void slotMenuEndGame();
    void slotMenuWin();
    void endGameDesired();
    void displaySumGame(int score, int temporaryGold);
    void resetDataTxt();

    void upgradeVitesseTir();
    void upgradeDeplacement();
    void upgradeVitesseDefilement();

    void testCleanEnemy();
    void updateGold();

    void deleteDisplaySum();
    void setVitesseEnemie(int value);

    void createInstructions();
    void deleteInstructions();

    void createSuivantInstruction();
    void deleteSuivantInstruction();

    void createLastInstruction();
    void deleteLastInstruction();

};

#endif // GAME_H
