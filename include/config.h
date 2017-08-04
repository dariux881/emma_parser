#ifndef EMMAPARSER_API
#define EMMAPARSER_API

#if defined WIN32 || _WIN64
#ifdef EMMA_EXPORT
#define EMMAPARSER_API __declspec(dllexport)
#else
#define EMMAPARSER_API __declspec(dllimport)
#endif
#else
#define EMMAPARSER_API
#endif

#endif
