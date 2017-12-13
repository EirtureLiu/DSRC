//
// Created by Jie Liu on 2017/9/20.
//

#include "com_genedock_sdk_internal_compress_DSRCImpl.h"
#include <Dsrc.h>  
#include <Windows.h>  

char* jstringToWindows(JNIEnv *env, jstring jstr);
jstring WindowsTojstring(JNIEnv* env, const char* str);


JNIEXPORT jint JNICALL Java_com_genedock_sdk_internal_compress_DSRCImpl_decompress
        (JNIEnv *env, jobject obj, jstring inputFile, jstring outputFile, jint t) {
    using namespace dsrc::lib;

    const char *inFilename_ = jstringToWindows(env, inputFile);
    const char *outFilename_ = jstringToWindows(env, outputFile);

    try {
        DsrcModule dsrc;
//        dsrc.SetThreadsNumber(t);
        dsrc.Decompress(inFilename_, outFilename_);
    }
    catch (const DsrcException &e) {
        return -1;
    }

//    std::cerr << "Success!" << std::endl;
    env->ReleaseStringUTFChars(inputFile, 0);
    env->ReleaseStringUTFChars(outputFile, 0);
    return 0;

}

/*
 * Class:     com_genedock_dsrc_DSRCImpl
 * Method:    compress
 * Signature: (Ljava/lang/String;Ljava/lang/String;IIIIIIIZZ)I
 * int t, int d, int q, int f, int b, int m, int o, boolean l, boolean c
 */
JNIEXPORT jint JNICALL Java_com_genedock_sdk_internal_compress_DSRCImpl_compress
        (JNIEnv *env, jobject obj, jstring inputFile, jstring outputFile, jint t, jint m) {
    using namespace dsrc::lib;


    const char *inFilename_ = jstringToWindows(env, inputFile);
    const char *outFilename_ = jstringToWindows(env, outputFile);

    // Configure DSRC compressor
    try {
        DsrcModule dsrc;
        dsrc.SetThreadsNumber(t);

        switch (m) {
            //case 3:
            //	pars.tagPreserveFlags = BIT(1) | BIT(2);
            case 2:
                dsrc.SetDnaCompressionLevel(3);
                dsrc.SetQualityCompressionLevel(2);
                dsrc.SetFastqBufferSizeMB(256);
                break;
            case 1:
                dsrc.SetDnaCompressionLevel(2);
                dsrc.SetQualityCompressionLevel(2);
                dsrc.SetFastqBufferSizeMB(64);
                break;
            case 0:
                dsrc.SetDnaCompressionLevel(0);
                dsrc.SetQualityCompressionLevel(0);
                dsrc.SetFastqBufferSizeMB(8);
                break;
        }

        dsrc.Compress(inFilename_, outFilename_);
    }
    catch (const DsrcException &e) {
        return -1;
    }

//    std::cerr << "Success!" << std::endl;
    env->
            ReleaseStringUTFChars(inputFile,
                                  0);
    env->
            ReleaseStringUTFChars(outputFile,
                                  0);
    return 0;
}

char* jstringToWindows(JNIEnv *env, jstring jstr)
{ //UTF8/16 to gb2312  
	int length = (env)->GetStringLength(jstr);
	const jchar* jcstr = (env)->GetStringChars(jstr, 0);
	char* rtn = (char*)malloc(length * 2 + 1);
	int size = 0;
	size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)jcstr, length, rtn, (length * 2 + 1), NULL, NULL);
	if (size <= 0)
		return NULL;
	(env)->ReleaseStringChars(jstr, jcstr);
	rtn[size] = 0;
	return rtn;
}

jstring WindowsTojstring(JNIEnv* env, const char* str)
{//gb2312 to utf8/16  
	jstring rtn = 0;
	int slen = strlen(str);
	unsigned short * buffer = 0;
	if (slen == 0)
		rtn = (env)->NewStringUTF(str);
	else
	{
		int length = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, NULL, 0);
		buffer = (unsigned short *)malloc(length * 2 + 1);
		if (MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, (LPWSTR)buffer, length) >0)
			rtn = (env)->NewString((jchar*)buffer, length);
	}
	if (buffer)
		free(buffer);

	return rtn;
}
