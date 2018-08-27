#ifndef TRANS_H
#define TRANS_H

#include "matrix.h"
#include "obj.h"

#include <vector>
#include <stack>


class Complex_Transformation;



class Transformation{

protected:

	Matrix matrix;

public:

	Transformation(){ matrix = Matrix (4,4);}

	Transformation( const Transformation& t);

	virtual ~Transformation(){}

	virtual Matrix get_matrix() const ;

	virtual Complex_Transformation operator+ ( const Transformation& );

	virtual Transformation operator- ();

	virtual Complex_Transformation operator- ( Transformation& t );

	//const Transformation operator- ( const Transformation& );

	virtual const Transformation& operator>> ( Obj& obj) const ;

};



// ==========================================================================================================================



class Translation : public Transformation{

public:

	Translation( double dx = 0, double dy = 0, double dz = 0 );

};



// ==========================================================================================================================



class Scaling : public Transformation{

public:

	Scaling( double sx = 1, double sy = 1, double sz = 1 );

};



// ==========================================================================================================================



class Rotation : public Transformation{

public:

	Rotation( axis os, double angle );

};



// ==========================================================================================================================



class Complex_Transformation : public Transformation{

protected:

	std::vector < const Transformation > transformations;

public:
	Complex_Transformation();

	Complex_Transformation( const Transformation& t );

	Complex_Transformation( const Transformation& t , const Transformation& t2);

	Complex_Transformation( const Complex_Transformation& );

	virtual Complex_Transformation operator+ ( const Transformation& );

	const Transformation& operator= ( const Complex_Transformation& );

	const Transformation& operator[] ( int i ) const;

	Transformation& operator[] ( int i );

	virtual const Transformation& operator>> ( Obj& obj) ;
	
	virtual Matrix get_matrix() const ;

	//void push ( const Transformation& );

	//void operator>> ( Obj& obj) const ;
};



// ==========================================================================================================================



class RotationArb : public Complex_Transformation{

public:

	//Rotation( axis os, double angle, double dx = 0, double dy = 0, double dz = 0);
};



#endif