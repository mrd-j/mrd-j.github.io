// Room: /u/zqb/tiezhang/sslin-1.c

inherit ROOM;

void create()
{
    set("short", "松树林");
    set("long", @LONG
你走进一片黑压压的松树林，这里的松树枝繁叶茂，树冠相叠，遮天蔽
日。几素阳光从树梢间照射下来，在淡淡的雾气中，形成一条条白色的光柱，
煞是好看。你走着走着，忽然发现自己已迷失在这片松林中，找不到出去的
路了。
LONG    );
    set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"sslin-2",
  "west" : __FILE__,
  "south" : __DIR__ "shanlu-7",
  "north" : __FILE__,
]));
    set("no_clean_up", 0);

    setup();
    replace_program(ROOM);
}
