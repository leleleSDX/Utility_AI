#include "UtilityAIBTRunNQSQuery.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>


using namespace godot;

// Method binds.

void UtilityAIBTRunNQSQuery::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_nqs_search_space_node_path", "nqs_search_space_node_path"), &UtilityAIBTRunNQSQuery::set_nqs_search_space_node_path);
    ClassDB::bind_method(D_METHOD("get_nqs_search_space_node_path"), &UtilityAIBTRunNQSQuery::get_nqs_search_space_node_path);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "nqs_search_space_node_path", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UtilityAINQSSearchSpaces"), "set_nqs_search_space_node_path","get_nqs_search_space_node_path");

    ClassDB::bind_method(D_METHOD("set_top_n_to_find", "top_n_to_find"), &UtilityAIBTRunNQSQuery::set_top_n_to_find);
    ClassDB::bind_method(D_METHOD("get_top_n_to_find"), &UtilityAIBTRunNQSQuery::get_top_n_to_find);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "top_n_to_find", PROPERTY_HINT_RANGE, "1,32,or_greater"), "set_top_n_to_find","get_top_n_to_find");

    ClassDB::bind_method(D_METHOD("set_time_budget_usec", "time_budget_usec"), &UtilityAIBTRunNQSQuery::set_time_budget_usec);
    ClassDB::bind_method(D_METHOD("get_time_budget_usec"), &UtilityAIBTRunNQSQuery::get_time_budget_usec);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "time_budget_usec", PROPERTY_HINT_RANGE, "0,10000,or_greater"), "set_time_budget_usec","get_time_budget_usec");
    
}


// Constructor and destructor.

UtilityAIBTRunNQSQuery::UtilityAIBTRunNQSQuery() {
    _nqs_search_space_node = nullptr;
    _time_budget_usec = 200;
    _top_n_to_find = 1;
}


UtilityAIBTRunNQSQuery::~UtilityAIBTRunNQSQuery() {
    _nqs_search_space_node = nullptr;
}


// Getters and Setters.

void UtilityAIBTRunNQSQuery::set_nqs_search_space_node_path( NodePath nqs_search_space_node_path ) {
    _nqs_search_space_node_path = nqs_search_space_node_path;
}


NodePath UtilityAIBTRunNQSQuery::get_nqs_search_space_node_path() const {
    return _nqs_search_space_node_path;
}


void UtilityAIBTRunNQSQuery::set_time_budget_usec( int time_budget_usec ) {
    _time_budget_usec = time_budget_usec;
}


int  UtilityAIBTRunNQSQuery::get_time_budget_usec() const {
    return _time_budget_usec;
}


void UtilityAIBTRunNQSQuery::set_top_n_to_find( int top_n_to_find ) {
    _top_n_to_find = top_n_to_find;
}


int  UtilityAIBTRunNQSQuery::get_top_n_to_find() const {
    return _top_n_to_find;
}


// Handling methods.

int UtilityAIBTRunNQSQuery::tick(Variant user_data, double delta) { 
    if( _nqs_search_space_node == nullptr ) {
        return BT_FAILURE;
    }
    _nqs_search_space_node->set_top_n_to_find(_top_n_to_find);
    bool is_completed = _nqs_search_space_node->execute_query(_time_budget_usec);
    if( !is_completed ) {
        return BT_RUNNING;
    }
    return BT_SUCCESS;
}


void UtilityAIBTRunNQSQuery::_ready() {
    if( Engine::get_singleton()->is_editor_hint() ) return;
    _nqs_search_space_node = godot::Object::cast_to<UtilityAINQSSearchSpaces>(get_node_or_null(_nqs_search_space_node_path));
}

/**
void UtilityAIBTRunNQSQuery::_exit_tree() {

}
/**/
