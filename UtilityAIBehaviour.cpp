#include "UtilityAIBehaviour.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "UtilityAIConsideration.h"
#include "UtilityAIConsiderationGroup.h"


using namespace godot;

// Method binds.

void UtilityAIBehaviour::_bind_methods() {

    ADD_SUBGROUP("Configuration","");

    ClassDB::bind_method(D_METHOD("set_can_be_interrupted", "can_be_interrupted"), &UtilityAIBehaviour::set_can_be_interrupted);
    ClassDB::bind_method(D_METHOD("get_can_be_interrupted"), &UtilityAIBehaviour::get_can_be_interrupted);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "can_be_interrupted", PROPERTY_HINT_NONE), "set_can_be_interrupted","get_can_be_interrupted");
    
    ClassDB::bind_method(D_METHOD("set_cooldown_seconds", "cooldown_seconds"), &UtilityAIBehaviour::set_cooldown_seconds);
    ClassDB::bind_method(D_METHOD("get_cooldown_seconds"), &UtilityAIBehaviour::get_cooldown_seconds);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown_seconds", PROPERTY_HINT_RANGE, "0.0,600.0,allow_greater"), "set_cooldown_seconds","get_cooldown_seconds");

    ADD_SUBGROUP("Debugging","");

    ClassDB::bind_method(D_METHOD("set_score", "score"), &UtilityAIBehaviour::set_score);
    ClassDB::bind_method(D_METHOD("get_score"), &UtilityAIBehaviour::get_score);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "score", PROPERTY_HINT_RANGE,"-100.0,100.0"), "set_score","get_score");

    ClassDB::bind_method(D_METHOD("set_current_action_index", "current_action_index"), &UtilityAIBehaviour::set_current_action_index);
    ClassDB::bind_method(D_METHOD("get_current_action_index"), &UtilityAIBehaviour::get_current_action_index);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_action_index", PROPERTY_HINT_RANGE,"-0,256"), "set_current_action_index","get_current_action_index");
    
    
    //ClassDB::bind_method(D_METHOD("evaluate"), &UtilityAIBehaviour::evaluate);
    /**
    ClassDB::bind_method(D_METHOD("update_current_state", "delta"), &UtilityAIBehaviour::_update_current_state);
    /**/
}


// Constructor and destructor.

UtilityAIBehaviour::UtilityAIBehaviour() {
    _current_action_node = nullptr;
    _score = 0.0f;
    _cooldown_seconds = 0.0;
    _current_cooldown_seconds = 0.0;
    _current_action_index = 0;
    _can_be_interrupted = false;
}


UtilityAIBehaviour::~UtilityAIBehaviour() {
}

// Handling functions.




// Getters and Setters.

void  UtilityAIBehaviour::set_can_be_interrupted( bool can_be_interrupted ) {
    _can_be_interrupted = can_be_interrupted;
}

bool  UtilityAIBehaviour::get_can_be_interrupted() const {
    return _can_be_interrupted;
}

void UtilityAIBehaviour::set_score( float score ) {
    _score = score;
}

float UtilityAIBehaviour::get_score() const {
    return _score;
}

void UtilityAIBehaviour::set_cooldown_seconds( double cooldown_seconds ) {
    _cooldown_seconds = cooldown_seconds;
}

double UtilityAIBehaviour::get_cooldown_seconds() const {
    return _cooldown_seconds;
}

void UtilityAIBehaviour::set_current_action_index( int current_action_index ) {
    _current_action_index = current_action_index;
}

int  UtilityAIBehaviour::get_current_action_index() const {
    return _current_action_index;
}


/**
void UtilityAIBehaviour::set_update_method( int update_method ) {
    _update_method = update_method;
}

int UtilityAIBehaviour::get_update_method() const {
    return _update_method;
}
/**/

// Godot virtuals.

void UtilityAIBehaviour::_notification(int p_what) {
	switch (p_what) {
        case NOTIFICATION_ENTER_TREE: {
            // Entered the tree. 
        } break;
		case NOTIFICATION_EXIT_TREE: {
			
		} break;
	}
}

void UtilityAIBehaviour::_ready() {
    if( !get_is_active() ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;

    // Get the considerations and actions.    
    
}

/*void UtilityAIBehaviour::_process(double delta ) {
    //if( _update_method != UtilityAIBehaviour_UPDATE_METHOD_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;

    _current_state->_state_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

void UtilityAIBehaviour::_physics_process(double delta ) {
    //if( _update_method != UtilityAIBehaviour_UPDATE_METHOD_PHYSICS_PROCESS ) return;
    if( !_is_active ) return;
    if( Engine::get_singleton()->is_editor_hint() ) return;
    if( _current_state == nullptr ) return;
    _current_state->_state_physics_process(delta);
    //_current_state->_state_execute_Behaviours(delta);
}

/**/


// Handling functions.

double UtilityAIBehaviour::evaluate() { // UtilityAIAgent* agent, double delta) {
    if( !get_is_active() ) return 0.0;
    if( Engine::get_singleton()->is_editor_hint() ) return 0.0;

    // If the behaviour is on cooldown, it cannot be chosen.
    //if( _current_cooldown_seconds > 0.0 ) {
    //    _current_cooldown_seconds -= delta;
    //    return 0.0;
    //}

    _score = 0.0;

    // Evaluate the children.
    int num_children = get_child_count();
    for( int i = 0; i < num_children; ++i ) {
        UtilityAIConsiderations* considerationNode = godot::Object::cast_to<UtilityAIConsiderations>(get_child(i));
        if( considerationNode == nullptr ) continue;
        if( !considerationNode->get_is_active() ) continue;
        _score += considerationNode->evaluate();//agent, delta);
        if( considerationNode->get_has_vetoed()){
            _score = 0.0;
            return 0.0; // The consideration vetoed this behaviour.
        }
    }//endfor children

    return _score;
}


void UtilityAIBehaviour::start_behaviour() {
    _current_cooldown_seconds = _cooldown_seconds;
    _current_action_index = 0;
    _current_action_node = nullptr;
    //WARN_PRINT("Behaviour started.");
    //_current_action_node = update_behaviour();
}


void UtilityAIBehaviour::end_behaviour() {
    //WARN_PRINT("Behaviour ended.");
    _current_action_index = 0;
    _current_action_node = nullptr;
    
}


UtilityAIAction* UtilityAIBehaviour::update_behaviour() {
    //WARN_PRINT("AIBehaviour::update_behaviour(): stepping actions.");
    return (UtilityAIAction*) step_actions();
}


Node* UtilityAIBehaviour::step_actions() {
    //WARN_PRINT("UtilityAIBehaviour::step_actions()");
    if( _current_action_node != nullptr ) {
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Has a current action");
        if( !_current_action_node->get_is_finished() ) return _current_action_node;
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Action finished, ending it...");
        // The action has finished.
        _current_action_node->end_action();
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Done ending action.");
        _current_action_node = nullptr;
    }//endif current action node valid

    //WARN_PRINT("UtilityAIBehaviour::step_actions(): Checking if the current index is an action group.");
    // Check if the current index has an action group and if that group has a follow-up action.
    Node* current_node = get_child(_current_action_index);
    UtilityAIActionGroup* current_action_group = godot::Object::cast_to<UtilityAIActionGroup>(current_node);
    if( current_action_group != nullptr ) {
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Yes, current action is an action group. Stepping...");
        _current_action_node = godot::Object::cast_to<UtilityAIAction>(current_action_group->step_actions());
        //if( _current_action_node == nullptr ) WARN_PRINT("UtilityAIBehaviour::step_actions(): group sent back a NULL action pointer.");
        if( _current_action_node != nullptr ) return _current_action_node;
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Action has completed, endng action for the action group.");
        current_action_group->end_action();
        //WARN_PRINT("UtilityAIBehaviour::step_actions(): Action group action ended.");
    }//endif current node index is action group
    //WARN_PRINT("UtilityAIBehaviour::step_actions(): Finding a new action...");       
    
    ++_current_action_index;
    while( _current_action_index < get_child_count() ) {
        
        if( UtilityAIAction* action_node = godot::Object::cast_to<UtilityAIAction>(get_child(_current_action_index)) ) {
            //WARN_PRINT("UtilityAIBehaviour::step_actions(): Found an action, starting the action...");
            _current_action_node = action_node;
            _current_action_node->start_action();
            //WARN_PRINT("UtilityAIBehaviour::step_actions(): Done, returning action node.");
            return _current_action_node;
        } else if(UtilityAIActionGroup* action_group = godot::Object::cast_to<UtilityAIActionGroup>(get_child(_current_action_index)) ) {
            //WARN_PRINT("UtilityAIBehaviour::step_actions(): Found an action group, starting the action group.");
            action_group->start_action();
            //WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping it to find the sub action...");    
            _current_action_node = godot::Object::cast_to<UtilityAIAction>(action_group->step_actions());
            //if( _current_action_node == nullptr ) {
            //    WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping function returned NULL action pointer.");    
            //}
            if( _current_action_node != nullptr ) {
                //WARN_PRINT("UtilityAIBehaviour::step_actions(): Stepping function returned a valid action pointer.");    
                _current_action_node->start_action();
                return _current_action_node;
            }
        }// endif is action or action_group
        ++_current_action_index;
        
    }//endwhile action index in bounds

    //WARN_PRINT("UtilityAIBehaviour::step_actions(): NO ACTION FOUND! ");
    return nullptr;
}


