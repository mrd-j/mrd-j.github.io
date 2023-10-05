#include <ansi.h> 

inherit "/inherit/char/smith.c"; 

void create()
{
        set_name("铁匠", ({ "tiejiang", "smith" }));
        set("title", "甲胄店老板");
        set("shen_type", 1);
        set("gender", "男性" );
        set("age", 33);
        set("long", "铁匠正用铁钳夹住一块红热的铁块放进炉中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   "/d/jingzhou/obj/armor",
                   "/d/jingzhou/obj/beixin",
                   "/d/city/npc/obj/jinsijia",
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}
