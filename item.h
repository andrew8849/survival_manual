#ifndef ITEM_H
#define ITEM_H

#include <QString>

#define TOOL_AMOUNT 300

class ITEM
{
public:
    ITEM();

    struct info{
      QString NAME;
      QString Tabs;
      QString Damage;
      QString Armor;
      QString Durability;
      QString Consol;
      QString Kinds;
      QString hunger;
      QString Sanity;
      QString Health;
      QString Wetness;
      QString Overheating;
      QString Freezing;
      QString Fuel;
      QString Rot;
      QString How;
      QString Etc;
    };

    ITEM::info Item[TOOL_AMOUNT];
};

#endif // ITEM_H
