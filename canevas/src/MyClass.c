#include "MyClass.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "dyntable.h"
#include "tree.h"
#include "list.h"
#include "heap.h"
#include "town.h"
#include "road.h"
#include "graph.h"
#include "test.h"
#include "main.h"

JNIEXPORT void JNICALL Java_application_MyClass_Dijkstra
(JNIEnv * env, jobject obj, jstring s1, jstring s2, jstring s3, jint i1) {
	const char *fileNameIn = (*env)->GetStringUTFChars(env, s1, NULL);
	const char *fileNameOut = (*env)->GetStringUTFChars(env, s2, NULL);
	const char *sourceName = (*env)->GetStringUTFChars(env, s3, NULL);
	int heaptype = (int)i1;
	Dijkstra( fileNameIn,  fileNameOut,  sourceName,  heaptype);
}
