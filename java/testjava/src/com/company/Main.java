package com.company;

import java.io.IOError;
import java.io.IOException;
import java.lang.ref.SoftReference;
import java.lang.ref.WeakReference;
import java.math.BigDecimal;
import java.util.Objects;

public class Main {

    public static void main(String[] args) {
	    TestInnerClass innerClass = new TestInnerClass();
		innerClass.getClass();
	    TestInnerClass.StaticIn staticIn = new TestInnerClass.StaticIn();
	    TestInnerClass.In in = new TestInnerClass().new In();
	    in.test();
		innerClass.test2((String text)->{
			System.out.println("lambda" + text);
		});
		//try{
			WeakReference<TestInnerClass> weakReference = new WeakReference(innerClass);
			//SoftReference<TestInnerClass> weakReference = new SoftReference(innerClass);
			innerClass = null;
			System.out.println(Objects.toString(innerClass));
			//System.out.println(Objects.requireNonNull(innerClass));
			System.gc();
			String s = "ab\uD83D\uDE03cd";
			String s2 = s.substring(2);
			StringBuilder sb = new StringBuilder();
			sb.append("abcd");
			sb.replace(0, 1, "e");
			int count = s.codePointCount(0, s.length());
			double pi = Math.PI;
			System.out.println("weak:" + (null == weakReference.get() ? "release" : "ok"));
		BigDecimal bigDecimal = new BigDecimal("0.3");
		bigDecimal = bigDecimal.add(new BigDecimal("0.2"));
		double dd = bigDecimal.doubleValue();
		double d2 = 0.1;
		d2 += 0.3;
			//System.in.read();
//		}catch(IOException e){
//			e.printStackTrace();
//		}
    }
}
