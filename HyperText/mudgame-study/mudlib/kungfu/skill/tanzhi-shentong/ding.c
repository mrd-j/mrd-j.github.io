#include <ansi.h>
#include <combat.h>

#define DING "「" HIC "定昆仑" NOR "」"

string final(object me, object target);

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/tanzhi-shentong/ding"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DING "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(DING "只能空手施展。\n");

        //if (target->is_busy())
        //        return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");
        if (target->query_temp("no_perform"))
                return notify_fail("对方现在已经无法控制真气，放胆攻击吧。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 120)
                return notify_fail("你的弹指神通不够娴熟，难以施展" DING "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 120)
                return notify_fail("你对经络学的了解不够，难以施展" DING "。\n");

        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" DING "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" DING "。\n");

        if (me->query("max_neili") < 1500)
                return notify_fail("你的内力修为不足，难以施展" DING "。\n");

        if (me->query("neili") < 300)
                return notify_fail("你现在的真气不够，难以施展" DING "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "合指轻弹，顿时只听“飕”的一声，一缕若有若无的"
              "罡气已朝$n" HIC "电射而去。\n" NOR;

        ap = me->query_skill("finger");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
/*                msg +=  HIR "$n" HIR "只觉胁下一麻，已被$P"
                        HIR "指气射中，全身酸软无力，呆立当场。\n" NOR;
                target->start_busy(ap / 30 + 2);
*/
                damage = ap / 4 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 0, (: final, me, target, 0 :));
                me->start_busy(2);
                me->add("neili", -200);

        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，轻轻一跃，跳了开去。\n" NOR;
                me->start_busy(1);
                me->add("neili", -150);
        }
        message_combatd(msg, me, target);
        return 1;
}

string final(object me, object target)
{
        target->set_temp("no_perform", 1);
        call_out("ding_end", 1 + random(5), me, target);
        return HIR "$n" HIR "只觉眼前寒芒一闪而过，随即全身一阵"
               "刺痛，几股血柱自身上射出。\n$p陡然间一提真气，"
               "竟发现周身力道竟似涣散一般，全然无法控制。\n" NOR;
}

void ding_end(object me, object target)
{
        if (target && target->query_temp("no_perform"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }
                target->delete_temp("no_perform");
    }
    return;
}
