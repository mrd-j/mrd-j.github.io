//jinjie.c

#include <armor.h>

inherit HANDS;

void create()
{
        set_name("金戒指", ({ "jin jie", "jinjie", "ring" }));
        set("weight", 400);
        if (clonep())
            set_default_object(__FILE__);
        else
    {
            set("unit", "个");
            set("value", 10000);
            set("material", "gold");
            set("armor_prop/armor", 1);
            set("armor_prop/personality", 1);
    }

        setup();
}
