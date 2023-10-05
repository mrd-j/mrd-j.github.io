
inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
这里是古墓中的密室，四周密不透风，你只能借着墙上昏
暗的灯光来勉强分辨方向。墙是用整块的青石砌合起来的，接
合的甚是完美，你难以从中找出一丝缝隙。墙上好象雕有一些
浮雕。
LONG
        );

        set("exits", ([
                "east" : __FILE__,
                "north" : __DIR__"mishi3",
                "south" : __DIR__"mishi7",
                "west" : __FILE__,
        ]));

        setup();
        replace_program(ROOM);
}
