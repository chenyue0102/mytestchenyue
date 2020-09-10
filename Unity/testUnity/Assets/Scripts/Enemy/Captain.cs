using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Captain : Enemy
{
    private SpriteRenderer spriteRenderer;
    public override void Init()
    {
        base.Init();
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    public override void Update()
    {
        base.Update();
        if (2 != animState)
        {
            spriteRenderer.flipX = false;
        }
    }

    public override void SkillAttack()
    {
        base.SkillAttack();

        if (anim.GetCurrentAnimatorStateInfo(1).IsName("Skill"))
        {
            Vector3 movePosition;
            if (transform.position.x > targetPoint.position.x)
            {
                movePosition = Vector3.right;
            }
            else
            {
                movePosition = Vector3.left;
            }
            transform.position = Vector2.MoveTowards(transform.position, transform.position + movePosition, speed * 2 * Time.deltaTime);
            spriteRenderer.flipX = true;
        }
    }
}
