#include "considerations.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>


using namespace godot;

// Method binds.

void UtilityAIConsiderations::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_has_vetoed", "has_vetoed"), &UtilityAIConsiderations::set_has_vetoed);
    ClassDB::bind_method(D_METHOD("get_has_vetoed"), &UtilityAIConsiderations::get_has_vetoed);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_vetoed", PROPERTY_HINT_NONE), "set_has_vetoed","get_has_vetoed");
    

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIConsiderations::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIConsiderations::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_NONE ), "set_score","get_score");

    ClassDB::bind_method(D_METHOD("set_weight", "weight"), &UtilityAIConsiderations::set_weight);
    ClassDB::bind_method(D_METHOD("get_weight"), &UtilityAIConsiderations::get_weight);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "weight", PROPERTY_HINT_NONE ), "set_weight","get_weight");


}


// Constructor and destructor.

UtilityAIConsiderations::UtilityAIConsiderations() {
    _has_vetoed = false;
    _score = 0.0;
    _weight = 1.0;
}


UtilityAIConsiderations::~UtilityAIConsiderations() {
}

// Handling functions.



// Getters and Setters.

void UtilityAIConsiderations::set_has_vetoed( bool has_vetoed ) {
    _has_vetoed = has_vetoed;
}

bool UtilityAIConsiderations::get_has_vetoed() const {
    return _has_vetoed;
}


void UtilityAIConsiderations::set_score( double score ) {
    _score = score;
}

double UtilityAIConsiderations::get_score() const {
    return _score;
}

void UtilityAIConsiderations::set_weight( double weight ) {
    _weight = weight;
}

double UtilityAIConsiderations::get_weight() const {
    return _weight;
}

double UtilityAIConsiderations::evaluate() { 
    return 0.0;
}


