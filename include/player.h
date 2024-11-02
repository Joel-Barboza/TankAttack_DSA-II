#ifndef PLAYER_H
#define PLAYER_H

#include "include/tank.h"
#include "include/singly_linked_list.h"
#include "include/queue.h"
#include "include/power_up.h"

class Player
{
public:
    Player();
    SinglyLinkedList<Tank*>* tankList = new SinglyLinkedList<Tank*>();
    Queue<PowerUp*>* powerUpQueue = new Queue<PowerUp*>();
};

#endif // PLAYER_H
