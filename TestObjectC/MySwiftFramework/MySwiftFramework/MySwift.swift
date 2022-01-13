//
//  MySwift.swift
//  MySwiftFramework
//
//  Created by chenyue on 2022/1/13.
//

import Foundation

@objcMembers public class MySwift{
    var myTest : MyTest;
    public init(){
        myTest = MyTest();
    }
    
    public func sum(a : Int, b : Int)->Int{
        return Int(myTest.sum(Int32(a), b: Int32(b)));
    }
}
