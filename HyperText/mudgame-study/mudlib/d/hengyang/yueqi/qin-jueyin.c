#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(WHT "七玄流银·绝音" NOR, ({ "jueyin qin", "jueyin", "qin" }));
        set_weight(1000);

    if (clonep())
        set_default_object(__FILE__);
    else {
                set("unit", "把");
                set("long", WHT "此琴通体泛出银光，耀眼夺"
                "目。上刻「" HIR "绝音" WHT "」。\n" NOR);
        set("value", 5000000);
        set("material", "wood");
    }
    setup();
}

void init()
{
        add_action("play_qin", "play");
}
