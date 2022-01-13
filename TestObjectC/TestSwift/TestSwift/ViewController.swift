//
//  ViewController.swift
//  TestSwift
//
//  Created by chenyue on 2022/1/13.
//

import UIKit
import MySwiftFramework

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        let mySwift : MySwift = MySwift();
        let c = mySwift.sum(a: 1, b: 2);
        print("c=", c, separator: "", terminator: "");
        let myTest = MyTest();
        let d = myTest.sum(1, b: 2);
        print("d=",d);
    }


}

