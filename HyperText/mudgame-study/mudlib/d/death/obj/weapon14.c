#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name(HIY "九凰杖" NOR, ({ "jiuhuang zhang", "zhang", "jiuhuang", "staff" }) );
        set_weight(13000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 450000);
                set("material", "steel");
        }
        init_staff(65);
        setup();
}

