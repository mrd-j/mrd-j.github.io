#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(HIB "青鲨嗜" NOR, ({ "qingsha jian", "qingsha", "jian", "sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 1600000);
                set("material", "steel");
        }
        init_sword(120);
        setup();
}
