#include "Operand.hpp"

Operand::Operand(int _id , int _parent_id , int _value){
	id = _id;
	parent_id = _parent_id;
	value = _value;
}
double Operand::calculate(){
	return value;
}