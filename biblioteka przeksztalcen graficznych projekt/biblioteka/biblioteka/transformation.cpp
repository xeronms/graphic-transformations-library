#include "transformation.h"




// TRANSFORMATION ==========================================================================


Transformation::Transformation( const Transformation& t){
		matrix = new Matrix( t.get_matrix() );
}


Transformation::~Transformation(){

	delete matrix;
}


Matrix Transformation::get_matrix() const {

	return *matrix;
}


Complex_Transformation Transformation::operator+ ( const Transformation& t ){

	// dodawanie dwoch transformacji tworzy complex_trans. ale gdy dodajemy complex_trans do czegos innego to korzystamy z wirtualnej wersji w klasie complex_trans

	Matrix A = *matrix * *t.matrix;	

	return Complex_Transformation(A , *this, t);
}


const Transformation& Transformation::operator>> ( Obj& obj) const {

	obj.transform( *matrix );

	return *this;
}




// TRANSLATION ====================================================================================


Translation::Translation( double dx, double dy, double dz ) {

	matrix = new Matrix( 4, 4);

	matrix->translation_init( dx, dy, dz );

}




// SCALING =========================================================================================


Scaling::Scaling( double sx, double sy, double sz ){

	matrix = new Matrix( 4, 4);

	matrix->scaling_init( sx, sy, sz );

}




// ROTATION =======================================================================================


Rotation::Rotation( axis os, double angle, double dx, double dy, double dz ){

	matrix = new Matrix( 4, 4);

	if ( dx || dy || dz ) // jesli os obrotu inna niz 0 0 0
	{}


	matrix->rotation_init( os, angle );
}




// COMP TRANSL ===================================================================================


Complex_Transformation::Complex_Transformation( const Matrix& M , const Transformation& t,  const Transformation& t2 ){

	matrix = new Matrix( M );

	push(t);
	
	push(t2);
}



Complex_Transformation::Complex_Transformation( const Complex_Transformation& t ){

	matrix = new Matrix( t.get_matrix() );

	transformations = t.transformations;
}


Complex_Transformation Complex_Transformation::operator+ ( const Transformation& t ){ 

	// CT[T1,T2] + T3 = CT[T1,T2,T3]

	transformations.emplace_back( Transformation ( t ) );

	*matrix = (*matrix) * t.get_matrix();

	return *this;
}


const Transformation& Complex_Transformation::operator= ( const Complex_Transformation& t ){

	delete matrix;
	
	matrix = new Matrix( t.get_matrix() );

	transformations = t.transformations;

	return *this;
}


void Complex_Transformation::push ( const Transformation& t ){

	transformations.emplace_back( Transformation (t) );

}