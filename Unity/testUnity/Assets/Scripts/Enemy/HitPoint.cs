using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HitPoint : MonoBehaviour
{
    public bool bombAvilable;
    int dir;
    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            collision.GetComponent<IDamageable>().GetHit(1);
        }
        else if (collision.CompareTag("Bomb") && bombAvilable)
        {
            if (transform.position.x > collision.transform.position.x)
            {
                dir = -1;
            }
            else
            {
                dir = 1;
            }
            Debug.Log("踢炸弹");
            collision.gameObject.GetComponent<Rigidbody2D>().AddForce(new Vector2(dir, 1) * 10, ForceMode2D.Impulse);
        }
    }
}
