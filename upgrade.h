#ifndef UPGRADE_H
#define UPGRADE_H

#include "button.h"

using namespace std;

class Upgrade
{
public:
    Upgrade();
private:
    Button *vitesseTirButton;
    Button *vitesseDeplacementButton;
    Button *vitesseDefilementButton;
};

#endif // UPGRADE_H
