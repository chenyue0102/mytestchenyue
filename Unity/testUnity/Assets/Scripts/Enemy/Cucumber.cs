using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cucumber : Enemy
{

    public override void Attack()
    {
        Debug.Log("Attack");
        if (Vector2.Distance(transform.position, targetPoint.position) < attackRange)
        {
            if (Time.time > nextAttack)
            {
                Debug.Log("Attack");
                nextAttack = Time.time + attackRange;
            }
        }
    }

    public override void SkillAttack()
    {
        if (Vector2.Distance(transform.position, targetPoint.position) < skillRange)
        {
            if (Time.time > nextAttack)
            {
                Debug.Log("SkillAttack");
                nextAttack = Time.time + attackRange;
            }
        }
    }
}
