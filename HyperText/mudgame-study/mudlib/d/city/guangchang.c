#include <ansi.h>
inherit ROOM;

string look_gaoshi();

void create()
{
    set("short", "中央广场");
    set("long", @LONG
这里是城市的正中心，一个很宽阔的广场，铺着青石地面。
游手好闲的人常在这里溜溜达达，经常有艺人在这里表演。中
央一棵大榕树(tree)盘根错节，据传已有千年的树龄，是这座
城市的历史见证，树干底部有一个很大的树洞(dong)，树干显
眼的位置贴有一张告示(gaoshi)。你可以看到北边有来自各地
的行人来来往往，南面人声鼎沸，一派繁华景象，东边不时地
传来朗朗的读书声，西边则见不到几个行人，一片肃静。
LONG);
    set("no_sleep_room",1);
    set("outdoors", "city");
    set("item_desc", ([
        "dong" : WHT "\n这是一个黑不溜湫的大洞，里面不知道"
                    "有些什么古怪。\n" NOR,
        "tree" : GRN "\n这是一棵巨大古老的大榕树，枝叶非常"
                    "的茂密。\n" NOR,
        "gaoshi" : (: look_gaoshi :),
    ]));

    set("exits", ([
        "east" : __DIR__"dongdajie1",
        "south" : __DIR__"nandajie1",
        "west" : __DIR__"xidajie1",
        "north" : __DIR__"beidajie1",
        "in" : "/d/gaibang/inhole",
    ]));

    set("objects", ([
        "/d/taishan/npc/jian-ke" : 1,
        "/d/beijing/npc/haoke1" : 1,
    ]));
    setup();
    "/clone/fam/notice"->foo();
    "/d/city/npc/liapo"->come_here();

}

void init()
{
    if (userp(this_player()))
    {
        this_object()->add("visitor", 1);
    }
    add_action("do_enter", "enter");
    add_action("do_climb", "climb");
}

int do_enter(string arg)
{
    object me;
    me = this_player();

    if (! arg || arg == "")
        return 0;

    if (arg == "dong")
    {
        if (me->is_busy())
        {
            return notify_fail("你的动作还没有完成，不能移动。\n");
            return 1;
        }

        message("vision", HIC + me->name() + HIC "一弯腰往洞里走"
                "了进去。\n" NOR, environment(me), ({me}));

        me->move("/d/gaibang/inhole");
        message("vision", HIC + me->name() + HIC "从洞里走了进来"
                "。\n" NOR, environment(me), ({me}));
        return 1;
    }
}

int do_climb(string arg)
{
    object me, ob;
    me = this_player();

    if (! arg || arg == "")
        return 0;

    if (arg == "tree")
    {
        if (me->is_busy())
        {
            return notify_fail("你的动作还没有完成，不能移动。\n");
            return 1;
        }

        foreach( ob in deep_inventory( me ) )
        if ( ob == me->query_temp( "is_riding" ) )
        {
            message_vision( "$N从$n上飞身跳下。\n", me, ob );
            me->delete_temp( "is_riding" );
            ob->delete_temp( "is_rided_by" );
            ob->move( environment( me ) );
        }

        message_vision(HIC "$N" HIC "攀着榕树的枝杈，三下两下爬了上去。\n" NOR, me);

        me->move(__DIR__"tree");
        message("vision", HIC + me->name() + HIC "从下面的广场攀爬了上来。\n"
                NOR, environment(me), ({me}));
        return 1;
    }
}

string look_gaoshi()
{
    string returnback;
    int count, sp;
    count = query("visitor");
    returnback = "\n" +
                 "******************************************************************\n" +
                 "********                                                  ********\n" +
                 "********                    扬州府通告                    ********\n" +
                 "********                                                  ********\n" +
                 "********    近期共有" + chinese_number(count) + "人通过此地。";
    for (sp = 0; sp < 26 - strwidth(chinese_number(count)); sp++)
        returnback += " ";
    returnback += "********\n"
                  "********                                                  ********\n" +
                  "******************************************************************\n";
    return returnback;
}
