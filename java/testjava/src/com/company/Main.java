package com.company;

import java.io.IOError;
import java.io.IOException;
import java.lang.ref.SoftReference;
import java.lang.ref.WeakReference;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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

		double pi = Math.PI;

		testString();
		testWeakReference();
		testBigDecimal();
		testRandom();
		testRegex();
		testArray();
    }

    public static void testArray(){
    	ArrayList<Integer> numbers = new ArrayList<>();
    	numbers.add(1);
    	numbers.add(2);
    	numbers.add(3);
    	numbers.forEach(i->System.out.println("foreach value:" + i));
    	System.out.println("numbers " + numbers);
    	numbers.remove(2);
		System.out.println("numbers remove " + numbers);
		numbers.removeIf(i->i == 2);
		System.out.println("numbers removeIf " + numbers);
		numbers.clear();
		System.out.println("numbers clear " + numbers);
	}

    public static void testRegex(){
    	//查找hello
		Pattern pattern = Pattern.compile("^urn:(\\S+):(device|service):(\\S+):([0-9]+)$");
		Matcher matcher = pattern.matcher("urn:schemas-upnp-org:service:AVTransport:1");
		while(matcher.find()){
			String str = matcher.group();
			System.out.println(str);
		}
		if (matcher.matches()){
			int groupCount = matcher.groupCount();
			//0 表示整个匹配表达式
			if (groupCount > 0){
				String strEntirePattern = matcher.group(0);
				System.out.println("strEntirePattern " + " " + strEntirePattern);
			}
			for (int i = 1; i < groupCount + 1; i++){
				String str = matcher.group(i);
				System.out.println("matcher " + i + " " + str);
			}
		}
	}

    public static void testWeakReference(){
		TestInnerClass innerClass = new TestInnerClass();
		WeakReference<TestInnerClass> weakReference = new WeakReference(innerClass);
		//SoftReference<TestInnerClass> weakReference = new SoftReference(innerClass);
		innerClass = null;
		System.out.println(Objects.toString(innerClass));
		//System.out.println(Objects.requireNonNull(innerClass));
		System.gc();
		System.out.println("weak:" + (null == weakReference.get() ? "release" : "ok"));
	}

    public static void testString(){
		String s = "ab\uD83D\uDE03cd";
		String s2 = s.substring(2);
		StringBuilder sb = new StringBuilder();
		sb.append("abcd");
		sb.replace(0, 1, "e");
		//得到文字的数量
		int count = s.codePointCount(0, s.length());
	}

    public static void testBigDecimal(){
		BigDecimal bigDecimal = new BigDecimal("0.3");
		bigDecimal = bigDecimal.add(new BigDecimal("0.2"));
		try{
			BigDecimal resultDecimal1 = bigDecimal.divide(new BigDecimal("0.1"));
			//BigDecimal resultDecimal2 = bigDecimal.divide(new BigDecimal("1.1"));//无法整除，会抛出异常
			System.out.println("resultDecimal " + resultDecimal1.doubleValue() + " " /*+ resultDecimal2.doubleValue()*/);
		}catch (ArithmeticException e){
			e.printStackTrace();
		}

		double dd = bigDecimal.doubleValue();
		double d2 = 0.1;
		d2 += 0.3;
	}

    public static void testRandom(){
		Random random = new Random(System.currentTimeMillis());
		ArrayList<Integer> numbers = new ArrayList<>();
		String str = "";
		for (int i = 0; i < 5; i++){
			str += String.valueOf(random.nextInt()) + " ";
		}

		ThreadLocalRandom threadLocalRandom = ThreadLocalRandom.current();
		for (int i = 0; i < 5; i++){
			str += String.valueOf(threadLocalRandom.nextInt()) + " ";
		}
		System.out.println("random " + str);
	}
}
