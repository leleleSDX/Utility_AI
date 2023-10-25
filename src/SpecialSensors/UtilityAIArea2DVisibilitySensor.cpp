#include "UtilityAIArea2DVisibilitySensor.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>


using namespace godot;


// Method binds.

void UtilityAIArea2DVisibilitySensor::_bind_methods() {

    ADD_SUBGROUP("Configuration","");
    
    ClassDB::bind_method(D_METHOD("set_from_vector", "from_vector"), &UtilityAIArea2DVisibilitySensor::set_from_Vector2);
    ClassDB::bind_method(D_METHOD("get_from_vector"), &UtilityAIArea2DVisibilitySensor::get_from_Vector2);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "from_vector", PROPERTY_HINT_NONE), "set_from_vector","get_from_vector");
    
    ClassDB::bind_method(D_METHOD("set_visibility_volume_nodepath", "visibility_volume_nodepath"), &UtilityAIArea2DVisibilitySensor::set_visibility_volume_nodepath);
    ClassDB::bind_method(D_METHOD("get_visibility_volume_nodepath"), &UtilityAIArea2DVisibilitySensor::get_visibility_volume_nodepath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "visibility_volume_nodepath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Area2D"), "set_visibility_volume_nodepath","get_visibility_volume_nodepath");
    
    ClassDB::bind_method(D_METHOD("set_max_expected_entities_found", "max_expected_entities_found"), &UtilityAIArea2DVisibilitySensor::set_max_expected_entities_found);
    ClassDB::bind_method(D_METHOD("get_max_expected_entities_found"), &UtilityAIArea2DVisibilitySensor::get_max_expected_entities_found);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "max_expected_entities_found", PROPERTY_HINT_RANGE, "1,32,or_greater"), "set_max_expected_entities_found","get_max_expected_entities_found");


    ADD_SUBGROUP("Occlusion","");
    
    ClassDB::bind_method(D_METHOD("set_do_occlusion_test", "do_occlusion_test"), &UtilityAIArea2DVisibilitySensor::set_do_occlusion_test);
    ClassDB::bind_method(D_METHOD("get_do_occlusion_test"), &UtilityAIArea2DVisibilitySensor::get_do_occlusion_test);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "do_occlusion_test", PROPERTY_HINT_NONE), "set_do_occlusion_test","get_do_occlusion_test");

    ClassDB::bind_method(D_METHOD("set_collision_mask", "collision_mask"), &UtilityAIArea2DVisibilitySensor::set_collision_mask);
    ClassDB::bind_method(D_METHOD("get_collision_mask"), &UtilityAIArea2DVisibilitySensor::get_collision_mask);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "collision_mask", PROPERTY_HINT_LAYERS_3D_PHYSICS), "set_collision_mask","get_collision_mask");

    ClassDB::bind_method(D_METHOD("set_occlusion_test_exclusion_list", "occlusion_test_exclusion_list"), &UtilityAIArea2DVisibilitySensor::set_occlusion_test_exclusion_list);
    ClassDB::bind_method(D_METHOD("get_occlusion_test_exclusion_list"), &UtilityAIArea2DVisibilitySensor::get_occlusion_test_exclusion_list);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "occlusion_test_exclusion_list", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "RID")), "set_occlusion_test_exclusion_list","get_occlusion_test_exclusion_list");

    //ClassDB::bind_method(D_METHOD("set_entity_mask", "entity_mask"), &UtilityAIArea2DVisibilitySensor::set_entity_mask);
    //ClassDB::bind_method(D_METHOD("get_entity_mask"), &UtilityAIArea2DVisibilitySensor::get_entity_mask);
    //ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_mask", PROPERTY_HINT_LAYERS_3D_PHYSICS), "set_entity_mask","get_entity_mask");

    ClassDB::bind_method(D_METHOD("on_area_entered", "area"), &UtilityAIArea2DVisibilitySensor::on_area_entered);
    ClassDB::bind_method(D_METHOD("on_area_exited", "aera"), &UtilityAIArea2DVisibilitySensor::on_area_exited);

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_num_entities_found", "num_entities_found"), &UtilityAIArea2DVisibilitySensor::set_num_entities_found);
    ClassDB::bind_method(D_METHOD("get_num_entities_found"), &UtilityAIArea2DVisibilitySensor::get_num_entities_found);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "num_entities_found", PROPERTY_HINT_RANGE, "0,32,or_greater"), "set_num_entities_found","get_num_entities_found");

    ClassDB::bind_method(D_METHOD("set_closest_intersecting_area_index", "closest_intersecting_area_index"), &UtilityAIArea2DVisibilitySensor::set_closest_intersecting_area_index);
    ClassDB::bind_method(D_METHOD("get_closest_intersecting_area_index"), &UtilityAIArea2DVisibilitySensor::get_closest_intersecting_area_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "closest_intersecting_area_index", PROPERTY_HINT_RANGE, "-1,32,or_greater"), "set_closest_intersecting_area_index","get_closest_intersecting_area_index");

    ClassDB::bind_method(D_METHOD("set_intersecting_areas", "intersecting_areas"), &UtilityAIArea2DVisibilitySensor::set_intersecting_areas);
    ClassDB::bind_method(D_METHOD("get_intersecting_areas"), &UtilityAIArea2DVisibilitySensor::get_intersecting_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "intersecting_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Area2D")), "set_intersecting_areas","get_intersecting_areas");

    ClassDB::bind_method(D_METHOD("set_squared_distances_to_intersecting_areas", "squared_distances_to_intersecting_areas"), &UtilityAIArea2DVisibilitySensor::set_squared_distances_to_intersecting_areas);
    ClassDB::bind_method(D_METHOD("get_squared_distances_to_intersecting_areas"), &UtilityAIArea2DVisibilitySensor::get_squared_distances_to_intersecting_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "squared_distances_to_intersecting_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "float")), "set_squared_distances_to_intersecting_areas","get_squared_distances_to_intersecting_areas");

    ClassDB::bind_method(D_METHOD("set_closest_unoccluded_area_index", "closest_unoccluded_area_index"), &UtilityAIArea2DVisibilitySensor::set_closest_unoccluded_area_index);
    ClassDB::bind_method(D_METHOD("get_closest_unoccluded_area_index"), &UtilityAIArea2DVisibilitySensor::get_closest_unoccluded_area_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "closest_unoccluded_area_index", PROPERTY_HINT_RANGE, "-1,32,or_greater"), "set_closest_unoccluded_area_index","get_closest_unoccluded_area_index");

    ClassDB::bind_method(D_METHOD("set_unoccluded_areas", "unoccluded_areas"), &UtilityAIArea2DVisibilitySensor::set_unoccluded_areas);
    ClassDB::bind_method(D_METHOD("get_unoccluded_areas"), &UtilityAIArea2DVisibilitySensor::get_unoccluded_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "unoccluded_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Area2D")), "set_unoccluded_areas","get_unoccluded_areas");

    ClassDB::bind_method(D_METHOD("set_squared_distances_to_unoccluded_areas", "squared_distances_to_unoccluded_areas"), &UtilityAIArea2DVisibilitySensor::set_squared_distances_to_unoccluded_areas);
    ClassDB::bind_method(D_METHOD("get_squared_distances_to_unoccluded_areas"), &UtilityAIArea2DVisibilitySensor::get_squared_distances_to_unoccluded_areas);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "squared_distances_to_unoccluded_areas", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "float")), "set_squared_distances_to_unoccluded_areas","get_squared_distances_to_unoccluded_areas");

    //ClassDB::bind_method(D_METHOD("set_unoccluded_bodies", "unoccluded_bodies"), &UtilityAIArea2DVisibilitySensor::set_unoccluded_bodies);
    //ClassDB::bind_method(D_METHOD("get_unoccluded_bodies"), &UtilityAIArea2DVisibilitySensor::get_unoccluded_bodies);
    //ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "unoccluded_bodies", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Node3D")), "set_unoccluded_bodies","get_unoccluded_bodies");

}


// Constructor and destructor.

UtilityAIArea2DVisibilitySensor::UtilityAIArea2DVisibilitySensor() {
    _visibility_volume_node = nullptr;
    _do_occlusion_test = true;
    _collision_mask = 1;
    _expected_number_of_areas_to_track = 16;
    _expected_number_of_bodies_to_track = 16;
    _num_entities_found = 0;
    _max_expected_entities_found = 16;
    _one_over_max_expected_entities_found = 1.0 / ((double)_max_expected_entities_found);

    _unoccluded_areas.resize(_expected_number_of_areas_to_track);
    //_unoccluded_bodies.resize(_expected_number_of_bodies_to_track);

    _closest_intersecting_area_index = -1;
    _closest_unoccluded_area_index = -1;
}


UtilityAIArea2DVisibilitySensor::~UtilityAIArea2DVisibilitySensor() {
}


// Godot virtuals.

/*void UtilityAIArea2DVisibilitySensor::_ready() {
    initialize_sensor();
}
/**/

void UtilityAIArea2DVisibilitySensor::_notification(int p_what) {
    switch (p_what) {
		case NOTIFICATION_EXIT_TREE: {
			// Remove the signal connections.
            _visibility_volume_node->disconnect("area_entered", Callable(this, "on_area_entered"));
            _visibility_volume_node->disconnect("area_exited", Callable(this, "on_area_exited"));

		} break;
	}
}



// Handling functions.

void UtilityAIArea2DVisibilitySensor::initialize_sensor() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    Node* node = get_node_or_null(_visibility_volume_nodepath);
    ERR_FAIL_COND_MSG( node == nullptr, "UtilityAIArea2DVisibilitySensor::initialize_sensor() - Error, the nodepath for the Area2D has not been set.");
    _visibility_volume_node = godot::Object::cast_to<Area2D>(node);
    ERR_FAIL_COND_MSG( _visibility_volume_node == nullptr, "UtilityAIArea2DVisibilitySensor::initialize_sensor() - Error, the node set as the Area2D is not of type Area2D.");
    
    // Connect to the area entered and exited signals.
    Error error_visibility_volume_on_entered = _visibility_volume_node->connect("area_entered", Callable(this, "on_area_entered"));
    Error error_visibility_volume_on_exited  = _visibility_volume_node->connect("area_exited", Callable(this, "on_area_exited"));
}


double UtilityAIArea2DVisibilitySensor::evaluate_sensor_value() {
    if( _visibility_volume_node == nullptr ) {
        return get_sensor_value();
    }

    //Ref<World3D> w3d = _visibility_volume_node->get_world_3d();
    //ERR_FAIL_COND_V(w3d.is_null(), get_sensor_value());
    PhysicsDirectSpaceState2D *dss = nullptr;
    
    if( _do_occlusion_test ) {
        dss = PhysicsServer2D::get_singleton()->space_get_direct_state(PhysicsServer2D::get_singleton()->area_get_space(_visibility_volume_node->get_rid()));
        //PhysicsDirectSpaceState3D *dss = PhysicsServer3D::get_singleton()->space_get_direct_state(w3d->get_space());
        ERR_FAIL_NULL_V(dss, get_sensor_value());
    }

    _num_entities_found = 0;
    _closest_intersecting_area_index = -1;
    _closest_unoccluded_area_index = -1;
    float closest_intersecting_area_distance = 0.0f;
    float closest_unoccluded_area_distance = 0.0f;
    int   found_unoccluded_areas = 0;
    Vector2 zero_vector = Vector2();
    _unoccluded_areas.clear();
    _squared_distances_to_unoccluded_areas.clear();
    _squared_distances_to_intersecting_areas.clear();
    for( int i = 0; i < _intersecting_areas.size(); ++i ) {
        Area2D* area = godot::Object::cast_to<Area2D>(_intersecting_areas[i]);
        if( area == nullptr ) {
            continue;
        }
        Vector2 area_position = area->get_global_position();

        // Calculate the distance to the area.
        Vector2 from_to = area_position - _from_vector;
        float distance_squared = from_to.length_squared();
        _squared_distances_to_intersecting_areas.push_back(distance_squared);
        if( _closest_intersecting_area_index == -1 ) {
            _closest_intersecting_area_index = i;
            closest_intersecting_area_distance = distance_squared;
        } else if( closest_intersecting_area_distance > distance_squared ) {
            _closest_intersecting_area_index = i;
            closest_intersecting_area_distance = distance_squared;
        }

        if( _do_occlusion_test ) {    
            Vector2 to = area_position;
            if (to == zero_vector) {
                continue; 
            }
            Ref<PhysicsRayQueryParameters2D> params = godot::PhysicsRayQueryParameters2D::create(_from_vector, 
                                                                                                 to, 
                                                                                                 _collision_mask, 
                                                                                                 _occlusion_test_exclusion_list);
            //(const Vector2 &from, const Vector2 &to, uint32_t collision_mask = 4294967295, const TypedArray<RID> &exclude = {})
            params->set_collide_with_bodies(true);
            params->set_collide_with_areas(true);
            //params->set_block_signals(true);
            Dictionary results = dss->intersect_ray( params );
            if( results.is_empty() ) {
                _unoccluded_areas.push_back(area);
                _squared_distances_to_unoccluded_areas.push_back(distance_squared);
                if( _closest_unoccluded_area_index == -1 ) {
                    _closest_unoccluded_area_index = found_unoccluded_areas;
                    closest_unoccluded_area_distance = distance_squared;
                } else if( closest_unoccluded_area_distance > distance_squared ) {
                    _closest_unoccluded_area_index = found_unoccluded_areas;
                    closest_unoccluded_area_distance = distance_squared;
                }
                ++found_unoccluded_areas;
                ++_num_entities_found;
            }
        } else {
            ++_num_entities_found;
        }

        
    }//endfor entered areas.
    
    set_sensor_value(((double)_num_entities_found) * _one_over_max_expected_entities_found);
    return get_sensor_value();
}


void UtilityAIArea2DVisibilitySensor::on_area_entered(Area2D* area ) {
    //WARN_PRINT("Area entered!");
    if( area == nullptr ) {
        return;
    }
    if( _intersecting_areas.has(area) ) {
        return;
    }   
    _intersecting_areas.push_back(area);
}


void UtilityAIArea2DVisibilitySensor::on_area_exited(Area2D* area ) {
    //WARN_PRINT("Area exited");
    if( area == nullptr ) {
        return;
    }
    if( !_intersecting_areas.has(area ) ) {
        return;
    }
    int index = _intersecting_areas.find(area);
    if( index < 0 ) {
        return;
    }
    _intersecting_areas.remove_at(index);
}


// Getters and Setters.

// Configuration values. 

void UtilityAIArea2DVisibilitySensor::set_from_Vector2( Vector2 from ) {
    _from_vector = from;
}


Vector2 UtilityAIArea2DVisibilitySensor::get_from_Vector2() const {
    return _from_vector;
}


void UtilityAIArea2DVisibilitySensor::set_visibility_volume_nodepath( NodePath Area2D_nodepath ) {
    _visibility_volume_nodepath = Area2D_nodepath;
}


NodePath UtilityAIArea2DVisibilitySensor::get_visibility_volume_nodepath() const {
    return _visibility_volume_nodepath;
}


void UtilityAIArea2DVisibilitySensor::set_visibility_volume_node( Area2D* node ) {
    _visibility_volume_node = node;
}


Area2D* UtilityAIArea2DVisibilitySensor::get_visibility_volume_node() const {
    return _visibility_volume_node;
}


void UtilityAIArea2DVisibilitySensor::set_do_occlusion_test( bool do_occlusion_test ) {
    _do_occlusion_test = do_occlusion_test;
}


bool UtilityAIArea2DVisibilitySensor::get_do_occlusion_test() const {
    return _do_occlusion_test;
}


void UtilityAIArea2DVisibilitySensor::set_collision_mask( uint32_t collision_mask) {
    _collision_mask = collision_mask;
}


uint32_t UtilityAIArea2DVisibilitySensor::get_collision_mask() const {
    return _collision_mask;
}


/**
void UtilityAIArea2DVisibilitySensor::set_entity_mask( uint32_t entity_mask) {
    _entity_mask = entity_mask;
}

uint32_t UtilityAIArea2DVisibilitySensor::get_entity_mask() const {
    return _entity_mask;
}
/**/

void UtilityAIArea2DVisibilitySensor::set_max_expected_entities_found( int max_expected_entities_found ) {
    if( _max_expected_entities_found <= 0 ) {
        return;
    }
    _max_expected_entities_found = max_expected_entities_found;
    _one_over_max_expected_entities_found = 1.0 / ((double)_max_expected_entities_found);
}


int  UtilityAIArea2DVisibilitySensor::get_max_expected_entities_found() const {
    return _max_expected_entities_found;
}


void UtilityAIArea2DVisibilitySensor::set_occlusion_test_exclusion_list( TypedArray<RID> occlusion_test_exclusion_list ) {
    _occlusion_test_exclusion_list = occlusion_test_exclusion_list;
}


TypedArray<RID> UtilityAIArea2DVisibilitySensor::get_occlusion_test_exclusion_list() const {
    return _occlusion_test_exclusion_list;
}


// Debugging / current values.

void UtilityAIArea2DVisibilitySensor::set_num_entities_found( int num_entities_found ) {
    _num_entities_found = num_entities_found;
}


int  UtilityAIArea2DVisibilitySensor::get_num_entities_found() const {
    return _num_entities_found;
}


void UtilityAIArea2DVisibilitySensor::set_closest_intersecting_area_index( int closest_intersecting_area_index ) {
    _closest_intersecting_area_index = closest_intersecting_area_index;
}


int  UtilityAIArea2DVisibilitySensor::get_closest_intersecting_area_index() const {
    return _closest_intersecting_area_index;
}


void UtilityAIArea2DVisibilitySensor::set_closest_unoccluded_area_index( int closest_unoccluded_area_index ) {
    _closest_unoccluded_area_index = closest_unoccluded_area_index;
}


int  UtilityAIArea2DVisibilitySensor::get_closest_unoccluded_area_index() const {
    return _closest_unoccluded_area_index;
}


void UtilityAIArea2DVisibilitySensor::set_intersecting_areas( TypedArray<Area2D> intersecting_areas ) {
    _intersecting_areas = intersecting_areas;
}


TypedArray<Area2D> UtilityAIArea2DVisibilitySensor::get_intersecting_areas() const {
    return _intersecting_areas;
}


void UtilityAIArea2DVisibilitySensor::set_unoccluded_areas( TypedArray<Area2D> unoccluded_areas ) {
    _unoccluded_areas = unoccluded_areas;
}


TypedArray<Area2D> UtilityAIArea2DVisibilitySensor::get_unoccluded_areas() const {
    return _unoccluded_areas;
}


void UtilityAIArea2DVisibilitySensor::set_unoccluded_bodies( TypedArray<Node2D> unoccluded_bodies ) {
    _unoccluded_bodies = unoccluded_bodies;
}


TypedArray<Node2D> UtilityAIArea2DVisibilitySensor::get_unoccluded_bodies() const {
    return _unoccluded_bodies;
}


void UtilityAIArea2DVisibilitySensor::set_squared_distances_to_intersecting_areas( TypedArray<float> squared_distances_to_intersecting_areas ) {
    _squared_distances_to_intersecting_areas = squared_distances_to_intersecting_areas;
}


TypedArray<float> UtilityAIArea2DVisibilitySensor::get_squared_distances_to_intersecting_areas() const {
    return _squared_distances_to_intersecting_areas;
}


void UtilityAIArea2DVisibilitySensor::set_squared_distances_to_unoccluded_areas( TypedArray<float> squared_distances_to_unoccluded_areas ) {
    _squared_distances_to_unoccluded_areas = squared_distances_to_unoccluded_areas;
}


TypedArray<float> UtilityAIArea2DVisibilitySensor::get_squared_distances_to_unoccluded_areas() const {
    return _squared_distances_to_unoccluded_areas;
}

