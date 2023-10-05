inherit ROOM;

void create()
{
        set("short", "松林小路");
        set("long", @LONG
这是山脚松林中的小路，两边长满参天的红松树，只能看
见一线天空。路旁有道士在奋力砍树。西边通向密林深处，东
边可回大道。
LONG);
        set("outdoors", "wudang");
        set("exits", ([
                "west" : __DIR__"slxl2",
                "east" : __DIR__"wdroad10",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
