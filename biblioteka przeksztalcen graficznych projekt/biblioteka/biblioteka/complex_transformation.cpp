#include "transformation.h"


// COMPLEX TRANSFORMATION ==========================================================================



Complex_Transformation::Complex_Transformation(){}



Complex_Transformation::Complex_Transformation( const Transformation& t,  const Transformation& t2 ){

	// funkcja uzywana dla operator+
	
	transformations.push_back( t );

	transformations.push_back( t2 );
}



Complex_Transformation::Complex_Transformation( const Transformation& t ){

	// CT = T

	transformations.push_back( t );

}



Complex_Transformation::Complex_Transformation( const Complex_Transformation& t ){

	//	 CT = T1 + T2

	transformations = t.transformations; // for i in transformations ??
}



Complex_Transformation Complex_Transformation::operator+ ( const Transformation& t ){ 

	// CT[T1,T2] + T3 = CT[T1,T2,T3]

	transformations.push_back( t );

	return *this;
}



const Transformation& Complex_Transformation::operator= ( const Complex_Transformation& t ){
	
	transformations = t.transformations;

	return *this;
}


/*
void  Complex_Transformation::operator>> ( Obj& obj) const {

	*matrix = (*transformations)[0].get_matrix();

	for ( int i = 1 ; i < transformations->size(); i++ ){
	
		*matrix = *matrix * (*transformations)[i].get_matrix();
	}

	obj.transform( *matrix );

}
*/




const Transformation& Complex_Transformation::operator[] ( int i ) const {

	return (transformations)[i];

}



const Transformation& Complex_Transformation::operator>> ( Obj& obj) {

	obj.transform( get_matrix() );

	return *this;
}



Matrix Complex_Transformation::get_matrix() const {

	Matrix m(4,4);

	m.translation_init(0,0,0);

	for ( size_t i = 0; i < transformations.size(); ++i ){
	
		m = m * transformations[i].get_matrix();
	
	}

	return m;
}



/*
void Complex_Transformation::push ( const Transformation& t ){

	transformations.push_back( t );

}*/