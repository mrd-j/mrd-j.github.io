inherit ROOM;

void create()
{
        set("short", "长廊");
        set("long", @LONG
这是连接内堂和后堂的长廊，虽不见花木，但也能闻到淡
淡的花香。
LONG);
        set("exits", ([
               "north"   : __DIR__"changlang4",
               "south"   : __DIR__"changlang2",
               "east"   : __DIR__"xiangfang2",
               "west"   : __DIR__"xiangfang1",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
