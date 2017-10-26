package arm.test.app;

import arm.test.lib.FooClass;

public class Main {

	public static void main(String[] argcs)
	{
		FooClass counter = new FooClass(5);
		counter.increment();
		counter.increment();
		System.out.println(counter.getValue());
		
	}

}
