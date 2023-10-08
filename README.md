# Utility_AI
A Utility AI implementation for the Godot Engine using gdextension.

## Node listing

* *UtilityAIAgent* This is the main node that is used manage the UtilityAI. It represents an AI entity.
* *UtilityAIBehaviour* The various things the AI agent can do are called _behaviours_. Each Behaviour consists of _considerations_ and _actions_.
* *UtilityAIConsideration* The AI agent does it's reasoning on what behaviour to use by going through its considerations and producing a score for each behaviour. This node is used to represent a single thing the AI Agent should consider about a behaviour. A consideration uses a _sensor_ for input data.
* *UtilityAIConsiderationGroup* Several considerations can be grouped to create more complex or high-level logic.
* *UtilityAISensor* The sensor node is used to update input data to the AI Agent's considerations.
* *UtilityAISensorGroup* Several sensors can be grouped for more high-level sensor input to the considerations.
* *UtilityAIAction* A behaviour, if selected, will run any actions attached to it.
* *UtilityAIActionGroup* Groups can help organize how a behaviour will run the actions attached to it.

## How to use the nodes

Start by adding a UtilityAIAgent to your scene. Next you can add the Sensors as the childs of the AI agent node. And then add the Behaviours. It is expected that any sensors are before behaviours. 

Then add considerations to the Behaviours you have added. And finally the Actions. 

In your code update the sensor's `sensor_value` with a floating point value between 0.0 and 1.0. Then run the UtilityAIAgent's `evaluate_options` method and `update_current_behaviour` method to get an `action` to execute. You can then get the action by using the `get_current_action` method.
Do what ever you need to do for the action selected and once done, mark it as finished using the `set_is_finished(true)` method. This will allow the current behaviour to step to the next action during the `update_current_behaviour` call.

## Nodes in-depth 

### UtilityAIAgent 

This is the main node that is used to manage the UtilityAI. A UtilityAIAgent node represents an AI entity that can reason based in `sensor` input and then choose `behaviours` to react to the sensor input.

#### Properties

|Type|Name|Description|
|--|--|--|
|int|num_behaviours_to_select|Pick a behaviour out of top `num_behaviours_to_select` behaviours found after reasoning.|
|float|thinking_delay_in_seconds|Delay time forced between calls to the method `evaluate_options`.|
|--|--|--|

#### Methods 

|Return value|Name|Description|
|--|--|--|
|void|evaluate_options(float delta)|Gathers input from sensors and evaluates all the available behaviours by calculating a score for each of them and then choosing a random behaviour from the top `num_behaviours_to_select` behaviours.|
|void|update_current_behaviour()|Updates the currently selected behaviour and if the current `action` has been marked as finished, returns the next action.|
|--|--|--|

### UtilityAISensor and UtilityAISensorGroup

These two node types should be added as child nodes of the `UtilityAIAgent` node. They are used to give input data to `consideration` nodes. A `sensor` is used by one or more `consideration` nodes. A `sensor group` is a node that can be used to aggregate input from several sensors (or sensor groups) for a higher-level input to the consideration nodes. 

Why use sensors in the first place? Consider the situation where you have several behaviours that use the "IsPlayerClose" consideration and maybe different variations, such as "IsPlayerAboutMidDistanceFromMe" or what ever. With the sensor nodes you can calculate the distance once and set it to a sensor, and then all the various considerations can make use of the distance in a relatively easy way and the distance only needs to be calculated once.

#### Properties

The `UtilityAISensor` has the following properties:

|Type|Name|Description|
|--|--|--|
|float|sensor_value|A floating point value in the range of 0..1.|
|--|--|--|

The `UtilityAISensorGroup` has the following properties:

|Type|Name|Description|
|--|--|--|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5,OneMinusScore:6.|
|--|--|--|


#### Methods 

None.


### UtilityAIBehaviour

This node type should be added as child node of the `UtilityAIAgent` node, preferably after any `sensor` and `sensor group` nodes. There can be several behaviour nodes as childs of the `UtilityAIAgent` node.

As you may have guessed from the name, the purpose of the behaviour nodes is to define what the `AI agent` will do based on different inputs given using the `sensor` nodes. To accomplish this each behaviour node must have one or more `consideration` or `consideration group` nodes as its childs, and also one or more `action` or `action group` nodes. 

The behaviour node will use the  `consideration` nodes that are its childs to determine a `score` for itself. When the behaviour is chosen by the `AI agent` as the one to execute, the `action` nodes are stepped through.

#### Properties

The `UtilityAIBehaviour` has the following properties:

|Type|Name|Description|
|--|--|--|
|bool|can_be_interrupted|A boolean value to determine if the behaviour can be interrupted or not. If a behaviour cannot be interrupted, the `evaluate_options` method of the `UtilityAIAgent` will not execute until the behaviour has completed all its actions.|
|float|score|The score for the behaviour after the behaviour has evaluated its considerations.|
|--|--|--|

#### Methods 

None.

### UtilityAIConsideration and UtilityAIConsiderationGroup

These two node types should be added as child nodes of the `UtilityAIBehaviour` node. They are used when a `behaviour` is being scored by the `AI agent`. 

Each consideration node can contain an `activation curve` that can be defined in the node properties. If no curve has been set, the consideration nodes input value will be used as the consideration result as-is.

If a `sensor` or a `sensor group` is used as the input value for a consideration the input for the consideration will be the `sensor_value` property of the sensor node. Otherwise the value of the consideration's `activation_input_value` property will be used.

Consideration groups can be used to aggregate the input from several considerations or consideration groups to create more complex consideration logic. 

#### Properties

The `UtilityAIConsideration` has the following properties:

|Type|Name|Description|
|--|--|--|
|float|activation_input_value|A floating point value in the range of 0..1.|
|NodePath|input_sensor_node_path|A nodepath to a sensor or a sensor group node that will set the `activation_input_value`.|
|Curve|activation_curve|A godot curve property that defines how the `activation_input_value` will be translated to a `score`.|
|float|score|The resulting score for the consideration after evaluation.|
|--|--|--|

The `UtilityAIConsiderationGroup` has the following properties:

|Type|Name|Description|
|--|--|--|
|float|evaluation_method|A choice of how the sensors and sensor groups that are childs of the node are aggregated. Can be one of the following: Sum:0,Min:1,Max:2,Mean:3,Multiply:4,FirstNonZero:5,OneMinusScore:6.|
|float|score|The resulting score for the consideration group after evaluation.|
|--|--|--|


#### Methods 

None.

### UtilityAIAction and UtilityAIActionGroup

These two node types should be added as child nodes of the `UtilityAIBehaviour` node. They are used when a `behaviour` is being executed by the `AI agent`. 

Action groups can be used create sequences of actions, or to pick one random action from several choices. This allows for more complex actions to be performed by a behaviour.

*NOTE!* When the `AI agent` has chosen a behaviour, the action step function is called to find the first action to execute. The action that is being executed must be set as finished for the `AI agent` step function to be able to go to the next action. The action logic itself can be implemented anywhere else.

#### Properties

The `UtilityAIAction` has the following properties:

|Type|Name|Description|
|--|--|--|
|int|action_id|A user-definable numeric ID for the action. Provided as an alternative to using action node names for identifying which is the current action the `AI agent` is currently executing.|
|bool|is_finished|Use this property only to let the `AI agent` know when the chosen action is finished. The stepper function will immediately set it back to false once it has moved on to the next action.|
|--|--|--|

The `UtilityAIActionGroup` has the following properties:

|Type|Name|Description|
|--|--|--|
|float|execution_rule|A choice of how the actions that are child nodes are executed: Sequence:0,PickOneAtRandom:1. The Sequence choice will execute the actions from top to bottom and the Pick One At Random does what it says it will.|
|bool|is_finished|Set internally by the stepper, visible only for debugging purposes.|
|--|--|--|


#### Methods 

None.


