using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bomb : MonoBehaviour
{
    public delegate void ExplotionNotify(Transform transform);
    private ExplotionNotify explotionNotify;
    private Animator anim;
    private Rigidbody2D rb;
    private Collider2D coll;
    public LayerMask targeLayer;

    public float startTime;
    public float waitTime;
    public float radius;
    public float bombForce;

    // Start is called before the first frame update
    void Start()
    {
        startTime = Time.time;
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
        coll = GetComponent<Collider2D>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!anim.GetCurrentAnimatorStateInfo(0).IsName("BombOff"))
        {
            if (Time.time > startTime + waitTime)
            {
                anim.Play("BombExplotion");
            }
        }
    }

    public void OnDrawGizmos()
    {
        Gizmos.DrawWireSphere(transform.position, radius);
    }

    void Explotion()
    {
        Collider2D[] aroundObjects = Physics2D.OverlapCircleAll(transform.position, radius, targeLayer);//检测周围物体
        //coll.enabled = false;
        //rb.gravityScale = 0;
        foreach (var item in aroundObjects)
        {
            Vector3 pos = transform.position - item.transform.position;
            item.GetComponent<Rigidbody2D>().AddForce((-pos + Vector3.up) * bombForce, ForceMode2D.Impulse);

            if (item.CompareTag("Bomb") && item.GetComponent<Animator>().GetCurrentAnimatorStateInfo(0).IsName("BombOff"))
            {
                item.GetComponent<Bomb>().TurnOn();
            }
            if (item.CompareTag("Player"))
            {
                item.GetComponent<IDamageable>().GetHit(2);
            }
            if (item.CompareTag("Enemy"))
            {
                item.GetComponent<IDamageable>().GetHit(2);
            }
        }
        //explotionNotify(transform);
        //explotionNotify = null;
    }

    void DestroyThis()
    {
        Destroy(gameObject);
    }

    public void TurnOff()
    {
        anim.Play("BombOff");
        gameObject.layer = LayerMask.NameToLayer("NPC");
        gameObject.GetComponent<SpriteRenderer>().sortingLayerName = "NPC";
    }

    public void TurnOn()
    {
        anim.Play("BomoOn");
        gameObject.layer = LayerMask.NameToLayer("Bomb");
        gameObject.GetComponent<SpriteRenderer>().sortingLayerName = "Bomb";
        startTime = Time.time;
    }

    public void SetExplotionNotify(ExplotionNotify notify)
    {
        if (null != explotionNotify)
        {
            explotionNotify = notify;
        }
        else
        {
            explotionNotify += notify;
        }
    }
}
