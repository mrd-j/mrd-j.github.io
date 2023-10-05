// combatd.c
// Update by Doing for HELL

#pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

// 关于玩家数据(/combat/)的说明
// PKS：杀害的玩家数目
// MKS；杀死的NPC数目(动物不计算)
// WPK：主动杀死玩家的次数
// WPK_NOTGOOD：主动杀死非正派(shen < 500)玩家的次数
// WPK_BAD：    主动杀死的邪派(shen <-500)玩家的次数
// WPK_NOTBAD： 主动杀死非邪派(shen >-500)玩家的次数
// WPK_GOOD：   主动杀死的正派(shen > 500)玩家的次数
// DPS：主动打晕玩家的次数
// DPS_NOTGOOD：主动打晕非正派(shen < 500)玩家的次数
// DPS_BAD：    主动打晕的邪派(shen <-500)玩家的次数
// DPS_NOTBAD： 主动打晕非邪派(shen >-500)玩家的次数
// DPS_GOOD：   主动打晕的正派(shen > 500)玩家的次数
// dietimes：   死亡的次数

// combat/today纪录(mapping)
// which_day: 日期(实际时间中日期)
// id       : n, 主动打晕某个ID的次数

#define MAX_KILL_TIMES_PERMAN 2
#define MAX_KILL_TIMES_PERDAY 8

// 经验底线(random(my_exp) > EXP_LIMIT，则不加经验)
#define EXP_LIMIT 200000

string *guard_msg = ({
    append_color(CYN "$N注视著$n的行动，企图寻找机会出手。\n" NOR, CYN),
    append_color(CYN "$N正盯著$n的一举一动，随时准备发动攻势。\n" NOR, CYN),
    append_color(CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR, CYN),
    append_color(CYN "$N目不转睛地盯著$n的动作，寻找进攻的最佳时机。\n" NOR, CYN),
    append_color(CYN "$N慢慢地移动著脚步，伺机出手。\n" NOR, CYN),
});

string *catch_hunt_msg = ({
    append_color(HIW "$N和$n仇人相见分外眼红，立刻打了起来！\n" NOR, HIW),
    append_color(HIW "$N对著$n一声大喝，蓦地直冲过来！\n" NOR, HIW),
    append_color(HIW "$N和$n一碰面，二话不说就打了起来！\n" NOR, HIW),
    append_color(HIW "$N一眼瞥见$n，「哼」的一声冲了过来！\n" NOR, HIW),
});

string *winner_msg = ({
    append_color(CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR, CYN),
    append_color(CYN "\n$N双手一拱，笑著说道：承让！\n\n" NOR, CYN),
    append_color(CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR, CYN),
    append_color(CYN "\n$N双手一拱，笑著说道：知道我的利害了吧！\n\n" NOR, CYN),
    append_color(CYN "\n$n向后退了几步，说道：这场比试算我输了，下回看我怎么收拾你！\n\n" NOR, CYN),
    append_color(CYN "\n$n向后一纵，恨恨地说道：君子报仇，十年不晚！\n\n" NOR, CYN),
    append_color(CYN "\n$n脸色一寒，说道：算了算了，就当是我让你吧！\n\n" NOR, CYN),
    append_color(CYN "\n$n纵声而笑，叫道：“你运气好！你运气好！”一面身子向后跳开。\n\n" NOR, CYN),
    append_color(CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR, CYN),
    append_color(CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR, CYN),
    append_color(CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR, CYN),
});

void create()
{
    seteuid(getuid());
    set("channel_id", "战斗精灵");
}

// message after damage info
nosave string foo_before_hit = 0;
nosave string foo_after_hit = 0;

void set_bhinfo(string msg)
{
    if (!foo_before_hit)
    {
        foo_before_hit = msg;
        return;
    }

    foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
    if (!foo_after_hit)
    {
        foo_after_hit = msg;
        return;
    }

    foo_after_hit += msg;
}

string query_bhinfo() { return foo_before_hit; }

string query_ahinfo() { return foo_after_hit; }

void clear_bhinfo() { foo_before_hit = 0; }

void clear_ahinfo() { foo_after_hit = 0; }

string damage_msg(int damage, string type)
{
    string str;

    if (damage == 0)
        return "结果没有造成任何伤害。\n";

    switch (type)
    {
    case "擦伤":
    case "割伤":
        if (damage < 15)
            return "结果只是轻轻地划破$p的皮肉。\n";
        else if (damage < 40)
            return "结果在$p$l划出一道细长的血痕。\n";
        else if (damage < 100)
            return "结果「嗤」地一声，$w已在$p$l划出一道伤口！\n";
        else if (damage < 200)
            return "结果「嗤」地一声，$w已在$p$l划出一道血淋淋的伤口！\n";
        else if (damage < 400)
            return "结果「嗤」地一声，$w已在$p$l划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
        else
            return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！\n";
        break;
    case "刺伤":
        if (damage < 15)
            return "结果只是轻轻地刺破$p的皮肉。\n";
        else if (damage < 40)
            return "结果在$p$l刺出一个创口。\n";
        else if (damage < 100)
            return "结果「噗」地一声，$w已刺入了$n$l寸许！\n";
        else if (damage < 200)
            return "结果「噗」地一声，$w已刺进$n的$l，使$p不由自主地退了几步！\n";
        else if (damage < 400)
            return "结果「噗嗤」地一声，$w已在$p$l刺出一个血肉□糊的血窟窿！\n";
        else
            return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！\n";
        break;
    case "瘀伤":
    case "震伤":
        if (damage < 15)
            return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
        else if (damage < 40)
            return "结果在$p的$l造成一处瘀青。\n";
        else if (damage < 100)
            return "结果一击命中，$n的$l登时肿了一块老高！\n";
        else if (damage < 150)
            return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
        else if (damage < 200)
            return "结果「砰」地一声，$n退了两步！\n";
        else if (damage < 400)
            return "结果这一下「砰」地一声打得$n连退了好几步，差一点摔倒！\n";
        else if (damage < 800)
            return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
        else
            return "结果只听见「砰」地一声巨响，$n像一捆稻草般飞了出去！\n";
        break;
    case "内伤":
        if (damage < 15)
            return "结果只是把$n打得退了半步，毫发无损。\n";
        else if (damage < 40)
            return "结果$n痛哼一声，在$p的$l造成一处瘀伤。\n";
        else if (damage < 100)
            return "结果一击命中，把$n打得痛得弯下腰去！\n";
        else if (damage < 150)
            return "结果$n闷哼了一声，脸上一阵青一阵白，显然受了点内伤！\n";
        else if (damage < 200)
            return "结果$n脸色一下变得惨白，昏昏沉沉接连退了好几步！\n";
        else if (damage < 400)
            return "结果重重地击中，$n「哇」地一声吐出一口鲜血！\n";
        else if (damage < 800)
            return "结果「轰」地一声，$n全身气血倒流，口中鲜血狂喷而出！\n";
        else
            return "结果只听见几声喀喀轻响，$n一声惨叫，像滩软泥般塌了下去！\n";
        break;
    case "点穴":
        if (damage < 15)
            return "结果只是轻轻的碰到$n的$l，根本没有点到穴道。\n";
        else if (damage < 40)
            return "结果$n痛哼一声，在$p的$l造成一处淤青。\n";
        else if (damage < 100)
            return "结果一击命中，$N点中了$n$l上的穴道，$n只觉一阵麻木！\n";
        else if (damage < 200)
            return "结果$n闷哼了一声，脸上一阵青一阵白，登时觉得$l麻木！\n";
        else if (damage < 400)
            return "结果$n脸色一下变得惨白，被$N点中$l的穴道,一阵疼痛遍布整个$l！\n";
        else if (damage < 800)
            return "结果$n一声大叫，$l的穴道被点中,疼痛直入心肺！\n";
        else
            return "结果只听见$n一声惨叫，一阵剧痛夹杂着麻痒游遍全身，跟着直挺挺的倒了下去！\n";
        break;
    case "抽伤":
        if (damage < 15)
            return "结果只是在$n的皮肉上碰了碰，好象只蹭破点皮。\n";
        else if (damage < 40)
            return "结果在$n$l抽出一道轻微的紫痕。\n";
        else if (damage < 100)
            return "结果「啪」地一声在$n$l抽出一道长长的血痕！\n";
        else if (damage < 200)
            return "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n";
        else if (damage < 400)
            return "结果只听「啪」地一声，$n的$l被抽得皮开肉绽，痛得$p咬牙切齿！\n";
        else if (damage < 800)
            return "结果「啪」地一声爆响！这一下好厉害，只抽得$n皮开肉绽，血花飞溅！\n";
        else
            return "结果只听见$n一声惨嚎，$w重重地抽上了$p的$l，$n顿时血肉横飞，十命断了九条！\n";
        break;
    case "反震伤":
        if (damage < 15)
            return "结果$N受到$n的内力反震，闷哼一声。\n";
        else if (damage < 40)
            return "结果$N被$n的反震得气血翻腾，大惊失色。\n";
        else if (damage < 100)
            return "结果$N被$n的反震得站立不稳，摇摇晃晃。\n";
        else if (damage < 200)
            return "结果$N被$n以内力反震，「嘿」地一声退了两步。\n";
        else if (damage < 300)
            return "结果$N被$n的震得反弹回来的力量震得半身发麻。\n";
        else if (damage < 400)
            return "结果$N被$n的内力反震，胸口有如受到一记重击，连退了五六步！\n";
        else if (damage < 600)
            return "结果$N被$n内力反震，眼前一黑，身子向後飞出丈许！\n";
        else
            return "结果$N被$n内力反震，眼前一黑，狂吐鲜血，身子象断了线的风筝向後飞去！\n";
        break;
    case "砸伤":
        if (damage < 10)
            return "结果只是轻轻地碰到，像是给$n搔了一下痒。\n";
        else if (damage < 40)
            return "结果在$n的$l砸出一个小臌包。\n";
        else if (damage < 100)
            return "结果$N这一下砸个正着，$n的$l登时肿了一块老高！\n";
        else if (damage < 150)
            return "结果$N这一下砸个正着，$n闷哼一声显然吃了不小的亏！\n";
        else if (damage < 200)
            return "结果只听「砰」地一声，$n疼得连腰都弯了下来！\n";
        else if (damage < 400)
            return "结果这一下「轰」地一声砸得$n眼冒金星，差一点摔倒！\n";
        else if (damage < 800)
            return "结果重重地砸中，$n眼前一黑，「哇」地一声吐出一口鲜血！\n";
        else
            return "结果只听见「轰」地一声巨响，$n被砸得血肉模糊，惨不忍睹！\n";
    case "枪伤":
        if (damage < 10)
            return HIC "结果子弹只是轻轻地擦过，并没有真正击中$n" HIC "。\n" NOR;
        else if (damage < 100)
            return HIR "结果$N" HIR "这一枪正中$n" HIR "的$l，直把$n" HIR "轰得血肉模糊！\n" NOR;
        else
            return HIR "结果$N" HIR "这一枪正中$n" HIR "的$l，轰出了一个碗口大的血洞！\n" NOR;
    default:
        if (!type)
            type = "伤害";
        if (damage < 15)
            str = "结果只是勉强造成一处轻微";
        else if (damage < 40)
            str = "结果造成轻微的";
        else if (damage < 100)
            str = "结果造成一处";
        else if (damage < 150)
            str = "造成一处严重";
        else if (damage < 200)
            str = "结果造成颇为严重的";
        else if (damage < 300)
            str = "结果造成相当严重的";
        else if (damage < 400)
            str = "结果造成十分严重的";
        else if (damage < 600)
            str = "结果造成极其严重的";
        else
            str = "结果造成非常可怕的严重";
        return str + type + "！\n";
    }
}

string eff_status_msg(int ratio)
{
    if (ratio == 100)
        return HIG "看起来气血充盈，并没有受伤。" NOR;
    if (ratio > 95)
        return HIG "似乎受了点轻伤，不过光从外表看不大出来。" NOR;
    if (ratio > 90)
        return HIY "看起来可能受了点轻伤。" NOR;
    if (ratio > 80)
        return HIY "受了几处伤，不过似乎并不碍事。" NOR;
    if (ratio > 60)
        return HIY "受伤不轻，看起来状况并不太好。" NOR;
    if (ratio > 40)
        return HIR "气息粗重，动作开始散乱，看来所受的伤著实不轻。" NOR;
    if (ratio > 30)
        return HIR "已经伤痕累累，正在勉力支撑著不倒下去。" NOR;
    if (ratio > 20)
        return HIR "受了相当重的伤，只怕会有生命危险。" NOR;
    if (ratio > 10)
        return RED "伤重之下已经难以支撑，眼看就要倒在地上。" NOR;
    if (ratio > 5)
        return RED "受伤过重，已经奄奄一息，命在旦夕了。" NOR;
    return RED "受伤过重，已经有如风中残烛，随时都可能断气。" NOR;
}

string status_msg(int ratio)
{
    if (ratio == 100)
        return HIG "看起来充满活力，一点也不累。" NOR;
    if (ratio > 95)
        return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
    if (ratio > 90)
        return HIY "看起来可能有些累了。" NOR;
    if (ratio > 80)
        return HIY "动作似乎有点不太灵光，但仍然有条不紊。" NOR;
    if (ratio > 60)
        return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
    if (ratio > 40)
        return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
    if (ratio > 30)
        return HIR "招架已然散乱，正勉力支撑著不倒下去。" NOR;
    if (ratio > 20)
        return HIR "看起来已经力不从心了。" NOR;
    if (ratio > 10)
        return RED "歪歪斜斜地站都站立不稳，眼看就要倒地。" NOR;
    return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;
}

// Doing
// Reduce the power of the combat_exp
int valid_power(int combat_exp)
{
    if (combat_exp < 2000000)
        return combat_exp;

    combat_exp -= 2000000;
    if (combat_exp < 1000000)
        return 2000000 + combat_exp / 10;

    combat_exp -= 1000000;
    return 2000000 + (1000000 / 10) + (combat_exp / 20);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs int skill_power(object ob, string skill, int usage, int delta)
{
    int level, power;
    mapping dbase;
    mapping temp;
    mapping fight;
    mapping apply;

    if (!living(ob))
        return 0;

    level = ob->query_skill(skill);

    dbase = ob->query_entire_dbase();
    temp = ob->query_entire_temp_dbase();
    if (temp)
    {
        apply = temp["apply"];
        fight = temp["fight"];
    }

    switch (usage)
    {
    case SKILL_USAGE_ATTACK:
        if (apply)
            level += apply["attack"];
        break;
    case SKILL_USAGE_DEFENSE:
        if (apply)
            level += apply["defense"];
        break;
    }

    level += delta;
    if (level < 1)
    {
        power = valid_power((int)ob->query("combat_exp")) / 2;
        if (usage == SKILL_USAGE_ATTACK)
            power = power / 30 * dbase["str"];
        else
            power = power / 30 * dbase["dex"];

        return power;
    }

    if (level > 500)
        power = (level / 10) * level * level;
    else
        power = level * level * level / 10;

    power += valid_power(dbase["combat_exp"]);

    if (usage == SKILL_USAGE_ATTACK)
    {
        power = power / 30 * (dbase["str"] + (temp ? temp["str"] : 0));
        if (fight && ob->is_fighting())
            power += power / 100 * fight["attack"];
    }
    else
    {
        power = power / 30 * (dbase["dex"] + (temp ? temp["dex"] : 0));
        if (fight && ob->is_fighting())
            power += power / 100 * fight[skill];
    }
    return power;
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
    mapping my, your;
    mapping my_temp, your_temp;
    mapping prepare, action;
    string limb, *limbs;
    string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
    string parry_msg;
    mixed foo;

    int delta;
    int ap, dp, pp;
    int damage, damage_bonus;
    int wounded;
    int str1, int1;

    object weapon2; // weapon of victim
    object cloth;   // armor of victim

    string result;
    string damage_info;
    mapping fight;

    int shenzhao, nl_now, nl_limit, nl_improve;
    //object env_me;
    //object env_v;

    if (environment(me)->query("no_fight"))
    {
        message_vision(HIW "$N" HIW "和$n" HIW "各自退了一步，收住了招。\n" NOR,
                       me, victim);
        me->remove_enemy(victim);
        victim->remove_enemy(me);
        return 0;
    }

    if (environment(me) != environment(victim))
    {
        me->remove_enemy(victim);
        victim->remove_enemy(me);
        return 0;
    }

    my = me->query_entire_dbase();
    your = victim->query_entire_dbase();

    if (!(my_temp = me->query_entire_temp_dbase()))
        my_temp = allocate_mapping(5);

    if (!(your_temp = victim->query_entire_temp_dbase()))
        your_temp = allocate_mapping(5);

    //
    // (0) Choose skills.
    //
    prepare = me->query_skill_prepare();
    if (!prepare)
        prepare = ([]);

    if (objectp(weapon))
        attack_skill = weapon->query("skill_type");//武器的技能类型定义在/inherit/weapon目录下。
    else
    {
        switch (sizeof(prepare))
        {
        case 0:
            attack_skill = "unarmed";
            break;
        case 1:
            attack_skill = (keys(prepare))[0];
            break;
        case 2:
            attack_skill = (keys(prepare))[me->query_temp("action_flag")];
            break;
        }
    }

    if (attack_skill == "pin")
        // the pin skill will the same as the sword skill,
        // why don't I remove pin skill ? because I don't
        // want the pin will be treat as sword, only at the
        // combatd, they as same.
        attack_skill = "sword";

    //
    // (1) Find out what action the offenser will take.
    //action是个什么东东？打开/kungfu/skill目录下的随便一个技能文件看看就明白了。
    me->reset_action();//action相关函数在这里定义了 /feature/attack.c，随机设置damage_type和action
    action = me->query_action();

    if (!action)
    {
        // reconfirm
        me->reset_action();
        action = me->query_action();
        if (!mapp(action))
        {
            CHANNEL_D->do_channel(this_object(), "sys",
                                  sprintf("%s(%s): bad action = %O",
                                          me->query("name"), me->query("id"),
                                          me->query_action(1)));
            return 0;
        }
    }

    if (me->query_temp("action_flag") == 0)
        result = "\n" + action["action"] + "！\n" NOR;
    else
        result = "\n" NOR + HIW "紧跟着" NOR + action["action"] + "！\n" NOR;

    //
    // (2) Prepare AP, DP for checking if hit.
    limbs = victim->query("limbs");//肢体，在dbase([……,"limbs":({……,}),])中。
    if (!arrayp(limbs))
    {
        limbs = ({"身体"});
        victim->set("limbs", limbs);
    }
    limb = limbs[random(sizeof(limbs))];//随机选择一个肢体赋值给limb。

    if (!my["not_living"])
    {
        fight = allocate_mapping(5);//返回一个预分配了 5 个元素的映射变量，然后赋值给fight。
        fight["attack"] = action["attack"];
        fight["dodge"] = action["dodge"];
        fight["parry"] = action["parry"];
        my_temp["fight"] = fight;
    }

    //SKILL_USAGE_ATTACK 值为1 在 /include/combat.h 定义了它
    //ap，attack power；dp，defence power；pp，Parry power。
    ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
    ap += random(me->query_skill("count", 1) / 2);
    if (ap < 1)
        ap = 1;

    if (my["character"] == "阴险奸诈")
        ap += ap * 20 / 100;

    //SKILL_USAGE_DEFENSE 值为2 在 /include/combat.h 定义了它
    //SKILL_D(x) 值为 "/kungfu/skill/" + x
    dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
    if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
    {
        dp += dp / 100 * SKILL_D(dodge_skill)->query_effect_dodge(me, victim);
    }
    if (dp < 1)
        dp = 1;

    if (victim->is_busy())
        dp /= 3;

    //
    // (3) Fight!
    //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
    //     AP and DP are greater than zero, so we always have chance to hit
    //     or be hit.
    //
    damage = 0;
    wounded = 0;
    damage_info = "";
    if (random(ap + dp) < dp)
    { // Does the victim dodge this hit?
#if INSTALL_COMBAT_TEST
        if (wizardp(me) && me->query("env/combat_test"))
            tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                "，DP：" + dp + "。\n" NOR);
        if (wizardp(victim) && victim->query("env/combat_test"))
            tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                    "，DP：" + dp + "。\n" NOR);
#endif
        if (!dodge_skill)
            dodge_skill = "dodge";
        result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

        if (dp < ap && (!userp(victim) || !userp(me)))
        {
            if (random(your["combat_exp"]) < EXP_LIMIT && random(2))
            {
                your["combat_exp"]++;
                victim->improve_skill("dodge", 1);
            }
        }
    }
    else
    {
        //
        //      (4) Check if the victim can parry this attack.
        //
        if (!userp(me) || !userp(victim))
        {
            if (ap < dp && random(my["int"]) > 8)
            {
                if (my["potential"] < me->query_potential_limit())
                    my["potential"]++;

                if (stringp(attack_skill))
                    me->improve_skill(attack_skill, 1);
            }
        }
        delta = 0;
        if (weapon2 = your_temp["weapon"])
        {
            if (!weapon)
                delta = 10;
        }
        else
        {
            if (weapon)
                delta = -10;
        }
        pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);

        if (victim->is_busy())
            pp /= 3;
        if (pp < 1)
            pp = 1;

        if (stringp(parry_skill = victim->query_skill_mapped("parry")))
            pp += pp / 100 * SKILL_D(parry_skill)->query_effect_parry(me, victim);

        if (random(ap + pp) < pp)
        {
#if INSTALL_COMBAT_TEST
            if (wizardp(me) && me->query("env/combat_test"))
                tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                    "，PP：" + pp + "。\n" NOR);
            if (wizardp(victim) && victim->query("env/combat_test"))
                tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                        "，PP：" + pp + "。\n" NOR);
#endif
            if (!parry_skill)
                parry_skill = "parry";
            // change to SKILL_D(parry_skill) after added parry msg to those
            // martial arts that can parry.
            parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);

            if (!stringp(parry_msg))
                parry_msg = SKILL_D("parry")->query_parry_msg(weapon2);

            if (stringp(parry_msg))
                result += parry_msg;

            if (pp < ap && (!userp(victim) || !userp(me)))
            {
                if (random(your["combat_exp"]) < EXP_LIMIT && random(2))
                {
                    your["combat_exp"]++;
                    victim->improve_skill("parry", 1);
                }
            }
        }
        else
        {
            //
            //      (5) We hit the victim and the victim failed to parry
            //

            if (weapon)
                damage = me->query_temp("apply/damage");
            else
                damage = me->query_temp("apply/unarmed_damage");
            damage = (damage + random(damage)) / 2;
            if (action["damage"])
                damage += action["damage"] * damage / 100;

            damage_bonus = me->query_str();
            if (my["jianu"])
            {
                // does angry bnous
                damage_bonus += me->cost_craze(my["jianu"]);
                if (me->query_craze() > 1000 &&
                    random(my["jianu"] + 200) > 200)
                {
                    damage_info += random(2) ? HIR "$N" HIR "大喝一声，双目圆睁，一股凌厉的杀气油然而起！\n" NOR
                                             : HIR "$N" HIR "奋不顾身的扑上前来，招招紧逼$n" HIR "，毫不容情。\n" NOR;
                    me->cost_craze(200 + random(300));
                    damage_bonus += my["jianu"] * 2;
                }
            }

            // Clear the special message info after damage info
            foo_before_hit = 0;
            foo_after_hit = 0;

            // Let force skill take effect.
            if (my["jiali"] && (my["neili"] > my["jiali"]))
            {
                if (force_skill = me->query_skill_mapped("force"))
                {
                    foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage_bonus += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage_bonus += foo["damage"];
                    }
                }
#if INSTALL_COMBAT_TEST
                if (wizardp(me) && me->query("env/combat_test"))
                    tell_object(me, HIY "【测试精灵】：己方 AP：" + ap +
                                        "，DP：" + dp + "，PP：" + pp +
                                        "，额外攻击效果：" + damage_bonus +
                                        "，内力对比效果：" + foo + "。\n" NOR);
                if (wizardp(victim) && victim->query("env/combat_test"))
                    tell_object(victim, HIC "【测试精灵】：对方 AP：" + ap +
                                            "，DP：" + dp + "，PP：" + pp +
                                            "，额外攻击效果：" + damage_bonus +
                                            "，内力对比效果：" + foo + "。\n" NOR);
#endif
            }

            if (action["force"])
                damage_bonus += action["force"] * damage_bonus / 100;

            // calculate the damage
            if (damage_bonus > 0)
                damage += (damage_bonus + random(damage_bonus)) / 3;

            // Let's attack & parry skill, weapon & armor do effect
            while (damage > 0)
            {
                if (my["not_living"] || your["not_living"])
                    // Only two living do this
                    break;

                if (damage < 1)
                    break;

                // Let parry skill take its special effort.
                if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                {
                    foo = SKILL_D(dodge_skill)->valid_damage(me, victim, damage, weapon);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                    if (damage < 1)
                        break;
                }

                if (stringp(parry_skill = victim->query_skill_mapped("parry")))
                {
                    foo = SKILL_D(parry_skill)->valid_damage(me, victim, damage, weapon);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                    if (damage < 1)
                        break;
                }

                // Let armor/cloth take its special effort
                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["armor"]))
                {
                    foo = cloth->valid_damage(me, victim, damage, weapon);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                }
                else if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["cloth"]))
                {
                    foo = cloth->valid_damage(me, victim, damage, weapon);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                }

                if (damage < 1)
                    break;

                // Let attack skill take its special effort.
                if (martial_skill = me->query_skill_mapped(attack_skill))
                {
                    foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                    if (damage < 1)
                        break;
                }

                // Let weapon or living have their special damage.
                if (weapon)
                {
                    foo = weapon->hit_ob(me, victim, damage);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                }
                else
                {
                    foo = me->hit_ob(me, victim, damage);
                    if (stringp(foo))
                        damage_info += foo;
                    else if (intp(foo))
                        damage += foo;
                    else if (mapp(foo))
                    {
                        damage_info += foo["msg"];
                        damage += foo["damage"];
                    }
                }

                // finish
                break;
            }

            //
            //      (6) Inflict the damage.
            //

#if INSTALL_COMBAT_TEST
            if (wizardp(me) && me->query("env/combat_test"))
                tell_object(me, HIY "【测试精灵】：你对" +
                                    victim->query("name") + "造成" +
                                    damage + "点伤害。\n" NOR);
            if (wizardp(victim) && victim->query("env/combat_test"))
                tell_object(victim, HIG "【测试精灵】：你受到" +
                                        me->query("name") + damage + "点伤害。\n" NOR);
#endif

            if (damage > 0)
            {
                if (my["character"] == "心狠手辣")
                    damage += damage * 20 / 100;//伤害提升20%

                // 新增str int对攻击的影响，几率正比 伤害反比
                // do str effect
                str1 = me->query("str") * 2 + me->query_str() + random(me->query_temp("str") / 2);
                damage += damage * str1 / 300;
                // do int effect
                int1 = me->query("int");
                if (random(int1) > 8)
                {
                    if (int1 < 16)
                        damage += damage * 10 / int1;
                    else if (int1 < 40)
                        damage += damage * 7 / int1;
                    else
                        damage += damage * 4 / int1;
                }

                //do dex effect 闪避
                if (((me->query("dex") - 10) / 4 + 2) > random(100))
                    damage = 0;

                // calculate wounded
                wounded = damage;
                if (mapp(your_temp["apply"]) && your_temp["apply"]["armor"] > 0)
                    wounded -= random(your_temp["apply"]["armor"]);

                if (wounded > 400)
                    wounded = (wounded - 400) / 4 + 300;
                else if (wounded > 200)
                    wounded = (wounded - 200) / 2 + 200;
                else if (wounded < 1)
                    wounded = 0;

                // recalculate damage
                if (damage > 400)
                    damage = (damage - 400) / 4 + 300;
                else if (damage > 200)
                    damage = (damage - 200) / 2 + 200;

                if (your["character"] == "光明磊落")
                    wounded -= wounded * 20 / 100;

                // do con effect
                wounded -= wounded * (me->query("con") - 10) / 100;

                damage = victim->receive_damage("qi", damage, me);
                if (wounded > 0 &&
                    ((me->is_killing(your["id"]) && random(3) == 1) ||
                     random(3) == 1))
                {
                    // We are sure that damage is greater than victim's armor here.
                    victim->receive_wound("qi", wounded, me);
                }

                // add message before hit in victim
                if (foo_before_hit)
                    result += foo_before_hit;

                result += damage_msg(damage, action["damage_type"]);
                damage_info += "( $n" + status_msg(victim->query("qi") * 100 / victim->query("max_qi")) + ")\n";
            }

            if (foo_after_hit)
                damage_info += foo_after_hit;
        }
    }

    result = replace_string(result, "$l", limb);
    if (objectp(weapon))
        result = replace_string(result, "$w", weapon->name());
    else if (objectp(weapon = me->query_temp("weapon")))
        result = replace_string(result, "$w", weapon->name());
    else if (stringp(action["weapon"]))
        result = replace_string(result, "$w", action["weapon"]);
    else if (attack_skill == "finger" || attack_skill == "hand")
        result = replace_string(result, "$w", "手指");
    else if (attack_skill == "strike" || attack_skill == "claw")
        result = replace_string(result, "$w", "手掌");
    else
        result = replace_string(result, "$w", "拳头");

    message_combatd(result, me, victim, damage_info);
    /*取消平招伤害数值显示 2017-02-09
    //测试代码开始
    if (damage > 0)
    {
        if( userp(me) )     tell_object(me, HIW "( 你对" + victim->query("name")+HIW+"造成"+ damage + "点伤害，" + wounded + "点创伤。)\n" NOR);
        if( userp(victim) ) tell_object(victim, HIG "("+ me->query("name") +HIG+ "对你造成" + damage +"点伤害，"+ wounded + "点创伤。)\n" NOR);
    }
    //测试代码结束
    */
    //神照功战斗中自行回内
    shenzhao = me->query_skill("shenzhaojing", 1);
    nl_limit = me->query("max_neili") * 4 / 5;
    nl_now = me->query("neili");
    nl_improve = shenzhao / 4 + random(shenzhao / 2);
    if (nl_limit > nl_now && (nl_limit - nl_now) < nl_improve)
        nl_improve = nl_limit - nl_now;
    if (shenzhao > 200 && nl_limit > nl_now && random(7) == 1)
    {
        tell_object(me, HIW "你只觉得内息澎湃，感觉内息得到了一些恢复\n" NOR);
        me->add("neili", nl_improve);
    }
    //先天功战斗中自行回血
    if (me->query_skill_mapped("force") == "xiantian-gong" && random(8) == 1)
    {
        me->receive_heal("qi", random(me->query_skill("xiantian-gong", 1) / 2) + 20);
        tell_object(me, HIG "先天玄功自行运转，伤势竟然得到了恢复！\n" NOR);
    }
    //hubo debuff
    if (me->query_temp("debuff/1st"))
    {
        damage = damage * me->query_temp("debuff/1st") / 100;
        me->delete_temp("debuff/1st");
    }
    if (me->query_temp("debuff/2nd"))
    {
        damage = damage * me->query_temp("debuff/2nd") / 100;
        me->delete_temp("debuff/2nd");
    }

    if (damage > 0)
    {
        if (victim->is_busy())
            victim->interrupt_me(me, 8 + random(4));
        if ((!me->is_killing(your["id"])) &&
            (!victim->is_killing(my["id"])) &&
            !victim->query("not_living") &&
            your["qi"] * 3 <= your["max_qi"])
        {
            me->remove_enemy(victim);
            victim->remove_enemy(me);
            message_vision(winner_msg[random(sizeof(winner_msg))],
                           me, victim);
            if (me == victim->query_competitor())
            {
                me->win();
                victim->lost();
            }
        }
    }

    if (functionp(action["post_action"]))
        evaluate(action["post_action"], me, victim, weapon, damage);

    // See if the victim can make a riposte.
    //TYPE_REGULAR 值为0，在/include/combat.h中定义了。
    //TYPE_QUICK   值为2，在/include/combat.h中定义了。
    //TYPE_RIPOSTE 值为1，在/include/combat.h中定义了。
    if (attack_type == TYPE_REGULAR &&
        damage < 1 &&
        your_temp["guarding"])
    {
        //your_temp["guarding"];
        if (random(my["dex"]) < 5)
        {
            message_combatd(HIC "$N" HIC "一击不中，露出了破绽！\n" NOR,
                            me, 0, "");
            do_attack(victim, me, your["weapon"],
                      TYPE_QUICK);
        }
        else
        {
            message_combatd(HIC "$N" HIC "见$n" HIC "攻击失误，趁机发动攻击！\n" NOR,
                            victim, me, "");
            do_attack(victim, me, your["weapon"],
                      TYPE_RIPOSTE);
        }
    }
}

// do damage when perform
// I will consider the damage of the weapon
// what is final: final may be a function with result type string,
// or a single string.
// The syntax of the final string is info:damage_type@limb or info only,
// If the limb if ?, the system will auto select limb of
// target, if the final is a single string, the system will
// treat as damage infomation.
varargs string do_damage(object me, object target, mixed type,
                         int damage, int percent, mixed final)
{
    mapping my;
    object weapon;
    object cloth;
    int apply;
    int armor;
    int wound;
    int jiali;
    //int bonus;
    mixed foo;
    string msg;
    string skill;
    string *limbs;
    string limb;
    string damage_type;
    string result;
    int str, int1;
    int damage_bonus;
    int shenzhao, nl_now, nl_limit, nl_improve;

    // Am I use weapon
    //WEAPON_ATTACK  值为 1
    //UNARMED_ATTACK 值为 0
    if (type == WEAPON_ATTACK)
    {
        apply = me->query_temp("apply/damage");
        weapon = me->query_temp("weapon");
    }
    else if (type == UNARMED_ATTACK)
    {
        apply = me->query_temp("apply/unarmed_damage");
        weapon = 0;
    }
    else
    {
        apply = 0;
        weapon = 0;
    }

    // Check the target's armor
    armor = target->query_temp("apply/armor");

    damage += apply;
    msg = "";
    foo_after_hit = 0;

    while (type == UNARMED_ATTACK || type == WEAPON_ATTACK)
    {
        // Let parry skill take its special effort
        if (skill = target->query_skill_mapped("parry"))
        {
            foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
            if (stringp(foo))
                msg += foo;
            else if (intp(foo))
                damage += foo;
            else if (mapp(foo))
            {
                msg += foo["msg"];
                damage += foo["damage"];
            }
        }

        if (damage < 1)
            break;
        // Let cloth & armor take its special effort
        if (cloth = target->query_temp("armor/armor"))
        {
            foo = cloth->valid_damage(me, target, damage, weapon);
            if (stringp(foo))
                msg += foo;
            else if (intp(foo))
                damage += foo;
            else if (mapp(foo))
            {
                msg += foo["msg"];
                damage += foo["damage"];
            }
        }
        else if (cloth = target->query_temp("armor/cloth"))
        {
            foo = cloth->valid_damage(me, target, damage, weapon);
            if (stringp(foo))
                msg += foo;
            else if (intp(foo))
                damage += foo;
            else if (mapp(foo))
            {
                msg += foo["msg"];
                damage += foo["damage"];
            }
        }

        // Finish
        break;
    }

    while (damage > 0)
    {
        if (target->is_busy())
            target->interrupt_me(target, 4 + random(4));

        // Let weapon/unarmed attack take its special effort
        if (type == WEAPON_ATTACK)
            // weapon attack
            foo = weapon->hit_ob(me, target, damage);
        else if (type == UNARMED_ATTACK)
            // unarmed attack
            foo = me->hit_ob(me, target, damage);
        else if (objectp(type))
            // special item attack
            foo = type->hit_ob(me, target, damage);

        if (stringp(foo))
            msg += foo;
        else if (intp(foo))
            damage += foo;
        else if (mapp(foo))
        {
            msg += foo["msg"];
            damage += foo["damage"];
        }

        // do enforce effect
        my = me->query_entire_dbase();
        if ((jiali = my["jiali"]) > 0 && my["neili"] >= jiali)
        {
            // eforced
            my["neili"] -= jiali;
            if (type == REMOTE_ATTACK)
            {
                damage_bonus = jiali * damage / 200;
            }
            else
            {
                damage_bonus = jiali * damage / 300;

                // check special force effort
                skill = target->query_skill_mapped("force");
                if (stringp(skill))
                {
                    foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);
                    if (stringp(foo))
                        msg += foo;
                    else if (intp(foo))
                        damage_bonus += foo;
                    else if (mapp(foo))
                    {
                        msg += foo["msg"];
                        damage_bonus += foo["damage"];
                    }
                }
                damage += damage_bonus;
            }
        }

        // do strength effect
        str = me->query("str") * 2 + me->query_str() + random(me->query_temp("str") / 2);
        if (str < 40)
            damage += damage * str / 50;
        else if (str < 70)
            damage += damage * ((str - 30) / 2 + 20) / 50;
        else
            damage += damage * ((str - 60) / 4 + 30) / 50;

        // do int effect
        int1 = me->query("int");
        if (random(int1) > 8)
        {
            if (int1 < 16)
                damage += damage * 10 / int1;
            else if (int1 < 40)
                damage += damage * 7 / int1;
            else
                damage += damage * 4 / int1;
        }

        if (damage < 1)
            break;

        // recalculate damage
        if (damage > 1500)
            damage = (damage - 1500) / 4 + 1000;
        else if (damage > 500)
            damage = (damage - 500) / 2 + 500;

        //hubo debuff
        if (me->query_temp("debuff/1st"))
        {
            damage = damage * me->query_temp("debuff/1st") / 100;
            me->delete_temp("debuff/1st");
        }
        if (me->query_temp("debuff/2nd"))
        {
            damage = damage * me->query_temp("debuff/2nd") / 100;
            me->delete_temp("debuff/2nd");
        }
        // do damage
        target->receive_damage("qi", damage, me);
        armor -= random(me->query_skill("count", 1) / 2);
        if (armor < 1)
            armor = 1;
        wound = (damage - random(armor)) * percent / 100;
        if (target->query("character") == "光明磊落")
            wound -= wound * 20 / 100;
        // do con effect
        wound -= wound * (me->query("con") - 10) / 100;

        if (wound > 0)
            target->receive_wound("qi", wound, me);

        //神照功战斗中自行回内
        shenzhao = me->query_skill("shenzhaojing", 1);
        nl_limit = me->query("max_neili") * 4 / 5;
        nl_now = me->query("neili");
        nl_improve = shenzhao / 4 + random(shenzhao / 2);
        if (nl_limit > nl_now && (nl_limit - nl_now) < nl_improve)
            nl_improve = nl_limit - nl_now;
        if (shenzhao > 200 && nl_limit > nl_now && random(3) == 1)
        {
            tell_object(me, HIW "你只觉得内息澎湃，感觉内息得到了一些恢复\n" NOR);
            me->add("neili", nl_improve);
        }

        if (functionp(final))
            final = evaluate(final);
        if (stringp(final))
        {
            if (sscanf(final, "%s@%s", final, limb) == 2)
            {
                if (sscanf(final, "%s:%s", result, damage_type) != 2)
                {
                    result = HIR "这招打了个正中！";
                    damage_type = final;
                }
                if (sscanf(limb, "?%*s"))
                {
                    // auto select limb
                    limbs = target->query("limbs");
                    if (!arrayp(limbs))
                    {
                        limbs = ({"身体"});
                        target->set("limbs", limbs);
                    }
                    limb = limbs[random(sizeof(limbs))];
                }

                // indicate damage type & limb
                final = replace_string(damage_msg(damage, damage_type), "$l", limb);
                final = replace_string(final, "$n", "$n" HIR);
                final = replace_string(final, "$N", "$N" HIR);
                final = replace_string(final, "$p", "$p" HIR);
                final = replace_string(final, "$P", "$P" HIR);
                if (weapon)
                    final = replace_string(final, "$w", weapon->name() + HIR);
                final = result + HIR + final + NOR;
            }

            msg += final;
            msg += "( $n" + status_msg(target->query("qi") * 100 / target->query("max_qi")) + ")\n";
        }

        break;
    }

    if (foo_after_hit)
        msg += foo_after_hit;

    return msg;
}

//      fight()
//
//      This is called in the attack() defined in F_ATTACK, which handles fighting
//      in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
    //object ob;
    object weapon;
    string askill;
    int double_attack;
    mapping prepare;
    //string result;

    if (!living(me))
        return;

    prepare = me->query_skill_prepare();
    if (weapon = me->query_temp("weapon"))
        askill = weapon->query("skill_type");
    else if (!prepare || sizeof(prepare) == 0)
        askill = "unarmed";
    else if (sizeof(prepare))
        askill = (keys(prepare))[0];
    if (askill == "pin")
        askill = "sword";

    askill = me->query_skill_mapped(askill);
    if (askill && random(me->query_dex()) >= 8)
        double_attack = (sizeof(prepare) >= 2 && !weapon) ||
                        SKILL_D(askill)->double_attack();

    // If victim is busy or unconcious, always take the chance to make an attack.
    if (victim->is_busy() || !living(victim))
    {
        me->set_temp("guarding", 0);
        if (!victim->is_fighting(me))
            victim->fight_ob(me);
        do_attack(me, victim, weapon, TYPE_QUICK);

        if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
        {
            me->set_temp("action_flag", 1);
            do_attack(me, victim, me->query_temp("weapon"), TYPE_QUICK);
            me->set_temp("action_flag", 0);
        }

        // Else, see if we are brave enough to make an aggressive action.
    }
    else if (me->query_str() > random(victim->query_str() * 3 / 4))
    {
        me->set_temp("guarding", 0);
        if (!victim->is_fighting(me))
            victim->fight_ob(me);
        do_attack(me, victim, weapon, TYPE_REGULAR);

        if (me->is_fighting(victim) && victim->is_fighting(me) && double_attack)
        {
            me->set_temp("action_flag", 1);
            do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
            me->set_temp("action_flag", 0);
        }

        // Else, we just start guarding.
    }
    else if (!me->query_temp("guarding"))
    {
        me->set_temp("guarding", 1);
        message_combatd(guard_msg[random(sizeof(guard_msg))], me, victim, "");
        return;
    }
    else
        return;
}

//      auto_fight()
//
//      This function is to start an automatically fight. Currently this is
//      used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
    // Don't let NPC autofight NPC.
    if (!userp(me) && !userp(obj))
        return;

    if (me->query_temp("owner") == obj ||
        obj->quety_temp("owner") == me)
        return;

    // Because most of the cases that we cannot start a fight cannot be checked
    // before we really call the kill_ob(), so we just make sure we have no
    // aggressive callout wating here.
    if (me->query_temp("looking_for_trouble"))
        return;
    me->set_temp("looking_for_trouble", 1);

    // This call_out gives victim a chance to slip trough the fierce guys.
    call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
    int shen;

    // Are we still exist( not becoming a corpse )?
    if (!me || !obj || !living(me))
        return;

    me->set_temp("looking_for_trouble", 0);

    if (me->is_fighting(obj) ||
        environment(me) != environment(obj) ||
        environment(me)->query("no_fight"))
        return;

    shen = 0 - (int)me->query("shen");
    message_vision("$N用一种异样的眼神扫视著在场的每一个人。\n", me);

    if (!userp(me) || (int)me->query("neili") > (random(shen) + shen) / 10)
        return;

    if (shen > (int)me->query("score") && !wizardp(obj))
    {
        message_vision(HIW "$N" HIW "对著$n" HIW "喝道：" +
                           RANK_D->query_self_rude(me) + "看你实"
                                                         "在很不顺眼，去死吧。\n" NOR,
                       me, obj);
        me->kill_ob(obj);
    }
    else
    {
        message_vision(HIW "$N" HIW "对著$n" HIW "喝道：喂！" +
                           RANK_D->query_rude(obj) + HIW "，" +
                           RANK_D->query_self_rude(me) + HIW "正想"
                                                             "找人打架，陪我玩两手吧！\n" NOR,
                       me, obj);
        me->fight_ob(obj);
    }
}

void start_hatred(object me, object obj)
{
    if (!me || !obj || !living(me))
        return;

    me->set_temp("looking_for_trouble", 0);

    if (me->is_fighting(obj) ||
        environment(me) != environment(obj) ||
        environment(me)->query("no_fight"))
        return;

    if (me->query_temp("owner") == obj->query("id") ||
        obj->query_temp("owner") == me->query("id"))
        return;

    // We found our hatred! Charge!
    if (me->query("race") != "野兽")
        message_vision(element_of(catch_hunt_msg), me, obj);
    else
        message_vision(append_color(HIR "$N向$n发起了攻击！\n" NOR, HIR), me, obj);
    me->want_kill(obj);
    me->kill_ob(obj);

    if (!playerp(me) && me->is_busy() && !intp(me->query_busy()))
        me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
    if (!me || !obj || !living(me))
        return;

    me->set_temp("looking_for_trouble", 0);

    if (me->is_fighting(obj) ||
        environment(me) != environment(obj) ||
        environment(me)->query("no_fight"))
        return;

    // We found our vendetta opponent! Charge!
    me->want_kill(obj);
    me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
    if (!me || !obj || !living(me))
        return;

    me->set_temp("looking_for_trouble", 0);

    if (me->is_fighting(obj) ||
        environment(me) != environment(obj) ||
        environment(me)->query("no_fight"))
        return;

    // We got a nice victim! Kill him/her/it!!!
    me->want_kill(obj);
    me->kill_ob(obj);
}

int player_escape(object killer, object ob)
{
    object iob;
    string msg;

    if (!objectp(ob))
        return 0;

    // 是玩家么？
    if (!playerp(ob))
        return 0;

    if ((int)ob->query("combat/which_day") == time() / 86400 &&
        (int)ob->query("total_count") > 0)
        return 0;

    // 真的晕倒了，察看是否是被别人有意打晕的
    if (!killer)
        killer = ob->query_defeated_by();
    if (!killer || !playerp(killer) ||
        !killer->is_want_kill(ob->query("id")))
        return 0;

    if (ob->query("combat_exp") >= 100000)
        return 0;

    switch (random(5))
    {
    case 0:
        msg = HIW "\n$N突然听得身后一声冷哼，只见一掌轻轻按来。$N大"
                  "吃一惊，不及多加思索，只是抬手一格。匆忙之间只怕对手"
                  "过于厉害，难以招架，急忙向后跃开。却见来人并不出手追"
                  "击，只是一伸手拎起$n，转身迈开大步，瞬间即逝。\n\n" NOR;
        break;

    case 1:
        msg = HIW "\n$N将$n打翻在地，“哈哈”一声笑声尚未落下，只听"
                  "身后有人冷哼一声，忽然间掌风袭体，$N顿感呼吸不畅，几"
                  "欲窒息，慌忙中急忙退后，待得立稳脚跟，却见$n早已无影"
                  "无踪。\n\n" NOR;
        break;

    case 2:
        msg = HIW "忽然间一人掠至，喝道：“岂有此理？我郭某最恨便是"
                  "欺善怕恶之徒，住手！”说罢一掌击来，$N奋力招架，一招"
                  "之下几欲吐血！只见来人轻轻提起$n，冷哼一声，转身离去"
                  "。$N惊骇之下，竟然说不出一句话来。\n\n" NOR;
        break;

    case 3:
        msg = HIW "突然听得一人喝道：“且慢！”只见一道黑影掠到，身"
                  "形一展已挡在$N面前，左手拎起$n，颇为愤慨地对$N道：“"
                  "今日所幸尚未伤人命，你行事未免太过横行！”$N正值诧异"
                  "间，却见那来人竟已拎起$n，迈开大步，转瞬即逝。\n\n" NOR;
        break;

    default:
        msg = HIW "$N忽然听得“咦”的一声，急忙转过头来，发现身后不"
                  "知何时竟多一对中年夫妇，自己全然未能觉察。只听那女子"
                  "说道：“靖哥哥，你看这人好生霸道，竟似要赶尽杀绝。”"
                  "那男子沉声道：“甚是，我这就将人救起。”说完便飞身跃"
                  "至$N跟前，$N顿时大惊，接连朝那男子攻出数招，可那男子"
                  "理也不理，尽顾拎起$n，转身便迈开大步，和方才那女子一"
                  "起消失得无影无踪。\n\n";
        break;
    }

    if ((environment(killer) == environment(ob)) &&
        killer->is_fighting(ob))
    {
        msg = replace_string(msg, "$n", ob->name());
        message_sort(msg, killer);
    }
    else
    {
        msg = HIW "此时正逢一男子路过，见了" + ob->name() + HIW "晕倒在地，咦了一声，随即将他背负在背上，跨步远去"
                                                                "。\n" NOR;
        message("vision", msg, environment(ob));
    }

    // 将身上背的人放下
    foreach (iob in deep_inventory(ob))
        if (iob->is_character())
            iob->move_environment(ob);

    // 初始化玩家的状态
    ob->clear_condition();
    ob->remove_killer(killer);
    killer->remove_killer(ob);

    ob->move("/d/wuguan/guofu_dating");
    ob->set("startroom", "/d/wuguan/guofu_dayuan");
    ob->revive();
    ob->set("eff_qi", ob->query("max_qi"));
    ob->set("eff_jing", ob->query("max_jing"));
    ob->set("qi", 0);
    ob->set("jing", 0);
    ob->set_temp("mark/guofu_wait", 1);
    tell_object(ob, HIW "你睁开眼来，发现一位体态魁梧的中年男子正微笑"
                        "着注视着你。\n\n" NOR +
                        HIC "郭靖对你微笑道：" +
                        RANK_D->query_respect(ob) + "你终于醒了。切记江湖"
                                                    "险恶，活命不\n易，以后行走江湖可要多加小心谨慎。"
                                                    "\n" NOR);

    if (!ob->query("mark/guofu_ok") && !ob->query("mark/guofu_out") && !ob->query("mark/guofu_over") && ob->query("combat_exp") < 5000)
    {
        tell_object(ob, HIC "\n郭靖沉思片刻，对你说道：你现在出外"
                            "太过危险，还是多留在\n我府上一段时间。这"
                            "段时间你可以顺便帮府上做点事情，也好\n强"
                            "身健体，锻炼锻炼自己。具体事务可以找齐儿"
                            "帮你安排。\n\n" NOR);
        ob->set("mark/guofu_ok", 1);
    }
    return 1;
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    switch (event)
    {
    case "dead":
        message_vision(NOR "\n$N扑在地上挣扎了几下，腿一伸，口中喷出几口" HIR "鲜血" NOR "，死了！\n\n" NOR, ob);
        break;

    case "unconcious":
        message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
        player_escape(0, ob);
        break;

    case "revive":
        message_vision(HIC "\n$N" HIC "慢慢睁开眼睛，清醒了过来。\n\n" NOR, ob);
        break;
    }
}

// called when winner hit the victim to unconcious
void winner_reward(object winner, object victim)
{
    object owner;
    int temp;
    int td;
    mapping today;

    owner = winner->query_temp("owner");
    if (objectp(owner))
        winner = owner;

    winner->defeated_enemy(victim);

    if (!playerp(winner) || wizardp(victim) && 0)
        return;

    if (!winner->is_want_kill(victim->query("id")))
        // only if I want kill ob, I will record it.
        return;

    winner->add("combat/DPS", 1);
    if (victim->is_not_bad())
        winner->add("combat/DPS_NOTBAD", 1);
    if (victim->is_not_good())
        winner->add("combat/DPS_NOTGOOD", 1);
    if (victim->is_bad())
        winner->add("combat/DPS_BAD", 1);
    if (victim->is_good())
        winner->add("combat/DPS_GOOD", 1);

    if (victim->query_condition("killer"))
        return;

    if (victim->query("combat_exp") < 150)
        return;

    log_file("static/killrecord",
             sprintf("%s %s defeat %s\n",
                     log_time(), log_id(winner), log_id(victim)));

    td = time() / 86400;
    today = winner->query("combat/today");

    if (!mapp(today) || today["which_day"] != td)
    {
        today = (["which_day":td,
                "total_count":1,
                              victim->query("id"):1,
        ]);
    }
    else
    {
        // count how many times that winner hit the victim to unconcious
        temp = ++today[victim->query("id")];

        // 清除该玩家的死亡保护
        winner->clear_condition("die_guard");

        if (temp == MAX_KILL_TIMES_PERMAN)
        {
            // reach limit
            tell_object(winner, BLINK HIR "\n今天你已经打晕" +
                                    victim->name() + chinese_number(temp) +
                                    "次了，手下留"
                                    "情吧，否则麻烦可要找上门了。\n" NOR);
        }
        else if (temp > MAX_KILL_TIMES_PERMAN)
            // too many times
            winner->set("combat/need_punish", "这厮逼人太甚，真是岂有此理！");

        // count how many users that winner hit to unconcious
        temp = ++today["total_count"];
        if (temp == MAX_KILL_TIMES_PERDAY)
        {
            // reach limit
            tell_object(winner, BLINK HIR "\n今天你已经打晕" +
                                    chinese_number(temp) + "次玩家了，手下留"
                                                           "情吧，否则麻烦可要找上门了。\n" NOR);
        }
        else if (temp > MAX_KILL_TIMES_PERDAY)
            // too many users
            winner->set("combat/need_punish", "丧尽天良，大肆屠戮，罪无可恕！");
    }
    winner->set("combat/today", today);
}

// todo 优化此方法，代码太乱了
void killer_reward(object killer, object victim)
{
    object owner;
    string vmark;
    string msg = "莫名其妙地死了";
    string follow_msg = 0;
    object weapon;
    mapping actions;
    int shen_delta;
    mapping ks, vs, kcombat;
    int flag;

    if (!objectp(victim))
        return;

    if (objectp(killer))
    {
        owner = killer->query_temp("owner");
        if (objectp(owner))
            killer = owner;
    }

    // This while is only to enable "break"
    vs = victim->query_entire_dbase();
    while (1)
    {
        if (!objectp(killer))
            break;

        // call the killer's override function
        killer->killed_enemy(victim);

        if (!objectp(killer) || !playerp(killer))
            break;

        // 任务记录
        QUEST_D->doKilled(victim, killer);

        // assure the killer's dbase
        ks = killer->query_entire_dbase();
        if (!mapp(kcombat = ks["combat"]))
        {
            kcombat = ([]);
            ks["combat"] = kcombat;
        }

        // adjust the "shen" & "experience" of the killer
        if (ks["combat_exp"] <= vs["combat_exp"] * 1.1)
        {
            if (ks["combat_exp"] >= 100000 &&
                ks["combat_exp"] >= vs["combat_exp"] * 2 / 3)
            {
                // adjust experience
                if (!intp(ks["experience"]))
                    ks["experience"] = 0;
                killer->improve_experience(1 + random(5));
            }

            // adjust shen
            shen_delta = -vs["shen"] / 10;
            if (shen_delta > 100)
            {
                // 非线性校正获得的正神
                shen_delta = (shen_delta - 100) / 3 + 100;

                if (shen_delta > 200)
                    shen_delta = (shen_delta - 200) / 3 + 200;

                if (shen_delta > 300)
                    shen_delta = (shen_delta - 300) / 3 + 300;
            }
            else if (shen_delta < -100)
            {
                // 非线性校正获得的负神
                shen_delta = (shen_delta + 100) / 3 - 100;

                if (shen_delta < -200)
                    shen_delta = (shen_delta + 200) / 3 - 200;

                if (shen_delta < -300)
                    shen_delta = (shen_delta + 300) / 3 - 300;
            }

            ks["shen"] += shen_delta;
        }

        // weapon get the bonus
        if (weapon = killer->query_temp("weapon") ||
                     weapon = killer->query_temp("armor/hands"))
            weapon->killer_reward(killer, victim);

        // record the user's killing
        if (userp(victim))
        {
            if (!intp(kcombat["PKS"]))
                kcombat["PKS"] = 1;
            else
                kcombat["PKS"]++;

            // do family action
            FAMILY_D->family_kill(killer, victim);

            // do league action
            LEAGUE_D->league_kill(killer, victim);

            if (victim->query_condition("killer"))
            {
                follow_msg = "听说杀人凶手" + victim->name(1) +
                             "被" + killer->name(1) + "在" +
                             environment(victim)->short() + HIM "就地正法了。";
                break;
            }

            if (!killer->is_want_kill(vs["id"]))
                break;

            if (!intp(kcombat["WPK"]))
                kcombat["WPK"] = 1;
            else
                kcombat["WPK"]++;

            // 清除该玩家的死亡保护
            killer->clear_condition("die_guard");

            if (!killer->query_condition("killer"))
            {
                follow_msg = "听说官府发下海捕文书，缉拿杀人凶手" +
                             killer->name(1) + "。";
                killer->apply_condition("killer", 500);
            }
            else
            {
                follow_msg = "听说官府加紧捉拿累犯重案的暴徒" +
                             killer->name(1) + "。";
                killer->apply_condition("killer", 800 +
                                                      (int)killer->query_condition("killer"));
            }

            // assure data of kcombat
            if (!intp(kcombat["WPK_NOTBAD"]))
                kcombat["WPK_NOTBAD"] = 0;
            if (!intp(kcombat["WPK_NOTGOOD"]))
                kcombat["WPK_NOTGOOD"] = 0;
            if (!intp(kcombat["WPK_GOOD"]))
                kcombat["WPK_GOOD"] = 0;
            if (!intp(kcombat["WPK_BAD"]))
                kcombat["WPK_BAD"] = 0;

            // record the combat info.
            if (victim->is_not_bad())
                kcombat["WPK_NOTBAD"]++;
            if (victim->is_not_good())
                kcombat["WPK_NOTGOOD"]++;
            if (victim->is_good())
                kcombat["WPK_GOOD"]++;
            if (victim->is_bad())
                kcombat["WPK_BAD"]++;
            break;
        }

        if (vs["can_speak"])
            if (!intp(kcombat["MKS"]))
                kcombat["MKS"] = 1;
            else
                kcombat["MKS"]++;

        break;
    }

    // die penalty & message of victim
    if (playerp(victim))
    {
        // clear punish info.
        victim->delete ("combat/need_punish");

        // clear all condition
        victim->clear_condition();

        // 增加死亡保护
        victim->apply_condition("die_guard", 6000);

        if (victim->query("skybook/guard/death") < 1 && victim->query_temp("guard_death") < 1)
        {
            // adjust shen
            vs["shen"] -= vs["shen"] / 10;

            if (vs["max_neili"] >= 20)
                vs["max_neili"] -= 20;
            else
                vs["max_neili"] = 0;

            // adjust combat exp.
            vs["combat_exp"] -= vs["combat_exp"] * 3 / 100;

            // adjust weiwang
            vs["weiwang"] -= vs["weiwang"] / 10;

            // adjust score
            vs["score"] -= vs["score"] / 10;

            // remove vendetta
            map_delete(vs, "vendetta");

            // lost half of potential
            if (vs["potential"] > vs["learned_points"])
                vs["potential"] += (vs["learned_points"] - vs["potential"]) / 2;

            // lost half of experience
            if (vs["experience"] > vs["learned_experience"])
                vs["experience"] += (vs["learned_experience"] - vs["experience"]) / 2;

            //生死玄关 by 薪有所属
            if (!victim->query("death"))
                flag = 100; //没打通生死玄关时掉技能几率为百分之百
            else
            {
                // 按照实战经验修正掉技能几率，经验越高越不容易死亡掉技能
                /*
                if (victim->query("combat_exp")>= 100000000)
                    flag=0;//打通生死玄关且exp 1亿以上时百分之百不掉技能
                else if (victim->query("combat_exp")>= 80000000) flag=10;
                else if (victim->query("combat_exp")>= 60000000) flag=20;
                else if (victim->query("combat_exp")>= 40000000) flag=30;
                else if (victim->query("combat_exp")>= 20000000) flag=40;
                else if (victim->query("combat_exp")>= 10000000) flag=50;
                else if (victim->query("combat_exp")>= 5000000) flag=60;
                else flag = 70;
                */
                //调整death效果 2017-01-30
                if (victim->query("combat_exp") >= 50000000)
                    flag = 0;
                else if (victim->query("combat_exp") >= 30000000)
                    flag = 10;
                else if (victim->query("combat_exp") >= 20000000)
                    flag = 20;
                else if (victim->query("combat_exp") >= 15000000)
                    flag = 30;
                else if (victim->query("combat_exp") >= 10000000)
                    flag = 40;
                else if (victim->query("combat_exp") >= 5000000)
                    flag = 50;
                else
                    flag = 70;
            }
            if (random(100) < flag)
                victim->skill_death_penalty();
        }
        else
        {
            if (!victim->query_temp("guard_death"))
                victim->add("skybook/guard/death", -1);

            victim->add("skybook/no_death", 1);
        }

        // generate message of die reason
        if (objectp(killer) && killer->is_character())
        {
            msg = "被" + filter_color(killer->name(1));
            actions = killer->query_action();
            switch (mapp(actions) ? actions["damage_type"] : "杀伤")
            {
            case "擦伤":
            case "割伤":
                msg += "砍死了";
                break;
            case "刺伤":
                msg += "刺死了";
                break;
            case "震伤":
            case "瘀伤":
                msg += "击死了";
                break;
            case "枪伤":
                msg += "开枪击毙了";
                break;
            case "内伤":
                msg += "震死了";
                break;
            default:
                msg += "杀死了";
            }
        }
        if (stringp(victim->query_temp("die_reason")))
            msg = filter_color(victim->query_temp("die_reason"));

        victim->delete_temp("die_reason");
        CHANNEL_D->do_channel(this_object(), "rumor",
                              sprintf("听说%s" HIM + msg + "。", victim->name(1)));

        // show the follow msg after victim die
        if (follow_msg)
            CHANNEL_D->do_channel(this_object(), "rumor",
                                  follow_msg);

        victim->set("combat/last_die", filter_color(msg));
        if (objectp(killer) && playerp(killer) && playerp(victim))
        {
            string cname;
            object couple;

            log_file("static/killrecord",
                     sprintf("%s %s killed %s\n",
                             log_time(),
                             log_id(killer), log_id(victim)));

            killer->remove_killer(victim);

            // check sadly
            cname = victim->query("couple/id");
            if (cname &&
                victim->query("gender") == "女性" &&
                victim->query("combat_exp") >= 970000 &&
                objectp(couple = find_player(cname)) &&
                couple != killer)
            {
                couple->add("static/sadly", 1);
                tell_object(couple, "你的妻子死在了" +
                                        killer->name(1) + "的手下" +
                                        "，你感到了一阵深深的哀伤。\n");
            }
        }
    }

    if (stringp(vmark = victim->query("vendetta_mark")) && objectp(killer))
        killer->add("vendetta/" + vmark, 1);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
    mapping p, ap;
    string msg;
    string poison_type;

    if (!mapp(p = ob->query_temp("daub/poison")))
        return;

    if (!stringp(poison_type = ob->query_temp("daub/poison_type")))
        return;

    if (!p["remain"])
        return;

    // affect parameter
    ap = allocate_mapping(4);
    if (ob == me)
        ap["level"] = p["level"] * 9 / 10 + 1;
    else
        ap["level"] = p["level"] * 8 / 10 + 1;

    ap["id"] = p["id"];
    ap["name"] = p["name"];
    ap["duration"] = 1;

    if (p["remain"] > p["level"])
    {
        // decrase the remain poison
        p["remain"] -= p["level"];
    }
    else
    {
        // the poison has run out
        ob->delete_temp("daub");
    }

    msg = HIB "突然$n" HIB "觉得受伤的地方有一些麻痒";
    if (p["id"] == victim->query("id"))
    {
        if (!victim->query_temp("has_announce/defense1"))
        {
            victim->set_temp("has_announce/defense1", 1);
            victim->start_call_out(bind((: call_other, __FILE__, "clear_announce", victim :), victim), 15);
            msg += "。\n" NOR HIC "$n" HIC "默一运功，冷笑两声：“好个" +
                   RANK_D->query_rude(me) + "，居然在我面前卖弄" +
                   RANK_D->query_self_rude(victim) +
                   "毒药？”\n" NOR;
        }
        else
            msg += "，不过$n并没有在意。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    if (p["level"] < victim->query_skill("poison", 1))
    {
        if (!victim->query_temp("has_announce/defense2"))
        {
            victim->set_temp("has_announce/defense2", 1);
            victim->start_call_out(bind((: call_other, __FILE__, "clear_announce", victim :), victim), 15);
            msg += "。\n" NOR HIC "$n" HIC "呼吸数次，嘿然冷笑道："
                   "米粒之珠，也放光华？\n" NOR;
        }
        else
            msg += "，不过$n显然并没有把它放在心上。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    if (p["level"] < victim->query_skill("force") / 2)
    {
        if (!victim->query_temp("has_announce/defense3"))
        {
            victim->set_temp("has_announce/defense3", 1);
            victim->start_call_out(bind((: call_other, __FILE__, "clear_announce", victim :), victim), 15);
            msg += "。\n" NOR HIC "$n" HIC "长笑道：好家伙，居然" +
                   (ob == me ? "在身上淬毒" : "使用淬毒兵器") +
                   "，这些下三滥的手段也敢到我面前卖弄？\n" NOR;
        }
        else
            msg += "，不过$n看起来似乎并无大碍。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    victim->affect_by(poison_type, ap);

    msg += "，大概是中毒了。\n" NOR;
    if (p["level"] < victim->query_skill("force"))
    {
        msg += HIB "$n" HIB "深深吸一了口气，面目凝重，手中的攻势陡然一紧。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    msg += HIR "$n" HIR "闷哼一声，攻势顿缓，神情甚是痛苦。\n" NOR;
    victim->start_busy(1 + random(2));
    set_ahinfo(msg);
    return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
    mapping p, ap;
    string msg;
    string poison_type;

    if (!mapp(p = ob->query_temp("daub/poison")))
        return;

    if (!stringp(poison_type = ob->query_temp("daub/poison_type")))
        return;

    if (!p["remain"])
        return;

    if (me->query_temp("armor/hands"))
        return;

    // affect parameter
    ap = allocate_mapping(4);
    ap["level"] = p["level"] * 7 / 10 + 1;

    ap["id"] = p["id"];
    ap["name"] = p["name"];
    ap["duration"] = 1;

    if (p["remain"] > p["level"])
    {
        // decrase the remain poison
        p["remain"] -= p["level"];
    }
    else
    {
        // the poison has run out
        ob->delete_temp("daub");
    }

    msg = HIB "突然$N" HIB "觉得浑身有些麻痒";
    if (p["id"] == me->query("id"))
    {
        if (!me->query_temp("has_announce/defense1"))
        {
            me->set_temp("has_announce/defense1", 1);
            me->start_call_out(bind((: call_other, __FILE__, "clear_announce", me :), me), 15);
            msg += "。\n" NOR HIC "$N" HIC "默一运功，冷笑两声：好个" +
                   RANK_D->query_rude(victim) + "，居然在我面前卖弄" +
                   RANK_D->query_self_rude(victim) +
                   "的毒药！把你衣服上的毒药都还给我！\n" NOR;
        }
        else
            msg += "，不过$N并没有在意。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    if (p["level"] < me->query_skill("poison", 1))
    {
        if (!me->query_temp("has_announce/defense2"))
        {
            me->set_temp("has_announce/defense2", 1);
            me->start_call_out(bind((: call_other, __FILE__, "clear_announce", me :), me), 15);
            msg += "。\n" NOR HIC "$N" HIC "冷笑道：米粒之珠也放"
                   "光华？你在衣衫上淬毒我就怕你了？\n" NOR;
        }
        else
            msg += "，不过$N显然并没有把它放在心上。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    if (p["level"] < me->query_skill("force") / 2)
    {
        if (!me->query_temp("has_announce/defense3"))
        {
            me->set_temp("has_announce/defense3", 1);
            me->start_call_out(bind((: call_other, __FILE__, "clear_announce", me :), me), 15);
            msg += "。\n" NOR HIC "$N" HIC "长笑道：居然在衣衫上"
                   "淬毒，这些下三滥的手段也敢到我面前卖弄？\n" NOR;
        }
        else
            msg += "，不过$N看起来似乎并无大碍。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    me->affect_by(poison_type, ap);

    msg += "，看来有些不妙。\n" NOR;
    if (p["level"] < me->query_skill("force"))
    {
        msg += HIB "$N" HIB "深深吸一了口气，面目凝重，手中的攻势陡然一紧。\n" NOR;
        set_ahinfo(msg);
        return;
    }

    msg += HIR "$N" HIR "脚步一个跄踉，攻势顿缓，神色难看之极。\n" NOR;
    me->start_busy(1 + random(2));
    set_ahinfo(msg);
    return;
}

void clear_announce(object me)
{
    if (!objectp(me))
        return;

    me->delete_temp("has_announce");
}
