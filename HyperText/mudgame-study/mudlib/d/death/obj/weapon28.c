#include <ansi.h>
#include <weapon.h>

inherit WHIP;

void create()
{
        set_name(HIR "烈火神鞭" NOR, ({ "liehuo bian", "bian", "liehuo", "whip" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 420000);
                set("material", "steel");
        }
        init_whip(60);
        setup();
}
