#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
        set_name(HIM "绸舞扇" NOR, ({ "chouwu shan", "chouwu", "shan" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIM "这是一把丝绸扇面，彩绘花草，舞动"
                            "时绚丽多彩的绸舞扇。\n" NOR);
                set("value", 1000);
                set("material", "wood");
                set("wield_msg", "$N拿起一把$n握在手里。\n");
                set("unwield_msg", "$N合上$n，收回怀里。\n");
        }
        init_dagger(15);
        setup();
}

