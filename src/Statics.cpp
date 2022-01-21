#include "Statics.h"


const char* Statics::errorString(GLenum err)
{
	switch (err) {
	case GL_NO_ERROR:
		return "No error";
	case GL_INVALID_ENUM:
		return "Invalid enum";
	case GL_INVALID_VALUE:
		return "Invalid value";
	case GL_INVALID_OPERATION:
		return "Invalid operation";
	case GL_STACK_OVERFLOW:
		return "Stack overflow";
	case GL_STACK_UNDERFLOW:
		return "Stack underflow";
	case GL_OUT_OF_MEMORY:
		return "Out of memory";
	default:
		return "No error";
	}
}

char* Statics::textFileRead(const char* fn)
{
	FILE* fp;
	char* content = NULL;
	int count = 0;
	if (fn != NULL) {
		fp = fopen(fn, "rt");
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = (int)ftell(fp);
			rewind(fp);
			if (count > 0) {
				content = (char*)malloc(sizeof(char) * (count + 1));
				count = (int)fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		else {
			printf("error loading %s\n", fn);
		}
	}
	return content;
}

void Statics::checkError(const char* str)
{
	GLenum glErr = glGetError();
	if (glErr != GL_NO_ERROR) {
		if (str) {
			printf("%s: ", str);
		}
		printf("GL_ERROR = %s.\n", errorString(glErr));
		assert(false);
	}
}
