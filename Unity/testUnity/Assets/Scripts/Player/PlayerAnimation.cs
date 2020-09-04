using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimation : MonoBehaviour
{
    private Animator anim;//动画
    private Rigidbody2D rb;//刚体
    private PlayerController controller;

    // Start is called before the first frame update
    void Start()
    {
        anim = GetComponent<Animator>();
        rb = GetComponent<Rigidbody2D>();
        controller = GetComponent<PlayerController>();
    }

    // Update is called once per frame
    void Update()
    {
        anim.SetFloat("speed", Mathf.Abs(rb.velocity.x));//rb.velocity.x物体速度
        anim.SetFloat("velocityY", rb.velocity.y);
        anim.SetBool("jump", controller.isJump);
        anim.SetBool("ground", controller.isGround);
    }
}
