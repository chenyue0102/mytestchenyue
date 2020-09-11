using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Animations;

public class Door : MonoBehaviour
{
    Animator anim;
    BoxCollider2D coll;
    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        coll = GetComponent<BoxCollider2D>();
        coll.enabled = false;
    }

    public void OpenDoor()
    {
        anim.Play("Open");
        coll.enabled = true;
    }

    public void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            GameManager.instance.NextLevel();
        }
    }
}
