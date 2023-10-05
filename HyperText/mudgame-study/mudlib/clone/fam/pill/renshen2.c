#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(NOR + YEL "千年人参" NOR, ({ "qiannian renshen", "qiannian",
                                              "renshen", "shen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "产于高山上的珍贵药材，服用后可提升内功等级。\n" NOR);
                set("base_unit", "株");
                set("base_value", 15000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("pill_point", 35000);
                set("force_point", 5);
                set("pill_msg1", HIR "你只觉一股暖气散布全身，说不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只觉一股热流涌上，内息得到了完全的补充。\n" NOR);
        }
        setup();
}
