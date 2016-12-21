#include <stdio.h>  /* For fprintf() */

/**
 * Print error message by given error code and message
 * 
 * @param errorCode   error code
 * @param message     message
 */
void SCKT_LOG(int errorCode, const char* message) {
	#ifdef __unix__
	fprintf(stderr, "Platform: __unix__ | Line Number: %d | Error Code: %d | Message: %s\n", __LINE__, errorCode, message);
	#endif /* __unix__ */
	#ifdef _WIN32
	fprintf(stderr, "Platform: _WIN32 | Line Number: %d | Error Code: %d | Message: %s\n", __LINE__, errorCode, message);
	#endif /* _WIN32 */
}
