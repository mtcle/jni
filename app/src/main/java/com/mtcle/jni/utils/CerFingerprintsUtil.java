package com.mtcle.jni.utils;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.Locale;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Log;

/**
 * 描述：指纹获取
 * 创建时间：2015-6-24 下午2:48:22
 */
public class CerFingerprintsUtil {

	private static final long serialVersionUID = 119L;
	/**
	 * 描述：获取指纹MD5
	 * </br>创建人：李满义</br>
	 * 创建时间：2015-6-24 下午2:00:26
	 * @param context
	 * @return
	 */
	public static String getCerMD5(Context context) {
		Signature[] signs = getRawSignature(context, context.getPackageName());
		if ((signs == null) || (signs.length == 0)) {
			return null;
		} else {
			Signature sign = signs[0];
			String signMD5 = MD5.getMessageDigest(sign.toByteArray());
			Log.d("Fingerprints", "Cer-MD5: " + signMD5);
			return signMD5;
		}
	}
	/**
	 * 描述：获取指纹SHA1
	 * </br>创建人：李满义</br>
	 * 创建时间：2015-6-24 下午2:28:21
	 * @param context
	 * @return
	 */
	public static String getCerSHA1(Context context) {
		Signature[] signs = getRawSignature(context, context.getPackageName());
		if ((signs == null) || (signs.length == 0)) {
			return null;
		}
		Signature sign = signs[0];
		byte[] cert = sign.toByteArray();
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-1");
			byte[] publicKey = md.digest(cert);
			StringBuffer hexString = new StringBuffer();
			for (int i = 0; i < publicKey.length; i++) {
				String appendString = Integer.toHexString(0xFF & publicKey[i]);
				if (appendString.length() == 1)
					hexString.append("0");
				hexString.append(appendString);
			}
			
			String hexStrUpperCase = hexString.toString().toUpperCase(Locale.CHINA);
			return hexStrUpperCase;
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
			return null;
		}
	}
	/**
	 * 描述：获取指纹SHA1</br>
	 * 创建人：李满义</br>
	 * 创建时间：2015-6-24 下午2:11:49</br>
	 * @param context
	 * @param packageName
	 * @return
	 * @deprecated 网上找的方法，但是取出的值不对，use {@link getCerSHA1} instead.
	 */
	@Deprecated
	public static String getCerSHA1_X509(Context context, String packageName) {
		Signature[] signs = getRawSignature(context, packageName);
		if ((signs == null) || (signs.length == 0)) {
			return null;
		}
		Signature sign = signs[0];
		byte[] cert = sign.toByteArray();

		InputStream input = new ByteArrayInputStream(cert);
		CertificateFactory cf = null;
		try {
			cf = CertificateFactory.getInstance("X509");
		} catch (CertificateException e) {
			e.printStackTrace();
		}
		X509Certificate c = null;
		try {
			c = (X509Certificate) cf.generateCertificate(input);
		} catch (CertificateException e) {
			e.printStackTrace();
		}
		try {
			MessageDigest md = MessageDigest.getInstance("SHA-1");
			byte[] publicKey = md.digest(c.getPublicKey().getEncoded());
			StringBuffer hexString = new StringBuffer();
			for (int i = 0; i < publicKey.length; i++) {
				String appendString = Integer.toHexString(0xFF & publicKey[i]);
				if (appendString.length() == 1)
					hexString.append("0");
				hexString.append(appendString);
			}
			Log.d("Fingerprints", "Cer-SHA1-X509: " + hexString.toString());
			return hexString.toString();
		} catch (NoSuchAlgorithmException e1) {
			e1.printStackTrace();
			return null;
		}
	}
	private static Signature[] getRawSignature(Context context, String packageName) {
		if ((packageName == null) || (packageName.length() == 0)) {
			return null;
		}
		PackageManager pkgMgr = context.getPackageManager();
		PackageInfo info = null;
		try {
			/** 通过包管理器获得指定包名包含签名的包信息 **/
			info = pkgMgr.getPackageInfo(packageName, PackageManager.GET_SIGNATURES);
		} catch (PackageManager.NameNotFoundException e) {
			return null;
		}
		if (info == null) {
			return null;
		}
		return info.signatures;
	}
}
