#include "tuition.h"
#include "Player.h"

using namespace std;

int Tuition::action(Player *player){ 
  player->payTuition();
  return 0;
}