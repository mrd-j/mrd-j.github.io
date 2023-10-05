// questd.c 处理任务的守护进程
// 包括师门任务函数载体和系统注册任务(SYSREG_QUEST)
// Updated by Vin for heros.cn

#include <ansi.h>
#include <quest.h>

#pragma optimize
// #pragma save_binary

inherit CORE_QUEST_D;
inherit F_DBASE;

// 定义提供给外部调用的接口函数
public mixed accept_ask(object me, object who, string topic);
public void set_information(object qob, string key, mixed info);
public mixed query_information(object qob, string key);
public void remove_information(object qob, string key);
public void remove_all_information(object qob);
public void remove_quest(string name);
public string generate_information(object knower, object who, string topic);
public void start_all_quest();

void create()
{
    seteuid(getuid());
    set("channel_id", "任务精灵");
    set_heart_beat(900);
    call_out("collect_all_quest_information", 1);
    doScanQuest();
}

int askQuest(object who, object me)
{
    notify_fail("对方没有任务需要你的帮助。\n");
    return doAssign(who, me);
}

int completeQuest(object who, object me)
{
    return doReward(who, me);
}

#define ONE_DAY (86400 / DATE_SCALE)
#define MAX_QUEST_LEVEL 3

private void special_bonus(object me, object who, mixed arg)
{
    int gongxian;

    // 随机奖励

    string *ob1_list = ({
        "/d/beijing/npc/dan/danA_5.c",
        "/d/beijing/npc/dan/danB_6.c",
        "/d/beijing/npc/dan/danC_5.c",
        "/d/beijing/npc/dan/danD_6.c",
        "/d/beijing/npc/dan/danM_9.c",
        "/d/beijing/npc/dan/danS_1.c",
        "/d/beijing/npc/dan/danS_2.c",
        "/d/beijing/npc/dan/danS_4.c",
        "/d/beijing/npc/dan/danS_4.c",
        "/d/beijing/npc/dan/danS_5.c",

        "/clone/fam/pill/full1",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/neili1",
        "/clone/fam/etc/va1",
        "/clone/fam/etc/va2",
        "/clone/fam/etc/va3",
        "/clone/fam/etc/va4",
        "/clone/fam/etc/va5",
        "/clone/fam/etc/va6",
    });

    // 完成三十个任务
    string *ob2_list = ({
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/food1",
        "/clone/fam/pill/neili2",
    });

    // 完成五十个任务
    string *ob3_list = ({
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/sheli3",
        "/clone/gift/cdiamond",
        "/clone/gift/cagate",
        "/clone/gift/ccrystal",
        "/clone/gift/cjade",
    });

    // 完成一百个任务
    string *ob4_list = ({
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/sheli4",
        "/clone/fam/gift/str1",
        "/clone/fam/gift/int1",
        "/clone/fam/gift/con1",
        "/clone/fam/gift/dex1",
        "/clone/fam/item/handan",
        "/clone/fam/item/bixue",
        "/clone/fam/item/zijin",
        "/clone/fam/item/wujin",
        "/clone/fam/item/taijin",
        "/clone/fam/pill/renshen1",
        "/clone/fam/pill/lingzhi1",
        "/clone/fam/pill/xuelian1",
    });

    // 完成两百个任务
    string *ob5_list = ({
        "/clone/fam/etc/lv5a",
        "/clone/fam/etc/lv5b",
        "/clone/fam/etc/lv5c",
        "/clone/fam/etc/lv5d",
        "/clone/fam/etc/lv5e",
        "/clone/fam/pill/renshen2",
        "/clone/fam/pill/lingzhi2",
        "/clone/fam/pill/xuelian2",
    });

    // 完成三百个任务
    string *ob6_list = ({
        "/clone/fam/gift/str2",
        "/clone/fam/gift/int2",
        "/clone/fam/gift/con2",
        "/clone/fam/gift/dex2",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/item/zhenlong",
        "/clone/fam/item/jiulei",
    });

    // 完成四百个任务
    string *ob7_list = ({
        "/clone/tattoo/buttock1",
        "/clone/tattoo/buttock2",
        "/clone/tattoo/buttock3",
        "/clone/tattoo/buttock4",
        "/clone/tattoo/buttock5",
        "/clone/tattoo/buttock6",
        "/clone/tattoo/buttock7",
        "/clone/tattoo/buttock8",
    });

    // 完成五百个任务
    string *ob8_list = ({
        "/clone/fam/gift/str2",
        "/clone/fam/gift/int2",
        "/clone/fam/gift/con2",
        "/clone/fam/gift/dex2",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/etc/lv7a",
        "/clone/fam/etc/lv7b",
        "/clone/fam/etc/lv7c",
        "/clone/fam/etc/lv7d",
    });

    // 完成六百个任务
    string *ob9_list = ({
        "/clone/tattoo/body1",
        "/clone/tattoo/body2",
        "/clone/tattoo/body3",
        "/clone/tattoo/body4",
        "/clone/tattoo/body5",
        "/clone/tattoo/body6",
        "/clone/tattoo/body7",
        "/clone/tattoo/body8",
        "/clone/tattoo/body9",
        "/clone/tattoo/body10",
    });

    // 完成七百个任务
    string *ob10_list = ({
        "/clone/fam/pill/yulu",
        "/clone/fam/pill/dimai",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/xuelian4",
        "/clone/fam/item/baxian",
        "/clone/fam/item/kunlun",
        "/clone/fam/item/haoyue",
        "/clone/fam/item/leihuo",
        "/clone/fam/item/yinzhu",
    });

    // 完成八百个任务
    string *ob11_list = ({
        "/clone/tattoo/spcs1",
        "/clone/tattoo/spcs2",
        "/clone/tattoo/spcs3",
        "/clone/tattoo/spcs4",
        "/clone/tattoo/spcs5",
        "/clone/tattoo/spcs6",
        "/clone/tattoo/spcs7",
        "/clone/tattoo/spcs8",
        "/clone/tattoo/spcs9",
        "/clone/tattoo/spcs10",
    });

    // 完成九百个任务
    string *ob12_list = ({
        "/clone/fam/skpaper/blade1",
        "/clone/fam/skpaper/claw1",
        "/clone/fam/skpaper/club1",
        "/clone/fam/skpaper/cuff1",
        "/clone/fam/skpaper/dagger1",
        "/clone/fam/skpaper/finger1",
        "/clone/fam/skpaper/hammer1",
        "/clone/fam/skpaper/hand1",
        "/clone/fam/skpaper/parry1",
        "/clone/fam/skpaper/staff1",
        "/clone/fam/skpaper/strike1",
        "/clone/fam/skpaper/sword1",
        "/clone/fam/skpaper/throwing1",
        "/clone/fam/skpaper/unarmed1",
        "/clone/fam/skpaper/whip1",
    });

    // 完成一千个任务
    string *ob13_list = ({
        "/clone/fam/gift/str3",
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/dex3",
        "/clone/fam/item/yanluo",
        "/clone/fam/item/lihuo",
        "/clone/fam/item/qiankun_stone",
    });
    // 新增1000万exp且1000任务奖励
    string *ob14_list = ({
        "/clone/tattoo/spc1",
        "/clone/tattoo/spc2",
        "/clone/tattoo/spc3",
        "/clone/tattoo/spc4",
        "/clone/tattoo/spc5",
        "/clone/tattoo/spc6",
        "/clone/tattoo/spc7",
        "/clone/tattoo/spc8",
        "/clone/tattoo/spc9",
        "/clone/tattoo/spc10",
    }) + ob13_list;

    // 新增2000万exp且1000任务奖励
    string *ob15_list = ({
        "/clone/fam/etc/bipo",
        "/clone/fam/etc/huanshi",
        "/clone/fam/etc/binghuozhu",
        "/clone/fam/etc/leishenzhu",
        "/clone/fam/item/bless_water",
        "/clone/tattoo/spc11",
        "/clone/tattoo/spc12",
        "/clone/tattoo/spc13",
    }) + ob14_list;
    // 增加5000万exp且1000任务奖励
    string *ob16_list = ({
        "/clone/fam/obj/guo.c",
        "/clone/fam/max/tianshu1",
        "/clone/fam/max/tianshu2",
    }) + ob15_list;
    // 增加1亿exp且1000任务奖励
    string *ob17_list = ({
        "/d/death/obj/tianjing",
    }) + ob16_list;

    string un, gift;
    object ob;

    int exp;
    exp = who->query("combat_exp");

    if (stringp(arg))
        gift = arg;
    else if (who->query("quest_count") == 1000)
    {
        gift = ob13_list[random(sizeof(ob13_list))];
        gongxian = 500;

        if (exp >= 10000000)
        {
            gift = ob14_list[random(sizeof(ob14_list))];
        }
        if (exp >= 20000000)
        {
            gift = ob15_list[random(sizeof(ob15_list))];
        }
        if (exp >= 50000000)
        {
            gift = ob16_list[random(sizeof(ob16_list))];
        }
        if (exp >= 100000000)
        {
            gift = ob17_list[random(sizeof(ob17_list))];
        }
    }
    else if ((who->query("quest_count") == 900) && (exp >= 900000))
    {
        gift = ob12_list[random(sizeof(ob12_list))];
        gongxian = 450;
    }
    else if ((who->query("quest_count") == 800) && (exp >= 800000))
    {
        gift = ob11_list[random(sizeof(ob11_list))];
        gongxian = 400;
    }
    else if ((who->query("quest_count") == 700) && (exp >= 700000))
    {
        gift = ob10_list[random(sizeof(ob10_list))];
        gongxian = 350;
    }
    else if ((who->query("quest_count") == 600) && (exp >= 600000))
    {
        gift = ob9_list[random(sizeof(ob9_list))];
        gongxian = 300;
    }
    else if ((who->query("quest_count") == 500) && (exp >= 500000))
    {
        gift = ob8_list[random(sizeof(ob8_list))];
        gongxian = 250;
    }
    else if (who->query("quest_count") == 400)
    {
        gift = ob7_list[random(sizeof(ob7_list))];
        gongxian = 200;
    }
    else if (who->query("quest_count") == 300)
    {
        gift = ob6_list[random(sizeof(ob6_list))];
        gongxian = 150;
    }
    else if (who->query("quest_count") == 200)
    {
        gift = ob5_list[random(sizeof(ob5_list))];
        gongxian = 100;
    }
    else if (who->query("quest_count") == 100)
    {
        gift = ob4_list[random(sizeof(ob4_list))];
        gongxian = 50;
    }
    else if (who->query("quest_count") == 50)
    {
        gift = ob3_list[random(sizeof(ob3_list))];
        gongxian = 25;
    }
    else if (who->query("quest_count") == 30)
    {
        gift = ob2_list[random(sizeof(ob2_list))];
        gongxian = 15;
    }
    else
    {
        gift = ob1_list[random(sizeof(ob1_list))];
        gongxian = 1;
    }
    ob = new (gift);

    if (ob->query("base_unit"))
        un = ob->query("base_unit");
    else
        un = ob->query("unit");

    if (who->query("gongxian") >= gongxian)
    {
        message_vision(CYN "$n" CYN "对$N" CYN "微笑道：我这里有一" + un + ob->name() + CYN "，如果你用得着就拿"
                        "去吧。\n" NOR, who, me);

        tell_object(who, HIW "\n获得" + ob->name() + HIW "需要消耗"
                    "你" + chinese_number(gongxian) + "点门派"
                    "贡献，你是否愿意(" HIY "answer Y|N" HIW ")接受？\n\n" NOR);

        // 记录可以领取任务奖励的NPC
        who->set_temp("quest_gift/npc", me->query("id"));

        // 记录任务奖励物品的路径
        who->set_temp("quest_gift/obj", gift);

        // 记录领取该物品所需的门牌贡献
        who->set_temp("quest_gift/gongxian", gongxian);
    }
    else
        message_vision(CYN "$n" CYN "对$N" CYN "道：正好我这"
                           "里有…嗯…还是算了，相信你也用不到。"
                           "\n" NOR,
                       who, me);
    destruct(ob);
}

public mixed accept_ask(object me, object who, string topic)
{
    string my_fam;

    my_fam = me->query("family/family_name");

    if (topic == "历练" || topic == "历炼" ||
        topic == "锻炼")
    {
        if (my_fam != who->query("family/family_name"))
            return "你是谁？找我有什么事情么？";

        if (who->query("out_family"))
            return "去吧！" + who->name(1) + "，好自为之！";

        if (who->query("combat_exp") < 50000)
        {
            message_vision(CYN "$N" CYN "叹了一口气，看了看$n" CYN "道：你的武功基础还不太好，还是"
                               "再好好锻炼吧。\n" NOR,
                           me, who);
            return 1;
        }

        if (who->query("score") < 100)
        {
            message_vision(CYN "$N" CYN "摆摆手道：你的江湖阅"
                               "历太少，现在不可外出独自行走江湖。"
                               "\n" NOR,
                           me, who);
            return 1;
        }

        who->set("out_family", 1);
        if (me->is_good())
        {
            message_sort(HIY "$N" HIY "对$n" HIY "欣慰的点了"
                             "点头，道：看来我们" + my_fam + "又"
                             "出了一位人才啊！你记住了，我辈武人"
                             "，切忌不可好勇争斗，要多做行侠仗义"
                             "之事！\n" NOR,
                         me, who);
        }
        else if (me->is_bad())
        {
            message_sort(HIR "$N" HIR "对$n" HIR "哈哈大笑道"
                             "：好！好！好！你可以出去走走看看了"
                             "，对那些自认所谓大侠之辈可不要手软"
                             "，去吧！\n" NOR,
                         me, who);
        }
        else
        {
            message_sort(HIY "$N" HIY "对$n" HIY "叮嘱道：以"
                             "后你行走江湖常常是孤身一人，记得要"
                             "敬重前辈，不可狂妄自大，切记了，去"
                             "吧！\n" NOR,
                         me, who);
        }

        message_sort(HIC "$N" HIC "翻出一本小册子，对$n" HIC "道"
                         "：今后你行走江湖，许多山川地理，世间风情你"
                         "都可以记录在这本地图册上，以供参考，对你多"
                         "少也会有些帮助。\n" NOR,
                     me, who);

        tell_object(who, HIC "\n你获得了师傅赠给你的地图册。\n" NOR +
                             WHT "请参见帮助(" HIW "help quest" NOR +
                             WHT ")以获得更详细的信息。\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + who->name(1) + "已经开始闯荡江湖。");
        return 1;
    }
}

// 领取任务
// 如果目前正在协助别人，不能领取任务
int ask_quest(object me, object who)
{
    string fam, myfam; // 门派信息
    object ob;         // 任务重的某些对象或人物
    mapping q;         // WHO的人物
    object aob;        // WHO目前正在协助的对象
    int exp;           // WHO的经验
    int t;             // 用来计算时间的变量
    int level;         // QUEST的等级
    int reborn;        //转世次数
    string place;
    string gender;

    message_vision("$n向$N打听有关任务的情况。\n", me, who);

    fam = me->query("family/family_name");
    myfam = who->query("family/family_name");

    if ((!myfam && fam != "侠客盟") || (myfam && myfam != fam))
    {
        message_vision(CYN "$N" CYN "瞪大眼睛看着$n" CYN "，道"
                           "：你又不是我们" + fam + "的，来捣什么乱"
                           "？\n" NOR, me, who);
        return 1;
    }

    if (who->query_temp("quest_gift"))
    {
        message_vision(CYN "$N" CYN "对$n" CYN "皱眉道：我问你"
                           "话呢，那东西你到底要(" HIY "answer Y|N" NOR +
                           CYN ")还是不要？\n" NOR,
                       me, who);
        return 1;
    }

    q = who->query("quest");
    if (mapp(q))
    {
        if (q["freequest"] > 0)
        {
            message_vision(CYN "$N" CYN "对$n" CYN "说道：我这里暂"
                               "时也没什么事情，你还是自己锻炼一段时间"
                               "吧。\n" NOR,
                           me, who);
            tell_object(who, HIY "你突然想到：现在江湖正值动乱，何"
                                 "不四处走访，也许可提高自己的经验阅历"
                                 "。\n" NOR);
            return 1;
        }

        if (q["master_id"] && q["master_id"] != me->query("id"))
        {
            message_vision(CYN "$N" CYN "看了看$n" CYN "，"
                               "哼了一声，没有理会$n" CYN "。\n" NOR,
                           me, who);
            return 1;
        }

        switch (q["type"])
        {
        case "kill":
            message_vision(CYN "$N" CYN "一脸怒容对$n" CYN "道：我不是让"
                               "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                               "之前杀了" NOR + HIR + q["name"] + NOR + CYN "的吗？现在是" + CHINESE_D->chinese_monthday(time()) +
                               "，那家伙的人头呢？\n" NOR,
                           me, who);
            break;
        case "letter":
            message_vision(CYN "$N" CYN "一脸怒容对$n" CYN "道：我不是让"
                               "你" + CHINESE_D->chinese_monthday(q["limit"]) +
                               "之前把信送到" NOR + HIC + q["name"] + NOR + CYN "那里的吗？现在是" + CHINESE_D->chinese_monthday(time()) +
                               "，他的回执呢？\n" NOR,
                           me, who);
            break;
        }
        return 1;
    }

    if (me->query("eff_qi") * 2 < me->query("max_qi") ||
        me->query("qi") * 2 < me->query("max_qi"))
    {
        message_vision(HIC "$N" HIC "捂着胸口，一副非常痛苦的样子，对你的"
                           "话显然没有听进去。\n" NOR,
                       me);
        return 1;
    }

    exp = who->query("combat_exp");
    if (exp < 10000)
    {
        message_vision(CYN "$N" CYN "叹了一口气，对$n" CYN "道：就你那点水平，"
                           "我实在没法给你派任务。\n" NOR,
                       me, who);
        return 1;
    }

    if (objectp(aob = who->query_temp("quest/assist")))
    {
        message_vision(CYN "$N" CYN "看了看$n" CYN "，道：我听说你不是帮" NOR +
                           HIY + aob->name(1) + NOR + CYN "去了么？先办妥了"
                           "再说吧！\n" NOR,
                       me, who);
        return 1;
    }

    if (exp < 100000)
    {
        object letter;

        if (who->query("score") < 20)
        {
            message_vision(CYN "$N" CYN "摇摇头，对$n" CYN "道：可惜你"
                               "的江湖阅历太差，不然我还可以让你帮我送封信"
                               "。\n" NOR,
                           me, who);
            return 1;
        }

        ob = new (CLASS_D("generate") + "/receiver.c");
        NPC_D->place_npc(ob, ({"大理一带", "关外", "星宿海", "天山", "终南山",
                               "西域", "凌霄城附近", "五毒教附近"}));
        NPC_D->set_from_me(ob, me, 100);
        NPC_D->random_move(ob);
        place = ob->query("place");

        letter = new ("/clone/misc/letter");
        letter->set("long", "这是一封" + me->name() + "写给" + ob->name() + "的亲笔信函。\n");
        letter->set("send_from", me->query("id"));
        letter->set("send_to", ob->query("id"));
        letter->set("send_from_name", me->name());
        letter->move(me);

        message_vision(CYN "$N" CYN "对$n" CYN "道：这封信你帮我交到" NOR +
                           HIC + ob->name() + NOR + CYN "手中，他现在应该在" +
                           place + "，然后把回执带回来给我！\n" NOR,
                       me, who);

        me->force_me("give letter to " + who->query("id"));
        who->set("quest/info", letter->query("id"));
        who->set("quest/type", "letter");
    }
    else
    {
        // 门派中人需要外出历练
        if (myfam && !who->query("out_family"))
        {
            message_vision(CYN "$N" CYN "摆摆手，对$n" CYN "道：我现在"
                               "这里倒是有一些事情，不过待你外出历练段时间"
                               "后再说吧！\n" NOR,
                           me, who);
            return 1;
        }

        if (who->query("score") < 100)
        {
            message_vision(CYN "$N" CYN "叹了一口气，对$n" CYN "道：你"
                               "还是在江湖上多历练历练，增进些阅历再说吧！"
                               "\n" NOR,
                           me, who);
            tell_object(who, HIY "看来还是先加强自己的江湖阅历才行。\n" NOR);
            return 1;
        }

        if (who->is_bad() && me->is_good())
        {
            message_vision(CYN "$N" CYN "大怒道：岂有此理！你居然已经误"
                               "入歧途，还敢来见我！\n" NOR,
                           me, who);
            return 1;
        }

        if (who->is_good() && me->is_bad())
        {
            message_vision(CYN "$N" CYN "大怒道：岂有此理！才几天不见，"
                               "你居然也学起假仁假义来了，快给我滚！\n" NOR,
                           me, who);
            return 1;
        }

        // reborn = 0;
        reborn = who->query("reborn/count");
        level = who->query_temp("quest/next_level");
        if (level < 0 || level > MAX_QUEST_LEVEL)
            level = 0;
        level += reborn;
        who->delete_temp("super");
        //添加转世超级npc
        if (who->query("reborn") && who->query("combat_exp") > 800000 && random(50) <= reborn)
        {
            who->set_temp("super", reborn);
            ob = new (CLASS_D("generate") + "/killed_super.c");
            ob->set("can_learn/dugu-jiujian/nothing", 1);
        }
        else
            ob = new (CLASS_D("generate") + "/killed.c");
        NPC_D->place_npc(ob, who->query("combat_exp") < 500000 ? ({"大理一带", "终南山", "关外", "西域"}) : who->query("combat_exp") < 800000 ? ({"大理一带", "终南山", "西域"}) : 0);
        NPC_D->set_from_me(ob, who, 100);
        ob->add_temp("apply/attack", ob->query_skill("force", 1) * (level - 1) / 15);
        ob->add_temp("apply/dodge", ob->query_skill("force", 1) * (level - 1) / 15);
        ob->add_temp("apply/parry", ob->query_skill("force", 1) * (level - 1) / 15);
        ob->add_temp("apply/damage", 5 + level * 7);
        ob->add_temp("apply/unarmed_damage", 5 + level * 7);
        ob->add_temp("apply/armor", 10 + level * 15);
        ob->set_temp("quester", who->query("id"));
        NPC_D->random_move(ob);
        place = ob->query("place");
        gender = (ob->query("gender") == "女性") ? "她" : "他";

        message("vision", WHT + me->name() + WHT "小声的对" + who->name() + WHT "吩咐着什么，" + who->name() + WHT "一边听，一边不住的点头。\n" NOR,
                environment(who), ({who}));
        if (me->is_good())
        {
            ob->set("shen", -ob->query("combat_exp") / 2000);
            if (me->query("family/family_name") == "少林派")
                tell_object(who, CYN + me->name() + CYN "对你道：虽"
                                "然我们出家人以慈悲为怀，但是对于大"
                                "凶大恶之徒也不能放过。\n最近" NOR +
                                HIR + ob->name() + NOR + CYN "在" +
                                place + "作恶多端，你去把" + gender +
                                "除了，提头来见。\n" NOR);
            else
                tell_object(who, CYN + me->name() + CYN "对你道：" NOR + HIR + ob->name() + NOR + CYN "这个"
                                "败类打家劫舍，无恶不作，听说" + gender +
                                "最近在" + place + "，你去除掉" + gender +
                                "，提头来见我！\n" NOR);
        }
        else if (me->is_bad())
        {
            ob->set("shen", ob->query("combat_exp") / 2000);
            tell_object(who, CYN + me->name() + CYN "对你道：" NOR + HIR + ob->name() + NOR + CYN "这个所谓大侠屡次"
                            "和我派作对，听说" + gender + "最近在" + place +
                            "，你去宰了" + gender + "，提头来见！\n" NOR);
        }
        else
        {
            ob->set("shen_type", 0);
            ob->set("shen", 0);
            tell_object(who, CYN + me->name() + CYN "对你说道：我早就看" NOR + HIR + ob->name() + NOR + CYN "不顺眼"
                            "，听说" + gender + "最近在" + place + "，你去做了" + gender + "，带" + gender + "的人头来交差！\n" NOR);
        }
        who->set("quest/type", "kill");
        switch (level)
        {
        case 0:
            message_vision(CYN "$N" CYN "顿了顿，又对$n" CYN "道：这个"
                               "事情容易办得很，你要是还办不成那可不象话。"
                               "\n" NOR,
                           me, who);
            break;
        case 1:
            break;
        case 2:
            message_vision(CYN "$N" CYN "看了看$n" CYN "又道：这个事情"
                               "很是有些难办，你要是不行我就另找人吧。\n" NOR,
                           me, who);
            break;
        case 3:
            message_vision(CYN "$N" CYN "叹了口气，郑重的对$n" CYN "道"
                               "：这次任务凶险得紧，你不要勉强自己，不行就"
                               "算了。\n" NOR,
                           me, who);
            break;
        }

        if (level > 0 && random(10) == 1)
        {
            string flee_msg;

            // 随机重新放置NPC的位置
            message_sort(HIC "\n$N" HIC "话音刚落，突然一人匆忙赶了过"
                             "来，喊道：不好了，不好了。听说那个叫" HIW +
                             ob->name() + HIC "的家伙在" + place + HIC "失"
                             "踪了，现在也不知道去了哪里。\n\n" NOR,
                         me, who);

            message_vision(CYN "$N" CYN "呆了半晌，这才对$n" CYN "叹道"
                               "：这事麻烦了，看来只有靠你自己努力了。\n" NOR,
                           me, who);

            switch (random(3))
            {
            case 0:
                flee_msg = "听说$N听到了江湖上有人追杀的风声，已经躲"
                           "到PLACE去了。";
                break;
            case 1:
                flee_msg = "有人说$N就在咱们这地界呢，但是也有人说"
                           "在PLACE，不知道是真是假。";
                break;
            default:
                flee_msg = "不知道……哦？好像听人说过是在PLACE。";
                break;
            }
            ob->random_place(flee_msg);
        }
    }

    who->set("quest/family", fam);
    who->set("quest/master_name", me->name());
    who->set("quest/master_id", me->query("id"));
    who->set("quest/name", ob->name());
    who->set("quest/id", ob->query("id"));
    who->set("quest/level", level);
    who->set("quest/place", place);
    t = time();
    who->set("quest/time", t);
    t = time() / ONE_DAY;
    // 因为现在游戏时间改为60倍，1天24分钟，是以前的1/6，减少天数限制
    if (ob->query("place") == "西域")
        t += 3;
    else
        t += 2;
    t = t * ONE_DAY - 1;
    who->set("quest/limit", t);
    message("vision", WHT + me->name() + WHT "在你耳边悄声说道：你务必要在" NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT "之前完成！\n" NOR, who);

    /*
    //测试后门，非测试时注释掉
    if (who->query("id") == "mudren")
    {
        who->move(environment(ob));
        message_vision(CYN "$N" CYN "马不停蹄的赶到$n所在地。\n" NOR, who, ob);
        who->set_leader(ob);
    }
    */
    who->start_busy(1);
    return 1;
}

int accept_object(object me, object who, object ob)
{
    mapping q;         // WHO的任务
    string msg;        // 掌门说的消息
    string fam, myfam; // 门派名称
    object dob;        // 打晕敌人的人
    int bonus;         // 奖励(正整数，1是正常)
    int t;             // 用来计算时间的变量
    int exp;           // 获得的经验
    int pot;           // 获得的潜能
    int mar;           // 获得的实战体会
    int weiwang;       // 获得的威望
    int score;         // 获得的江湖阅历
    int gongxian;      // 获得的门派贡献
    int lvl;           // 人物的等级
    int quest_level;   // QUEST的等级
    int quest_count;   // 连续QUEST的数目
    int timeover;      // 标志：超时了？
    int added;         // 做任务的时候额外出现的敌人或敌人逃走
    int reborn;        //新增转世次数
    mixed special = 0; // 是否有特殊奖励

    message_vision("$n向$N打听有关任务的情况。\n", me, who);

    fam = me->query("family/family_name");
    myfam = who->query("family/family_name");

    if ((!myfam && fam != "侠客盟") || (myfam && myfam != fam))
        return 0;

    q = who->query("quest");
    if (ob->is_letter())
    {
        if (ob->query("send_from") != me->query("id"))
        {
            message_vision(CYN "$N" CYN "道：你要干什么？\n" NOR, me);
            return -1;
        }

        if (!q || q["type"] != "letter" || ob->query("send_to") != q["id"])
        {
            message_vision(CYN "$N" CYN "深深的叹了一口气，没说什么？\n" NOR, me);
            destruct(ob);
            return 1;
        }

        message_vision(CYN "$N" CYN "瞪着$n" CYN "道：干什么？交给你"
                           "的活你不打算干了？\n" NOR,
                       me, who);
        return -1;
    }

    if (ob->is_receipt())
    {
        if (ob->query("reply_to") != me->query("id"))
        {
            me->force_me("say 给我这玩意干什么？");
            return 0;
        }

        if (!q || q["type"] != "letter" || q["id"] != ob->query("reply_by"))
        {
            me->force_me("nod");
            me->force_me("say 多谢了。");
            destruct(ob);
            return 1;
        }

        msg = CYN "$N" CYN "接过" + ob->name() + NOR + CYN "，仔细看了"
                  "看，满意的说：很好。\n" NOR;
        t = time();
        if (t > q["limit"])
        {
            msg += CYN "$N" CYN "叹了口气，又道：可惜，不是让你" +
                   CHINESE_D->chinese_monthday(q["limit"]) + "前做完吗？算"
                   "了，将功补过，你先退下吧。\n" NOR;
            timeover = 1;
        }
        else
        {
            if (t - q["time"] < ONE_DAY)
            {
                msg += CYN "$N" CYN "点点头道：你很不错，这么"
                           "快就完成了，好好干！\n" NOR;
            }
            else
                msg += CYN "$N" CYN "点点头道：这次不错，辛苦"
                           "了。\n" NOR;

            timeover = 0;
        }
        bonus = (ob->query("receive_from") == who->query("id"));
        exp = 15 + random(10);
        pot = 5 + random(8);
        mar = 1;
        score = 6 + random(5);
        weiwang = 1;
        gongxian = 1;
        destruct(ob);
    }
    else
    {
        if (!mapp(q) || !ob->is_corpse() && !ob->is_head())
            return 0;

        if (!stringp(ob->query("owner_id")))
        {
            message_vision(CYN "$N" CYN "捂着鼻子看了看" + ob->name() + NOR + CYN "，道：什么臭烘烘的？快给我"
                               "拿走。\n" NOR, me);
            return 0;
        }

        if (ob->query("taskob") == q["id"])
        {
            message_vision(CYN "$N" CYN "捂着鼻子看了看" + ob->name() + NOR + CYN "，道：什么臭烘烘的？快给我"
                               "拿走。\n" NOR, me);
            return 0;
        }

        if (ob->query("owner_id") != q["id"])
            return 0;

        msg = CYN "$N" CYN "接过" + ob->name() + NOR + CYN "，哈哈大笑"
                           "，对$n" CYN "道：";

        if (me->is_good())
            msg += CYN "又除了一害，很好！";
        else if (me->is_bad())
            msg += CYN "好极了！什么大侠，不堪一击！";
        else
            msg += CYN "干得好，漂亮！";

        msg += "\n" NOR;
        t = time();
        if (who->query_temp("quest/escape_times"))
        {
            msg += CYN "$N" CYN "赞许道：这次没想到敌人这么强悍，实"
                       "在未曾料到，辛苦，辛苦！\n" NOR;
            timeover = 0;
        }
        else if (t > q["limit"])
        {
            msg += CYN "$N" CYN "摇摇头，又道：可惜，不是让你" +
                   CHINESE_D->chinese_monthday(q["limit"]) + "前做完吗？算"
                   "了，将功补过，你先退下吧。\n" NOR;
            timeover = 1;
        }
        else
        {
            if (t - q["time"] < ONE_DAY)
            {
                msg += CYN "$N" CYN "点点头道：干得不错，这么"
                           "快就完成了，好好干！\n" NOR;
            }
            else
                msg += CYN "$N" CYN "点点头道：这次不错，辛苦"
                           "了。\n" NOR;

            timeover = 0;
        }

        // bonus为1表示正常奖励，为2表示扣除一半。
        bonus = (ob->query("killed_by") == who->query("id")) &&
                (ob->query("defeated_by") == who ||
                 !ob->query("defeated_by") &&
                     ob->query("defeated_by_who") == who->name(1));
        if (ob->query("assist") == who)
        {
            dob = ob->query("defeated_by");
            msg += CYN "$N" CYN "欣慰的对$n" CYN "道：这次你能够"
                       "得到" + (dob ? dob->name(1) : "同门师兄弟") +
                   NOR + CYN "的帮忙，也属不易！以后彼此要多加照"
                             "应！\n" NOR;
            bonus = 2;
        }
        else if (bonus)
            bonus = 1;

        destruct(ob);
        reborn = who->query("reborn/count");
        lvl = NPC_D->check_level(who);
        exp = 10 + random(5) + lvl + reborn;
        pot = 5 + random(3) + lvl + reborn;
        mar = 1 + random(2);
        weiwang = 2 + random(3) + lvl / 2;
        score = 2 + random(3) + lvl / 2;
        gongxian = 1;
        quest_count = who->query("quest_count") + 1;

        // add temped for keep compactible with old version
        if (who->query_temp("quest/total_count"))
        {
            quest_count = who->query_temp("quest/total_count") + 1;
            who->delete_temp("quest/total_count");
        }

        // 根据任务完成的次数修正奖励
        if (quest_count >= 500)
        {
            // 连续完成了超过500次的任务
            exp += 80 + random(quest_count / 20 + 1);
            pot += 45 + random(quest_count / 25 + 1);
            mar = 50 + random(20);
            weiwang += 8 + random(20);
            score += 4 + random(15);
            gongxian += random(2);
        }
        else if (quest_count >= 200)
        {
            // 连续完成了超过200次的任务
            exp += 70 + random(quest_count / 20 + 1);
            pot += 40 + random(quest_count / 25 + 1);
            mar = 20 + random(10);
            weiwang += 5 + random(15);
            score += 3 + random(10);
        }
        else if (quest_count >= 100)
        {
            // 连续完成了超过100次的任务
            exp += 50 + random(quest_count / 20 + 1);
            pot += 30 + random(quest_count / 25 + 1);
            weiwang += 3 + random(10);
            score += 2 + random(10);
        }
        else if (quest_count >= 10)
        {
            // 连续完成了超过10次的任务
            exp += 45 + random(quest_count / 20 + 1);
            pot += 25 + random(quest_count / 25 + 1);
            weiwang += 1 + random(5);
            score += 1 + random(5);
        }

        switch (quest_level = q["level"])
        {
        case 0:
            exp = exp / 2 + 1;
            pot = pot / 2 + 1;
            gongxian = gongxian / 2 + 1;
            weiwang = weiwang / 3 + 1;
            score = score / 4 + 1;
            msg += CYN "$N" CYN "看着$n" CYN "接着说道：还行吧，下"
                       "次我给你个难点的任务。\n" NOR;
            break;
        case 1:
            msg += CYN "$N" CYN "对$n" CYN "又道：不错，看来我可以"
                       "托付些重任给你了。\n" NOR;
            break;
        case 2:
            exp += exp / 4;
            pot += pot / 4;
            weiwang += weiwang / 4;
            score += score / 4;
            msg += CYN "$N" CYN "对$n" CYN "笑道：真是不错，不愧是"
                       "我们" + fam + "的"
                       "矫矫者。\n" NOR;
            break;
        case 3:
            exp += exp / 2;
            pot += pot / 2;
            weiwang += weiwang / 2;
            score += score / 2;
            msg += CYN "$N" CYN "赞许道：非常不错，这次可给我们" +
                   fam + "争脸了。\n" NOR;
            break;
        }

        if (quest_count == 30)
        {
            msg += CYN "$N" CYN "哈哈大笑两声道：真有你的，连着三"
                       "十次任务都完成的漂漂亮亮，很好，很好。\n" NOR;
            special = 1;
        }
        else if (quest_count == 50)
        {
            msg += CYN "$N" CYN "哈哈大笑两声道：真有你的，连着五"
                       "十次任务都完成的漂漂亮亮，很好，很好。\n" NOR;
            special = 1;
        }
        else if (quest_count == 100)
        {
            msg += CYN "$N" CYN "哈哈大笑两声道：真有你的，连着上"
                       "百次任务都完成的漂漂亮亮，很好，很好。\n" NOR;
            special = 1;
        }
        else if (quest_count == 200)
        {
            msg += CYN "$N" CYN "大喜道：不错不错，真是不错，两百"
                       "次任务干得很好。\n" NOR;
            special = 1;
        }
        else if (quest_count == 300)
        {
            msg += CYN "$N" CYN "大喜道：不错不错，连续三百个任务"
                       "都丝毫不出差错，真是漂亮。\n" NOR;
            special = 1;
        }
        else if (quest_count == 400)
        {
            msg += CYN "$N" CYN "大喜道：真是不错，竟然连续四百个"
                       "任务丝毫不出差错，干得好。\n" NOR;
            special = 1;
        }
        else if (quest_count == 500)
        {
            msg += CYN "$N" CYN "叹道：真是长江后浪推前浪，想不到"
                       "你接连五百次任务都无一疏漏，真是不错！\n" NOR;
            special = 1;
        }
        else if (quest_count == 600)
        {
            msg += CYN "$N" CYN "叹道：真是长江后浪推前浪，想不到"
                       "你接连六百次任务都无一疏漏，漂亮之极！\n" NOR;
            special = 1;
        }
        else if (quest_count == 700)
        {
            msg += CYN "$N" CYN "叹道：真是长江后浪推前浪，想不到"
                       "你七百次任务竟无一疏漏，不易，不易！\n" NOR;
            special = 1;
        }
        else if (quest_count == 800)
        {
            msg += CYN "$N" CYN "叹道：真是长江后浪推前浪，想不到"
                       "你接连八百次任务都无一疏漏，不易之极！\n" NOR;
            special = 1;
        }
        else if (quest_count == 900)
        {
            msg += CYN "$N" CYN "深深地叹道：想不到你接连九百次任"
                       "务都无一疏漏，不易之极！不易之极！\n" NOR;
            special = 1;
        }
        else if (quest_count == 1000)
        {
            msg += CYN "$N" CYN "深深叹了口气，道：想不到你连着一"
                       "千次任务无一失手，看来我们" +
                   me->query("family/family_name") +
                   "真是后继有人啊！\n" NOR;
            special = 1;
        }
        else if (quest_count > 1000)
        {
            quest_count = 0;
        }
        else if ((quest_count % 10) == 0)
        {
            msg += CYN "$N" CYN "喜道：真是不赖，居然连着" +
                   chinese_number(quest_count) +
                   "次都没有失手，干的好！\n" NOR;
        }

        quest_level = q["level"];
        quest_level++;
        if (quest_level > MAX_QUEST_LEVEL)
            quest_level = 1;

        who->set("quest_count", quest_count);
        //记录任务总数
        if (!who->query("state/quest"))
        {
            who->set("state/quest", quest_count);
        }
        else
        {
            who->add("state/quest", 1);
        }
        who->set_temp("quest/next_level", quest_level);
    }

    if ((added = (int)who->query_temp("quest/help_count")) > 0)
    {
        msg += HIY "$N" HIY "又道：这次敌人伏下帮手，而你能随机应变，"
                   "完成任务，可喜，可贺！\n" NOR;
        who->delete_temp("quest/help_count");
    }
    added += (int)who->query_temp("quest/escape_times") * 2;
    who->delete_temp("quest/escape_times");
    // 根据NPC的帮手和逃走的次数调整经验
    if (added)
    {
        exp += exp * added / 2;
        pot += pot * added / 2;
    }
    //BK之后潜能奖励补贴
    if (who->query("breakup"))
    {
        pot += random((int)who->query_skill("force", 1) / 3);
    }
    //转世出现超级npc额外奖励潜能,体会
    pot += random(pot * who->query_temp("super"));
    mar += random(mar * who->query_temp("super"));
    message_vision(msg, me, who);
    who->delete ("quest");
    if (!bonus)
        return 1;

    exp /= bonus;
    pot /= bonus;
    mar /= bonus;
    weiwang /= bonus;
    score /= bonus;
    gongxian /= bonus;

    // 无门派的江湖游侠奖励加成
    if (!myfam)
    {
        exp += random(exp / 2);
        pot += random(pot / 2);
        mar += random(mar / 2);
        weiwang += random(weiwang / 2);
        score += random(score / 2);
        gongxian += random(gongxian / 2);
    }

    // bouns
    if (timeover)
    {
        exp /= 2;
        pot /= 3;
        mar /= 2;
        weiwang /= 4;
        score /= 4;
        gongxian /= 2;
    }
    else
    {
        // 百分之一的几率直接赠送物品奖励
        if ((quest_count >= 100 && random(200) == 1) || special)
            special_bonus(me, who, special);
    }

    if (who->query("potential") >= who->query_potential_limit())
        pot = 1;

    if (who->query("experience") >= who->query_experience_limit())
        mar = 1;

    // 八面玲珑增加门派贡献值
    //if (who->query("special_skill/cunning") && random(2) < 1)
    //八面玲珑增加贡献几率由25%提高到50% by 薪有所属
    if (who->query("special_skill/cunning"))
        gongxian = gongxian + random(2);

    // 转世特技诡辩奇学增加门派贡献值 by 薪有所属
    if (who->query("special_skill/guibian"))
        gongxian = gongxian * 2;

    message("vision", sprintf(HIC "通过这次锻炼你获得了%s点经验，"
                                  "%s点潜能及%s点实战体会。\n同时还增"
                                  "长了%s点江湖阅历，%s点威望及%s点门"
                                  "派贡献度。\n" NOR,
                              chinese_number(exp), chinese_number(pot), chinese_number(mar), chinese_number(score), chinese_number(weiwang), chinese_number(gongxian)),
            who);
    who->add("combat_exp", exp);
    who->add("potential", pot);
    who->add("experience", mar);
    who->add("weiwang", weiwang);
    who->add("score", score);
    who->add("gongxian", gongxian);

    // 随机停止发送任务，必须等完成一定数量的freequest才能继续。
    if (random(100) == 1 && quest_count >= 50 && !who->query_temp("wiz_test"))
        who->add("quest/freequest", 1 + random(3));

    return 1;
}

int cancel_quest(object me, object who)
{
    mapping dbase;
    mapping q;
    object ob;
    string msg;
    int n;
    int g;
    int k;

    dbase = who->query_entire_dbase();

    if (!mapp(q = dbase["quest"]) ||
        q["master_id"] != me->query("id"))
        return notify_fail("我没给你什么任务啊？\n");

    switch (q["type"])
    {
    case "kill":
        if (q["notice"] == "die")
        {
            message_vision(CYN "$N" CYN "点点头，对$n" CYN "道：算了，听说这人"
                               "已经被杀了，你不用再辛苦了。\n" NOR,
                           me, who);
        }
        else
        {
            message_vision(CYN "$N" CYN "摆摆手，对$n" CYN "道：你干不了就算了"
                               "，让别人做吧！\n" NOR,
                           me, who);
            //2015年4月19日 取消任务有50%的机率不清零
            //2016年11月2日 取消任务不清零机率改为和福缘挂钩
            //转世特技诡辩奇学不中断任务连续数
            k = who->query("kar");
            if (random(k) > 14 || who->query("special_skill/guibian"))
            {
                message_vision(HIG "$N" HIG "对$n" HIG "道：看在你对师门忠心耿耿"
                                   "的份上，这次就不重罚了。\n" NOR,
                               me, who);
            }
            else
            {
                who->delete ("quest_count");
            }
        }

        who->delete_temp("quest/next_level");
        n = (40 + random(40) + NPC_D->check_level(who) * 5);
        g = (10 + random(10) + NPC_D->check_level(who));

        switch (q["level"])
        {
        case 0:
            n *= 2;
            break;
        case 1:
            break;
        case 2:
            n = 0;
            break;
        case 3:
            n = 0;
            break;
        }
        if (!n)
            break;

        // adjust weiwang
        dbase["weiwang"] -= n;
        if (dbase["weiwang"] < 0)
            dbase["weiwang"] = 0;
        msg = HIR "你的江湖威望受到了损失";

        //转世特技诡辩奇学减免损失 by 薪有所属
        if (!who->query("special_skill/guibian"))
        {
            // adjust gongxian
            dbase["gongxian"] -= g;
            if (dbase["gongxian"] < 0)
                dbase["gongxian"] = 0;
            msg += HIR "，师门对你的信任降低了";

            // adjust experience
            if (dbase["experience"] > dbase["learned_experience"])
            {
                dbase["experience"] += (dbase["learned_experience"] - dbase["experience"]) * 2 / 3;
                msg += "，由于疲于奔命，你的实战体会难以及时消化吸收";
            }
        }
        // notice place
        message("vision", msg + "。\n" NOR, who);

        break;

    case "letter":
        message_vision(CYN "$N" CYN "叹口气，看了看$n" CYN "道：连这点小事都干不了？算了吧。\n" NOR,
                       me, who);
        who->add("score", -(15 + random(10)));
        if (who->query("score") < 0)
            who->set("score", 0);
        message("vision", HIR "你的江湖阅历受到了损失。\n" NOR, who);
        break;
    }
    who->start_busy(2);

    ob = find_living(q["id"]);
    map_delete(dbase, "quest");
    if (!ob || ob->query_temp("quester") != who->query("id"))
        return 1;

    if (environment(ob))
        message_vision(HIC "$N" HIC "看了看四周，急急忙忙的走掉了。\n" NOR, ob);

    destruct(ob);
    return 1;
}

/***********************************************************
  系统注册任务概念

    HELL采用任务对象来管理众多各式各样的任务，而任务守护进程
就是他们的管理者。为什么需要任务对象？这是因为大部分任务都具
有类似的处理过程：收集情报，根据线索完成某些要求，实现最终任
务，获得奖励。为了能够快速的编写和实现多种任务，共享重复的实
现代码，系统规定了任务对象的格式，只要遵循任务对象的格式，就
可以快速的生成玩家任务。

    让我们首先看一下任务的结构：一个任务实际上就是一个自动机，
然后由玩家不断的触发这个自动机最后达到一个稳定状态，一般来说
就是任务成功或是终止。系统可以为任务对象制定一些标准事件，然
后由任务的设计者自己制定一些事件，这就组合成了一个任务的输入
事件，然后系统为任务维护一个状态，这样就构成了一个完整的自动
机。

    看一个简单的“杀人”任务。

    杀一个人主要需要三个要素：时间、地点、人物。在某一个时间，
某个地点出现一个人物，杀掉它就算完成，可以获得奖励。那么我们
设计的流程预期是这样的：一个人打听到了这个任务，就去相应的地
点，杀人，杀掉以后获得奖励。

    任务对象的自动机器：

                                      消息收集完全
            <原生态> -> 人物生成态 -----------+
                           /                  |
                 <Timeout>/    <Timeout>      |
                   -------<---------------\   |
                 /                         \  v
            <结束态>   <--------------- 人物出现态
                            杀死该人

<原生态>和<结束态>是系统规定的状态，<Timeout> 是系统原先保留
的事件。而人物生成态和人物出现态是该任务特有的状态，另外消息
收集完全和杀死该人则是该任务对象特有的事件。

<原生态>阶段系统初始化任务对象，完成一些必要的操作，并将控制
权传递给任务对象以进行后续的操作。这时该任务就自动生成一个人
物，制定它的等级，正邪，预期出现的地点，打听的难度等等。然后
就进入到人物生成态，同时表明自己需要接受超时事件。

此时，玩家如果打听消息，有可能打听到这个任务，并经过反复打听，
获得了该人出现的地点信息，则该人物对象认为消息收集完全，就真
正的生成这个人物，等候玩家将它消灭。

如果该人物被消灭，则通知任务对象，人物对象转移到<结束态>。另
外一个进入结束态的可能是超时了。

进入<结束态>，系统自动清除该任务对象。

任务产生：这可以是游戏中的机关产生，故事产生，和系统随机产生
等等。只要调入一个对象，就可以产生任务。

任务消息：除了通常的消息，有一种消息即通过电脑控制的人物产生，
包括店小二和特殊的传递消息的人物，这些消息可以反映出当前任务
的一些信息，这些功能已经由系统封装。任务产生以后，系统调用接
口函数：register_information()来登记和任务相关的消息 -- 为什
么不在任务产生的同时由任务自己登记？这是因为任务守护进程有可
能析构后重新创建，这样将遗失所有登记的数据，此时任务守护进程
就会遍历系统中所有的任务，调用register_information()接口来重
新组织这些消息。

消息数据结构：

---+-- scheme(1) -*
   |
   +-- scheme(2) -*
   |
   +-- scheme(3) --+-- 关键字：消息1
                   |
                   +-- 关键字：消息2
                   |
                   .........

打听需要一定的江湖阅历，当random(江湖阅历) > 消息的时候， 就
有可能打听到这个消息。消息可能是一个函数，如果是这样的话，在
打听消息的时候系统把打听的对象和打听消息的人，关键字传递给该
函数，取它的返回结果。

QUEST_D提供的消息API：

QUEST_D->add_quest(QUEST_OBJECT);
QUEST_D->set_information(QUEST_OBJECT, key, information);
QUEST_D->query_information(QUEST_OBJECT, key);
QUEST_D->remove_information(QUEST_OBJECT, key);
QUEST_D->remove_all_information(QUEST_OBJECT);

QUEST_OB必须提供的消息接口：

QUEST_OB->register_information();
QUEST_OB->name();
QUEST_OB->can_know_by(object knower);
QUEST_OB->can_rumor_by(object knower);
QUEST_OB->query_introduce(object knower, object who);

***********************************************************/

// 系统增加一个任务
public void add_quest(object qob)
{
    mapping total;

    if (!mapp(total = query("information")))
    {
        // 原先没有任何任务
        total = ([qob:1]);
        set("information", total);
    }
    else
    {
        // 查看这个任务是否已经有定义
        if (undefinedp(total[qob]))
            // 增加一个任务，因为这时候刚刚将任
            // 务加入，还没有任何相关的具体信息，
            // 所以这个条目对应的就只是一个简单
            // 整数标识。
            total[qob] = 1;
    }
}

// 设置消息
public void set_information(object qob, string key, mixed info)
{
    mapping total;
    mapping all_info;

    if (!stringp(key) || (!stringp(info) && !functionp(info)))
    {
        log_file("static/quest",
                 sprintf("%s Quest:%O(%s) set illegal info:%s:%O.\n",
                         log_time(), qob, qob->name(), key, info));
        return;
    }

    if (!mapp(total = query("information")))
        total = ([]);

    if (!mapp(all_info = total[qob]))
    {
        // 原先没有该任务对象的消息信息
        all_info = ([]);
        total += ([qob:all_info]);
    }

    all_info[key] = info;
    set("information", total);
}

// 查询消息
public mixed query_information(object qob, string key)
{
    mapping total;
    mapping all_info;

    if (!mapp(total = query("information")))
        return 0;

    if (!mapp(all_info = total[qob]))
        return 0;

    return all_info[key];
}

// 删除消息
public void remove_information(object qob, string key)
{
    mapping total;
    mapping all_info;

    if (!mapp(total = query("information")))
        return;

    if (!mapp(all_info = total[qob]))
        return;

    map_delete(all_info, key);
    if (!sizeof(all_info))
    {
        // 该任务对象已经没有消息了
        map_delete(total, qob);
        return;
    }
}

// 删除某一个对象的所有消息
public void remove_all_information(object qob)
{
    mapping total;

    if (!mapp(total = query("information")))
        return;

    // 在删除所有消息的同时，任务本身也去掉了 -- 为什么
    // 这样做，这是因为如果是一个没有任何消息的任务（仅
    // 靠任务介绍提供信息）调用这个函数的含义就是清除任
    // 务本身，而一个提供消息的任务清除所有消息也具有相
    // 同的含义。
    map_delete(total, qob);
}

// 删除某一个任务
public void remove_quest(string name)
{
    mapping total;
    object *obs;
    object qob;

    if (!mapp(total = query("information")))
        return;

    obs = keys(total);
    obs = filter_array(obs, (: objectp($1) :));

    if (!sizeof(obs))
        return;

    qob = find_object(name);
    if (!objectp(qob) || member_array(qob, obs) == -1)
    {
        obs = filter_array(obs, (: $1->name() == $(name) :));
        if (!sizeof(obs))
            return;
        qob = obs[0];
    }

    remove_all_information(qob);
    return;
}

// QUEST系统重新启动的时候收集所有任务对象的消息
private void collect_all_quest_information()
{
    mapping total;
    object qob;
    object *obs;

    CHANNEL_D->do_channel(this_object(), "sys",
                          "任务精灵开始收集所有的任务信息。");

    if (!mapp(total = query("information")))
    {
        total = ([]);
        set("information", total);
    }

    obs = filter_array(objects(), (: $1->is_quest() :));

    // 扫描所有的QUEST对象，登记信息
    foreach (qob in obs)
    {
        reset_eval_cost();
        total[qob] = 0;
        catch (qob->register_information());
    }

    // 唤醒几个子任务守护进程
    start_all_quest();
}

public void start_all_quest()
{
    string quest;
    string *qlist;
    string name;
    int pos;

    quest = read_file(CONFIG_DIR "quest");
    if (!stringp(quest))
        // 配置文件中没有任务
        return;

    qlist = explode(quest, "\n");
    foreach (name in qlist)
    {
        // 防止运行超时
        reset_eval_cost();

        if (strlen(name) < 1 || name[0] == '#')
            // 空行或者是注释行
            continue;

        // 去掉行尾的注释和空格
        pos = strsrch(name, '#');
        if (pos > 1)
            name = name[0..pos - 1];
        name = replace_string(name, " ", "");

        // 生成文件名字
        name = QUEST_DIR + name + ".c";
        if (file_size(name) < 0)
        {
            // 没有这个任务
            log_file("static/quest",
                     sprintf("%s invalid quest: %s\n",
                             log_time(), name));
            continue;
        }

        // 启动这个任务
        catch (call_other(name, "startup"));
    }
}

// 整理所有的任务
private void heart_beat()
{
    mapping total;
    mixed key;
    int live_time;
    int t;

    // 重新启动所有的任务进程：如果因为某种故障停止运行，
    // 此时可以将它们重新启动，如果他们原本没有出故障，
    // 那么此时重新启动会修改它们的心跳时间。
    start_all_quest();

    if (!mapp(total = query("information")))
        return;

    // 计算当前时间
    t = time();

    // 扫描所有的任务，只保留有效的任务
    foreach (key in keys(total))
    {
        reset_eval_cost();
        if (!objectp(key))
            map_delete(total, key);
        else
            switch (key->query_status())
            {
            case QUEST_CREATE:
                if (t - key->query("start_time") > QUEST_CREATE_PERIOD)
                {
                    // 创建任务超过有效时间了，结束之
                    log_file("static/quest", sprintf("%s quest: %s create timeout\n%O",
                                                     log_time(), base_name(key),
                                                     key->query_entire_dbase()));
                    catch (key->change_status(QUEST_FINISH));
                    map_delete(total, key);
                }
                break;

            case QUEST_FINISH:
                if (t->query("finish_time") > QUEST_FINISH_PERIOD)
                    // 结束任务超过有效时间了
                    key->change_status(QUEST_ERROR);
                break;

            case QUEST_ERROR:
                // 任务在运行错误状态中
                break;

            default:
                // 任务在通常运行状态中
                if ((live_time = key->query("live_time")) > 0 &&
                    live_time < t - key->query("start_time"))
                {
                    // 生存超过了时间
                    catch (key->change_status(QUEST_FINISH));
                    map_delete(total, key);
                }
                break;
            }
    }
}

// 供消息灵通人士调用使用
public string generate_information(object knower, object who, string topic)
{
    mapping total;
    object *obs;
    object *dest;
    string name, title;
    object last_ob;
    mixed answer;

    total = query("information");

    switch (random(30))
    {
    case 0:
        return "阿嚏！有点感冒，不好意思。";
    case 1:
        return "等…等等，你说什么？没听清楚。";
    case 2:
        return "嗯，稍等啊，就好…好了，你刚才说啥？";
    case 3:
        return "这个…这个…哦，好了，啊？你问我呢？";
    case 4:
        return "唉呦！不好意思，是你问我么？";
    case 5:
        return "就好…就好…好了，你说啥？";
    case 7:
        return "嗯，你稍等一下，我这里还没忙完。";
    }

    if (topic == "rumor" || topic == "消息")
    {
        // 生成传闻
        if (!mapp(total) ||
            !sizeof(obs = filter_array(keys(total), (: objectp($1) :))))
        {
            // 目前没有任何任务
            switch (random(3))
            {
            case 0:
                return "最近没啥消息。";
            case 1:
                return "好像最近挺太平的。";
            default:
                return "不知道...你去问问别人吧。";
            }
        }

        // 过滤该小二可以散布的消息
        obs = filter_array(obs, (: objectp($1) && $1->can_rumor_by($(knower)) :));
        if (!sizeof(obs))
        {
            // 该人士不能散布信息
            switch (random(3))
            {
            case 0:
                return "我倒是听说最近江湖上出了不少事儿。";
            case 1:
                return "哎呀呀！你也知道了一些秘密？快给我说说！";
            default:
                return "这年头，是越来越乱了。";
            }
        }

        // 随机选择一个可以散布的任务消息
        last_ob = obs[random(sizeof(obs))];
        knower->set_temp("last_asked_quest", last_ob);
        if (answer = last_ob->query_prompt(knower, who))
            return answer;

        switch (random(3))
        {
        case 0:
            return "你可曾听过最近有关『" HIY +
                   last_ob->name() + NOR CYN "』的传闻？";
        case 1:
            return "最近正在盛传『" HIY +
                   last_ob->name() + NOR CYN "』这件事情呢！";
        default:
            return "你没有听到大家都在议论『" HIY +
                   last_ob->name() + NOR CYN "』吗？";
        }
    }

    if (!mapp(total))
        return 0;

    // 获得该人知道的所有任务信息
    obs = filter_array(keys(total), (: objectp($1) :));
    obs = filter_array(obs, (: $1->can_know_by($(knower)) :));

    // 查看是否问某一个任务的某一个条目
    if (sscanf(topic, "%s.%s", name, title) == 2)
    {
        dest = filter_array(obs, (: $1->name() == $(name) :));
        if (!sizeof(dest))
            return 0;

        last_ob = dest[0];
    }
    else
    {
        // 查看是否问某一个任务
        dest = filter_array(obs, (: $1->name() == $(topic) :));
        if (sizeof(dest) > 0)
        {
            last_ob = dest[0];
            knower->set_temp("last_asked_quest", last_ob);
            answer = last_ob->query_introduce(knower, who);
            if (stringp(answer))
                return answer;
            return "你说的是" HIY + knower->name() +
                   HIY "那件事情吗？你问我算是问对人了。" NOR;
        }
        else
        // 查看最后一次被询问的任务消息中是否有该条目
        {
            last_ob = knower->query_temp("last_asked_quest");
            if (!objectp(last_ob) || !mapp(total[last_ob]))
                return 0;

            title = topic;
        }
    }

    // 返回有关某个任务的某个条目的消息
    knower->set_temp("last_asked_quest", last_ob);
    answer = total[last_ob];

    if (!mapp(answer))
        return 0;

    // 这个任务登记了具体的信息
    answer = answer[title];
    if (functionp(answer))
        return evaluate(answer, knower, who, topic);

    if (stringp(answer))
        return answer;

    return 0;
}
