package com.company;

public class TestInnerClass {
    static class StaticIn {
        public StaticIn(){
            System.out.println("StaticIn");
        }
        public void test(){
            System.out.println("StaticIn test");
        }
    }
    class In{
        public In(){
            System.out.println("In");
        }
        public void test(){
            System.out.println("In test");
        }
    }
    @FunctionalInterface
    interface TestLambda {
        void lambdaOut(String text);
    }
    public void test2(TestLambda s){
        s.lambdaOut("test2");
    }
    public void finalize(){
        System.out.println("finalize");
    }
}
