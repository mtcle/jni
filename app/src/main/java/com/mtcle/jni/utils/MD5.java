package com.mtcle.jni.utils;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5 {
	
	public static String getMessageDigest(byte[] data) {
	    byte[] hash;
	    try {
	        hash = MessageDigest.getInstance("MD5").digest(data);
	    } catch (NoSuchAlgorithmException e) {
	        throw new RuntimeException("Huh, MD5 should be supported?", e);
	    }
	    StringBuilder hex = new StringBuilder(hash.length * 2);
	    for (byte b : hash) {
	        if ((b & 0xFF) < 0x10) hex.append("0");
	        hex.append(Integer.toHexString(b & 0xFF));
	    }
	    return hex.toString();

	}
}
