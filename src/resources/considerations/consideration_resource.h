#ifndef UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED
#define UTILITY_AI_CONSIDERATION_RESOURCE_H_INCLUDED

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/curve.hpp>
#include "consideration_resources.h"
#include "../../agent_behaviours/sensors.h"

namespace godot {

class UtilityAIConsiderationResource : public UtilityAIConsiderationResources {
    GDCLASS(UtilityAIConsiderationResource, UtilityAIConsiderationResources )

private:
    bool                _is_active;
    Ref<Curve>          _activation_curve;
    UtilityAISensors*   _input_sensor;
    NodePath            _input_sensor_nodepath; // Node pointer doesn't seem to get saved for a resource, so a node path needs to be used.
protected:
    static void _bind_methods();

public:
    UtilityAIConsiderationResource();
    ~UtilityAIConsiderationResource();
    
    
    // Getters and setters for attributes.
   
    void set_input_sensor_nodepath( NodePath input_sensor_nodepath );
    NodePath get_input_sensor_nodepath() const;


    void set_activation_curve( Ref<Curve> activation_curve );
    Ref<Curve> get_activation_curve() const;

    
    // Handling methods.
    
    virtual double evaluate(bool& has_vetoed, Node* parent_node) override;
    virtual double sample_activation_curve( double input_value ) const;


};

}


#endif 

