#ifndef _NOISEMAP_H_
#define _NOISEMAP_H_

#include "Precompiled.h"
#include "MathLib.h"

class NoiseMap {

	void GenerateNoise( GLfloat* data ) {
		for ( int y = 0; y < sizeY; y++ ) {
			for ( int x = 0; x < sizeX; x++ )
			{
				data[y * sizeX + x] = (rand() % 32768) / 32768.0;
			}
		}
	}

	double smoothNoise( GLfloat* data, double x, double y )
	{
		//get fractional part of x and y
		double fractX = x - int( x );
		double fractY = y - int( y );

		//wrap around
		int x1 = (int( x ) + sizeX) % sizeX;
		int y1 = (int( y ) + sizeY) % sizeY;

		//neighbor values
		int x2 = (x1 + sizeX - 1) % sizeX;
		int y2 = (y1 + sizeY - 1) % sizeY;

		//smooth the noise with bilinear interpolation
		double value = 0.0;
		value += fractX     * fractY     * data[y1 * sizeX + x1];
		value += (1 - fractX) * fractY     * data[y1 * sizeX + x2];
		value += fractX     * (1 - fractY) * data[y2 * sizeX + x1];
		value += (1 - fractX) * (1 - fractY) * data[y2 * sizeX + x2];

		return value;
	}

	double turbulence( GLfloat* data, double x, double y, double size )
	{
		double value = 0.0, initialSize = size;

		while ( size >= 1 )
		{
			value += smoothNoise( data, x / size, y / size ) * size;
			size /= 2.0;
		}

		return myMath::MapValue( (128.0 * value / initialSize), 0, 255, 0, 1 );
	}

	void PerlinNoise2D( int size ) {

		GLfloat* tempData = new GLfloat[sizeX*sizeY];

		GenerateNoise( tempData );

		for ( int y = 0; y < sizeY; y++ ) {
			for ( int x = 0; x < sizeX; x++ )
			{
				noiseData[y * sizeX + x] = turbulence( tempData, x, y, size );
			}
		}

		delete tempData;
	}

	GLint sizeX, sizeY;

public:

	GLfloat* noiseData;
	

	NoiseMap( GLuint seed, GLint noiseSize, GLint sizeX, GLint sizeY ) {
		srand( seed );
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		noiseData = nullptr;
		GenerateNewNoiseMap( noiseSize, sizeX, sizeY );
	}
	~NoiseMap() {
		delete noiseData;
	}

	void GenerateNewNoiseMap( GLint noiseSize, GLint sizeX, GLint sizeY ) {

		if ( noiseData )
			delete noiseData;
		noiseData = new GLfloat[sizeX*sizeY];
		memset( noiseData, 0, sizeX*sizeY * sizeof( GLfloat ) );

		if ( noiseSize > 0 ) {
			PerlinNoise2D( noiseSize );
		}
	}

};
#endif // !_NOISEMAP_H_