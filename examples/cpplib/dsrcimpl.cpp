//
// Created by Jie Liu on 2017/9/20.
//

#include "com_genedock_sdk_internal_compress_DSRCImpl.h"
#include <Dsrc.h>


JNIEXPORT jint JNICALL Java_com_genedock_sdk_internal_compress_DSRCImpl_decompress
        (JNIEnv *env, jobject obj, jstring inputFile, jstring outputFile, jint t) {
    using namespace dsrc::lib;

    const char *inFilename_ = env->GetStringUTFChars(inputFile, 0);
    const char *outFilename_ = env->GetStringUTFChars(outputFile, 0);

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


    const char *inFilename_ = env->GetStringUTFChars(inputFile, 0);
    const char *outFilename_ = env->GetStringUTFChars(outputFile, 0);

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

