#ifndef _MATHLIB_H_
#define _MATHLIB_H_

#define PI			3.14159265358979323846f

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace myMath {

	inline GLfloat MapValue( GLfloat value, GLfloat inputMin, GLfloat inputMax, GLfloat outputMin, GLfloat outputMax ) {
		GLfloat result;
		result = ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin) + outputMin;
		return result;
	}

}
#endif
