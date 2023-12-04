#ifndef UtilityAIBTPassBy_H_INCLUDED
#define UtilityAIBTPassBy_H_INCLUDED 

#include "UtilityAIBehaviourTreeNodes.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/method_ptrcall.hpp>



namespace godot {

class UtilityAIBTPassBy : public UtilityAIBehaviourTreeNodes {
    GDCLASS(UtilityAIBTPassBy, UtilityAIBehaviourTreeNodes)

private:
    //int _tick_result;
    
protected:
    static void _bind_methods();

public:
    UtilityAIBTPassBy();
    ~UtilityAIBTPassBy();
    
    
    // Getters and setters for attributes.
        
    //void set_tick_result( int tick_result );
    //int  get_tick_result() const;

    // Handling functions.

    virtual int tick(Variant user_data, double delta) override;

    // Godot virtuals.

};

}


#endif 