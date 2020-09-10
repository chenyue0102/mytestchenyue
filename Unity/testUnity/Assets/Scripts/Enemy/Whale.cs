using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Whale : Enemy
{
    public float scaleStep;
    public float maxScale = 1.8f;
    public override void SkillAttack()
    {
        base.SkillAttack();
    }

    public void Swalow()
    {
        targetPoint.GetComponent<Bomb>().TurnOff();
        targetPoint.gameObject.SetActive(false);
        Vector3 scale = transform.localScale * 1.1f;
        if (Mathf.Abs(scale.x) < maxScale)
        {
            transform.localScale = scale;
        }
    }
}
