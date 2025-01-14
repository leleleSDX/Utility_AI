#ifndef UtilityAISTRoot_H_INCLUDED
#define UtilityAISTRoot_H_INCLUDED 

#include "nodes.h"
#include <godot_cpp/classes/node.hpp>



namespace godot {

class UtilityAISTRoot : public UtilityAIStateTreeNodes {
    GDCLASS(UtilityAISTRoot, UtilityAIStateTreeNodes)

private:
    uint64_t                 _total_tick_usec;    
    //UtilityAIStateTreeNodes* _active_state;
    TypedArray<UtilityAIStateTreeNodes> _active_states;
protected:
    static void _bind_methods();

public:
    UtilityAISTRoot();
    ~UtilityAISTRoot();
    
    
    // Getters and setters for attributes.
    
    uint64_t get_total_tick_usec() const;
    void set_total_tick_usec(uint64_t total_tick_usec );

    //UtilityAIStateTreeNodes* get_active_state() const;
    //_active_states

    // Handling functions.
    //virtual TypedArray<UtilityAIStateTreeNodes> _tick( Variant user_data, double delta) override;
    void tick(Variant user_data, double delta);

    // Godot virtuals.
    void _ready();
};

}


#endif 
