#ifndef CDS_HEADER
#define CDS_HEADER

#ifdef CDS_CALL
#	undef CDS_CALL
#else
#	define CDS_CALL __attribute__((visibility("default")))
#endif

#endif
