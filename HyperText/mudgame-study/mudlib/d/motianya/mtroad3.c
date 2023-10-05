// mtroad3.c  树林

inherit ROOM;

void create()
{
        set("short", "树林");
        set("long", @LONG
这里是茂密的森林。四周都是数不清的长草，一股阴森恐怖的气
氛。远处不时传来野兽的嚎叫，你实在不想在这里多留。
LONG );
        set("outdoors", "motianya");
        set("exits", ([
            "east"  : __DIR__"mtroad2",
            "west"  : __FILE__,
            "north" : __FILE__,
            "south" : __DIR__"mtroad4",
        ]));
        set("objects", ([
            __DIR__"npc/qiaofu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}

