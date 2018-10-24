package com.mtcle.libjava;

public class MyClass {
    public static void main(String[] a){
//bug fixed~~~
    }

    int getNextInterval(final int interval, final boolean increase) {
        int result = interval;
        int sign = increase ? 1 : -1;
        if (sign < 0) {
            if (interval <= 60 * 1000) {
                result = interval + sign * 10 * 1000;
            } else if (interval <= 120 * 1000) {
                result = interval + sign * 30 * 1000;
            } else {
                result = interval + sign * 45 * 1000;
            }
        } else {
            if (interval < 60 * 1000) {
                result = interval + sign * 10 * 1000;
            } else if (interval < 120 * 1000) {
                result = interval + sign * 30 * 1000;
            } else {
                result = interval + sign * 45 * 1000;
            }
        }

        if (result > getMaxInterval()) {
            result = getMaxInterval();
        }
        if (result < getMinInterval()) {
            result = getMinInterval();
        }
        return result;
    }
}
