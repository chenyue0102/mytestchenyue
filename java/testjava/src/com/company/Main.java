package com.company;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.lang.annotation.Annotation;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.invoke.MethodType;
import java.lang.ref.WeakReference;
import java.lang.reflect.*;
import java.math.BigDecimal;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

import javax.swing.*;

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
		testMethodHandle();
		testTemplate();
		testException();
		testAnnotation();
		testProxy();
		testGson();
    }

    public static class TestGson{
    	public int id;
    	public String name;
	}

    public static void testGson(){
		TestGson testGson = new TestGson();
		testGson.id = 100;
		testGson.name = "hello,Gson";
		Gson gson = new Gson();
		String jsonText = gson.toJson(testGson, TestGson.class);
		System.out.println(jsonText);

		TestGson testGson2 = gson.fromJson(jsonText, TestGson.class);
		if (testGson.id == testGson2.id && Objects.equals(testGson.name, testGson2.name)){
			System.out.println("json equal");
		}else{
			System.out.println("json not equal");
		}

		ArrayList<TestGson> arrayList = new ArrayList<>();
		arrayList.add(testGson);
		arrayList.add(testGson2);
		String arrayJson = gson.toJson(arrayList, new TypeToken<ArrayList<TestGson>>(){}.getType());
		System.out.println(arrayJson);
		ArrayList<TestGson> arrayList2 = gson.fromJson(arrayJson, new TypeToken<ArrayList<TestGson>>(){}.getType());
		System.out.println("arrayJson Length:" + arrayList2.size());
	}

    public interface ITestProxy{
    	String getName();
		void setName(String name);
    }

    public static class TestProxy implements ITestProxy{
		@Override
		public String getName() {
			return name;
		}

		@Override
		public void setName(String name) {
			this.name = name;
		}
		String name;
	}

	public static class MyInvocationHandler implements InvocationHandler{
		@Override
		public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
			if (method.getName() == "getName"){
				String name = testProxy.getName();
				name += " append";
				return name;
			}else if (method.getName() == "setName"){
				String name = (String)args[0];
				name = "hello " + name;
				testProxy.setName(name);
				return null;
			}else{
				return null;
			}
		}
		TestProxy testProxy = new TestProxy();
	}

	public static void testProxy(){
		InvocationHandler invocationHandler = new MyInvocationHandler();
		try{
			ITestProxy testProxy = (ITestProxy)Proxy.newProxyInstance(ITestProxy.class.getClassLoader(), new Class[]{ITestProxy.class}, invocationHandler);
			testProxy.setName("test name");
			String name = testProxy.getName();
			System.out.println("proxy " + name);
		}catch (SecurityException | IllegalArgumentException e){
			e.printStackTrace();
		}
	}

    public static void testAnnotation(){
		Annotation[]annotations = TestAnnotation.class.getAnnotations();
		for (Annotation annotation:	annotations) {
			if (annotation instanceof ClassAnnotation){
				ClassAnnotation classAnnotation = (ClassAnnotation)annotation;
				System.out.println("classAnnotation " + classAnnotation.value());
			}else if (annotation instanceof FunctionalInterface){
				System.out.println("FunctionalInterface");
			}else{
				System.out.println("unknown annotation");
			}
		}
		try{
			Method method = TestAnnotation.class.getMethod("getAnnotationResult", String.class);
			Annotation[]annotations2 = method.getAnnotations();
			for (Annotation annotation2 : annotations2){
				if (annotation2 instanceof MethodAnnotation){
					MethodAnnotation methodAnnotation = (MethodAnnotation)annotation2;
					System.out.println("methodAnnotation" + methodAnnotation.value());
				}else{
					System.out.println("unknown annotation");
				}
			}
			Parameter[]parameters = method.getParameters();
			for (Parameter parameter : parameters){
				for (Annotation annotation3 : parameter.getAnnotations()){
					if (annotation3 instanceof ParameterAnnotation){
						ParameterAnnotation parameterAnnotation = (ParameterAnnotation)annotation3;
						System.out.println("ParameterAnnotation " + parameterAnnotation.value());
					}else{
						System.out.println("unknown annotation");
					}
				}
			}
		}catch (NoSuchMethodException | SecurityException e){
			e.printStackTrace();
		}
	}

    public static void testException(){
		Socket socket = new Socket();
		Socket socket1 = new Socket();
    	try(socket;socket1){
			if (socket.isClosed()){
				System.out.println("closed");
			}else{
				System.out.println("not closed");
			}
			socket1.connect(new InetSocketAddress("127.0.0.1", 10809));
			System.out.println("connect success");
			socket.connect(new InetSocketAddress("127.0.0.1", 6565));
			OutputStream outputStream = socket.getOutputStream();
			outputStream.write(new byte[]{0x01, 0x02, 0x03, 0x04});
		}catch (IOException e){
			e.printStackTrace();
		}finally {
    		System.out.println("finally");
		}
    	if (socket.isClosed() && socket1.isClosed()){
			System.out.println("have closed");
		}else{
			System.out.println("error");
		}
    	try{
			String context = "abcd1234";
			byte hash[] = MessageDigest.getInstance("MD5").digest(context.getBytes("utf-8"));
			StringBuilder hex = new StringBuilder(hash.length * 2);
			for (byte b : hash){
				if ((b & 0xff) < 0x10){
					hex.append("0");
				}
				hex.append(Integer.toHexString(b & 0xff));
			}
			System.out.println(hex);
		}catch (NoSuchAlgorithmException | UnsupportedEncodingException e){
			e.printStackTrace();
		}
	}

    public static void testTemplate(){
		TemplateBase<String> templateBase = new TemplateBase<>();
		templateBase.setNode("abc");
		System.out.println("templateBase " + templateBase.getNode());
		TemplateBase<Integer> templateBase1 = new TemplateBase<Integer>();
		System.out.println("templateBase class equal " + (templateBase.getClass() == templateBase1.getClass()));//true

		TemplateOverride templateOverride = new TemplateOverride();
		templateOverride.setNode("def");

		TemplateNumber<Integer> templateNumber = new TemplateNumber<>();
		templateNumber.setNode(100);
		Integer integer = templateNumber.getNode();
		//TemplateExtend<String> templateExtend1 = new TemplateExtend<>();
	}

	public static <T> void setNode(T value, TemplateBase<T> templateBase){
    	templateBase.setNode(value);
	}

	public static class TemplateBase<T>{
    	public void setNode(T node){
    		this.node = node;
		}
		public T getNode(){
    		return node;
		}
		T node;
	}

	public static class TemplateNumber<T extends Number & java.io.Serializable> extends TemplateBase<T>{
    	@Override
    	public void setNode(T node){
			System.out.println("TemplateExtend " + node);
			super.setNode(node);
		}
	}

	public static class TemplateOverride extends TemplateBase<String>{
    	//重写泛型基类函数
		@Override
		public void setNode(String node){
			System.out.println("TemplateOverride setNode" + node);
			super.setNode(node);
		}
	}

    public static class MyTest{
    	public static void doTest1(){
    		System.out.println("doTest1");
		}
		public String doTest2(String s){
    		System.out.println("doTest2 " + s);
    		return "doTest2" + s;
		}
		public int doTest3(int x, int y){
    		return x + y;
		}
//		public void setName(String name){
//    		System.out.println("setName " + name);
//    		this.name = name;
//		}
		public String getName(){
    		return name;
		}
		private String name;
	}
	public static void testMethodHandle(){
		try{
			MethodType methodType = MethodType.methodType(void.class);
			MethodHandle methodHandle = MethodHandles.lookup().findStatic(MyTest.class, "doTest1", methodType);
			methodHandle.invoke();

			MyTest myTest = new MyTest();
			MethodHandle methodHandles2 = MethodHandles.lookup()
					.findVirtual(MyTest.class, "doTest2",
					MethodType.methodType(String.class, String.class));
			String invokeResult = (String)methodHandles2.invoke(myTest, "_test2param");
			System.out.println("invokeResult " + invokeResult);

			MethodHandle methodHandle3 = MethodHandles.lookup()
					.findVirtual(MyTest.class, "doTest3", MethodType.methodType(int.class, int.class, int.class));
			int i = (int) methodHandle3.invoke(myTest, 2, 3);
			System.out.println("add " + i);

			//findSetter不需要类提供setter方法,如果已经存在setter方法,则使用findVirtual查找
			MethodHandle methodHandle4 = MethodHandles.lookup()
					.findSetter(MyTest.class, "name", String.class);
			methodHandle4.invoke(myTest, "kitty");
			String name = myTest.getName();
			System.out.println("name " + name);
		}catch (NoSuchMethodException e){
			e.printStackTrace();
		}catch (IllegalAccessException e){
			e.printStackTrace();
		}catch (Throwable e){
			e.printStackTrace();
		}
	}

	public static  <T extends Collection> void fillStringArray(T array){
    	String []names = new String[]{"java", "c++", "python", "lua"};
		for (String name: names) {
			array.add(name);
		}
	}

    public static void testArray(){
    	ArrayList<Integer> numbers = new ArrayList<>();
    	numbers.add(1);
    	numbers.add(2);
    	numbers.add(3);
		Object []nums = numbers.toArray();
		System.out.println("nums length:" + nums.length);
    	numbers.forEach(i->System.out.println("foreach value:" + i));
    	System.out.println("numbers " + numbers);
    	numbers.remove(2);
		System.out.println("numbers remove " + numbers);
		numbers.removeIf(i->i == 2);
		System.out.println("numbers removeIf " + numbers);
		numbers.clear();
		System.out.println("numbers clear " + numbers);

		ArrayList<String> names = new ArrayList<>();
		fillStringArray(names);
		names.stream().filter(name->name!="c++").forEach(name->System.out.println(name));
		Optional optional = names.stream().reduce((acc, item)->{acc += item;return acc;});
		String reduceResult = (String)optional.get();
		System.out.println("reduceResult " + reduceResult);

		//accDefault 是acc开始的值
		String accDefault = "accDefault";
		String reduceResult2 = names.stream().reduce(accDefault,(acc, item)->{acc += item;return acc;});
		System.out.println("reduceResult2 " + reduceResult2);

		ArrayList<String> reduceResult3 = names.stream().reduce(new ArrayList<String>(),
				(ArrayList<String> acc, String item)->{
			acc.add(item);
			System.out.println("BiFunction " + item + item.hashCode() + " acc " + acc.hashCode());
			return acc;
		}, (ArrayList<String> acc, ArrayList<String> items)->{
			//执行多线程情况下的合并操作
					System.out.println("BinaryOperator " + items + items.hashCode() + " acc "+ acc.hashCode());
					acc.addAll(items);
			return acc;
				});
		System.out.println("reduceResult3 " + reduceResult3);

		TreeSet<String> treeSet = new TreeSet<>();
		fillStringArray(treeSet);
		String cplusplus = "c";
		cplusplus += "+";
		cplusplus += "+";
		treeSet.add(cplusplus);
		System.out.println("treeSet " + treeSet);
		treeSet.remove(cplusplus);
		System.out.println("treeSet " + treeSet);

		Integer i1 = Integer.valueOf(100);
		Integer i2 = Integer.valueOf(100);
		Integer i3 = Integer.valueOf(123456);
		Integer i4 = Integer.valueOf(123456);
		System.out.println("100==100 " + (i1 == i2) + " 100 equal 100 " + i1.equals(i2)
		+ " 123456==123456 " + (i3 == i4) + " 123456 equal 123456 " + i3.equals(i4));

		HashSet<String> hashSet = new HashSet<>();
		fillStringArray(hashSet);
		hashSet.add(cplusplus);
		System.out.println("hashSet " + hashSet);
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
