#ifndef UtilityAINodeChildrenSearchSpace_H_INCLUDED
#define UtilityAINodeChildrenSearchSpace_H_INCLUDED 

#include "UtilityAINQSSearchSpaces.h"
#include <godot_cpp/classes/node.hpp>

namespace godot {

class UtilityAINodeChildrenSearchSpace : public UtilityAINQSSearchSpaces {
    GDCLASS(UtilityAINodeChildrenSearchSpace, UtilityAINQSSearchSpaces)

private:
    NodePath _parent_node_path;
    Node*    _parent_node;
protected:
    static void _bind_methods();

    
public:
    UtilityAINodeChildrenSearchSpace();
    ~UtilityAINodeChildrenSearchSpace();
    
    
    // Getters and setters for attributes.
    void set_parent_node_path( NodePath parent_node_path );
    NodePath get_parent_node_path() const;

    virtual TypedArray<Node> get_searchspace_nodes() const override;

    // Godot virtuals.
    void _ready();
};

}


#endif 
