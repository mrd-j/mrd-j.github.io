inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在衡山山路上，四望山峰错落，林壑幽深，溪泉飞瀑，
云雾缭绕，不觉心胸大快。再走一会儿就是半山亭了。
LONG);
        set("exits", ([
               "southup"    : __DIR__"chidifeng",
               "northwest"  : __DIR__"shanlu4",
        ]));

        set("outdoors", "hengyang");

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
