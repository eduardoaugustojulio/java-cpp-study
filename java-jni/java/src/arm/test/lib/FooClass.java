package arm.test.lib;

public class FooClass{

    static {
        System.loadLibrary("foo_jni");
    }

    private long self_ptr;

    public FooClass(int nb)
    {
        init(nb);
    }

    private native void init(int nb);

    public native int getValue();

    public native void increment();

    protected native void finalize();

}
