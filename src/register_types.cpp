#include "register_types.h"
#include <godot_cpp/classes/engine.hpp>

// Classes to include in to the gdextension module.

// Performance monitor singleton.
#include "performance_monitor_singleton.h"

// AI Agent behaviours.
#include "agent_behaviours/behaviour.h"
#include "agent_behaviours/behaviour_group.h"
#include "agent_behaviours/considerations.h"
#include "agent_behaviours/consideration_group.h"
#include "agent_behaviours/consideration.h"
#include "agent_behaviours/actions.h"
#include "agent_behaviours/action.h"
#include "agent_behaviours/action_group.h"
#include "agent_behaviours/agent.h"
#include "agent_behaviours/sensors.h"
#include "agent_behaviours/sensor.h"
#include "agent_behaviours/sensor_group.h"

// Special sensors.
#include "agent_behaviours/sensors/boolean.h"
#include "agent_behaviours/sensors/float_range.h"
#include "agent_behaviours/sensors/int_range.h"
#include "agent_behaviours/sensors/angle_vector2.h"
#include "agent_behaviours/sensors/angle_vector3.h"
#include "agent_behaviours/sensors/distance_vector2.h"
#include "agent_behaviours/sensors/distance_vector3.h"
#include "agent_behaviours/sensors/area2d_visibility.h"
#include "agent_behaviours/sensors/area3d_visibility.h"

// Special considerations.
#include "agent_behaviours/considerations/boolean.h"
#include "agent_behaviours/considerations/custom_property.h"

// Resource-based considerations
#include "resources/considerations/consideration_resources.h"
#include "resources/considerations/consideration_resource.h"
#include "resources/considerations/consideration_group_resource.h"


// Behaviour tree.
#include "behaviour_tree/nodes.h"
#include "behaviour_tree/root.h"

#include "behaviour_tree/composite_nodes.h"
#include "behaviour_tree/random_sequence.h"
#include "behaviour_tree/random_selector.h"
#include "behaviour_tree/sequence.h"
#include "behaviour_tree/selector.h"
#include "behaviour_tree/parallel.h"
#include "behaviour_tree/score_based_picker.h"

#include "behaviour_tree/decorator_nodes.h"
#include "behaviour_tree/repeater.h"
#include "behaviour_tree/repeat_until.h"
#include "behaviour_tree/limiter.h"
#include "behaviour_tree/inverter.h"
#include "behaviour_tree/fixed_result.h"
#include "behaviour_tree/pass_through.h"


#include "behaviour_tree/cooldown_ticks.h"
#include "behaviour_tree/cooldown_msec.h"
#include "behaviour_tree/cooldown_usec.h"
#include "behaviour_tree/leaf.h"
#include "behaviour_tree/run_nqs_query.h"
#include "behaviour_tree/node_reference.h"
#include "behaviour_tree/pass_by.h"

// State trees.

//#include "state_tree/leaf.h"
#include "state_tree/nodes.h"
#include "state_tree/root.h"
#include "state_tree/selector.h"


// Node Query System.
#include "node_query_system/node_query_system.h"

#include "node_query_system/search_spaces/nqs.h"
#include "node_query_system/search_spaces/node_group.h"
#include "node_query_system/search_spaces/node_children.h"

#include "node_query_system/search_spaces/area3d.h"
#include "node_query_system/search_spaces/area2d.h"


#include "node_query_system/search_criteria/nqs.h"
#include "node_query_system/search_criteria/custom.h"
#include "node_query_system/search_criteria/metadata.h"

#include "node_query_system/search_criteria/distance_to_node3d.h"
#include "node_query_system/search_criteria/distance_to_node2d.h"

#include "node_query_system/search_criteria/distance_to_vector3.h"
#include "node_query_system/search_criteria/distance_to_vector2.h"

#include "node_query_system/search_criteria/angle_to_vector3_xz.h"
#include "node_query_system/search_criteria/angle_to_vector3.h"
#include "node_query_system/search_criteria/angle_to_vector2.h"

#include "node_query_system/search_criteria/dot_product_vector3.h"
#include "node_query_system/search_criteria/dot_product_vector2.h"

#include "node_query_system/search_criteria/dot_product_to_position_vector3.h"
#include "node_query_system/search_criteria/dot_product_to_position_vector2.h"

#include "node_query_system/search_spaces/point_grid/navigtaion3d.h"
#include "node_query_system/search_spaces/point_grid/navigtaion3d_rectangular.h"

// Main header for UtilityAI.
#include "utility_ai.h"

// Standard headers.
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static UtilityAINodeQuerySystem* gpNodeQuerySystem;
static UtilityAIPerformanceMonitorSingleton* gdAIPerformanceMonitor;

void initialize_utility_ai_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // Add the classes here.
    ClassDB::register_class<UtilityAI>(true);
    ClassDB::register_class<UtilityAIConsiderations>(true);
    ClassDB::register_class<UtilityAIConsiderationGroup>();
    ClassDB::register_class<UtilityAIConsideration>();
    ClassDB::register_class<UtilityAISensors>(true);
    ClassDB::register_class<UtilityAISensorGroup>();
    ClassDB::register_class<UtilityAISensor>();
    ClassDB::register_class<UtilityAIActions>(true);
    ClassDB::register_class<UtilityAIActionGroup>();
    ClassDB::register_class<UtilityAIAction>();
    ClassDB::register_class<UtilityAIBehaviour>();
    ClassDB::register_class<UtilityAIBehaviourGroup>();
    ClassDB::register_class<UtilityAIAgent>();
    
    // Special sensors.
    ClassDB::register_class<UtilityAIBooleanSensor>();
    ClassDB::register_class<UtilityAIFloatRangeSensor>();
    ClassDB::register_class<UtilityAIIntRangeSensor>();
    ClassDB::register_class<UtilityAIAngleVector2Sensor>();
    ClassDB::register_class<UtilityAIAngleVector3Sensor>();
    ClassDB::register_class<UtilityAIDistanceVector2Sensor>();
    ClassDB::register_class<UtilityAIDistanceVector3Sensor>();
    ClassDB::register_class<UtilityAIArea2DVisibilitySensor>();
    ClassDB::register_class<UtilityAIArea3DVisibilitySensor>();    

    // Special considerations.
    ClassDB::register_class<UtilityAIBooleanConsideration>();
    ClassDB::register_class<UtilityAICustomPropertyConsideration>();

    // Resource-based considerations.
    ClassDB::register_class<UtilityAIConsiderationResources>(true);
    ClassDB::register_class<UtilityAIConsiderationResource>();
    ClassDB::register_class<UtilityAIConsiderationGroupResource>();

    // Behaviour tree.
    ClassDB::register_class<UtilityAIBehaviourTreeNodes>(true);
    ClassDB::register_class<UtilityAIBTRoot>();

    ClassDB::register_class<UtilityAIBTCompositeNodes>(true);
    ClassDB::register_class<UtilityAIBTSequence>();
    ClassDB::register_class<UtilityAIBTSelector>();
    ClassDB::register_class<UtilityAIBTParallel>();
    ClassDB::register_class<UtilityAIBTRandomSequence>();
    ClassDB::register_class<UtilityAIBTRandomSelector>();
    ClassDB::register_class<UtilityAIBTScoreBasedPicker>();

    ClassDB::register_class<UtilityAIBTDecoratorNodes>(true);
    ClassDB::register_class<UtilityAIBTRepeater>();
    ClassDB::register_class<UtilityAIBTRepeatUntil>();
    ClassDB::register_class<UtilityAIBTLimiter>();
    ClassDB::register_class<UtilityAIBTFixedResult>();
    ClassDB::register_class<UtilityAIBTInverter>();
    ClassDB::register_class<UtilityAIBTPassThrough>();
    ClassDB::register_class<UtilityAIBTCooldownTicks>();
    ClassDB::register_class<UtilityAIBTCooldownMsec>();
    ClassDB::register_class<UtilityAIBTCooldownUsec>(); 

    ClassDB::register_class<UtilityAIBTTaskNodes>(true);
    ClassDB::register_class<UtilityAIBTLeaf>();
    ClassDB::register_class<UtilityAIBTRunNQSQuery>();
    ClassDB::register_class<UtilityAIBTPassBy>();
    ClassDB::register_class<UtilityAIBTNodeReference>();

    // State tree.
    ClassDB::register_class<UtilityAIStateTreeNodes>(true);
    ClassDB::register_class<UtilityAISTRoot>();
    ClassDB::register_class<UtilityAISTSelector>();

    // Node Query System.
    ClassDB::register_class<UtilityAINodeQuerySystem>();

    ClassDB::register_class<UtilityAINQSSearchSpaces>(true);
    ClassDB::register_class<UtilityAINodeGroupSearchSpace>();
    ClassDB::register_class<UtilityAINodeChildrenSearchSpace>();

    ClassDB::register_class<UtilityAIArea3DSearchSpace>();
    ClassDB::register_class<UtilityAIArea2DSearchSpace>();

    //ClassDB::register_class<UtilityAINavigation3DPointGridSearchSpaces>(true);
    //ClassDB::register_class<UtilityAINavigation3DRectangularPointGridSearchSpace>();

    ClassDB::register_class<UtilityAINQSSearchCriteria>(true);
    ClassDB::register_class<UtilityAICustomSearchCriterion>();
    ClassDB::register_class<UtilityAIMetadataSearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDistanceToNode3DSearchCriterion>();
    ClassDB::register_class<UtilityAIDistanceToNode2DSearchCriterion>();

    ClassDB::register_class<UtilityAIAngleToVector3XZSearchCriterion>();
    ClassDB::register_class<UtilityAIAngleToVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIAngleToVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDotProductVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDotProductVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIDotProductToPositionVector3SearchCriterion>();
    ClassDB::register_class<UtilityAIDotProductToPositionVector2SearchCriterion>();

    ClassDB::register_class<UtilityAIPerformanceMonitorSingleton>();

    // Add singletons.
    gpNodeQuerySystem = memnew(UtilityAINodeQuerySystem);
    Engine::get_singleton()->register_singleton("NodeQuerySystem", gpNodeQuerySystem);

    gdAIPerformanceMonitor = memnew(UtilityAIPerformanceMonitorSingleton);
    Engine::get_singleton()->register_singleton("AIPerformanceMonitor", gdAIPerformanceMonitor);
}

void uninitialize_utility_ai_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    Engine::get_singleton()->unregister_singleton("NodeQuerySystem");
    memdelete(gpNodeQuerySystem);
    Engine::get_singleton()->unregister_singleton("AIPerformanceMonitor");
    memdelete(gdAIPerformanceMonitor);
}

extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT utility_ai_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_utility_ai_module);
    init_obj.register_terminator(uninitialize_utility_ai_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
