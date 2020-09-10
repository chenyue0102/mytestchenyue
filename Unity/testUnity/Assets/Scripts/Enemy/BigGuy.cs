using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BigGuy : Enemy
{
    public Transform pickPoint;
    public bool hasBomb;
    private PickUpState pickUpState = new PickUpState();
    private Bomb pickUpBomp;

    public void PickUp()//animation event
    {
        if (targetPoint.CompareTag("Bomb") && !hasBomb)
        {
            pickUpBomp = targetPoint.GetComponent<Bomb>();
            targetPoint.gameObject.transform.position = pickPoint.transform.position;
            targetPoint.SetParent(pickPoint);
            targetPoint.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Kinematic;
            targetPoint.gameObject.layer = LayerMask.NameToLayer("NPC");
            hasBomb = true;
            //TransitionToState(pickUpState);
        }
    }

    public override void Update()
    {
        base.Update();
        anim.SetBool("hasBomb", hasBomb);
    }

    public void Throw()//animation event
    {
        if (hasBomb && null != pickUpBomp)
        {
            pickUpBomp.GetComponent<Rigidbody2D>().bodyType = RigidbodyType2D.Dynamic;
            pickUpBomp.gameObject.layer = LayerMask.NameToLayer("Bomb");
            pickUpBomp.transform.SetParent(transform.parent.parent);

            int dir = 0;
            if (FindObjectOfType<PlayerController>().gameObject.transform.position.x < transform.position.x)
            {
                dir = -1;
            }
            else
            {
                dir = 1;
            }
            pickUpBomp.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 1) * 10, ForceMode2D.Impulse);
        }
        hasBomb = false;
    }

    public override void OnTriggerStay2D(Collider2D collision)
    {
        if (!hasBomb)
        {
            base.OnTriggerStay2D(collision);
        }
    }
}
