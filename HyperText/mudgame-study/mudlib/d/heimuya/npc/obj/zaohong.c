#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR "枣红缎面皮袍" NOR, ({ "zaohong pao", "zaohong", "pao" }));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("value", 3000);
                set("armor_prop/armor", 6);
        }
        setup();
}
