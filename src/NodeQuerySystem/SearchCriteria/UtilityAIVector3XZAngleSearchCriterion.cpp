#include "UtilityAIVector3XZAngleSearchCriterion.h"
#include <godot_cpp/classes/node3d.hpp>

using namespace godot;


UtilityAIVector3XZAngleSearchCriterion::UtilityAIVector3XZAngleSearchCriterion() {
    _min_angle_degrees = -90.0;
    _max_angle_degrees =  90.0;
    _min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
    _max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
    _angle_to_direction_vector = Vector3(0.0,0.0,-1.0);
    _xz_angle_vector = Vector2(1.0,0.0);
}


UtilityAIVector3XZAngleSearchCriterion::~UtilityAIVector3XZAngleSearchCriterion() {

}


void UtilityAIVector3XZAngleSearchCriterion::_bind_methods() {
    
    ClassDB::bind_method(D_METHOD("set_angle_to_direction_vector", "angle_to_direction_vector"), &UtilityAIVector3XZAngleSearchCriterion::set_angle_to_direction_vector);
    ClassDB::bind_method(D_METHOD("get_angle_to_direction_vector"), &UtilityAIVector3XZAngleSearchCriterion::get_angle_to_direction_vector);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "Angle_to_vector", PROPERTY_HINT_NONE), "set_angle_to_direction_vector","get_angle_to_direction_vector");
    
    ClassDB::bind_method(D_METHOD("set_min_angle_degrees", "min_angle_degrees"), &UtilityAIVector3XZAngleSearchCriterion::set_min_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_min_angle_degrees"), &UtilityAIVector3XZAngleSearchCriterion::get_min_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_min_angle_degrees","get_min_angle_degrees");
    
    ClassDB::bind_method(D_METHOD("set_max_angle_degrees", "max_angle_degrees"), &UtilityAIVector3XZAngleSearchCriterion::set_max_angle_degrees);
    ClassDB::bind_method(D_METHOD("get_max_angle_degrees"), &UtilityAIVector3XZAngleSearchCriterion::get_max_angle_degrees);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_angle_degrees", PROPERTY_HINT_RANGE, "-180.0,180.0"), "set_max_angle_degrees","get_max_angle_degrees");
    
    
}


void UtilityAIVector3XZAngleSearchCriterion::_initialize_criterion() {
    _max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
    _min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


// Getters and setters.

void UtilityAIVector3XZAngleSearchCriterion::set_angle_to_direction_vector( Vector3 angle_to_direction_vector ) {
    _angle_to_direction_vector = angle_to_direction_vector;
    _xz_angle_vector = Vector2(-_angle_to_direction_vector.z, _angle_to_direction_vector.x);
}


Vector3 UtilityAIVector3XZAngleSearchCriterion::get_angle_to_direction_vector() const {
    return _angle_to_direction_vector;
}


void UtilityAIVector3XZAngleSearchCriterion::set_min_angle_degrees( double min_angle_degrees ) {
    //if( _min_angle_degrees >= _max_angle_degrees ) return;
    if( _min_angle_degrees < -180.0 ) return;
    
    _min_angle_degrees = min_angle_degrees;
    _min_angle_radians = godot::Math::deg_to_rad(_min_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


double UtilityAIVector3XZAngleSearchCriterion::get_min_angle_degrees() const {
    return _min_angle_degrees;
}


void UtilityAIVector3XZAngleSearchCriterion::set_max_angle_degrees( double max_angle_degrees ) {
    //if( max_angle_degrees <= _min_angle_degrees ) return;
    if( max_angle_degrees > 180.0 ) return;
    _max_angle_degrees = max_angle_degrees;
    _max_angle_radians = godot::Math::deg_to_rad(_max_angle_degrees);
    _span_radians = _max_angle_radians - _min_angle_radians;
    _one_over_span_radians = 1.0 / _span_radians;
}


double UtilityAIVector3XZAngleSearchCriterion::get_max_angle_degrees() const {
    return _max_angle_degrees;
}


// Handing methods.

void UtilityAIVector3XZAngleSearchCriterion::apply_criterion( Node* node, bool& filter_out, double& score ) {
    Node3D* node3d = godot::Object::cast_to<Node3D>(node);
    if( node3d == nullptr ) return;

    _is_filtered = false;
    _score = 0.0;

    Vector3 node3d_direction_vector = -node3d->get_global_transform().basis.get_column(2);
    Vector2 node3d_2d_direction_vector = Vector2(node3d_direction_vector.z, node3d_direction_vector.x);
    
    double angle = _xz_angle_vector.angle_to(node3d_2d_direction_vector);
    
    if( get_use_for_filtering() ) {
        _is_filtered = (angle < _min_angle_degrees || angle > _max_angle_degrees );
    }//endif do filtering

    if( get_use_for_scoring() ) {
        if( angle >= _max_angle_degrees ) {
            _score = 1.0;
        } else if( angle <= _min_angle_degrees) {
            _score = 0.0;
        } else {
            double angle_from_lower_limit = angle - _min_angle_degrees;
            _score = angle_from_lower_limit * _one_over_span_radians; 
        }
        if( get_activation_curve().is_valid()) {
            _score = sample_activation_curve(_score);
        }
    }//endif do scoring
    
    filter_out = _is_filtered;
    score = _score;
    
}