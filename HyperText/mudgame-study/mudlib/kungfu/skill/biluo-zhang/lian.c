#include <ansi.h>
#include <combat.h>

#define LIAN "「" HIG "峰连碧罗" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int attack_time, i;

        if (userp(me) && ! me->query("can_perform/biluo-zhang/lian"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIAN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(LIAN "只能空手施展。\n");

        if ((int)me->query_skill("biluo-zhang", 1) < 100)
                return notify_fail("你碧罗掌法不够娴熟，难以施展" LIAN "。\n");

        if (me->query_skill_mapped("strike") != "biluo-zhang")
                return notify_fail("你没有激发碧罗掌法，难以施展" LIAN "。\n");

        if (me->query_skill_prepared("strike") != "biluo-zhang")
                return notify_fail("你没有准备碧罗掌法，难以施展" LIAN "。\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的内功修为不够，难以施展" LIAN "。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你现在的真气不够，难以施展" LIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        msg = HIC "\n$N" HIC "双掌陡然连续反转，一招「" HIG "峰连碧罗"
              HIC "」，双掌带风，已将$n" HIC "笼罩在掌风之中。" NOR;

        message_sort(msg, me, target);

    if (random(ap) > dp / 2)
    {
        msg = HIR "结果$n" HIR "目不暇接，顿时被$N" HIR "掌"
                      "风所困，顿时阵脚大乱。\n" NOR;
                me->add_temp("apply/attack", 50);
        } else
        {
                msg = HIY "$n" HIY "看清$N" HIY "这几招的来路，但"
                      "内劲所至，掌风犀利，也只得小心抵挡。\n" NOR;
        }
    message_combatd(msg, me, target);

        attack_time += 3 + random(ap / 40);

        if (attack_time > 6)
                attack_time = 6;

    me->add("neili", -attack_time * 20);

    for (i = 0; i < attack_time; i++)
    {
        if (! me->is_fighting(target))
            break;
                COMBAT_D->do_attack(me, target, 0, 0);
    }
        me->add_temp("apply/attack", -50);
    me->start_busy(1 + random(attack_time));

    return 1;
}
