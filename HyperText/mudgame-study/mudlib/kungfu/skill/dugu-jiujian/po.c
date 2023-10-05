#include <ansi.h>
#include <combat.h>

#define PO "「" HIR "总破式" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        string *learned;
        object weapon, weapon2;
        string type;
        mapping prepare;
        int n;
        int skill, ap, dp, ss;

        if (me->query("can_learn/dugu-jiujian/nothing"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (userp(me) && me->query("can_perform/dugu/po") < 100)
                return notify_fail("你所使用的外功中没有这种功能。\n");

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian", 1);

        if (! me->is_fighting(target))
                return notify_fail(PO "只能对战斗中的对手使用。\n");

        if (skill < 150)
                return notify_fail("你的独孤九剑等级不够，无法施展" PO "。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，无法施展" PO "。\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian")
                return notify_fail("你没有激发独孤九剑，无法施展" PO "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        weapon2 = target->query_temp("weapon");
        prepare = target->query_skill_prepare();

        if (weapon2) type = weapon2->query("skill_type");
        else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
        else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
        else if (sizeof(prepare) == 2)
                type = (keys(prepare))[target->query_temp("action_flag")];

        ap = skill + me->query_skill("sword", 1);

        learned = me->query("can_perform/dugu-jiujian");

        if (arrayp(learned) && member_array(type, learned) != -1)
                ap *= 2;

        ss = target->query_skill("pixie-jian", 1);

        if (ss < target->query_skill("dugu-jiujian", 1))
                  ss = target->query_skill("dugu-jiujian", 1);

        dp = target->query_skill(type, 1) * 2 + ss;

        if (ap + random(ap) > dp)
        {
                msg = HIC "$N" HIC "随意挥洒手中的" + weapon->name() +
                      HIC "，招招从出其不意的方位直指$n"
                      HIC + to_chinese(type)[4..<1] + "中的破绽。\n" NOR;

                n = 7 + random(7);
                if ((target->is_busy() && ap / 2 + random(ap) > dp)
                   || ap / 2 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "大吃一惊，慌乱之下破绽迭出，"
                               "$N" HIY "唰唰唰唰连攻" + chinese_number(n)
                               + "剑！\n" NOR;
                        message_combatd(msg, me, target);

                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (! target->is_busy() && random(2))
                                        target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        if (weapon2 && random(ap) > dp && type != "pin")
                        {
                                msg = HIW "$n" HIW "觉得眼前眼花缭乱，手中"
                                      "的" + weapon2->name() + HIW "一时竟"
                                      "然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "$n" HIY "略得空隙喘息，一时间却"
                                      "也无力反击。\n" NOR;
                        }
                } else
                {
                        msg += HIY "$n" HIY "连忙抵挡，一时间不禁手忙脚乱，"
                               "无暇反击。\n" NOR;
                        me->start_busy(1);
                        target->start_busy(1 + random(skill / 30));
                }
        } else
        {
                msg = HIC "$N" HIC "拿着手中的" + weapon->name() +
                      HIC "，东戳西指，不过$n" HIC "防守的异常严密，$N"
                      HIC "一时竟然无法找到破绽。\n" NOR;
                me->start_busy(3 + random(2));
                target->start_busy(1);
        }
        message_combatd(msg, me, target);
        return 1;
}
